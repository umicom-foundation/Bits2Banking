/*-----------------------------------------------------------------------------
 * Umicom Bits2Banking
 * File: labs/native/framework-filesystem-clients/names.c
 *
 * PURPOSE:
 *   Inspect portable names and component relations without filesystem effects.
 *
 * AUTHOR AND ORGANISATION:
 * Sammy Hegab
 * Umicom Foundation
 *
 * LICENCE:
 * MIT
 *---------------------------------------------------------------------------*/


#include "lab.h"
int LabNames(const char *scenario)
{
    if(!strcmp(scenario,"path-admission")){
        LAB_CHECK(UmiRootedFileValidateRelativePath("source/main.c")==UMI_STATUS_OK);
        LAB_CHECK(UmiRootedFileValidateRelativePath("source\\main.c")==UMI_STATUS_OK);
        LAB_CHECK(UmiRootedFileValidateRelativePath("caf\xc3\xa9/note.txt")==UMI_STATUS_OK);
    }else if(!strcmp(scenario,"path-relations")){
        UmiRootedPathRelation relation=UMI_ROOTED_PATH_DISJOINT;
        LAB_CHECK(UmiRootedFileCompareRelativePaths("Src/Main.c","src\\main.c",&relation)==UMI_STATUS_OK);
        LAB_CHECK(relation==UMI_ROOTED_PATH_EQUAL);
        LAB_CHECK(UmiRootedFileCompareRelativePaths("src","src/main.c",&relation)==UMI_STATUS_OK);
        LAB_CHECK(relation==UMI_ROOTED_PATH_FIRST_PARENT);
        LAB_CHECK(UmiRootedFileCompareRelativePaths("src","src-old/main.c",&relation)==UMI_STATUS_OK);
        LAB_CHECK(relation==UMI_ROOTED_PATH_DISJOINT);
    }else if(!strcmp(scenario,"invalid-path")){
        LAB_CHECK(UmiRootedFileValidateRelativePath("new/../outside")==UMI_STATUS_INVALID_ARGUMENT);
        LAB_CHECK(UmiRootedFileValidateRelativePath("new/.git/config")==UMI_STATUS_PERMISSION_DENIED);
        LAB_CHECK(UmiRootedFileValidateRelativePath("new/CON.txt")==UMI_STATUS_INVALID_ARGUMENT);
        UmiRootedPathRelation relation=UMI_ROOTED_PATH_SECOND_PARENT;
        LAB_CHECK(UmiRootedFileCompareRelativePaths("valid","../bad",&relation)!=UMI_STATUS_OK);
        LAB_CHECK(relation==UMI_ROOTED_PATH_SECOND_PARENT);
    }else return 2;
    puts("Portable-name observations matched; no filesystem identity was resolved.");
    return 0;
}
