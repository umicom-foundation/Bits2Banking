/*-----------------------------------------------------------------------------
 * Umicom Bits2Banking
 * File: labs/native/framework-toolchain-selection/main.c
 *
 * PURPOSE:
 *   Explore shared toolchain selection, environment ownership and compiler intent through an installed SDK.
 *
 * AUTHOR AND ORGANISATION:
 * Sammy Hegab
 * Umicom Foundation
 *
 * LICENCE:
 * MIT
 *---------------------------------------------------------------------------*/


#include "umicom/compiler/compiler.h"
#include "umicom/toolchain/catalogue.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define REQUIRE(c) do { if (!(c)) { \
    (void)fprintf(stderr,"toolchain lab: %s:%d: %s\n",__FILE__,__LINE__,#c); return 1; \
} } while (0)

/* Large inline values are serial lab owners, not automatic thread-stack objects.
 * Production applications should choose per-instance ownership and synchronization. */
static UmiToolchainProfile profile, selected, saved_profile;
static UmiEnvironmentPlan environment, saved_environment;
static UmiCompilerRequest request;
static UmiCompilerPlan plan, saved_plan;

static void MakeProfile(const char *id,const char *driver)
{
    umi_toolchain_profile_init(&profile);
    (void)snprintf(profile.profile_id,sizeof(profile.profile_id),"%s",id);
    (void)snprintf(profile.display_name,sizeof(profile.display_name),"%s",id);
    (void)strcpy(profile.target_triple,"x86_64-unknown-linux-gnu");
    profile.selected_c_compiler = UMI_TOOL_GCC;
    profile.tools[UMI_TOOL_GCC].state = UMI_TOOL_VALIDATED;
    (void)snprintf(profile.tools[UMI_TOOL_GCC].path,sizeof(profile.tools[UMI_TOOL_GCC].path),"%s",driver);
    /* Empty bin_directory avoids dependence on the host's inherited PATH.
     * VALIDATED here is synthetic fixture metadata, not a real compiler probe. */
}

static int Storage(void)
{
    MakeProfile("fixture","unexecuted-gcc");
    REQUIRE(umi_toolchain_profile_storage_valid(&profile));
    profile.tools[UMI_TOOL_GCC].state = UMI_TOOL_FAILED;
    REQUIRE(umi_toolchain_profile_storage_valid(&profile));
    static UmiCompilerProfile converted, previous;
    (void)memset(&converted,0x5a,sizeof(converted));
    (void)memcpy(&previous,&converted,sizeof(previous));
    REQUIRE(umi_compiler_profile_from_toolchain(&profile,"selected",&converted) == UMI_STATUS_UNAVAILABLE);
    REQUIRE(memcmp(&previous,&converted,sizeof(converted)) == 0);
    (void)memset(profile.display_name,'x',sizeof(profile.display_name));
    REQUIRE(!umi_toolchain_profile_storage_valid(&profile));
    (void)puts("storage: failed metadata is representable; unusable conversion preserves output");
    return 0;
}

static int Selection(UmiToolchainCatalogue *catalogue)
{
    MakeProfile("first","unexecuted-first-gcc");
    REQUIRE(umi_toolchain_catalogue_upsert_profile(catalogue,&profile) == UMI_STATUS_OK);
    MakeProfile("refused","gcc\ninvalid-environment");
    REQUIRE(umi_toolchain_catalogue_upsert_profile(catalogue,&profile) == UMI_STATUS_OK);
    REQUIRE(umi_toolchain_catalogue_select_with_environment(catalogue,"first",&selected,&environment) == UMI_STATUS_OK);
    const char *cc = umi_environment_plan_find(&environment,"CC");
    REQUIRE(cc != NULL && strcmp(cc,"unexecuted-first-gcc") == 0);
    for (size_t i = 0U; i < environment.count; ++i) {
        REQUIRE(environment.process_entries[i].name == environment.entries[i].name);
        REQUIRE(environment.process_entries[i].value == environment.entries[i].value);
    }
    (void)memcpy(&saved_profile,&selected,sizeof(selected));
    (void)memcpy(&saved_environment,&environment,sizeof(environment));
    UmiToolchainCatalogueSnapshot before, after;
    REQUIRE(umi_toolchain_catalogue_snapshot(catalogue,&before) == UMI_STATUS_OK);
    REQUIRE(umi_toolchain_catalogue_select_with_environment(catalogue,"refused",&selected,&environment) == UMI_STATUS_INVALID_ARGUMENT);
    REQUIRE(memcmp(&saved_profile,&selected,sizeof(selected)) == 0);
    REQUIRE(memcmp(&saved_environment,&environment,sizeof(environment)) == 0);
    REQUIRE(umi_toolchain_catalogue_snapshot(catalogue,&after) == UMI_STATUS_OK);
    REQUIRE(before.revision == after.revision && strcmp(after.selected_profile_id,"first") == 0);
    (void)puts("selection: refused environment preserves selection and both owners");
    (void)puts("ownership: process entries refer to receiving environment storage");
    return 0;
}

static int Compiler(UmiCompilerCentre *centre)
{
    MakeProfile("selected","unexecuted-first-gcc");
    REQUIRE(umi_compiler_centre_sync_toolchain(centre,&profile,"selected") == UMI_STATUS_OK);
    MakeProfile("selected","unexecuted-second-gcc");
    REQUIRE(umi_compiler_centre_sync_toolchain(centre,&profile,"selected") == UMI_STATUS_OK);
    REQUIRE(centre->providers.count == 1U && centre->profile_count == 1U);
    const UmiCompilerProfile *active = umi_compiler_centre_active_profile(centre);
    REQUIRE(active != NULL && strcmp(active->linker.driver,"unexecuted-second-gcc") == 0);
    const UmiCompilerProvider *provider = umi_compiler_registry_find(&centre->providers,"gcc");
    REQUIRE(provider != NULL && strcmp(provider->descriptor.executable,"unexecuted-second-gcc") == 0);
    (void)puts("compiler: repeated selection replaces driver and profile together");
    return 0;
}

static int PositionIndependent(void)
{
    UmiCompilerProvider provider = umi_compiler_gcc_provider("unexecuted-gcc","x86_64-unknown-linux-gnu");
    REQUIRE(umi_compiler_request_init(&request,"project","unit",UMI_COMPILER_LANGUAGE_C,
                                     "source.c","object.o") == UMI_STATUS_OK);
    request.position_independent = true;
    REQUIRE(umi_compiler_provider_plan(&provider,&request,&plan) == UMI_STATUS_OK);
    size_t found = 0U;
    for (size_t i = 0U; i < plan.argument_count; ++i)
        if (strcmp(plan.arguments[i],"-fPIC") == 0) ++found;
    REQUIRE(found == 1U);
    (void)memcpy(&saved_plan,&plan,sizeof(plan));
    request.action = UMI_COMPILER_ACTION_CHECK;
    REQUIRE(umi_compiler_provider_plan(&provider,&request,&plan) == UMI_STATUS_NOT_IMPLEMENTED);
    REQUIRE(memcmp(&saved_plan,&plan,sizeof(plan)) == 0);
    (void)puts("pic: explicit compile intent maps to -fPIC; unmapped check preserves plan");
    return 0;
}

int main(int argc,char **argv)
{
    if (argc != 2) { (void)fputs("Usage: btb-framework-toolchain-selection storage|selection|compiler|pic\n",stderr); return 2; }
    if (strcmp(argv[1],"storage") == 0) return Storage();
    if (strcmp(argv[1],"pic") == 0) return PositionIndependent();
    if (strcmp(argv[1],"selection") == 0) {
        UmiToolchainCatalogue *catalogue = NULL;
        REQUIRE(umi_toolchain_catalogue_create(&catalogue) == UMI_STATUS_OK);
        int result = Selection(catalogue);
        umi_toolchain_catalogue_destroy(catalogue);
        return result;
    }
    if (strcmp(argv[1],"compiler") == 0) {
        UmiCompilerCentre *centre = malloc(sizeof(*centre));
        REQUIRE(centre != NULL);
        umi_compiler_centre_init(centre);
        int result = Compiler(centre);
        free(centre);
        return result;
    }
    (void)fputs("Unknown scenario\n",stderr);
    return 2;
}
