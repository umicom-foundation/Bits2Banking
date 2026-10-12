/*-----------------------------------------------------------------------------
 * Bits2Banking — Device Tree Inspector
 * File: labs/native/device-tree-inspector/fdt.h
 * PURPOSE: Inspect a bounded flattened device tree in a hosted C23 laboratory.
 * AUTHOR AND ORGANISATION: Sammy Hegab, Umicom Foundation
 * LICENCE: MIT
 *---------------------------------------------------------------------------*/
#ifndef BTB_FDT_H
#define BTB_FDT_H
#include <stddef.h>
#include <stdint.h>

#define BTB_FDT_MAX_BYTES 65536U
#define BTB_FDT_MAX_NODES 64U
#define BTB_FDT_MAX_PROPERTIES 128U
#define BTB_FDT_MAX_DEPTH 8U

typedef enum BtbFdtStatus {
    BTB_FDT_OK = 0,
    BTB_FDT_INVALID_ARGUMENT,
    BTB_FDT_TRUNCATED,
    BTB_FDT_MALFORMED,
    BTB_FDT_UNSUPPORTED,
    BTB_FDT_LIMIT
} BtbFdtStatus;

typedef struct BtbFdtSummary {
    uint32_t formatVersion;
    uint32_t nodeCount;
    uint32_t propertyCount;
    uint32_t virtioMmioCount;
    uint32_t addressCells;
    uint32_t sizeCells;
    uint64_t proposedMmioBase;
    uint64_t proposedMmioBytes;
} BtbFdtSummary;

/* All inputs are borrowed for this synchronous call. Never dereference an MMIO
 * address described in the blob: this is metadata, NOT access permission.
 * Output is changed only when the entire parse succeeds. */
BtbFdtStatus BtbFdtInspect(const unsigned char *blob, size_t bytes,
                            BtbFdtSummary *outSummary);
const char *BtbFdtStatusText(BtbFdtStatus status);

#endif
