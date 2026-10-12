/*-----------------------------------------------------------------------------
 * Bits2Banking — Umicom Foundation
 * File: labs/native/writeback-sector-store/main.c
 * PURPOSE: Show that staging a Notes sector is not yet stable storage.
 * AUTHOR AND ORGANISATION: Sammy Hegab, Umicom Foundation
 * LICENCE: MIT
 *---------------------------------------------------------------------------*/
#include "block_store.h"
#include <stdio.h>
#include <string.h>

int main(void)
{
    BtbBlockStore store;
    BtbStorageInit(&store);
    unsigned char sector[BTB_SECTOR_BYTES] = {0};
    memcpy(sector, "Umicom Notes: training checkpoint", 33U);
    if (BtbStorageStage(&store, 1U, sector) != BTB_STORAGE_OK) return 1;
    printf("Staged sector: %s\n", sector);
    unsigned char observed[BTB_SECTOR_BYTES];
    if (BtbStorageReadStable(&store, 1U, observed) != BTB_STORAGE_OK) return 1;
    printf("Stable before flush: %s\n", observed[0] == 0U ? "(empty)" : "unexpected");
    BtbFlushReport report;
    if (BtbStorageFlush(&store, SIZE_MAX, &report) != BTB_STORAGE_OK) return 1;
    BtbStorageCrash(&store);
    if (BtbStorageRead(&store, 1U, observed) != BTB_STORAGE_OK) return 1;
    printf("Stable after flush and restart: %s\n", observed);
    printf("Sectors acknowledged by simulated flush: %zu\n", report.sectorsWritten);
    return 0;
}
