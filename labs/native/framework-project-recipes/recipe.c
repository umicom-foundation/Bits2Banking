/*-----------------------------------------------------------------------------
 * Umicom Bits2Banking
 * File: labs/native/framework-project-recipes/recipe.c
 *
 * PURPOSE:
 *   Provide borrowed recipe fixtures and explicit owned application identities for the course.
 *
 * AUTHOR AND ORGANISATION:
 * Sammy Hegab
 * Umicom Foundation
 *
 * LICENCE:
 * MIT
 *---------------------------------------------------------------------------*/


#include "lab.h"
#include <string.h>

/* These strings have static lifetime. The Framework borrows them during render;
 * it owns all rendered strings in the resulting plan. This fixture is teaching
 * data, not a replacement renderer or a complete distributable application. */
static const UmiDeveloperProjectTemplateFile files[] = {
    {"src/{{TARGET_NAME}}.c", "/* {{APPLICATION_NAME}} */\nint main(void) { return 0; }\n", 0, 0},
    {"README.md", "# {{APPLICATION_NAME}}\nApplication: {{APPLICATION_ID}}\n", 0, 0}
};
static const UmiDeveloperProjectTemplate recipe = {
    .structure_size = sizeof(UmiDeveloperProjectTemplate),
    .api_version = UMI_DEVELOPER_PROJECT_API_VERSION,
    .template_id = "learning.recipe.console",
    .title = "Umicom Recipe Study",
    .description = "A two-file memory-only project preview",
    .kind = UMI_DEVELOPER_PROJECT_EXECUTABLE,
    .build_system = UMI_DEVELOPER_PROJECT_BUILD_CMAKE,
    .primary_language_id = "developer.language.c23",
    .files = files,
    .file_count = sizeof files / sizeof files[0]
};
const UmiDeveloperProjectTemplate *LabRecipe(void) { return &recipe; }

void LabRequest(UmiDeveloperProjectGenerationRequest *request)
{
    umi_developer_project_generation_request_init(request);
    /* Literal lengths are bounded by the public owned fields. For user input,
     * use checked copies and report refusal rather than silently truncating. */
    strcpy(request->template_id, recipe.template_id);
    strcpy(request->application_name, "Umicom Recipe Study");
    strcpy(request->application_id, "org.umicom.recipe.study");
    strcpy(request->repository_name, "recipe-study");
    strcpy(request->target_name, "recipe_study");
    strcpy(request->project_root, "C:/learning/recipe-study");
    request->dry_run = 1;
}
