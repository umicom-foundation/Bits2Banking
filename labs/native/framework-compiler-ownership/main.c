/*-----------------------------------------------------------------------------
 * Umicom Bits2Banking
 * File: labs/native/framework-compiler-ownership/main.c
 *
 * PURPOSE:
 *   Demonstrate real installed Framework compiler ownership without invoking a toolchain.
 *
 * AUTHOR AND ORGANISATION:
 * Sammy Hegab
 * Umicom Foundation
 *
 * LICENCE:
 * MIT
 *---------------------------------------------------------------------------*/


#include "umicom/compiler/compiler.h"
#include <stdbool.h>
#include <stdio.h>
#include <string.h>

/* This serial teaching client keeps large inline records off the thread stack.
 * A concurrent application must give each operation its own serialized owner. */
static UmiCompilerRequest request, request_before;
static UmiCompilerPlan plan, plan_before, copied;
static UmiCompilerRegistry registry, registry_before;

static bool Require(bool condition,const char *message)
{
    if (!condition) (void)fprintf(stderr,"%s\n",message);
    return condition;
}

static bool TargetAlias(void)
{
    UmiCompilerTarget target, before;
    if (!Require(umi_compiler_target_parse("x86_64-unknown-linux-gnu",&target) == UMI_STATUS_OK,"Target initialization failed")) return false;
    if (!Require(umi_compiler_target_parse(target.triple,&target) == UMI_STATUS_OK,"Borrowed target initialization failed")) return false;
    (void)memcpy(&before,&target,sizeof(before));
    const UmiStatus status = umi_compiler_target_parse("unfinished",&target);
    if (!Require(status == UMI_STATUS_PARSE_ERROR && memcmp(&target,&before,sizeof(target)) == 0,"Rejected target changed the previous value")) return false;
    (void)printf("Target: %s\nRejected replacement: previous target retained\n",target.triple);
    return true;
}

static bool AbiAlias(void)
{
    UmiCompilerTarget target;
    UmiCompilerAbiProfile profile;
    if (!Require(umi_compiler_target_parse("x86_64-unknown-linux-gnu",&target) == UMI_STATUS_OK,"Target initialization failed")) return false;
    if (!Require(umi_compiler_abi_init(&profile,"client-abi",UMI_COMPILER_ABI_C,&target) == UMI_STATUS_OK,"ABI initialization failed")) return false;
    if (!Require(umi_compiler_abi_init(&profile,profile.abi_id,UMI_COMPILER_ABI_CPP,&profile.target) == UMI_STATUS_OK,"Borrowed ABI initialization failed")) return false;
    if (!Require(strcmp(profile.abi_id,"client-abi") == 0 && strcmp(profile.target.triple,target.triple) == 0 && profile.exceptions && profile.rtti && !profile.stable,"ABI defaults or borrowed inputs changed")) return false;
    (void)printf("ABI identifier: %s\nC++ metadata: exceptions and RTTI enabled\n",profile.abi_id);
    return true;
}

static bool CatalogueRefusal(void)
{
    const UmiCompilerProvider provider = umi_compiler_gcc_provider("gcc","x86_64-unknown-linux-gnu");
    umi_compiler_registry_init(&registry);
    if (!Require(umi_compiler_registry_register(&registry,&provider) == UMI_STATUS_OK,"Provider registration failed")) return false;
    /* Deliberately malformed fixture metadata; never repair a live owner by
     * clamping its count and pretending the producer is correct. */
    registry.count = UMI_COMPILER_MAX_PROVIDERS + 1U;
    (void)memcpy(&registry_before,&registry,sizeof(registry));
    if (!Require(!umi_compiler_registry_valid(&registry) &&
        umi_compiler_registry_find(&registry,"gcc") == NULL &&
        umi_compiler_registry_register(&registry,&provider) == UMI_STATUS_INVALID_STATE &&
        memcmp(&registry,&registry_before,sizeof(registry)) == 0,"Malformed catalogue was consumed or changed")) return false;
    (void)puts("Oversized catalogue: refused\nOwner bytes: retained");
    return true;
}

static bool RequestRefusal(void)
{
    if (!Require(umi_compiler_request_init(&request,"demo","main",UMI_COMPILER_LANGUAGE_C,"main.c","main.o") == UMI_STATUS_OK,"Request initialization failed")) return false;
    char oversized[UMI_COMPILER_TEXT_CAPACITY];
    (void)memset(oversized,'x',sizeof(oversized));
    (void)memcpy(&request_before,&request,sizeof(request));
    if (!Require(umi_compiler_request_add_option(&request,oversized) == UMI_STATUS_CAPACITY_EXCEEDED &&
        memcmp(&request,&request_before,sizeof(request)) == 0,"Rejected option changed request storage")) return false;
    if (!Require(umi_compiler_request_add_option(&request,"-O2") == UMI_STATUS_OK &&
        umi_compiler_request_add_option(&request,request.options[0]) == UMI_STATUS_OK &&
        request.option_count == 2U && strcmp(request.options[1],"-O2") == 0,"Borrowed option append failed")) return false;
    (void)puts("Oversized option: previous request retained\nBorrowed option: copied into slot 2");
    return true;
}

static bool LatePublication(void)
{
    const UmiCompilerProvider provider = umi_compiler_gcc_provider("gcc","x86_64-unknown-linux-gnu");
    if (!Require(umi_compiler_request_init(&request,"demo","main",UMI_COMPILER_LANGUAGE_C,"main.c","main.o") == UMI_STATUS_OK,"Request initialization failed")) return false;
    umi_compiler_plan_init(&plan);
    if (!Require(umi_compiler_plan_add_argument(&plan,"previous") == UMI_STATUS_OK,"Previous plan initialization failed")) return false;
    (void)memcpy(&plan_before,&plan,sizeof(plan));
    /* A bounded request path can still be too large for one plan argument. */
    (void)memset(request.source_path,'a',UMI_COMPILER_TEXT_CAPACITY);
    request.source_path[UMI_COMPILER_TEXT_CAPACITY] = '\0';
    if (!Require(umi_compiler_provider_plan(&provider,&request,&plan) == UMI_STATUS_CAPACITY_EXCEEDED &&
        memcmp(&plan,&plan_before,sizeof(plan)) == 0,"Late failure published a partial plan")) return false;
    (void)puts("Late argument failure: previous plan retained\nPrevious argument: previous");
    return true;
}

static bool BorrowedViews(void)
{
    const UmiCompilerProvider provider = umi_compiler_gcc_provider("gcc","x86_64-unknown-linux-gnu");
    if (!Require(umi_compiler_request_init(&request,"demo","main",UMI_COMPILER_LANGUAGE_C,"main.c","main.o") == UMI_STATUS_OK,"Request initialization failed")) return false;
    if (!Require(umi_compiler_provider_plan(&provider,&request,&plan) == UMI_STATUS_OK,"Plan construction failed")) return false;
    copied = plan;
    const char *const *view = umi_compiler_plan_arguments(&copied);
    if (!Require(view != NULL && copied.argument_count != 0U,"Argument view reconstruction failed")) return false;
    for (size_t index = 0U; index < copied.argument_count; ++index)
        if (!Require(view[index] == copied.arguments[index] && view[index] != plan.arguments[index] &&
            plan.argument_view[index] == plan.arguments[index],"Argument pointer belongs to another owner")) return false;
    (void)puts("Published view: receiving plan owns every argument\nCopied view: rebased into the copy");
    return true;
}

static bool RevisionBoundary(void)
{
    umi_compiler_plan_init(&plan);
    if (!Require(umi_compiler_plan_add_argument(&plan,"retained") == UMI_STATUS_OK,"Plan initialization failed")) return false;
    /* Isolated boundary injection for this lesson, never a production reset. */
    plan.revision = UINT64_MAX;
    (void)memcpy(&plan_before,&plan,sizeof(plan));
    if (!Require(umi_compiler_plan_add_argument(&plan,"new") == UMI_STATUS_CAPACITY_EXCEEDED &&
        memcmp(&plan,&plan_before,sizeof(plan)) == 0,"Revision exhaustion changed the plan")) return false;
    const char *const *view = umi_compiler_plan_arguments(&plan);
    if (!Require(view != NULL && strcmp(view[0],"retained") == 0 && plan.revision == UINT64_MAX,"Exhausted plan became unreadable")) return false;
    (void)puts("Revision exhausted: append refused\nReadable argument: retained");
    return true;
}

int main(int argc,char **argv)
{
    if (argc != 2) { (void)fprintf(stderr,"Choose target, abi, catalogue, request, publication, views or revision.\n"); return 2; }
    bool ok;
    if (strcmp(argv[1],"target") == 0) ok = TargetAlias();
    else if (strcmp(argv[1],"abi") == 0) ok = AbiAlias();
    else if (strcmp(argv[1],"catalogue") == 0) ok = CatalogueRefusal();
    else if (strcmp(argv[1],"request") == 0) ok = RequestRefusal();
    else if (strcmp(argv[1],"publication") == 0) ok = LatePublication();
    else if (strcmp(argv[1],"views") == 0) ok = BorrowedViews();
    else if (strcmp(argv[1],"revision") == 0) ok = RevisionBoundary();
    else { (void)fprintf(stderr,"Unknown scenario.\n"); return 2; }
    if (!ok) return 1;
    (void)puts("Compiler metadata only; no compiler process or application launch.");
    return 0;
}
