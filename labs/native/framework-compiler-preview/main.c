/*-----------------------------------------------------------------------------
 * Umicom Bits2Banking
 * File: labs/native/framework-compiler-preview/main.c
 *
 * PURPOSE:
 *   Teach compiler action previews and complete JSON presentation through the installed Framework SDK.
 *
 * AUTHOR AND ORGANISATION:
 * Sammy Hegab
 * Umicom Foundation
 *
 * LICENCE:
 * MIT
 *---------------------------------------------------------------------------*/


#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include "umicom/compiler/compiler.h"

/* Serial fixtures keep large inline owners away from a small thread stack. */
static UmiCompilerRequest request;
static UmiCompilerPlan plan, previous;
static char json[UMI_COMPILER_PLAN_JSON_CAPACITY];
static char saved_json[UMI_COMPILER_PLAN_JSON_CAPACITY];

static bool Require(bool condition,const char *message)
{
    if (!condition) (void)fprintf(stderr,"Observation failed: %s\n",message);
    return condition;
}

static bool Prepare(void)
{
    UmiCompilerProvider provider = umi_compiler_gcc_provider("unexecuted-driver",NULL);
    if (!Require(umi_compiler_request_init(&request,"lesson","unit",UMI_COMPILER_LANGUAGE_C,
            "source with spaces.c","not-created.o") == UMI_STATUS_OK,"request construction")) return false;
    request.action = UMI_COMPILER_ACTION_CHECK;
    (void)strcpy(request.standard,"c17");
    (void)strcpy(request.working_directory,"C:\\lesson workspace");
    return Require(umi_compiler_provider_plan(&provider,&request,&plan) == UMI_STATUS_OK,"plan construction");
}

static bool HasArgument(const char *value)
{
    for (size_t i = 0U; i < plan.argument_count; ++i)
        if (strcmp(plan.arguments[i],value) == 0) return true;
    return false;
}

static bool Actions(void)
{
    if (!Prepare()) return false;
    UmiCompilerProvider provider = umi_compiler_gcc_provider("unexecuted-driver",NULL);
    if (!Require(umi_compiler_provider_can_plan_action(&provider,request.language,request.action),
                 "CHECK mapping") ||
        !Require(HasArgument("-fsyntax-only") && !HasArgument("-c") && !HasArgument("-o"),
                 "syntax-only arguments")) return false;
    request.action = UMI_COMPILER_ACTION_COMPILE;
    if (!Require(umi_compiler_provider_plan(&provider,&request,&plan) == UMI_STATUS_OK,"compile mapping") ||
        !Require(HasArgument("-c") && HasArgument("-o") && !HasArgument("-fsyntax-only"),
                 "object arguments")) return false;
    (void)memcpy(&previous,&plan,sizeof(plan));
    request.action = UMI_COMPILER_ACTION_ARCHIVE;
    if (!Require(umi_compiler_provider_plan(&provider,&request,&plan) == UMI_STATUS_NOT_IMPLEMENTED,
                 "unmapped archive") ||
        !Require(memcmp(&plan,&previous,sizeof(plan)) == 0,"prior plan survives archive refusal")) return false;
    puts("Check: syntax-only arguments\nCompile: object arguments\nArchive: refused; previous plan retained");
    return true;
}

static bool Identity(void)
{
    char driver[UMI_COMPILER_PATH_CAPACITY + 1U];
    (void)memset(driver,'x',sizeof(driver));
    driver[sizeof(driver)-1U] = '\0';
    UmiCompilerProvider provider = umi_compiler_gcc_provider(driver,NULL);
    if (!Require(provider.revision == 0U && !provider.descriptor.available,"overlong driver refused"))
        return false;
    provider = umi_compiler_gcc_provider("not-installed-anywhere",NULL);
    if (!Require(provider.revision == 1U && provider.descriptor.available,"declared driver identity") ||
        !Require(strcmp(provider.descriptor.executable,"not-installed-anywhere") == 0,"complete identity"))
        return false;
    puts("Overlong driver: invalid provider\nNonempty driver: declared, not verified");
    return true;
}

static bool Json(void)
{
    if (!Prepare()) return false;
    if (!Require(umi_compiler_plan_add_argument(&plan,"NAME=\"quoted\"") == UMI_STATUS_OK,
                 "quoted argument") ||
        !Require(umi_compiler_plan_json(&plan,json,sizeof(json)) == UMI_STATUS_OK,"complete JSON"))
        return false;
    if (!Require(strstr(json,"\"executed\":false") != NULL,"no execution evidence") ||
        !Require(strstr(json,"\"toolchain_verified\":false") != NULL,"no toolchain evidence") ||
        !Require(strstr(json,"NAME=\\\"quoted\\\"") != NULL,"escaped quotes") ||
        !Require(strstr(json,"C:\\\\lesson workspace") != NULL,"escaped path") ||
        !Require(strstr(json,"\"source with spaces.c\"") != NULL,"one source argument")) return false;
    puts("JSON: ordered argument strings\nEscaping: quotes and backslashes preserved\nExecution evidence: false");
    return true;
}

static bool Refusal(void)
{
    if (!Prepare()) return false;
    (void)memset(json,0x5a,sizeof(json));
    (void)memcpy(saved_json,json,sizeof(json));
    if (!Require(umi_compiler_plan_json(&plan,json,8U) == UMI_STATUS_CAPACITY_EXCEEDED,
                 "short output buffer") ||
        !Require(memcmp(json,saved_json,sizeof(json)) == 0,"complete output preservation")) return false;
    plan.arguments[0][0] = (char)0xff;
    plan.arguments[0][1] = '\0';
    if (!Require(umi_compiler_plan_json(&plan,json,sizeof(json)) == UMI_STATUS_INVALID_ARGUMENT,
                 "invalid UTF-8") ||
        !Require(memcmp(json,saved_json,sizeof(json)) == 0,"failed text output preservation")) return false;
    puts("Short buffer: previous bytes retained\nInvalid UTF-8: previous bytes retained");
    return true;
}

int main(int argc,char **argv)
{
    if (argc != 2) { (void)fputs("Use actions, identity, json or refusal.\n",stderr); return 2; }
    bool ok = false;
    if (strcmp(argv[1],"actions") == 0) ok = Actions();
    else if (strcmp(argv[1],"identity") == 0) ok = Identity();
    else if (strcmp(argv[1],"json") == 0) ok = Json();
    else if (strcmp(argv[1],"refusal") == 0) ok = Refusal();
    else { (void)fputs("Unknown scenario.\n",stderr); return 2; }
    if (!ok) return 1;
    puts("Preview metadata only; no compiler process was started.");
    return 0;
}
