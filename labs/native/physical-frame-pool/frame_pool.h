/*-----------------------------------------------------------------------------
 * Bits2Banking — Physical Frame Ownership Laboratory
 * File: frame_pool.h
 * PURPOSE: Track reserved/free/owned 4 KiB frames, without touching RAM.
 * AUTHOR AND ORGANISATION: Sammy Hegab, Umicom Foundation
 * LICENCE: MIT
 *---------------------------------------------------------------------------*/
#ifndef BTB_FRAME_POOL_H
#define BTB_FRAME_POOL_H
#include <stddef.h>
#include <stdint.h>
#define BTB_FRAME_SIZE UINT64_C(4096)
#define BTB_FRAME_COUNT 128U

typedef enum BtbFrameResult {
    BTB_FRAME_OK = 0, BTB_FRAME_INVALID, BTB_FRAME_NOT_AVAILABLE,
    BTB_FRAME_NOT_OWNED, BTB_FRAME_OVERFLOW
} BtbFrameResult;

typedef enum BtbFrameState {
    BTB_FRAME_FREE = 0, BTB_FRAME_OWNED = 1, BTB_FRAME_RESERVED = 2
} BtbFrameState;

typedef struct BtbFramePool {
    uint64_t startAddress;
    uint8_t states[BTB_FRAME_COUNT];
    size_t ownedCount;
    size_t reservedCount;
} BtbFramePool;

/* Initialise 128 frame records; first eight are reserved for educational
 * firmware/boot structures. Zero or misaligned bases are rejected without
 * modifying pool. Addresses are identifiers, not pointers to mapped RAM. */
BtbFrameResult BtbFramePoolInit(BtbFramePool *pool, uint64_t startAddress);
/* Reserve a FREE, consecutive region. All-or-nothing: an occupied frame
 * leaves the entire pool unchanged. */
BtbFrameResult BtbFramePoolReserve(BtbFramePool *pool, size_t first, size_t count);
/* Allocate the lowest-numbered free frame; outAddress unchanged on failure. */
BtbFrameResult BtbFramePoolAllocate(BtbFramePool *pool, uint64_t *outAddress);
/* Release only a frame previously allocated by this pool. */
BtbFrameResult BtbFramePoolRelease(BtbFramePool *pool, uint64_t physicalAddress);
#endif
