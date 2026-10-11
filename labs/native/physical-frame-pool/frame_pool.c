/*-----------------------------------------------------------------------------
 * Bits2Banking — Physical Frame Ownership Laboratory
 * File: frame_pool.c
 * PURPOSE: Teach frame allocation, reservation and double-release guards.
 * AUTHOR AND ORGANISATION: Sammy Hegab, Umicom Foundation
 * LICENCE: MIT
 *---------------------------------------------------------------------------*/
#include "frame_pool.h"
#include <string.h>

BtbFrameResult BtbFramePoolInit(BtbFramePool *pool, uint64_t startAddress)
{
    if (pool == NULL || (startAddress & (BTB_FRAME_SIZE - 1U)) != 0U)
        return BTB_FRAME_INVALID;
    if (startAddress > UINT64_MAX - BTB_FRAME_SIZE * BTB_FRAME_COUNT)
        return BTB_FRAME_OVERFLOW;
    BtbFramePool newPool = {0};
    newPool.startAddress = startAddress;
    for (size_t i = 0U; i < 8U; ++i)
        newPool.states[i] = BTB_FRAME_RESERVED;
    newPool.reservedCount = 8U;
    memcpy(pool, &newPool, sizeof newPool);
    return BTB_FRAME_OK;
}

BtbFrameResult BtbFramePoolReserve(BtbFramePool *pool, size_t first, size_t count)
{
    if (pool == NULL || count == 0U || first >= BTB_FRAME_COUNT ||
        count > BTB_FRAME_COUNT - first)
        return BTB_FRAME_INVALID;
    /* Check every frame before mutating any: refusal is atomic. */
    for (size_t i = first; i < first + count; ++i)
        if (pool->states[i] != BTB_FRAME_FREE)
            return BTB_FRAME_NOT_AVAILABLE;
    for (size_t i = first; i < first + count; ++i)
        pool->states[i] = BTB_FRAME_RESERVED;
    pool->reservedCount += count;
    return BTB_FRAME_OK;
}

BtbFrameResult BtbFramePoolAllocate(BtbFramePool *pool, uint64_t *outAddress)
{
    if (pool == NULL || outAddress == NULL) return BTB_FRAME_INVALID;
    for (size_t i = 0U; i < BTB_FRAME_COUNT; ++i) {
        if (pool->states[i] != BTB_FRAME_FREE) continue;
        pool->states[i] = BTB_FRAME_OWNED;
        ++pool->ownedCount;
        *outAddress = pool->startAddress + i * BTB_FRAME_SIZE;
        return BTB_FRAME_OK;
    }
    return BTB_FRAME_NOT_AVAILABLE;
}

BtbFrameResult BtbFramePoolRelease(BtbFramePool *pool, uint64_t physicalAddress)
{
    if (pool == NULL || physicalAddress < pool->startAddress)
        return BTB_FRAME_INVALID;
    const uint64_t distance = physicalAddress - pool->startAddress;
    if ((distance & (BTB_FRAME_SIZE - 1U)) != 0U ||
        distance >= BTB_FRAME_SIZE * BTB_FRAME_COUNT)
        return BTB_FRAME_INVALID;
    const size_t index = (size_t)(distance / BTB_FRAME_SIZE);
    if (pool->states[index] != BTB_FRAME_OWNED || pool->ownedCount == 0U)
        return BTB_FRAME_NOT_OWNED;
    pool->states[index] = BTB_FRAME_FREE;
    --pool->ownedCount;
    return BTB_FRAME_OK;
}
