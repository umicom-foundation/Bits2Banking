/*-----------------------------------------------------------------------------
 * Umicom Bits2Banking
 * File: labs/native/framework-filesystem-clients/fixture.c
 *
 * PURPOSE:
 *   Create a bounded fresh fixture through exclusive Framework directory creation and release owned reads.
 *
 * AUTHOR AND ORGANISATION:
 * Sammy Hegab
 * Umicom Foundation
 *
 * LICENCE:
 * MIT
 *---------------------------------------------------------------------------*/


#include "lab.h"
int LabFixture(const char *parent,LabState *state)
{
    for(unsigned attempt=1U;attempt<10000U;++attempt){
        char leaf[32];snprintf(leaf,sizeof leaf,"run-%04u",attempt);
        UmiRootedDirectoryCreation report;
        UmiStatus status=UmiRootedDirectoryCreate(parent,leaf,&report);
        if(status==UMI_STATUS_ALREADY_EXISTS&&report.directories_created==0U)continue;
        if(status!=UMI_STATUS_OK){
            fprintf(stderr,"Fixture refused: status %d, %zu directories created.\n",(int)status,report.directories_created);
            return 1;
        }
        LAB_CHECK(umi_path_join(parent,leaf,state->root,sizeof state->root)==UMI_STATUS_OK);
        printf("Retained fixture: %s\n",state->root);
        return 0;
    }
    fputs("No unused fixture name in the bounded range; select another prepared parent.\n",stderr);
    return 1;
}
int LabReadEquals(const char *root,const char *relative,const void *expected,size_t length)
{
    unsigned char *bytes=NULL;size_t count=0U;
    UmiStatus status=UmiRootedFileRead(root,relative,64U,&bytes,&count);
    if(status!=UMI_STATUS_OK)return 1;
    int same=count==length&&bytes!=NULL&&memcmp(bytes,expected,length)==0&&bytes[count]=='\0';
    UmiRootedFileFree(bytes);
    return same?0:1;
}
