/*-----------------------------------------------------------------------------
 * Umicom Bits2Banking
 * File: labs/native/framework-filesystem-header/main.c
 *
 * PURPOSE:
 *   Compare a bounded ext-family header read with refusal before or after a read.
 *
 * AUTHOR AND ORGANISATION:
 * Sammy Hegab
 * Umicom Foundation
 *
 * LICENCE:
 * MIT
 *---------------------------------------------------------------------------*/

#include "umicom/image_inspection/gpt_filesystem.h"

#include <inttypes.h>
#include <stdio.h>
#include <string.h>

typedef struct HeaderFixture {
    unsigned char bytes[1024];
    unsigned calls;
    int outside;
} HeaderFixture;

/* This sparse fixture owns just the header. The reader has authority over
 * precisely one byte window even though the advertised image is larger. */
static UmiStatus ReadHeader(void *context, uint64_t offset, void *out, size_t length)
{
    HeaderFixture *fixture = context;
    ++fixture->calls;
    if (offset != UINT64_C(1049600) || length != sizeof fixture->bytes) {
        fixture->outside = 1;
        return UMI_STATUS_IO_ERROR;
    }
    memcpy(out, fixture->bytes, length);
    return UMI_STATUS_OK;
}

/* Write fixture bytes in disk order without relying on C struct layout. */
static void PutLittle32(unsigned char *out, uint32_t value)
{
    for (unsigned i = 0U; i < 4U; ++i)
        out[i] = (unsigned char)(value >> (i * 8U));
}

static void PrepareHeader(unsigned char *out)
{
    /* The ext-family superblock records counts, a block-size exponent and
     * a signature. This builds just the fields inspected by Framework. */
    PutLittle32(out + 0x00U, 1024U);
    PutLittle32(out + 0x04U, 4096U);
    PutLittle32(out + 0x18U, 2U);
    PutLittle32(out + 0x20U, 32768U);
    PutLittle32(out + 0x28U, 1024U);
    out[0x38U] = 0x53U;
    out[0x39U] = 0xefU;
    PutLittle32(out + 0x4cU, 1U);
    PutLittle32(out + 0x60U, 0x40U);
}

int main(int argc, char **argv)
{
    if (argc != 2) {
        fputs("Choose present, partition-too-short, unknown-signature, or volume-too-large.\n", stderr);
        return 2;
    }

    /* The geometry is a supplied teaching observation. No GPT table or
     * real disk is read, and no image file is allocated. */
    const UmiGptImageInfo image = {
        .partitions = 1U, .logicalBlockBytes = 512U,
        .firstUsableLba = 34U, .lastUsableLba = 599900U
    };
    UmiGptPartitionInfo partition = {.slot = 2U, .firstLba = 2048U, .lastLba = 400000U};
    HeaderFixture fixture = {0};
    PrepareHeader(fixture.bytes);

    /* Keep the same bytes for the too-short case. Its last admitted LBA
     * changes the right to read those bytes, not the allocation. */
    UmiStatus expected = UMI_STATUS_OK;
    unsigned expectedReads = 1U;
    const char *outcome = "header accepted";
    if (strcmp(argv[1], "partition-too-short") == 0) {
        partition.lastLba = 2050U;
        expected = UMI_STATUS_PARSE_ERROR;
        expectedReads = 0U;
        outcome = "partition refused before reading the header";
    } else if (strcmp(argv[1], "unknown-signature") == 0) {
        fixture.bytes[0x38U] = 0U;
        expected = UMI_STATUS_NOT_FOUND;
        outcome = "header read, but ext-family signature absent";
    } else if (strcmp(argv[1], "volume-too-large") == 0) {
        /* Four 512-byte logical blocks fit the header. The volume size
         * recorded in that header still needs a much larger partition. */
        partition.lastLba = 2051U;
        expected = UMI_STATUS_PARSE_ERROR;
        outcome = "header read, but filesystem volume exceeds partition";
    } else if (strcmp(argv[1], "present") != 0) {
        fputs("Unknown header scenario.\n", stderr);
        return 2;
    }

    /* A distinctive value makes any publication on refusal observable. */
    UmiGptFilesystemInfo observed = {
        .kind = UMI_GPT_FILESYSTEM_FAT32_BPB, .filesystemBlockBytes = 123U,
        .volumeBytes = 987U, .fatClusterSectors = 17U, .extIncompatibleFeatures = 29U
    };
    const UmiStatus status = UmiGptPartitionProbeFilesystem(ReadHeader, &fixture,
        UINT64_C(307200000), &image, &partition, UMI_GPT_FILESYSTEM_EXT_SUPERBLOCK, &observed);
    if (status != expected || fixture.calls != expectedReads || fixture.outside) {
        fprintf(stderr, "Unexpected status or read count: status=%d reads=%u\n", (int)status, fixture.calls);
        return 1;
    }
    printf("%s; reads=%u\n", outcome, fixture.calls);
    if (status == UMI_STATUS_OK) {
        if (observed.kind != UMI_GPT_FILESYSTEM_EXT_SUPERBLOCK ||
            observed.filesystemBlockBytes != 4096U || observed.volumeBytes != UINT64_C(16777216) ||
            observed.extIncompatibleFeatures != UINT32_C(0x40))
            return 1;
        printf("filesystem block=%" PRIu32 " bytes; volume=%" PRIu64 " bytes\n",
            observed.filesystemBlockBytes, observed.volumeBytes);
    } else {
        if (observed.kind != UMI_GPT_FILESYSTEM_FAT32_BPB ||
            observed.filesystemBlockBytes != 123U || observed.volumeBytes != 987U ||
            observed.fatClusterSectors != 17U || observed.extIncompatibleFeatures != 29U)
            return 1;
        puts("previous observation unchanged");
    }
    return 0;
}
