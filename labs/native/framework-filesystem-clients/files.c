/*-----------------------------------------------------------------------------
 * Umicom Bits2Banking
 * File: labs/native/framework-filesystem-clients/files.c
 *
 * PURPOSE:
 *   Observe directory and file creation reports while preserving existing content in a retained fixture.
 *
 * AUTHOR AND ORGANISATION:
 * Sammy Hegab
 * Umicom Foundation
 *
 * LICENCE:
 * MIT
 *---------------------------------------------------------------------------*/


#include "lab.h"
int LabFiles(const char *scenario,LabState *state)
{
    UmiRootedDirectoryCreation directory;
    if(!strcmp(scenario,"directory-chain")){
        LAB_CHECK(UmiRootedDirectoryEnsure(state->root,"notes/source",&directory)==UMI_STATUS_OK);
        LAB_CHECK(directory.complete&&directory.directories_created==2U);
        LAB_CHECK(UmiRootedDirectoryEnsure(state->root,"notes/source",&directory)==UMI_STATUS_OK);
        LAB_CHECK(directory.complete&&directory.directories_created==0U);
    }else if(!strcmp(scenario,"exclusive-directory")){
        LAB_CHECK(UmiRootedDirectoryCreate(state->root,"project",&directory)==UMI_STATUS_OK);
        LAB_CHECK(directory.complete&&directory.directories_created==1U);
        LAB_CHECK(UmiRootedDirectoryCreate(state->root,"project",&directory)==UMI_STATUS_ALREADY_EXISTS);
        LAB_CHECK(!directory.complete&&directory.directories_created==0U);
        LAB_CHECK(UmiRootedDirectoryEnsure(state->root,"project",&directory)==UMI_STATUS_OK);
        LAB_CHECK(directory.complete&&directory.directories_created==0U);
    }else if(!strcmp(scenario,"invalid-directory")){
        LAB_CHECK(UmiRootedDirectoryEnsure(state->root,"new/../outside",&directory)==UMI_STATUS_INVALID_ARGUMENT);
        LAB_CHECK(!directory.complete&&directory.directories_created==0U);
        int exists=1;
        LAB_CHECK(UmiRootedFileExists(state->root,"new/child.txt",&exists)==UMI_STATUS_OK&&!exists);
    }else if(!strcmp(scenario,"new-file")||!strcmp(scenario,"existing-file")||!strcmp(scenario,"empty-file")){
        const unsigned char content[]={0U,'U',255U,'M'};
        size_t length=!strcmp(scenario,"empty-file")?0U:sizeof content;
        LAB_CHECK(UmiRootedDirectoryEnsure(state->root,"notes",&directory)==UMI_STATUS_OK);
        UmiRootedFileCreation creation;
        LAB_CHECK(UmiRootedFileCreate(state->root,"notes/record.bin",content,length,&creation)==UMI_STATUS_OK);
        LAB_CHECK(creation.created&&creation.complete&&creation.bytes_written==length);
        if(!strcmp(scenario,"existing-file")){
            LAB_CHECK(UmiRootedFileCreate(state->root,"notes/record.bin","replacement",11U,&creation)==UMI_STATUS_ALREADY_EXISTS);
            LAB_CHECK(!creation.created&&!creation.complete&&creation.bytes_written==0U);
        }
        LAB_CHECK(LabReadEquals(state->root,"notes/record.bin",content,length)==0);
    }else return 2;
    puts("Native storage observations matched; fixture contents were retained.");
    return 0;
}
