/*-----------------------------------------------------------------------------
 * Umicom Bits2Banking
 * File: labs/native/framework-filesystem-clients/lab.h
 *
 * PURPOSE:
 *   Share owned lab state and public Framework client exercises.
 *
 * AUTHOR AND ORGANISATION:
 * Sammy Hegab
 * Umicom Foundation
 *
 * LICENCE:
 * MIT
 *---------------------------------------------------------------------------*/


#ifndef UMICOM_COURSE_FILESYSTEM_LAB_H
#define UMICOM_COURSE_FILESYSTEM_LAB_H
#include "umicom/developer_project/new_project.h"
#include "umicom/platform/rooted_files.h"
#include "umicom/platform/path.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
typedef struct LabState {
    char root[UMI_PATH_CAPACITY];
    UmiDeveloperProjectGenerationPlan plan;
    UmiDeveloperProjectModel model,previous_model;
    UmiBuildProfile profile,previous_profile;
} LabState;
#define LAB_CHECK(c) do{if(!(c)){fprintf(stderr,"%s:%d: %s\n",__FILE__,__LINE__,#c);return 1;}}while(0)
int LabFixture(const char *parent,LabState *state);
int LabReadEquals(const char *root,const char *relative,const void *expected,size_t length);
int LabNames(const char *scenario);
int LabFiles(const char *scenario,LabState *state);
int LabProjects(const char *scenario,LabState *state);
#endif
