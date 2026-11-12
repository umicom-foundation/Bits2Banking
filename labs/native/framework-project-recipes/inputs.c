/*-----------------------------------------------------------------------------
 * Umicom Bits2Banking
 * File: labs/native/framework-project-recipes/inputs.c
 *
 * PURPOSE:
 *   Observe catalogue, variable, identity and destination contracts through the installed Framework API.
 *
 * AUTHOR AND ORGANISATION:
 * Sammy Hegab
 * Umicom Foundation
 *
 * LICENCE:
 * MIT
 *---------------------------------------------------------------------------*/


#include "lab.h"
#include "umicom/developer_project/builtin_templates.h"
#include "umicom/developer_project/new_project.h"
#include <stdio.h>
#include <string.h>
#define REQUIRE(condition) do { if (!(condition)) { \
    fprintf(stderr, "%s:%d: %s\n", __FILE__, __LINE__, #condition); return 1; \
} } while (0)

int LabInputScenario(const char *name)
{
    UmiDeveloperProjectGenerationRequest request;
    UmiDeveloperProjectVariableSet variables;
    LabRequest(&request);
    umi_developer_project_variable_set_init(&variables);
    if (strcmp(name, "catalogue") == 0) {
        size_t count = umi_developer_project_builtin_template_count();
        int found = 0;
        REQUIRE(count > 0U);
        for (size_t i = 0U; i < count; ++i) {
            const UmiDeveloperProjectTemplate *entry =
                umi_developer_project_builtin_template_at(i);
            REQUIRE(entry != NULL);
            REQUIRE(umi_developer_project_template_validate(entry) == UMI_STATUS_OK);
            printf("%s: %zu files\n", entry->template_id, entry->file_count);
            if (strcmp(entry->template_id, "developer.template.c23-console") == 0)
                found = 1;
        }
        REQUIRE(found);
        REQUIRE(umi_developer_project_builtin_template_at(count) == NULL);
    } else if (strcmp(name, "variables") == 0) {
        char caller_value[] = "First name";
        REQUIRE(umi_developer_project_variable_set(&variables, "NAME", caller_value) == UMI_STATUS_OK);
        caller_value[0] = 'X';
        const char *borrowed = umi_developer_project_variable_get(&variables, "NAME");
        REQUIRE(borrowed != NULL && strcmp(borrowed, "First name") == 0);
        REQUIRE(umi_developer_project_variable_set(&variables, "COPY", borrowed) == UMI_STATUS_OK);
        borrowed = umi_developer_project_variable_get(&variables, "COPY");
        REQUIRE(borrowed != NULL && strcmp(borrowed, "First name") == 0);
        REQUIRE(variables.count == 2U);
    } else if (strcmp(name, "invalid-variable") == 0) {
        REQUIRE(umi_developer_project_variable_set(&variables, "NAME", "Valid") == UMI_STATUS_OK);
        memset(variables.variables[0].value, 'x', sizeof variables.variables[0].value);
        REQUIRE(umi_developer_project_variable_set_validate(&variables) == UMI_STATUS_INVALID_ARGUMENT);
        REQUIRE(umi_developer_project_variable_get(&variables, "NAME") == NULL);
        char output[32] = "previous preview";
        REQUIRE(umi_developer_project_render_text("{{NAME}}", &variables, output, sizeof output) == UMI_STATUS_INVALID_ARGUMENT);
        REQUIRE(strcmp(output, "previous preview") == 0);
    } else if (strcmp(name, "request") == 0 || strcmp(name, "invalid-request") == 0) {
        char message[256];
        if (strcmp(name, "invalid-request") == 0) {
            strcpy(request.target_name, "9bad-target");
            REQUIRE(umi_developer_project_generation_request_validate(&request, message, sizeof message) == UMI_STATUS_INVALID_ARGUMENT);
            puts(message);
        } else {
            REQUIRE(umi_developer_project_generation_request_validate(&request, message, sizeof message) == UMI_STATUS_OK);
            REQUIRE(umi_developer_project_generation_request_variables(&request, &variables) == UMI_STATUS_OK);
            const char *guard = umi_developer_project_variable_get(&variables, "HEADER_GUARD");
            REQUIRE(guard != NULL && strcmp(guard, "RECIPE_STUDY_GENERATED_H") == 0);
            puts(guard);
        }
    } else if (strcmp(name, "destination") == 0 || strcmp(name, "reserved-folder") == 0) {
        char output[UMI_DEVELOPER_PROJECT_PATH_CAPACITY] = "previous destination";
        UmiStatus status = UmiDeveloperProjectChooseDestination("C:/learning",
            strcmp(name, "destination") == 0 ? "recipe-study" : "CON", output, sizeof output);
        if (strcmp(name, "destination") == 0) {
            REQUIRE(status == UMI_STATUS_OK);
            REQUIRE(strcmp(output, "C:/learning/recipe-study") == 0);
        } else {
            REQUIRE(status != UMI_STATUS_OK);
            REQUIRE(strcmp(output, "previous destination") == 0);
            printf("Reserved folder refused with status %d.\n", (int)status);
        }
    } else return 2;
    return 0;
}
