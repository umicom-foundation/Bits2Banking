/*-----------------------------------------------------------------------------
 * Bits2Banking — Umicom Foundation
 * File: labs/native/writeback-sector-store/block_store.c
 * PURPOSE: A portable, deterministic write-back sector model in C23.
 * AUTHOR AND ORGANISATION: Sammy Hegab, Umicom Foundation
 * LICENCE: MIT
 *---------------------------------------------------------------------------*/
#include "block_store.h"
#include <string.h>

void BtbStorageInit(BtbBlockStore *store)
{
    if (store != NULL) {
        memset(store, 0, sizeof(*store));
    }
}

BtbStorageStatus BtbStorageStage(BtbBlockStore *store, size_t sector,
                                  const unsigned char data[BTB_SECTOR_BYTES])
{
    if (store == NULL || data == NULL || sector >= BTB_SECTOR_COUNT) {
        return BTB_STORAGE_INVALID_ARGUMENT;
    }
    /* A full-sector copy avoids exposing partial writes to the model. Real
     * device sectors can tear, so this is a pedagogical assumption. */
    memcpy(store->staged[sector], data, BTB_SECTOR_BYTES);
    store->dirty[sector] = 1U;
    return BTB_STORAGE_OK;
}

BtbStorageStatus BtbStorageReadStable(const BtbBlockStore *store, size_t sector,
                                       unsigned char output[BTB_SECTOR_BYTES])
{
    if (store == NULL || output == NULL || sector >= BTB_SECTOR_COUNT) {
        return BTB_STORAGE_INVALID_ARGUMENT;
    }
    memcpy(output, store->stable[sector], BTB_SECTOR_BYTES);
    return BTB_STORAGE_OK;
}

BtbStorageStatus BtbStorageRead(const BtbBlockStore *store, size_t sector,
                                 unsigned char output[BTB_SECTOR_BYTES])
{
    if (store == NULL || output == NULL || sector >= BTB_SECTOR_COUNT) {
        return BTB_STORAGE_INVALID_ARGUMENT;
    }
    memcpy(output, store->dirty[sector] != 0U ? store->staged[sector] : store->stable[sector],
           BTB_SECTOR_BYTES);
    return BTB_STORAGE_OK;
}

int BtbStorageHasDirty(const BtbBlockStore *store)
{
    if (store == NULL) return 0;
    for (size_t i = 0U; i < BTB_SECTOR_COUNT; ++i) {
        if (store->dirty[i] != 0U) return 1;
    }
    return 0;
}

BtbStorageStatus BtbStorageFlush(BtbBlockStore *store, size_t maxSectors,
                                  BtbFlushReport *report)
{
    if (store == NULL || report == NULL) return BTB_STORAGE_INVALID_ARGUMENT;
    /* Write order is deterministic. A failure budget can stop after some
     * sectors have reached the simulation's stable copy. */
    BtbFlushReport next = {0U, 0U};
    for (size_t i = 0U; i < BTB_SECTOR_COUNT; ++i) {
        if (store->dirty[i] == 0U) continue;
        if (next.sectorsWritten < maxSectors) {
            memcpy(store->stable[i], store->staged[i], BTB_SECTOR_BYTES);
            store->dirty[i] = 0U;
            ++next.sectorsWritten;
        } else {
            ++next.sectorsRemaining;
        }
    }
    *report = next;
    return next.sectorsRemaining == 0U ? BTB_STORAGE_OK : BTB_STORAGE_INCOMPLETE;
}

void BtbStorageCrash(BtbBlockStore *store)
{
    if (store == NULL) return;
    /* This simulates a restart. Changes that were never flushed disappear;
     * no actual power loss or host filesystem is involved. */
    memcpy(store->staged, store->stable, sizeof(store->stable));
    memset(store->dirty, 0, sizeof(store->dirty));
}

BtbStorageStatus BtbStorageExportStable(const BtbBlockStore *store, FILE *stream)
{
    if (store == NULL || stream == NULL) return BTB_STORAGE_INVALID_ARGUMENT;
    for (size_t i = 0U; i < BTB_SECTOR_COUNT; ++i) {
        if (fwrite(store->stable[i], 1U, BTB_SECTOR_BYTES, stream) != BTB_SECTOR_BYTES) {
            return BTB_STORAGE_IO_ERROR;
        }
    }
    return fflush(stream) == 0 ? BTB_STORAGE_OK : BTB_STORAGE_IO_ERROR;
}

BtbStorageStatus BtbStorageImportStable(BtbBlockStore *store, FILE *stream)
{
    if (store == NULL || stream == NULL) return BTB_STORAGE_INVALID_ARGUMENT;
    /* Parse into a separate candidate and publish it only after exactly
     * BTB_SECTOR_COUNT full sectors and a clean EOF have been established. */
    BtbBlockStore candidate;
    BtbStorageInit(&candidate);
    for (size_t i = 0U; i < BTB_SECTOR_COUNT; ++i) {
        if (fread(candidate.stable[i], 1U, BTB_SECTOR_BYTES, stream) != BTB_SECTOR_BYTES) {
            return BTB_STORAGE_IO_ERROR;
        }
    }
    const int next = fgetc(stream);
    if (next != EOF || ferror(stream) != 0) return BTB_STORAGE_IO_ERROR;
    memcpy(candidate.staged, candidate.stable, sizeof(candidate.stable));
    *store = candidate;
    return BTB_STORAGE_OK;
}
