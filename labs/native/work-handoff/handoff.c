/*-----------------------------------------------------------------------------
 * Bits2Banking | Umicom Foundation
 * File: labs/native/work-handoff/handoff.c
 * PURPOSE: Single-owner bounded handoff; no threads or shared mutable buffers.
 * AUTHOR: Sammy Hegab | LICENCE: MIT
 *---------------------------------------------------------------------------*/
#include "handoff.h"
#include <string.h>
#include <stdint.h>

static BtbWorkItem *BtbWorkResolve(BtbWorkQueue *queue, BtbWorkToken token)
{
    if (queue == NULL || token.slot >= BTB_WORK_CAPACITY || token.generation == 0U)
        return NULL;
    BtbWorkItem *item = &queue->items[token.slot];
    if (item->generation != token.generation || item->state == BTB_WORK_FREE)
        return NULL;
    return item;
}

BtbWorkResult BtbWorkInit(BtbWorkQueue *queue, size_t maxActive)
{
    if (queue == NULL || maxActive == 0U || maxActive > BTB_WORK_CAPACITY)
        return BTB_WORK_INVALID;
    memset(queue, 0, sizeof(*queue));
    queue->maxActive = maxActive;
    return BTB_WORK_OK;
}

BtbWorkResult BtbWorkSubmit(BtbWorkQueue *queue, uint64_t connectionId,
                            const void *bytes, size_t length, BtbWorkToken *token)
{
    if (queue == NULL || token == NULL || connectionId == 0U ||
        bytes == NULL || length == 0U || length > BTB_WORK_BYTES)
        return BTB_WORK_INVALID;
    if (queue->quiescing) return BTB_WORK_SHUTDOWN;
    if (queue->queued == BTB_WORK_CAPACITY) return BTB_WORK_FULL;
    for (uint32_t i = 0U; i < BTB_WORK_CAPACITY; ++i) {
        BtbWorkItem *item = &queue->items[i];
        if (item->state != BTB_WORK_FREE) continue;
        /* Retain the generation across release to reject late callbacks. */
        if (item->generation == UINT64_MAX) return BTB_WORK_BUSY;
        ++item->generation;
        item->state = BTB_WORK_QUEUED;
        item->connectionId = connectionId;
        item->length = length;
        memcpy(item->payload, bytes, length);
        const size_t tail = (queue->head + queue->queued) % BTB_WORK_CAPACITY;
        queue->waiting[tail] = i;
        ++queue->queued;
        *token = (BtbWorkToken){i, item->generation};
        return BTB_WORK_OK;
    }
    return BTB_WORK_FULL;
}

BtbWorkResult BtbWorkAcquire(BtbWorkQueue *queue, BtbWorkToken *token,
                             const BtbWorkItem **borrowedItem)
{
    if (queue == NULL || token == NULL || borrowedItem == NULL)
        return BTB_WORK_INVALID;
    *borrowedItem = NULL;
    if (queue->queued == 0U || queue->active >= queue->maxActive)
        return BTB_WORK_BUSY;
    const uint32_t slot = queue->waiting[queue->head];
    queue->head = (queue->head + 1U) % BTB_WORK_CAPACITY;
    --queue->queued;
    BtbWorkItem *item = &queue->items[slot];
    if (item->state != BTB_WORK_QUEUED) return BTB_WORK_INVALID;
    item->state = BTB_WORK_ACTIVE;
    ++queue->active;
    *token = (BtbWorkToken){slot, item->generation};
    *borrowedItem = item;
    return BTB_WORK_OK;
}

BtbWorkResult BtbWorkComplete(BtbWorkQueue *queue, BtbWorkToken token)
{
    BtbWorkItem *item = BtbWorkResolve(queue, token);
    if (item == NULL) return BTB_WORK_STALE;
    if (item->state != BTB_WORK_ACTIVE) return BTB_WORK_INVALID;
    item->state = BTB_WORK_COMPLETE;
    --queue->active;
    return BTB_WORK_OK;
}

BtbWorkResult BtbWorkCancel(BtbWorkQueue *queue, BtbWorkToken token)
{
    BtbWorkItem *item = BtbWorkResolve(queue, token);
    if (item == NULL) return BTB_WORK_STALE;
    if (item->state == BTB_WORK_ACTIVE) {
        --queue->active;
    } else if (item->state == BTB_WORK_QUEUED) {
        /* Remove the queued item without breaking FIFO ordering of survivors. */
        size_t found = queue->queued;
        for (size_t i = 0U; i < queue->queued; ++i) {
            if (queue->waiting[(queue->head + i) % BTB_WORK_CAPACITY] == token.slot) {
                found = i;
                break;
            }
        }
        if (found == queue->queued) return BTB_WORK_INVALID;
        for (size_t i = found; i + 1U < queue->queued; ++i) {
            queue->waiting[(queue->head + i) % BTB_WORK_CAPACITY] =
                queue->waiting[(queue->head + i + 1U) % BTB_WORK_CAPACITY];
        }
        --queue->queued;
    } else {
        return BTB_WORK_INVALID;
    }
    item->state = BTB_WORK_CANCELLED;
    return BTB_WORK_OK;
}

BtbWorkResult BtbWorkRelease(BtbWorkQueue *queue, BtbWorkToken token)
{
    BtbWorkItem *item = BtbWorkResolve(queue, token);
    if (item == NULL) return BTB_WORK_STALE;
    if (item->state != BTB_WORK_COMPLETE && item->state != BTB_WORK_CANCELLED)
        return BTB_WORK_BUSY;
    const uint64_t generation = item->generation;
    memset(item, 0, sizeof(*item));
    item->generation = generation;
    return BTB_WORK_OK;
}

void BtbWorkQuiesce(BtbWorkQueue *queue)
{
    if (queue != NULL) queue->quiescing = 1;
}

int BtbWorkDrained(const BtbWorkQueue *queue)
{
    return queue != NULL && queue->quiescing &&
           queue->queued == 0U && queue->active == 0U;
}

int BtbWorkInvariants(const BtbWorkQueue *queue)
{
    if (queue == NULL || queue->maxActive == 0U ||
        queue->maxActive > BTB_WORK_CAPACITY ||
        queue->queued > BTB_WORK_CAPACITY || queue->active > queue->maxActive ||
        queue->head >= BTB_WORK_CAPACITY) return 0;
    size_t queued = 0U, active = 0U;
    for (size_t i = 0U; i < BTB_WORK_CAPACITY; ++i) {
        if (queue->items[i].state == BTB_WORK_QUEUED) ++queued;
        if (queue->items[i].state == BTB_WORK_ACTIVE) ++active;
    }
    if (queued != queue->queued || active != queue->active) return 0;
    for (size_t i = 0U; i < queue->queued; ++i) {
        const uint32_t slot = queue->waiting[(queue->head + i) % BTB_WORK_CAPACITY];
        if (slot >= BTB_WORK_CAPACITY || queue->items[slot].state != BTB_WORK_QUEUED)
            return 0;
        for (size_t j = i + 1U; j < queue->queued; ++j)
            if (slot == queue->waiting[(queue->head + j) % BTB_WORK_CAPACITY]) return 0;
    }
    return 1;
}
