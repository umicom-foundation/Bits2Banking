/*-----------------------------------------------------------------------------
 * Umicom Bits2Banking
 * File: labs/native/framework-project-recipes/lab.h
 *
 * PURPOSE:
 *   Declare a small installed-SDK teaching client without duplicating Framework project services.
 *
 * AUTHOR AND ORGANISATION:
 * Sammy Hegab
 * Umicom Foundation
 *
 * LICENCE:
 * MIT
 *---------------------------------------------------------------------------*/


#ifndef BTB_PROJECT_RECIPES_LAB_H
#define BTB_PROJECT_RECIPES_LAB_H
#include "umicom/developer_project/generation_plan.h"
#include "umicom/developer_project/generation_request.h"
const UmiDeveloperProjectTemplate *LabRecipe(void);
void LabRequest(UmiDeveloperProjectGenerationRequest *request);
int LabInputScenario(const char *name);
int LabPreviewScenario(const char *name);
#endif
