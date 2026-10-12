/*-----------------------------------------------------------------------------
 * Bits2Banking — Umicom Foundation
 * File: labs/native/writeback-sector-store/test_block_store.c
 * PURPOSE: Verify write-back, partial flush, restart and bounded image I/O.
 * AUTHOR AND ORGANISATION: Sammy Hegab, Umicom Foundation
 * LICENCE: MIT
 *---------------------------------------------------------------------------*/
#include "block_store.h"
#include <stdio.h>
#include <string.h>

#define REQUIRE(condition) do { if (!(condition)) { \
    fprintf(stderr, "%s:%d failed: %s\n", __FILE__, __LINE__, #condition); return 1; \
} } while (0)

static void Fill(unsigned char block[BTB_SECTOR_BYTES], unsigned char value)
{
    memset(block, value, BTB_SECTOR_BYTES);
}

int main(void)
{
    BtbBlockStore store;
    BtbStorageInit(&store);
    unsigned char a[BTB_SECTOR_BYTES];
    unsigned char b[BTB_SECTOR_BYTES];
    unsigned char observed[BTB_SECTOR_BYTES];
    Fill(a, 0xA1U);
    Fill(b, 0xB2U);
    REQUIRE(BtbStorageRead(NULL, 0U, observed) == BTB_STORAGE_INVALID_ARGUMENT);
    REQUIRE(BtbStorageStage(&store, BTB_SECTOR_COUNT, a) == BTB_STORAGE_INVALID_ARGUMENT);
    REQUIRE(BtbStorageStage(&store, 0U, a) == BTB_STORAGE_OK);
    REQUIRE(BtbStorageStage(&store, 1U, b) == BTB_STORAGE_OK);
    REQUIRE(BtbStorageRead(&store, 0U, observed) == BTB_STORAGE_OK);
    REQUIRE(memcmp(observed, a, BTB_SECTOR_BYTES) == 0);
    REQUIRE(BtbStorageReadStable(&store, 0U, observed) == BTB_STORAGE_OK);
    REQUIRE(observed[0] == 0U);
    BtbFlushReport report = {99U, 99U};
    REQUIRE(BtbStorageFlush(&store, 0U, &report) == BTB_STORAGE_INCOMPLETE);
    REQUIRE(report.sectorsWritten == 0U && report.sectorsRemaining == 2U);
    REQUIRE(BtbStorageFlush(&store, 1U, &report) == BTB_STORAGE_INCOMPLETE);
    REQUIRE(report.sectorsWritten == 1U && report.sectorsRemaining == 1U);
    BtbStorageCrash(&store);
    REQUIRE(!BtbStorageHasDirty(&store));
    REQUIRE(BtbStorageRead(&store, 0U, observed) == BTB_STORAGE_OK);
    REQUIRE(memcmp(observed, a, BTB_SECTOR_BYTES) == 0);
    REQUIRE(BtbStorageRead(&store, 1U, observed) == BTB_STORAGE_OK);
    REQUIRE(observed[0] == 0U); /* Unflushed staged bytes disappeared. */
    REQUIRE(BtbStorageStage(&store, 1U, b) == BTB_STORAGE_OK);
    REQUIRE(BtbStorageFlush(&store, SIZE_MAX, &report) == BTB_STORAGE_OK);
    REQUIRE(report.sectorsWritten == 1U && report.sectorsRemaining == 0U);

    FILE *image = tmpfile();
    REQUIRE(image != NULL);
    REQUIRE(BtbStorageExportStable(&store, image) == BTB_STORAGE_OK);
    REQUIRE(fseek(image, 0L, SEEK_SET) == 0);
    BtbBlockStore imported;
    BtbStorageInit(&imported);
    REQUIRE(BtbStorageImportStable(&imported, image) == BTB_STORAGE_OK);
    REQUIRE(BtbStorageReadStable(&imported, 1U, observed) == BTB_STORAGE_OK);
    REQUIRE(memcmp(observed, b, BTB_SECTOR_BYTES) == 0);
    REQUIRE(fclose(image) == 0);

    /* Import failure leaves every caller-owned byte unchanged. */
    image = tmpfile();
    REQUIRE(image != NULL);
    REQUIRE(fwrite(a, 1U, 19U, image) == 19U);
    REQUIRE(fseek(image, 0L, SEEK_SET) == 0);
    BtbBlockStore snapshot = imported;
    REQUIRE(BtbStorageImportStable(&imported, image) == BTB_STORAGE_IO_ERROR);
    REQUIRE(memcmp(&snapshot, &imported, sizeof(imported)) == 0);
    REQUIRE(fclose(image) == 0);

    /* Reject an additional trailing byte in a nominally complete image. */
    image = tmpfile();
    REQUIRE(image != NULL);
    REQUIRE(BtbStorageExportStable(&store, image) == BTB_STORAGE_OK);
    REQUIRE(fputc('X', image) == (int)'X');
    REQUIRE(fseek(image, 0L, SEEK_SET) == 0);
    REQUIRE(BtbStorageImportStable(&imported, image) == BTB_STORAGE_IO_ERROR);
    REQUIRE(memcmp(&snapshot, &imported, sizeof(imported)) == 0);
    REQUIRE(fclose(image) == 0);

    puts("Write-back sector tests passed: staged, partial flush, crash, exact image, refused import.");
    return 0;
}
