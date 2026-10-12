/*-----------------------------------------------------------------------------
 * Bits2Banking — Device Tree Inspector
 * File: labs/native/device-tree-inspector/fixture.c
 * PURPOSE: Emit canonical big-endian FDT teaching fixture, never real firmware.
 * AUTHOR AND ORGANISATION: Sammy Hegab, Umicom Foundation
 * LICENCE: MIT
 *---------------------------------------------------------------------------*/
#include "fixture.h"
#include <string.h>

#define FIXTURE_RESERVATION_START 40U
#define FIXTURE_STRUCTURE_START 56U
#define TOKEN_BEGIN_NODE 1U
#define TOKEN_END_NODE 2U
#define TOKEN_PROPERTY 3U
#define TOKEN_END 9U

void BtbFdtWriteBe32(unsigned char *out, uint32_t value)
{
    out[0] = (unsigned char)(value >> 24U);
    out[1] = (unsigned char)(value >> 16U);
    out[2] = (unsigned char)(value >> 8U);
    out[3] = (unsigned char)value;
}
static void WriteWord(unsigned char *out, size_t *cursor, uint32_t word)
{
    BtbFdtWriteBe32(out + *cursor, word);
    *cursor += 4U;
}
static void WriteProperty(unsigned char *out, size_t *cursor,
                          uint32_t nameOffset, const void *value, size_t bytes)
{
    WriteWord(out, cursor, TOKEN_PROPERTY);
    WriteWord(out, cursor, (uint32_t)bytes);
    WriteWord(out, cursor, nameOffset);
    memcpy(out + *cursor, value, bytes);
    *cursor += bytes;
    while ((*cursor & 3U) != 0U) out[(*cursor)++] = 0U;
}
size_t BtbFdtMakeFixture(unsigned char *output, size_t capacity)
{
    if (output == NULL || capacity < 512U) return 0U;
    memset(output, 0, capacity);
    const char strings[] = "#address-cells\0#size-cells\0compatible\0reg\0";
    /* Offsets identify strings, not null-terminated fields in a C struct. */
    const uint32_t addressName = 0U;
    const uint32_t sizeName = 15U;
    const uint32_t compatibleName = 27U;
    const uint32_t regName = 38U;
    size_t cursor = FIXTURE_STRUCTURE_START;
    const unsigned char cells[] = {0, 0, 0, 2};
    WriteWord(output, &cursor, TOKEN_BEGIN_NODE);
    WriteWord(output, &cursor, 0U); /* root node: empty name + 4-byte padding */
    WriteProperty(output, &cursor, addressName, cells, sizeof(cells));
    WriteProperty(output, &cursor, sizeName, cells, sizeof(cells));
    WriteWord(output, &cursor, TOKEN_BEGIN_NODE);
    const char node[] = "virtio_block@10001000";
    memcpy(output + cursor, node, sizeof(node));
    cursor += sizeof(node);
    while ((cursor & 3U) != 0U) output[cursor++] = 0U;
    const char compatible[] = "virtio,mmio";
    WriteProperty(output, &cursor, compatibleName, compatible, sizeof(compatible));
    const unsigned char reg[] = {
        0, 0, 0, 0, 0x10, 0, 0x10, 0, /* 0x0000000010001000 */
        0, 0, 0, 0, 0, 0, 0x10, 0      /* 4096 bytes */
    };
    WriteProperty(output, &cursor, regName, reg, sizeof(reg));
    WriteWord(output, &cursor, TOKEN_END_NODE);
    WriteWord(output, &cursor, TOKEN_END_NODE);
    WriteWord(output, &cursor, TOKEN_END);
    const size_t structureBytes = cursor - FIXTURE_STRUCTURE_START;
    const size_t stringsOffset = cursor;
    memcpy(output + cursor, strings, sizeof(strings));
    cursor += sizeof(strings);
    if (cursor > capacity) return 0U;
    BtbFdtWriteBe32(output, 0xd00dfeedU);
    BtbFdtWriteBe32(output + 4U, (uint32_t)cursor);
    BtbFdtWriteBe32(output + 8U, FIXTURE_STRUCTURE_START);
    BtbFdtWriteBe32(output + 12U, (uint32_t)stringsOffset);
    BtbFdtWriteBe32(output + 16U, FIXTURE_RESERVATION_START);
    BtbFdtWriteBe32(output + 20U, 17U);
    BtbFdtWriteBe32(output + 24U, 16U);
    BtbFdtWriteBe32(output + 28U, 0U);
    BtbFdtWriteBe32(output + 32U, (uint32_t)sizeof(strings));
    BtbFdtWriteBe32(output + 36U, (uint32_t)structureBytes);
    return cursor;
}
