/*-----------------------------------------------------------------------------
 * Umicom Bits2Banking
 * File: labs/native/framework-gpt-inspection/image.c
 *
 * PURPOSE:
 *   Construct bounded synthetic GPT bytes and isolated malformed examples for teaching.
 *
 * AUTHOR AND ORGANISATION:
 * Sammy Hegab
 * Umicom Foundation
 *
 * LICENCE:
 * MIT
 *---------------------------------------------------------------------------*/


#include "lab.h"
#include <stdlib.h>
#include <string.h>

#define LAB_IMAGE_BYTES (512U * 1024U)
static void Put32(unsigned char *p, uint32_t value)
{
    for (unsigned i = 0U; i < 4U; ++i) p[i] = (unsigned char)(value >> (8U * i));
}
static void Put64(unsigned char *p, uint64_t value)
{
    for (unsigned i = 0U; i < 8U; ++i) p[i] = (unsigned char)(value >> (8U * i));
}
/* This encoder calculates checksums for synthetic records. Interpretation and
 * validation remain in Framework; a valid checksum does not admit a layout. */
static uint32_t Crc(const unsigned char *bytes, size_t length)
{
    uint32_t value = UINT32_MAX;
    for (size_t i = 0U; i < length; ++i) {
        value ^= bytes[i];
        for (unsigned bit = 0U; bit < 8U; ++bit)
            value = (value & 1U) ? (value >> 1U) ^ UINT32_C(0xedb88320) : value >> 1U;
    }
    return ~value;
}
static void Seal(LabImage *image, uint32_t width)
{
    uint64_t sectors = image->length / image->block;
    uint64_t reserve = 16384U / image->block;
    unsigned char *entries = image->bytes + 2U * image->block;
    size_t length = (size_t)4U * width;
    uint32_t crc = Crc(entries, length);
    memcpy(image->bytes + (sectors - 1U - reserve) * image->block, entries, length);
    for (unsigned b = 0U; b < 2U; ++b) {
        unsigned char *h = image->bytes + (b ? sectors - 1U : 1U) * image->block;
        Put32(h + 84U, width); Put32(h + 88U, crc); Put32(h + 16U, 0U);
        Put32(h + 16U, Crc(h, 92U));
    }
}
int LabImageCreate(LabImage *image, uint32_t block)
{
    if (image == NULL || image->bytes != NULL || (block != 512U && block != 4096U)) return 0;
    unsigned char *bytes = calloc(1U, LAB_IMAGE_BYTES);
    if (bytes == NULL) return 0;
    LabImage candidate = { .bytes = bytes, .length = LAB_IMAGE_BYTES, .block = block };
    uint64_t sectors = candidate.length / block, reserve = 16384U / block;
    uint64_t first = 2U + reserve, last = sectors - 2U - reserve;
    for (unsigned b = 0U; b < 2U; ++b) {
        unsigned char *h = bytes + (b ? sectors - 1U : 1U) * block;
        memcpy(h, "EFI PART", 8U); Put32(h + 8U, UINT32_C(0x10000)); Put32(h + 12U, 92U);
        Put64(h + 24U, b ? sectors - 1U : 1U); Put64(h + 32U, b ? 1U : sectors - 1U);
        Put64(h + 40U, first); Put64(h + 48U, last); h[56U] = 1U;
        Put64(h + 72U, b ? sectors - 1U - reserve : 2U);
        Put32(h + 80U, 4U);
    }
    unsigned char *entry = bytes + 2U * block;
    entry[0U] = 1U; entry[16U] = 2U;
    Put64(entry + 32U, first); Put64(entry + 40U, first + 10U);
    Seal(&candidate, 128U);
    *image = candidate;
    return 1;
}
void LabImageDestroy(LabImage *image)
{
    if (image == NULL) return;
    free(image->bytes);
    memset(image, 0, sizeof(*image));
}
int LabImageChange(LabImage *image, const char *scenario)
{
    if (image == NULL || image->bytes == NULL || scenario == NULL) return 0;
    uint64_t sectors = image->length / image->block, first = 2U + 16384U / image->block;
    unsigned char *primary = image->bytes + image->block;
    unsigned char *backup = image->bytes + (sectors - 1U) * image->block;
    unsigned char *entry = image->bytes + 2U * image->block;
    uint32_t width = 128U;
    if (!strcmp(scenario, "reservation") || !strcmp(scenario, "retry")) {
        Put64(primary + 40U, 3U); Put64(backup + 40U, 3U);
    } else if (!strcmp(scenario, "stride")) width = 384U;
    else if (!strcmp(scenario, "overlap")) {
        memcpy(entry + 128U, entry, 128U); entry[128U + 16U] = 3U;
        Put64(entry + 128U + 32U, first + 10U); Put64(entry + 128U + 40U, first + 20U);
    } else if (!strcmp(scenario, "backup")) backup[56U] = 2U;
    else return 0;
    Seal(image, width);
    return 1;
}
