/*-----------------------------------------------------------------------------
 * Umicom Bits2Banking
 * File: labs/framework/reflection-snapshot/media_labels.c
 *
 * PURPOSE:
 *   Inspect resource media labels through the shared Framework registry without opening or trusting content.
 *
 * AUTHOR AND ORGANISATION:
 * Sammy Hegab
 * Umicom Foundation
 *
 * LICENCE:
 * MIT
 *---------------------------------------------------------------------------*/


#include "umicom/reflection/registry.h"
#include <stdio.h>
#include <string.h>

int main(void)
{
    UmiReflectionResourceDescriptor resource={0},copy={0};
    resource.structure_size=(uint32_t)sizeof resource;
    strcpy(resource.resource_id,"learning.preview");
    strcpy(resource.module_id,"learning.media");
    strcpy(resource.display_name,"Example preview metadata");
    strcpy(resource.resource_uri,"memory://learning/preview");
    resource.kind=UMI_REFLECTION_RESOURCE_DOCUMENTATION;
    const char *labels[]={"umicom.layout","application/json","image/svg+xml","text/plain; charset=UTF-8"};
    const UmiStatus expected[]={UMI_STATUS_OK,UMI_STATUS_OK,UMI_STATUS_OK,UMI_STATUS_INVALID_ARGUMENT};
    for(size_t i=0U;i<sizeof labels/sizeof labels[0];++i) {
        /* These literals fit, but preserve the size rule for future lesson input. */
        size_t length=strlen(labels[i]);
        if(length>=sizeof resource.media_type)return 1;
        memcpy(resource.media_type,labels[i],length+1U);
        UmiStatus status=umi_reflection_resource_descriptor_validate(&resource);
        if(status!=expected[i])return 1;
        if(printf("%s: %s\n",labels[i],status==UMI_STATUS_OK?"accepted":"refused")<0)return 1;
    }
    UmiReflectionRegistry *registry=NULL;
    UmiReflectionRegistryConfig config=umi_reflection_registry_config_default();
    config.type_capacity=1U;config.module_capacity=1U;config.resource_capacity=1U;
    if(umi_reflection_registry_create(&config,&registry)!=UMI_STATUS_OK)return 1;
    int result=1;
    strcpy(resource.media_type,"image/svg+xml");
    if(umi_reflection_registry_register_resource(registry,&resource)!=UMI_STATUS_OK)goto cleanup;
    /* Metadata is copied by the registry. Modifying the local descriptor does
     * not rewrite the registry, and a refused upsert must not replace it. */
    strcpy(resource.media_type,"image/*");
    int replaced=0;
    if(umi_reflection_registry_upsert_resource(registry,&resource,&replaced)!=UMI_STATUS_INVALID_ARGUMENT)goto cleanup;
    if(umi_reflection_registry_get_resource(registry,"learning.preview",&copy)!=UMI_STATUS_OK)goto cleanup;
    if(strcmp(copy.media_type,"image/svg+xml"))goto cleanup;
    if(puts("Refused replacement preserved image/svg+xml.")<0)goto cleanup;
    if(puts("Only metadata was inspected; no resource bytes were opened.")<0)goto cleanup;
    result=0;
cleanup:
    umi_reflection_registry_destroy(registry);
    if(fflush(stdout)!=0)result=1;
    return result;
}
