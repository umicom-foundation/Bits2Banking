/*-----------------------------------------------------------------------------
 * Umicom Bits2Banking
 * File: labs/native/framework-filesystem-clients/main.c
 *
 * PURPOSE:
 *   Own the lab workspace and route explicit public-SDK exercises without running generated applications.
 *
 * AUTHOR AND ORGANISATION:
 * Sammy Hegab
 * Umicom Foundation
 *
 * LICENCE:
 * MIT
 *---------------------------------------------------------------------------*/


#include "lab.h"
int main(int argc,char **argv)
{
    if(argc!=3){fputs("Usage: filesystem-clients SCENARIO ABSOLUTE_EXISTING_PARENT\n",stderr);return 2;}
    const char *scenario=argv[1],*parent=argv[2];
    const char *const names[]={"path-admission","path-relations","invalid-path","directory-chain",
        "exclusive-directory","new-file","existing-file","empty-file","invalid-directory",
        "project-preview","project-create","project-collision","service-create","service-refusal","profile-preview"};
    size_t selected=0U;
    for(;selected<sizeof names/sizeof names[0];++selected)if(!strcmp(scenario,names[selected]))break;
    if(selected==sizeof names/sizeof names[0])return 2;
    if(UmiRootedFileValidatePath(parent,"fixture")!=UMI_STATUS_OK)return 2;
    /* Large plans and snapshots belong to one heap owner, not a native thread's
     * limited stack. Exercise functions borrow it; main always releases it. */
    LabState *state=calloc(1U,sizeof *state);
    if(state==NULL)return 1;
    int result;
    if(selected<3U)result=LabNames(scenario);
    else{
        int preview=!strcmp(scenario,"project-preview")||!strcmp(scenario,"profile-preview");
        if(preview){
            UmiStatus status=umi_path_copy(state->root,sizeof state->root,parent);
            if(status!=UMI_STATUS_OK){free(state);return 1;}
        }else if(LabFixture(parent,state)!=0){free(state);return 1;}
        result=selected<9U?LabFiles(scenario,state):LabProjects(scenario,state);
    }
    free(state);
    if(result==0)puts("Selected lab observation completed. This is not an application build or device qualification.");
    return result;
}
