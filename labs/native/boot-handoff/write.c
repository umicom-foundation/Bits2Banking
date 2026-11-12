/*-----------------------------------------------------------------------------
 * Umicom Bits2Banking
 * File: labs/native/boot-handoff/write.c
 *
 * PURPOSE:
 *   Teach canonical boot metadata encoding and unchanged output on refusal.
 *
 * AUTHOR AND ORGANISATION:
 * Sammy Hegab
 * Umicom Foundation
 *
 * LICENCE:
 * MIT
 *---------------------------------------------------------------------------*/

#include "umicom/kernel/boot_handoff.h"
#include <stdio.h>
#include <string.h>

static int Fail(const char *detail)
{
    fprintf(stderr,"Boot handoff exercise failed: %s\n",detail);
    return 1;
}

int main(int argc,char **argv)
{
    const char *mode=argc==1?"roundtrip":argv[1];
    if(argc>2||(strcmp(mode,"roundtrip")&&strcmp(mode,"small")&&
        strcmp(mode,"unreserved")&&strcmp(mode,"bad-text"))) {
        fputs("Usage: boot-handoff-write [roundtrip|small|unreserved|bad-text]\n",stderr);
        return 2;
    }
    /* This hosted client describes a synthetic machine. No integer address is
     * cast to a pointer and no boot image, device or physical RAM is touched. */
    UmicomKernelBootHandoff record={0};
    record.architecture=UMICOM_BOOT_RISCV64;
    record.kernel.address=0x80001000ULL;
    record.kernel.bytes=4096;
    record.ramCount=1;
    record.ram[0].address=0x80000000ULL;
    record.ram[0].bytes=0x100000;
    record.reservedCount=1;
    record.reserved[0].address=0x80000000ULL;
    record.reserved[0].bytes=8192;
    strcpy(record.commandLine,"console=serial");
    unsigned char bytes[UMICOM_BOOT_HANDOFF_MAX_BYTES],before[sizeof bytes];
    memset(bytes,0xa5,sizeof bytes);
    memcpy(before,bytes,sizeof before);
    UmicomSize written=99;
    UmicomSize capacity=sizeof bytes;
    UmicomBootHandoffStatus expected=UMICOM_BOOT_HANDOFF_OK;
    if(!strcmp(mode,"small")) {
        capacity=143;expected=UMICOM_BOOT_HANDOFF_LENGTH;
    } else if(!strcmp(mode,"unreserved")) {
        record.reserved[0].bytes=4096;expected=UMICOM_BOOT_HANDOFF_MEMORY;
    } else if(!strcmp(mode,"bad-text")) {
        record.commandLine[0]='\n';expected=UMICOM_BOOT_HANDOFF_TEXT;
    }
    UmicomBootHandoffStatus status=UmicomKernelBootHandoffWrite(&record,bytes,capacity,&written);
    if(status!=expected)return Fail("unexpected producer status");
    if(status!=UMICOM_BOOT_HANDOFF_OK) {
        if(written!=99||memcmp(bytes,before,sizeof bytes))
            return Fail("refusal changed caller storage");
        printf("Refused %s: bytes and length unchanged\n",mode);
        return 0;
    }
    /* The exact serialized length, not the capacity, is passed to the reader.
     * After this copy, the reader owns its observation independently of bytes. */
    UmicomKernelBootHandoff observation;
    status=UmicomKernelBootHandoffRead(bytes,written,&observation);
    if(status!=UMICOM_BOOT_HANDOFF_OK||written!=158||
        observation.ramCount!=1||observation.reservedCount!=1||
        strcmp(observation.commandLine,"console=serial"))
        return Fail("round trip changed the described machine");
    for(UmicomSize i=written;i<sizeof bytes;++i)
        if(bytes[i]!=0xa5)return Fail("writer changed the destination tail");
    memset(bytes,0,sizeof bytes);
    if(strcmp(observation.commandLine,"console=serial"))
        return Fail("reader borrowed producer storage");
    printf("Encoded %llu bytes; independent reader copy retained console=serial\n",
        (unsigned long long)written);
    return 0;
}
