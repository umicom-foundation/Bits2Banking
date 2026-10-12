/*-----------------------------------------------------------------------------
 * Bits2Banking — Device Tree Inspector
 * File: labs/native/device-tree-inspector/main.c
 * PURPOSE: Display one synthetic device-tree discovery observation.
 * AUTHOR AND ORGANISATION: Sammy Hegab, Umicom Foundation
 * LICENCE: MIT
 *---------------------------------------------------------------------------*/
#include "fdt.h"
#include "fixture.h"
#include <inttypes.h>
#include <stdio.h>

int main(void)
{
    unsigned char blob[512];
    const size_t bytes = BtbFdtMakeFixture(blob, sizeof(blob));
    BtbFdtSummary summary = {0};
    if (bytes == 0U || BtbFdtInspect(blob, bytes, &summary) != BTB_FDT_OK) {
        fputs("The synthetic device-tree fixture could not be inspected.\n", stderr);
        return 1;
    }
    printf("FDT format: %" PRIu32 ", nodes: %" PRIu32 ", properties: %" PRIu32 "\n",
           summary.formatVersion, summary.nodeCount, summary.propertyCount);
    printf("VirtIO MMIO candidates: %" PRIu32 "\n", summary.virtioMmioCount);
    printf("Advertised address: 0x%" PRIx64 ", extent: %" PRIu64 " bytes\n",
           summary.proposedMmioBase, summary.proposedMmioBytes);
    puts("An advertised address is not permission to access hardware.");
    return 0;
}
