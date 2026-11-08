/*-----------------------------------------------------------------------------
 * Umicom Bits2Banking
 * File: labs/native/framework-recipes/main.c
 *
 * PURPOSE:
 *   Inspect source recipe metadata and demonstrate independent task ownership
 * through an installed Framework SDK.
 *
 * AUTHOR AND ORGANISATION:
 * Sammy Hegab
 * Umicom Foundation
 *
 * LICENCE:
 * MIT
 *---------------------------------------------------------------------------*/

#include "umicom/build/recipe.h"
#include "umicom/platform/input_file.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
int main(int argc, char **argv) {
  if (argc != 3) {
    fprintf(
        stderr,
        "Usage: recipe-lab inspect|owned|identity|refuse ABSOLUTE_RECIPE\n");
    return 2;
  }
  const char *mode = argv[1];
  if (strcmp(mode, "inspect") && strcmp(mode, "owned") &&
      strcmp(mode, "identity") && strcmp(mode, "refuse"))
    return 2;
  UmiBuildRecipe *recipe = NULL;
  UmiBuildTaskRegistry *registry = NULL;
  UmiBuildRecipeReport report;
  UmiStatus status = UmiBuildRecipeReadFile(argv[2], &recipe, &report);
  if (!strcmp(mode, "refuse")) {
    if (status != UMI_STATUS_PARSE_ERROR || recipe != NULL) {
      UmiBuildRecipeDestroy(recipe);
      return 1;
    }
    puts("Command-bearing recipe refused; output owner unchanged.");
    return 0;
  }
  if (status != UMI_STATUS_OK) {
    fprintf(stderr, "%s\n", report.message);
    return 1;
  }
  UmiBuildRecipeInfo info;
  status = UmiBuildRecipeInfoRead(recipe, &info);
  if (status == UMI_STATUS_OK && !strcmp(mode, "owned")) {
    status = UmiBuildRecipeCreateTasks(recipe, &registry);
    UmiBuildRecipeDestroy(recipe);
    recipe = NULL;
    if (status == UMI_STATUS_OK &&
        umi_build_task_registry_count(registry) != info.stage_count)
      status = UMI_STATUS_INTERNAL_ERROR;
    UmiBuildTaskSnapshot task;
    if (status == UMI_STATUS_OK)
      status = umi_build_task_registry_at(registry, 0U, &task);
    if (status == UMI_STATUS_OK && (task.command[0] || !task.has_build_phase))
      status = UMI_STATUS_INTERNAL_ERROR;
    if (status == UMI_STATUS_OK)
      puts("Task registry remains owned after recipe destruction.");
  } else if (status == UMI_STATUS_OK && !strcmp(mode, "identity")) {
    unsigned char *bytes = NULL;
    size_t size = 0U;
    status = UmiInputFileRead(argv[2], UMI_BUILD_RECIPE_MAX_BYTES - 1U, &bytes,
                              &size);
    UmiBuildRecipe *other = NULL;
    /* The shared reader reserves a trailing byte. Replace that byte with
     * JSON whitespace and explicitly include it in the next bounded parse. */
    if (status == UMI_STATUS_OK) {
      bytes[size] = ' ';
      status = UmiBuildRecipeOpen(bytes, size + 1U, &other, &report);
    }
    UmiInputFileFree(bytes);
    UmiBuildRecipeInfo changed;
    if (status == UMI_STATUS_OK)
      status = UmiBuildRecipeInfoRead(other, &changed);
    if (status == UMI_STATUS_OK &&
        (strcmp(info.id, changed.id) ||
         !strcmp(info.recipe_sha256, changed.recipe_sha256)))
      status = UMI_STATUS_INTERNAL_ERROR;
    if (status == UMI_STATUS_OK)
      puts("Same recipe ID; different exact-byte digest after whitespace.");
    UmiBuildRecipeDestroy(other);
  } else if (status == UMI_STATUS_OK) {
    printf("Recipe %s: %zu inputs, %zu stages.\n", info.id, info.input_count,
           info.stage_count);
    printf("Build %s; host %s; target %s.\n", info.build, info.host,
           info.target);
  }
  if (status == UMI_STATUS_OK)
    puts("No recipe stage executed; source and toolchain claims are "
         "unverified.");
  umi_build_task_registry_destroy(registry);
  UmiBuildRecipeDestroy(recipe);
  return status == UMI_STATUS_OK ? 0 : 1;
}
