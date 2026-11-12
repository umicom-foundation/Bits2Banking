/*-----------------------------------------------------------------------------
 * Umicom Bits2Banking
 * File: labs/native/framework-filesystem-clients/projects.c
 *
 * PURPOSE:
 *   Compose installed Framework plan and service APIs without duplicating model or filesystem policy.
 *
 * AUTHOR AND ORGANISATION:
 * Sammy Hegab
 * Umicom Foundation
 *
 * LICENCE:
 * MIT
 *---------------------------------------------------------------------------*/


#include "lab.h"
static void PrepareRequest(UmiDeveloperProjectGenerationRequest *request,const char *destination)
{
    umi_developer_project_generation_request_init(request);
    strcpy(request->template_id,"developer.template.c23-console");
    strcpy(request->application_name,"Umicom Storage Study");
    strcpy(request->application_id,"org.umicom.storage.study");
    strcpy(request->repository_name,"umicom-storage-study");
    strcpy(request->target_name,"umicom_storage_study");
    memcpy(request->project_root,destination,strlen(destination)+1U);
    request->dry_run=0;
}
int LabProjects(const char *scenario,LabState *state)
{
    char destination[UMI_PATH_CAPACITY];
    LAB_CHECK(umi_path_join(state->root,"project",destination,sizeof destination)==UMI_STATUS_OK);
    if(!strncmp(scenario,"project-",8U)){
        UmiDeveloperProjectGenerationPlan *plan=&state->plan;
        umi_developer_project_generation_plan_init(plan);
        strcpy(plan->project_root,destination);strcpy(plan->template_id,"course.storage.fixture");
        plan->file_count=2U;
        strcpy(plan->files[0].relative_path,"src/main.c");
        strcpy(plan->files[0].content,"int main(void){return 0;}\n");
        strcpy(plan->files[1].relative_path,"README.md");
        strcpy(plan->files[1].content,"Umicom storage exercise\n");
        UmiDeveloperProjectGeneratorRequest request={plan,!strcmp(scenario,"project-preview"),0};
        UmiDeveloperProjectGeneratorReport report;
        LAB_CHECK(umi_developer_project_generator_create(&request,&report)==UMI_STATUS_OK);
        LAB_CHECK(report.files_created==2U&&report.files_skipped==0U);
        LAB_CHECK(report.bytes_written==strlen(plan->files[0].content)+strlen(plan->files[1].content));
        if(request.dry_run)LAB_CHECK(report.directories_created==0U);
        else{
            LAB_CHECK(report.directories_created==2U);
            LAB_CHECK(LabReadEquals(destination,"src/main.c",plan->files[0].content,strlen(plan->files[0].content))==0);
            if(!strcmp(scenario,"project-collision")){
                LAB_CHECK(umi_developer_project_generator_create(&request,&report)==UMI_STATUS_ALREADY_EXISTS);
                LAB_CHECK(report.files_created==0U&&report.directories_created==0U&&report.bytes_written==0U);
                LAB_CHECK(LabReadEquals(destination,"README.md",plan->files[1].content,strlen(plan->files[1].content))==0);
            }
        }
        printf("Plan application observed: dry=%d; files=%zu; directories=%zu.\n",
            report.dry_run,report.files_created,report.directories_created);
        return 0;
    }
    if(strcmp(scenario,"service-create")&&strcmp(scenario,"service-refusal")&&strcmp(scenario,"profile-preview"))return 2;
    if(!strcmp(scenario,"service-refusal")){
        UmiRootedDirectoryCreation directory;
        LAB_CHECK(UmiRootedDirectoryCreate(state->root,"project",&directory)==UMI_STATUS_OK);
    }
    UmiDeveloperProjectGenerationRequest request;PrepareRequest(&request,destination);
    request.dry_run=!strcmp(scenario,"profile-preview");
    UmiDeveloperProjectService *service=NULL;
    LAB_CHECK(umi_developer_project_service_create(&service)==UMI_STATUS_OK);
    /* Preserve the initial struct-assignment snapshots for review. Byte-level
     * refusal checks require copying padding as well as named fields. */
#if 0
    memset(&state->model,0xa5,sizeof state->model);state->previous_model=state->model;
    memset(&state->profile,0xa5,sizeof state->profile);state->previous_profile=state->profile;
#endif
    memset(&state->model,0xa5,sizeof state->model);
    memcpy(&state->previous_model,&state->model,sizeof state->model);
    memset(&state->profile,0xa5,sizeof state->profile);
    memcpy(&state->previous_profile,&state->profile,sizeof state->profile);
    UmiDeveloperProjectGeneratorReport report;
    UmiStatus status=umi_developer_project_service_generate_new(
        service,&request,&report,&state->model,&state->profile);
    UmiDeveloperProjectServiceSnapshot snapshot;
    UmiStatus observed=umi_developer_project_service_snapshot(service,&snapshot);
    /* The service owns registries only until this release. Outputs are copies;
     * no borrowed service pointer is used by the checks below. */
    umi_developer_project_service_destroy(service);
    LAB_CHECK(observed==UMI_STATUS_OK);
    if(!strcmp(scenario,"service-refusal")){
        LAB_CHECK(status==UMI_STATUS_ALREADY_EXISTS&&snapshot.project_count==0U);
        LAB_CHECK(memcmp(&state->model,&state->previous_model,sizeof state->model)==0);
        LAB_CHECK(memcmp(&state->profile,&state->previous_profile,sizeof state->profile)==0);
        LAB_CHECK(report.files_created==0U&&report.directories_created==0U);
    }else{
        LAB_CHECK(status==UMI_STATUS_OK&&snapshot.project_count==(request.dry_run?0U:1U));
        LAB_CHECK(!strcmp(state->model.project_id,request.application_id));
        LAB_CHECK(umi_build_profile_validate(&state->profile,NULL,0U)==UMI_STATUS_OK);
        LAB_CHECK(report.files_created>0U&&report.files_skipped==0U);
        printf("Model: %s; profile root: %s; registered projects: %zu.\n",
            state->model.project_id,state->profile.source_directory,snapshot.project_count);
    }
    return 0;
}
