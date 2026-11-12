/*-----------------------------------------------------------------------------
 * Umicom Bits2Banking
 * File: labs/native/framework-iso-inspection/main.c
 *
 * PURPOSE:
 *   Inspect synthetic optical records through the installed read-only Framework service.
 *
 * AUTHOR AND ORGANISATION:
 * Sammy Hegab
 * Umicom Foundation
 *
 * LICENCE:
 * MIT
 *---------------------------------------------------------------------------*/

#include "umicom/image_inspection/iso.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

enum { BLOCK=2048, IMAGE_BYTES=24*BLOCK };
typedef struct Source {
    const unsigned char *data;
    size_t size;
    unsigned calls;
    int fail;
    /* Optional exact-call fault; the earlier second-call switch remains supported. */
    unsigned failAt;
} Source;

/* A first-prefix read refusal can now be injected explicitly while preserving the original second-call fault scenario. The previous implementation is retained for review. */
#if 0
static UmiStatus Read(void *context,uint64_t offset,void *destination,size_t length)
{
    Source *source=context;
    ++source->calls;
    if(source->fail&&source->calls==2U)return UMI_STATUS_IO_ERROR;
    /* Subtract only after establishing that offset is within the buffer.
     * Conversion to size_t is then safe, including on a smaller host. */
    if(offset>(uint64_t)source->size||
        (uint64_t)length>(uint64_t)source->size-offset)return UMI_STATUS_IO_ERROR;
    memcpy(destination,source->data+(size_t)offset,length);
    return UMI_STATUS_OK;
}
#endif
static UmiStatus Read(void *context,uint64_t offset,void *destination,size_t length)
{
    Source *source=context;
    ++source->calls;
    if((source->fail&&source->calls==2U)||
        (source->failAt!=0U&&source->calls==source->failAt))return UMI_STATUS_IO_ERROR;
    /* Subtract only after establishing that offset is within the buffer.
     * Conversion to size_t is then safe, including on a smaller host. */
    if(offset>(uint64_t)source->size||
        (uint64_t)length>(uint64_t)source->size-offset)return UMI_STATUS_IO_ERROR;
    memcpy(destination,source->data+(size_t)offset,length);
    return UMI_STATUS_OK;
}

static void Fixture(unsigned char *image,int efi,unsigned count)
{
    /* Synthetic descriptors teach byte layout. They do not contain a root
     * directory tree, executable boot loader or valid EFI system partition. */
    unsigned char *primary=image+16U*BLOCK;
    primary[0]=1; memcpy(primary+1,"CD001",5); primary[6]=1;
    primary[80]=24; primary[87]=24; primary[129]=8; primary[130]=8;
    unsigned char *boot=image+17U*BLOCK;
    memcpy(boot+1,"CD001",5); boot[6]=1;
    memcpy(boot+7,"EL TORITO SPECIFICATION",23); boot[71]=19;
    unsigned char *end=image+18U*BLOCK;
    end[0]=255; memcpy(end+1,"CD001",5); end[6]=1;
    unsigned char *catalogue=image+19U*BLOCK;
    catalogue[0]=1; catalogue[1]=(unsigned char)(efi?0xef:0);
    catalogue[30]=0x55; catalogue[31]=0xaa;
    unsigned sum=0;
    for(unsigned i=0;i<32U;i+=2U)
        sum+=(unsigned)catalogue[i]|((unsigned)catalogue[i+1U]<<8U);
    unsigned checksum=(0U-sum)&65535U;
    catalogue[28]=(unsigned char)checksum;
    catalogue[29]=(unsigned char)(checksum>>8U);
    catalogue[32]=0x88; catalogue[38]=(unsigned char)count; catalogue[40]=20;
}

/* The client now distinguishes unrelated bytes, recognised truncation and retained observations through the same public parser. Existing scenarios and ownership remain available. The previous implementation is retained for review. */
#if 0
int main(int argc,char **argv)
{
    if(argc!=2) {
        fputs("Usage: btb-framework-iso-inspection bios|efi-zero|efi-one|endian|bios-zero|read-failure\n",stderr);
        return 2;
    }
    const char *scenario=argv[1];
    int efi=!strcmp(scenario,"efi-zero")||!strcmp(scenario,"efi-one");
    if(!efi&&strcmp(scenario,"bios")&&strcmp(scenario,"endian")&&
        strcmp(scenario,"bios-zero")&&strcmp(scenario,"read-failure"))return 2;
    unsigned char *image=calloc(IMAGE_BYTES,1);
    if(!image)return 1;
    unsigned count=efi?(!strcmp(scenario,"efi-one")?1U:0U):4U;
    if(!strcmp(scenario,"bios-zero"))count=0;
    Fixture(image,efi,count);
    if(!strcmp(scenario,"endian"))image[16U*BLOCK+87]=23;
    Source source={image,IMAGE_BYTES,0,!strcmp(scenario,"read-failure")};
    UmiIsoImageInfo info={0};
    UmiStatus status=UmiIsoImageInspect(Read,&source,source.size,&info);
    printf("Status: %d\nISO9660: %d; El Torito: %d; BIOS: %d; EFI: %d\n",
        (int)status,info.iso9660,info.elTorito,info.biosEntry,info.efiEntry);
    printf("Read callbacks: %u\n",source.calls);
    puts("Synthetic memory inspection only; no device, producer or boot execution.");
    /* Framework did not retain source or its bytes after the call. */
    free(image);
    return status==UMI_STATUS_OK?0:1;
}

#endif
int main(int argc,char **argv)
{
    static const char *known[]={
        "bios","efi-zero","efi-one","endian","bios-zero","read-failure",
        "prefix-short","prefix-unknown","prefix-truncated","prefix-sector",
        "prefix-read-failure","retained-error","retained-noniso"
    };
    if(argc!=2){
        fputs("Usage: btb-framework-iso-inspection SCENARIO\nSee README.md for the supported scenarios.\n",stderr);
        return 2;
    }
    const char *scenario=argv[1];
    int recognized=0;
    for(size_t i=0;i<sizeof(known)/sizeof(known[0]);++i)
        if(!strcmp(scenario,known[i]))recognized=1;
    if(!recognized)return 2;
    int efi=!strcmp(scenario,"efi-zero")||!strcmp(scenario,"efi-one");
    unsigned char *image=calloc(IMAGE_BYTES,1);
    if(!image)return 1;
    unsigned count=efi?(!strcmp(scenario,"efi-one")?1U:0U):4U;
    if(!strcmp(scenario,"bios-zero"))count=0;
    Fixture(image,efi,count);
    if(!strcmp(scenario,"endian"))image[16U*BLOCK+87]=23;
    Source source={image,IMAGE_BYTES,0,!strcmp(scenario,"read-failure"),0};
    UmiIsoImageInfo info={0};
    int retained=!strcmp(scenario,"retained-error")||!strcmp(scenario,"retained-noniso");
    if(retained){
        /* Establish a real earlier observation instead of inventing valid flags.
         * The second call demonstrates their lifetime, never current acceptance. */
        UmiStatus initial=UmiIsoImageInspect(Read,&source,source.size,&info);
        if(initial!=UMI_STATUS_OK){free(image);return 1;}
        puts("Prior BIOS observation accepted; next result must be checked separately.");
        source.calls=0;
    }
    if(!strncmp(scenario,"prefix-",7U)||retained){
        source.size=16U*BLOCK+6U;
        if(!strcmp(scenario,"prefix-short"))source.size=16U*BLOCK+5U;
        if(!strcmp(scenario,"prefix-sector")){
            source.size=17U*BLOCK;
            image[16U*BLOCK+80]=17;image[16U*BLOCK+87]=17;
        }
        if(!strcmp(scenario,"prefix-unknown")||!strcmp(scenario,"retained-noniso"))
            image[16U*BLOCK+1]='X';
        if(!strcmp(scenario,"prefix-read-failure"))source.failAt=1U;
    }
    UmiStatus status=UmiIsoImageInspect(Read,&source,source.size,&info);
    printf("Status: %d\nISO9660: %d; El Torito: %d; BIOS: %d; EFI: %d\n",
        (int)status,info.iso9660,info.elTorito,info.biosEntry,info.efiEntry);
    printf("Read callbacks: %u\n",source.calls);
    if(retained && status!=UMI_STATUS_OK)
        puts("Flags retained from prior inspection; they do not describe the refused source.");
    puts("Synthetic memory inspection only; no device, producer or boot execution.");
    /* Framework did not retain source or its bytes after the call. */
    free(image);
    return status==UMI_STATUS_OK?0:1;
}
