/*-----------------------------------------------------------------------------
 * Bits2Banking — Umicom Foundation
 * File: labs/native/writeback-sector-store/block_store.h
 * PURPOSE: Teach staged writes, simulated stable sectors, explicit flush and
 *          crash recovery using fixed-size, caller-owned C23 storage.
 * AUTHOR AND ORGANISATION: Sammy Hegab, Umicom Foundation
 * LICENCE: MIT
 *---------------------------------------------------------------------------*/
#ifndef BTB_BLOCK_STORE_H
#define BTB_BLOCK_STORE_H

#include <stddef.h>
#include <stdint.h>
#include <stdio.h>

#define BTB_SECTOR_BYTES 512U
#define BTB_SECTOR_COUNT 4U

typedef enum BtbStorageStatus {
    BTB_STORAGE_OK = 0,
    BTB_STORAGE_INVALID_ARGUMENT,
    BTB_STORAGE_INCOMPLETE,
    BTB_STORAGE_IO_ERROR
} BtbStorageStatus;

typedef struct BtbBlockStore {
    /* 'stable' represents durable sectors ONLY inside the simulation. Real
     * power-loss durability needs a device and a reviewed persistence path. */
    unsigned char stable[BTB_SECTOR_COUNT][BTB_SECTOR_BYTES];
    unsigned char staged[BTB_SECTOR_COUNT][BTB_SECTOR_BYTES];
    unsigned char dirty[BTB_SECTOR_COUNT];
} BtbBlockStore;

typedef struct BtbFlushReport {
    size_t sectorsWritten;
    size_t sectorsRemaining;
} BtbFlushReport;

void BtbStorageInit(BtbBlockStore *store);
BtbStorageStatus BtbStorageStage(BtbBlockStore *store, size_t sector,
                                  const unsigned char data[BTB_SECTOR_BYTES]);
BtbStorageStatus BtbStorageRead(const BtbBlockStore *store, size_t sector,
                                 unsigned char output[BTB_SECTOR_BYTES]);
BtbStorageStatus BtbStorageReadStable(const BtbBlockStore *store, size_t sector,
                                       unsigned char output[BTB_SECTOR_BYTES]);
/* maxSectors == SIZE_MAX writes all dirty sectors; smaller values inject a
 * bounded partial flush. A PARTIAL outcome is not a successful durability
 * acknowledgment. The caller must preserve uncertainty until recovery. */
BtbStorageStatus BtbStorageFlush(BtbBlockStore *store, size_t maxSectors,
                                  BtbFlushReport *report);
void BtbStorageCrash(BtbBlockStore *store);
int BtbStorageHasDirty(const BtbBlockStore *store);
/* These read/write only the simulated stable image. FILE* ownership stays with
 * the caller. Export writes through libc and fflush; it is NOT fsync or a power
 * loss guarantee. Import is failure-atomic for the BtbBlockStore object. */
BtbStorageStatus BtbStorageExportStable(const BtbBlockStore *store, FILE *stream);
BtbStorageStatus BtbStorageImportStable(BtbBlockStore *store, FILE *stream);

#endif
