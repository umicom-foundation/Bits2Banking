/*-----------------------------------------------------------------------------
 * Bits2Banking — Device Tree Inspector
 * File: labs/native/device-tree-inspector/fdt.c
 * PURPOSE: Decode FDT headers, structure tokens, and one MMIO description.
 * AUTHOR AND ORGANISATION: Sammy Hegab, Umicom Foundation
 * LICENCE: MIT
 *---------------------------------------------------------------------------*/
#include "fdt.h"
#include <limits.h>
#include <string.h>

#define FDT_MAGIC 0xd00dfeedU
#define FDT_BEGIN_NODE 1U
#define FDT_END_NODE 2U
#define FDT_PROP 3U
#define FDT_NOP 4U
#define FDT_END 9U
#define FDT_HEADER_BYTES 40U

typedef struct FdtFrame {
    int childStarted;
    int hasCompatible;
    int hasRegister;
    int matchesVirtioMmio;
    uint64_t deviceBase;
    uint64_t deviceBytes;
} FdtFrame;

static uint32_t Read32(const unsigned char *data)
{
    return ((uint32_t)data[0] << 24U) | ((uint32_t)data[1] << 16U) |
           ((uint32_t)data[2] << 8U) | (uint32_t)data[3];
}
static uint64_t Read64(const unsigned char *data)
{
    return ((uint64_t)Read32(data) << 32U) | (uint64_t)Read32(data + 4U);
}
static int Span(size_t offset, size_t bytes, size_t total)
{
    return offset <= total && bytes <= total - offset;
}
static int Overlap(size_t left, size_t leftBytes, size_t right, size_t rightBytes)
{
    return left < right ? right - left < leftBytes : left - right < rightBytes;
}
static int Align4(size_t value, size_t limit, size_t *aligned)
{
    if (value > limit || value > SIZE_MAX - 3U) return 0;
    const size_t result = (value + 3U) & ~(size_t)3U;
    if (result > limit) return 0;
    *aligned = result;
    return 1;
}
static int NameCharacter(unsigned char value)
{
    return (value >= 'a' && value <= 'z') ||
           (value >= 'A' && value <= 'Z') ||
           (value >= '0' && value <= '9') ||
           value == '#' || value == '_' || value == '-' ||
           value == '.' || value == ',' || value == '+' || value == '@';
}
static int NameValid(const unsigned char *name, size_t bytes, int root)
{
    if (bytes == 0U) return root;
    if (bytes > 96U) return 0;
    for (size_t i = 0U; i < bytes; ++i)
        if (!NameCharacter(name[i])) return 0;
    return 1;
}
static int CompatibleContains(const unsigned char *data, size_t bytes,
                              const char *wanted, int *found)
{
    if (bytes == 0U) return 0;
    const size_t wantedBytes = strlen(wanted);
    *found = 0;
    for (size_t pos = 0U; pos < bytes;) {
        const unsigned char *ending = memchr(data + pos, 0, bytes - pos);
        if (ending == NULL || ending == data + pos) return 0;
        const size_t itemBytes = (size_t)(ending - (data + pos));
        if (itemBytes == wantedBytes && memcmp(data + pos, wanted, itemBytes) == 0)
            *found = 1;
        pos += itemBytes + 1U;
    }
    return 1;
}
const char *BtbFdtStatusText(BtbFdtStatus status)
{
    switch (status) {
    case BTB_FDT_OK: return "OK";
    case BTB_FDT_INVALID_ARGUMENT: return "Invalid argument";
    case BTB_FDT_TRUNCATED: return "Truncated image";
    case BTB_FDT_MALFORMED: return "Malformed flattened device tree";
    case BTB_FDT_UNSUPPORTED: return "Unsupported format or cell layout";
    case BTB_FDT_LIMIT: return "Educational size or complexity limit";
    }
    return "Unknown status";
}
BtbFdtStatus BtbFdtInspect(const unsigned char *blob, size_t bytes,
                            BtbFdtSummary *outSummary)
{
    if (blob == NULL || outSummary == NULL) return BTB_FDT_INVALID_ARGUMENT;
    if (bytes < FDT_HEADER_BYTES) return BTB_FDT_TRUNCATED;
    if (Read32(blob) != FDT_MAGIC) return BTB_FDT_MALFORMED;
    const uint32_t totalWord = Read32(blob + 4U);
    if ((size_t)totalWord > BTB_FDT_MAX_BYTES) return BTB_FDT_LIMIT;
    const size_t total = (size_t)totalWord;
    if (total < FDT_HEADER_BYTES || total > bytes) return BTB_FDT_TRUNCATED;
    const size_t structure = (size_t)Read32(blob + 8U);
    const size_t strings = (size_t)Read32(blob + 12U);
    const size_t reservations = (size_t)Read32(blob + 16U);
    const uint32_t version = Read32(blob + 20U);
    const uint32_t lastCompatible = Read32(blob + 24U);
    const size_t stringBytes = (size_t)Read32(blob + 32U);
    const size_t structureBytes = (size_t)Read32(blob + 36U);
    if (version < 17U || lastCompatible > 17U || lastCompatible > version)
        return BTB_FDT_UNSUPPORTED;
    if ((structure % 4U) != 0U || (strings % 4U) != 0U ||
        (reservations % 8U) != 0U || reservations < FDT_HEADER_BYTES ||
        !Span(structure, structureBytes, total) ||
        !Span(strings, stringBytes, total) ||
        structureBytes < 12U || stringBytes == 0U ||
        Overlap(structure, structureBytes, strings, stringBytes) ||
        Overlap(0U, FDT_HEADER_BYTES, structure, structureBytes) ||
        Overlap(0U, FDT_HEADER_BYTES, strings, stringBytes))
        return BTB_FDT_MALFORMED;
    /* A reservation table is always a sequence of big-endian 16-byte pairs,
     * terminated by (0,0). Its observed bytes may not overlap either block. */
    size_t reserveCursor = reservations;
    int terminated = 0;
    for (size_t i = 0U; i < 128U; ++i) {
        if (!Span(reserveCursor, 16U, total) ||
            Overlap(reserveCursor, 16U, structure, structureBytes) ||
            Overlap(reserveCursor, 16U, strings, stringBytes)) return BTB_FDT_MALFORMED;
        const uint64_t address = Read64(blob + reserveCursor);
        const uint64_t extent = Read64(blob + reserveCursor + 8U);
        if (address > UINT64_MAX - extent) return BTB_FDT_MALFORMED;
        reserveCursor += 16U;
        if (address == 0U && extent == 0U) { terminated = 1; break; }
    }
    if (!terminated) return BTB_FDT_LIMIT;
    BtbFdtSummary result = {0};
    result.formatVersion = version;
    FdtFrame stack[BTB_FDT_MAX_DEPTH] = {{0}};
    size_t depth = 0U;
    size_t cursor = structure;
    const size_t end = structure + structureBytes;
    int rootOpened = 0;
    int finished = 0;
    while (cursor < end) {
        if (!Span(cursor, 4U, end)) return BTB_FDT_TRUNCATED;
        const uint32_t token = Read32(blob + cursor);
        cursor += 4U;
        if (token == FDT_NOP) continue;
        if (token == FDT_BEGIN_NODE) {
            if (rootOpened && depth == 0U) return BTB_FDT_MALFORMED;
            if (depth == BTB_FDT_MAX_DEPTH || result.nodeCount == BTB_FDT_MAX_NODES)
                return BTB_FDT_LIMIT;
            const unsigned char *ending = memchr(blob + cursor, 0, end - cursor);
            if (ending == NULL) return BTB_FDT_TRUNCATED;
            const size_t nameBytes = (size_t)(ending - (blob + cursor));
            if (!NameValid(blob + cursor, nameBytes, depth == 0U))
                return BTB_FDT_MALFORMED;
            if (depth != 0U) stack[depth - 1U].childStarted = 1;
            if (!Align4(cursor + nameBytes + 1U, end, &cursor))
                return BTB_FDT_TRUNCATED;
            stack[depth++] = (FdtFrame){0};
            ++result.nodeCount;
            rootOpened = 1;
        } else if (token == FDT_PROP) {
            if (depth == 0U || stack[depth - 1U].childStarted)
                return BTB_FDT_MALFORMED;
            if (!Span(cursor, 8U, end)) return BTB_FDT_TRUNCATED;
            const size_t valueBytes = (size_t)Read32(blob + cursor);
            const size_t nameOffset = (size_t)Read32(blob + cursor + 4U);
            cursor += 8U;
            if (!Span(cursor, valueBytes, end) || nameOffset >= stringBytes)
                return BTB_FDT_MALFORMED;
            const unsigned char *name = blob + strings + nameOffset;
            const unsigned char *endName = memchr(name, 0, stringBytes - nameOffset);
            if (endName == NULL || !NameValid(name, (size_t)(endName - name), 0))
                return BTB_FDT_MALFORMED;
            const size_t nameLength = (size_t)(endName - name);
            const unsigned char *value = blob + cursor;
            FdtFrame *frame = &stack[depth - 1U];
            if (depth == 1U && nameLength == 14U &&
                memcmp(name, "#address-cells", 14U) == 0) {
                if (valueBytes != 4U || result.addressCells != 0U) return BTB_FDT_MALFORMED;
                result.addressCells = Read32(value);
            } else if (depth == 1U && nameLength == 11U &&
                       memcmp(name, "#size-cells", 11U) == 0) {
                if (valueBytes != 4U || result.sizeCells != 0U) return BTB_FDT_MALFORMED;
                result.sizeCells = Read32(value);
            } else if (depth == 2U && nameLength == 10U &&
                       memcmp(name, "compatible", 10U) == 0) {
                if (frame->hasCompatible) return BTB_FDT_MALFORMED;
                frame->hasCompatible = 1;
                if (!CompatibleContains(value, valueBytes, "virtio,mmio", &frame->matchesVirtioMmio))
                    return BTB_FDT_MALFORMED;
            } else if (depth == 2U && nameLength == 3U && memcmp(name, "reg", 3U) == 0) {
                if (frame->hasRegister) return BTB_FDT_MALFORMED;
                frame->hasRegister = 1;
                /* This lesson handles one address and size using two 32-bit
                 * cells each; the full Kernel reader supports richer buses. */
                if (valueBytes == 16U) {
                    frame->deviceBase = Read64(value);
                    frame->deviceBytes = Read64(value + 8U);
                } else {
                    frame->deviceBytes = 0U;
                }
            }
            if (++result.propertyCount > BTB_FDT_MAX_PROPERTIES)
                return BTB_FDT_LIMIT;
            if (!Align4(cursor + valueBytes, end, &cursor)) return BTB_FDT_TRUNCATED;
        } else if (token == FDT_END_NODE) {
            if (depth == 0U) return BTB_FDT_MALFORMED;
            const FdtFrame *frame = &stack[depth - 1U];
            if (depth == 2U && frame->matchesVirtioMmio) {
                if (result.addressCells != 2U || result.sizeCells != 2U)
                    return BTB_FDT_UNSUPPORTED;
                if (!frame->hasRegister || frame->deviceBytes == 0U ||
                    frame->deviceBase > UINT64_MAX - frame->deviceBytes)
                    return BTB_FDT_MALFORMED;
                if (result.virtioMmioCount != 0U) return BTB_FDT_UNSUPPORTED;
                result.virtioMmioCount = 1U;
                result.proposedMmioBase = frame->deviceBase;
                result.proposedMmioBytes = frame->deviceBytes;
            }
            --depth;
        } else if (token == FDT_END) {
            if (!rootOpened || depth != 0U) return BTB_FDT_MALFORMED;
            for (size_t i = cursor; i < end; ++i)
                if (blob[i] != 0U) return BTB_FDT_MALFORMED;
            finished = 1;
            break;
        } else {
            return BTB_FDT_UNSUPPORTED;
        }
    }
    if (!finished || result.addressCells != 2U || result.sizeCells != 2U)
        return BTB_FDT_UNSUPPORTED;
    *outSummary = result;
    return BTB_FDT_OK;
}
