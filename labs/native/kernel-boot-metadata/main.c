/*-----------------------------------------------------------------------------
 * Bits2Banking
 * File: labs/native/kernel-boot-metadata/main.c
 *
 * PURPOSE:
 *   Explore real Kernel metadata validation and page reservation planning through an original synthetic tree.
 *
 * AUTHOR AND ORGANISATION:
 * Sammy Hegab
 * Umicom Foundation
 *
 * LICENCE:
 * MIT
 *---------------------------------------------------------------------------*/

#include "umicom/kernel/boot_reservations.h"
#include <stdio.h>
#include <string.h>

/* This fixture is intentionally a small byte protocol, not a native C struct.
 * Byte order and lengths are visible so learners can change one field at a time. */
static void Put32(unsigned char *p, UmicomU32 value)
{
    p[0]=(unsigned char)(value>>24U);p[1]=(unsigned char)(value>>16U);
    p[2]=(unsigned char)(value>>8U);p[3]=(unsigned char)value;
}
static void Put64(unsigned char *p, UmicomU64 value)
{
    Put32(p,(UmicomU32)(value>>32U));Put32(p+4U,(UmicomU32)value);
}
int main(int argc,char **argv)
{
    if(argc!=2)return 2;
    unsigned char tree[88]={0};
    Put32(tree,0xd00dfeedU);Put32(tree+4U,sizeof tree);
    Put32(tree+8U,72U);Put32(tree+12U,88U);Put32(tree+16U,40U);
    Put32(tree+20U,17U);Put32(tree+24U,16U);Put32(tree+36U,16U);
    Put64(tree+40U,0x80010001ULL);Put64(tree+48U,1U);
    Put32(tree+72U,1U);Put32(tree+80U,2U);Put32(tree+84U,9U);
    const char *mode=argv[1];
    if(!strcmp(mode,"overflow")){Put64(tree+40U,~(UmicomU64)0U-1U);Put64(tree+48U,8U);}
    else if(!strcmp(mode,"missing-end"))Put32(tree+84U,4U);
    else if(strcmp(mode,"plan"))return 2;
    UmicomKernelDeviceTreeLayout layout;
    UmicomKernelDeviceTreeLayoutStatus status=UmicomKernelDeviceTreeLayoutRead(tree,sizeof tree,&layout);
    if(strcmp(mode,"plan")){
        if(status==UMICOM_FDT_LAYOUT_OK){fputs("Malformed fixture was accepted.\n",stderr);return 1;}
        printf("Expected rejection: %s. No allocator was initialized.\n",UmicomKernelDeviceTreeLayoutStatusName(status));
        return 0;
    }
    if(status!=UMICOM_FDT_LAYOUT_OK)return 1;
    UmicomKernelBootReservationPlan plan;
    if(!UmicomKernelBootReservationsPlan(0x80000000U,1024U*1024U,0x80004000U,0x80008000U,&layout,&plan))return 1;
    if(plan.count!=3U||plan.ranges[2].base!=0x80010000U||plan.ranges[2].bytes!=4096U)return 1;
    for(UmicomSize i=0;i<plan.count;++i)
        printf("reserved[%llu] base=0x%llx bytes=%llu\n",(unsigned long long)i,
            (unsigned long long)plan.ranges[i].base,(unsigned long long)plan.ranges[i].bytes);
    puts("Synthetic plan only. No guest boot or physical allocation was performed.");
    return 0;
}
