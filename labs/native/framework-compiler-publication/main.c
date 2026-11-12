/*-----------------------------------------------------------------------------
 * Umicom Bits2Banking
 * File: labs/native/framework-compiler-publication/main.c
 *
 * PURPOSE:
 *   Demonstrate compiler metadata identity, coherent publication and explicit unsupported policy intent.
 *
 * AUTHOR AND ORGANISATION:
 * Sammy Hegab
 * Umicom Foundation
 *
 * LICENCE:
 * MIT
 *---------------------------------------------------------------------------*/


#include "umicom/compiler/compiler.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define REQUIRE(condition) do { if (!(condition)) { fprintf(stderr,"observation failed at line %d\n",__LINE__); return false; } } while (0)

static bool Keys(void)
{
    static UmiCompilerRequest request, changed;
    REQUIRE(umi_compiler_request_init(&request,"project","main",UMI_COMPILER_LANGUAGE_C,"main.c","main.o") == UMI_STATUS_OK);
    (void)strcpy(request.working_directory,"project-a");
    uint64_t original = umi_compiler_request_hash(&request);
    REQUIRE(original != 0U);
    changed = request; (void)strcpy(changed.working_directory,"project-b");
    REQUIRE(umi_compiler_request_hash(&changed) != original);
    changed = request; changed.debug_information = true;
    REQUIRE(umi_compiler_request_hash(&changed) != original);
    changed = request;
    REQUIRE(umi_compiler_request_add_include(&changed,"shared") == UMI_STATUS_OK);
    uint64_t include_key = umi_compiler_request_hash(&changed);
    changed = request;
    REQUIRE(umi_compiler_request_add_definition(&changed,"shared") == UMI_STATUS_OK);
    REQUIRE(umi_compiler_request_hash(&changed) != include_key);
    changed = request; changed.option_count = SIZE_MAX;
    REQUIRE(umi_compiler_request_hash(&changed) == 0U);
    puts("Metadata: directory, flags and collection boundaries contribute");
    puts("Malformed request: no key");
    return true;
}
static bool Prepare(UmiCompilerCentre *centre)
{
    static UmiCompilerProfile profile;
    static UmiCompilerProjectManifest manifest;
    UmiCompilerUnitManifest unit = {0};
    UmiCompilerTarget target;
    umi_compiler_centre_init(centre);
    UmiCompilerProvider provider = umi_compiler_gcc_provider("unverified-driver","x86_64-unknown-linux-gnu");
    REQUIRE(umi_compiler_registry_register(&centre->providers,&provider) == UMI_STATUS_OK);
    REQUIRE(umi_compiler_target_parse("x86_64-unknown-linux-gnu",&target) == UMI_STATUS_OK);
    REQUIRE(umi_compiler_profile_init(&profile,"debug","Debug","gcc",UMI_COMPILER_LANGUAGE_C,&target) == UMI_STATUS_OK);
    REQUIRE(umi_compiler_centre_add_profile(centre,&profile) == UMI_STATUS_OK);
    REQUIRE(umi_compiler_manifest_init(&manifest,"project","Project",target.triple) == UMI_STATUS_OK);
    (void)strcpy(unit.unit_id,"main"); (void)strcpy(unit.source,"src/main.c"); (void)strcpy(unit.output,"build/main.o");
    unit.language = UMI_COMPILER_LANGUAGE_C;
    REQUIRE(umi_compiler_manifest_add_unit(&manifest,&unit) == UMI_STATUS_OK);
    REQUIRE(umi_compiler_centre_add_manifest(centre,&manifest) == UMI_STATUS_OK);
    return true;
}
static bool Transaction(UmiCompilerCentre *centre,UmiCompilerCentre *before)
{
    static UmiCompilerPlan plan, previous;
    REQUIRE(Prepare(centre));
    REQUIRE(umi_compiler_centre_plan_unit_in_directory(centre,"project","main","C:/projects/example",&plan) == UMI_STATUS_OK);
    REQUIRE(strcmp(plan.working_directory,"C:/projects/example") == 0);
    centre->compilation_database.revision = UINT64_MAX;
    (void)memcpy(before,centre,sizeof(*centre)); (void)memcpy(&previous,&plan,sizeof(plan));
    REQUIRE(umi_compiler_centre_plan_unit_in_directory(centre,"project","main","C:/projects/new",&plan) == UMI_STATUS_CAPACITY_EXCEEDED);
    REQUIRE(memcmp(centre,before,sizeof(*centre)) == 0);
    REQUIRE(memcmp(&plan,&previous,sizeof(plan)) == 0);
    puts("Refused database update: centre and returned plan retained");
    return true;
}
static bool HasArgument(const UmiCompilerPlan *plan,const char *value)
{
    for (size_t index = 0U; index < plan->argument_count; ++index)
        if (strcmp(plan->arguments[index],value) == 0) return true;
    return false;
}
static bool Refresh(UmiCompilerCentre *centre)
{
    static UmiCompilerPlan plan;
    REQUIRE(Prepare(centre));
    REQUIRE(umi_compiler_centre_plan_unit_in_directory(centre,"project","main","C:/projects/first",&plan) == UMI_STATUS_OK);
    const UmiPolyglotCompilationEntry *stored = &centre->compilation_database.items[0];
    REQUIRE(!HasArgument(&stored->plan,"-Werror"));
    centre->profiles[0].policy.warnings_as_errors = true;
    REQUIRE(umi_compiler_centre_plan_unit_in_directory(centre,"project","main","C:/projects/second",&plan) == UMI_STATUS_OK);
    REQUIRE(centre->compilation_database.count == 1U);
    REQUIRE(HasArgument(&stored->plan,"-Werror") && HasArgument(&plan,"-Werror"));
    REQUIRE(strcmp(stored->directory,"C:/projects/second") == 0);
    for (size_t index = 0U; index < plan.argument_count; ++index) {
        REQUIRE(plan.argument_view[index] == plan.arguments[index]);
        REQUIRE(stored->plan.argument_view[index] == stored->plan.arguments[index]);
    }
    REQUIRE(umi_polyglot_compilation_database_add(&centre->compilation_database,stored) == UMI_STATUS_ALREADY_EXISTS);
    puts("Repeated source: stored command refreshed without adding a row");
    puts("Argument views: each receiving owner retains its own strings");
    return true;
}
static bool Policy(void)
{
    static UmiCompilerPlan plan, previous;
    umi_compiler_plan_init(&plan); plan.language = UMI_COMPILER_LANGUAGE_C; plan.action = UMI_COMPILER_ACTION_COMPILE;
    UmiCompilerPolicy policy = umi_compiler_policy_debug(); policy.sanitizers = UMI_COMPILER_SANITIZER_ADDRESS;
    REQUIRE(umi_compiler_policy_append_arguments(&policy,UMI_COMPILER_FAMILY_MSVC,&plan) == UMI_STATUS_OK);
    REQUIRE(HasArgument(&plan,"/fsanitize=address") && !HasArgument(&plan,"-fsanitize=address"));
    (void)memcpy(&previous,&plan,sizeof(plan));
    policy.sanitizers = UMI_COMPILER_SANITIZER_UNDEFINED;
    REQUIRE(umi_compiler_policy_append_arguments(&policy,UMI_COMPILER_FAMILY_MSVC,&plan) == UMI_STATUS_NOT_IMPLEMENTED);
    REQUIRE(memcmp(&plan,&previous,sizeof(plan)) == 0);
    policy = umi_compiler_policy_release();
    REQUIRE(umi_compiler_policy_append_arguments(&policy,UMI_COMPILER_FAMILY_CLANG,&plan) == UMI_STATUS_NOT_IMPLEMENTED);
    REQUIRE(memcmp(&plan,&previous,sizeof(plan)) == 0);
    puts("Policy: explicit MSVC address-sanitizer spelling");
    puts("Unsupported sanitizer and reproducible intent: prior plan retained");
    return true;
}
int main(int argc,char **argv)
{
    if (argc != 2) { fputs("Use: keys, transaction, refresh or policy\n",stderr); return 2; }
    bool accepted = false;
    if (strcmp(argv[1],"keys") == 0) accepted = Keys();
    else if (strcmp(argv[1],"policy") == 0) accepted = Policy();
    else if (strcmp(argv[1],"transaction") == 0 || strcmp(argv[1],"refresh") == 0) {
        /* The centre contains large inline collections. Two owners are allocated
         * only for the transaction comparison, never on the process stack. */
        UmiCompilerCentre *centre = malloc(sizeof(*centre));
        UmiCompilerCentre *before = strcmp(argv[1],"transaction") == 0 ? malloc(sizeof(*before)) : NULL;
        if (centre == NULL || (strcmp(argv[1],"transaction") == 0 && before == NULL))
            fputs("Cannot allocate compiler observation storage\n",stderr);
        else accepted = before != NULL ? Transaction(centre,before) : Refresh(centre);
        free(before); free(centre);
    } else { fputs("Unknown scenario\n",stderr); return 2; }
    if (!accepted) return 1;
    puts("Metadata observations only; no compiler or application was launched.");
    return 0;
}
