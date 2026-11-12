/*-----------------------------------------------------------------------------
 * Umicom Bits2Banking
 * File: labs/native/framework-project-recipes/preview.c
 *
 * PURPOSE:
 *   Keep a reviewed plan intact across late recipe failure and consume shared branded starter recipes.
 *
 * AUTHOR AND ORGANISATION:
 * Sammy Hegab
 * Umicom Foundation
 *
 * LICENCE:
 * MIT
 *---------------------------------------------------------------------------*/


#include "lab.h"
#include "umicom/developer_project/templates/c23_gtk4.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define REQUIRE(condition) do { if (!(condition)) { \
    fprintf(stderr, "%s:%d: %s\n", __FILE__, __LINE__, #condition); goto failed; \
} } while (0)

int LabPreviewScenario(const char *name)
{
    /* A plan owns more than half a megabyte of bounded file text. Heap storage
     * makes that cost explicit instead of spending a GUI/worker thread stack. */
    UmiDeveloperProjectGenerationPlan *plan = calloc(1U, sizeof *plan);
    UmiDeveloperProjectGenerationPlan *before = malloc(sizeof *before);
    UmiDeveloperProjectVariableSet variables;
    UmiDeveloperProjectGenerationRequest request;
    UmiDeveloperProjectTemplate recipe = *LabRecipe();
    UmiDeveloperProjectTemplateFile files[2] = {recipe.files[0], recipe.files[1]};
    LabRequest(&request);
    REQUIRE(plan != NULL && before != NULL);
    REQUIRE(umi_developer_project_generation_request_variables(&request, &variables) == UMI_STATUS_OK);
    recipe.files = files;
    REQUIRE(umi_developer_project_generation_plan_build(&recipe, &variables,
        request.project_root, plan) == UMI_STATUS_OK);
    REQUIRE(plan->file_count == 2U && strcmp(plan->files[0].relative_path, "src/recipe_study.c") == 0);
    memcpy(before, plan, sizeof *before);
    if (strcmp(name, "preview") == 0) {
        for (size_t i = 0U; i < plan->file_count; ++i)
            printf("%s (%zu text bytes)\n", plan->files[i].relative_path, strlen(plan->files[i].content));
    } else if (strcmp(name, "late-failure") == 0 || strcmp(name, "duplicate") == 0) {
        UmiStatus expected;
        if (strcmp(name, "late-failure") == 0) {
            files[1].content_template = "{{UNSET_VARIABLE}}";
            expected = UMI_STATUS_NOT_FOUND;
        } else {
            /* Keep the initial same-spelling fixture for review; the active
             * path differs before rendering so final-plan duplicate admission
             * is exercised rather than only template admission. */
#if 0
            files[1].relative_path = "src/{{TARGET_NAME}}.c";
#else
            files[1].relative_path = "src/recipe_study.c";
#endif
            expected = UMI_STATUS_ALREADY_EXISTS;
        }
        REQUIRE(umi_developer_project_generation_plan_build(&recipe, &variables,
            "C:/learning/replacement", plan) == expected);
        REQUIRE(memcmp(plan, before, sizeof *plan) == 0);
        printf("Status %d; the previous plan is byte-for-byte unchanged.\n", (int)expected);
    } else if (strcmp(name, "aliased-root") == 0) {
        REQUIRE(umi_developer_project_generation_plan_build(&recipe, &variables,
            plan->project_root, plan) == UMI_STATUS_OK);
        REQUIRE(strcmp(plan->project_root, before->project_root) == 0);
    } else if (strcmp(name, "gtk-branding") == 0) {
        const UmiDeveloperProjectTemplate *gtk = umi_developer_project_template_c23_gtk4();
        REQUIRE(gtk != NULL);
        REQUIRE(umi_developer_project_generation_plan_build(gtk, &variables,
            request.project_root, plan) == UMI_STATUS_OK);
        int build_identity = 0, window_identity = 0;
        for (size_t i = 0U; i < plan->file_count; ++i) {
            if (strcmp(plan->files[i].relative_path, "CMakeLists.txt") == 0)
                build_identity = strstr(plan->files[i].content, "umicom_apply_application_branding(") != NULL;
            if (strcmp(plan->files[i].relative_path, "src/main.c") == 0)
                window_identity = strstr(plan->files[i].content, "umi_gtk4_ws_apply_window_identity(") != NULL;
        }
        REQUIRE(build_identity && window_identity);
        puts("Shared build and window identity calls are present; no window was launched.");
    } else { free(before); free(plan); return 2; }
    free(before);
    free(plan);
    return 0;
failed:
    free(before);
    free(plan);
    return 1;
}
