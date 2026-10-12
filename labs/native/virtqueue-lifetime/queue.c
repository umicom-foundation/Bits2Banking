/*-----------------------------------------------------------------------------
 * Bits2Banking — Virtqueue Lifetime Laboratory
 * File: labs/native/virtqueue-lifetime/queue.c
 * PURPOSE: Retain simulated request buffers until completion or reset ACK.
 * AUTHOR AND ORGANISATION: Sammy Hegab, Umicom Foundation
 * LICENCE: MIT
 *---------------------------------------------------------------------------*/
#include "queue.h"
#include <limits.h>
#include <string.h>

static uint64_t Token(uint32_t index, uint32_t generation)
{
    return ((uint64_t)generation << 32U) | (uint64_t)(index + 1U);
}
static BtbVqStatus Find(BtbVq *queue, uint64_t token, BtbVqSlot **slot)
{
    const uint32_t word = (uint32_t)token;
    const uint32_t generation = (uint32_t)(token >> 32U);
    if (word == 0U || word > BTB_VQ_SLOT_COUNT || generation == 0U)
        return BTB_VQ_STALE_TOKEN;
    BtbVqSlot *found = &queue->slots[word - 1U];
    if (found->stage == BTB_VQ_FREE || found->stage == BTB_VQ_RETIRED ||
        found->generation != generation) return BTB_VQ_STALE_TOKEN;
    *slot = found;
    return BTB_VQ_OK;
}
static void ClearSlot(BtbVqSlot *slot)
{
    const uint32_t priorGeneration = slot->generation;
    /* The entire copied payload and owner metadata is scrubbed, including
     * unused capacity. Retirement refuses generation wrap/ABA reuse. */
    memset(slot, 0, sizeof(*slot));
    if (priorGeneration == UINT32_MAX) {
        slot->generation = UINT32_MAX;
        slot->stage = BTB_VQ_RETIRED;
    } else {
        slot->generation = priorGeneration + 1U;
        slot->stage = BTB_VQ_FREE;
    }
}
void BtbVqInit(BtbVq *queue)
{
    if (queue == NULL) return;
    memset(queue, 0, sizeof(*queue));
    for (size_t i = 0U; i < BTB_VQ_SLOT_COUNT; ++i)
        queue->slots[i].generation = 1U;
}
BtbVqStatus BtbVqPrepare(BtbVq *queue, uint32_t owner,
                         const void *bytes, size_t length, uint64_t *outToken)
{
    if (queue == NULL || owner == 0U || bytes == NULL || outToken == NULL ||
        length == 0U || length > BTB_VQ_PAYLOAD_CAPACITY) return BTB_VQ_INVALID_ARGUMENT;
    if (queue->resetPending) return BTB_VQ_BUSY;
    for (uint32_t i = 0U; i < BTB_VQ_SLOT_COUNT; ++i) {
        BtbVqSlot *slot = &queue->slots[i];
        if (slot->stage == BTB_VQ_FREE) {
            memcpy(slot->payload, bytes, length);
            slot->owner = owner;
            slot->payloadBytes = (uint32_t)length;
            slot->stage = BTB_VQ_PREPARED;
            *outToken = Token(i, slot->generation);
            return BTB_VQ_OK;
        }
    }
    return BTB_VQ_FULL;
}
BtbVqStatus BtbVqPublish(BtbVq *queue, uint32_t owner, uint64_t token)
{
    if (queue == NULL || owner == 0U) return BTB_VQ_INVALID_ARGUMENT;
    if (queue->resetPending) return BTB_VQ_BUSY;
    BtbVqSlot *slot = NULL;
    BtbVqStatus status = Find(queue, token, &slot);
    if (status != BTB_VQ_OK) return status;
    if (slot->owner != owner) return BTB_VQ_WRONG_OWNER;
    if (slot->stage != BTB_VQ_PREPARED) return BTB_VQ_WRONG_STATE;
    if (queue->availableCount >= BTB_VQ_SLOT_COUNT) return BTB_VQ_FULL;
    /* Publication grants the simulated device access to this copied slot.
     * Software must retain the slot until completion or confirmed reset. */
    const uint32_t tail = (queue->availableHead + queue->availableCount) % BTB_VQ_SLOT_COUNT;
    queue->available[tail] = token;
    ++queue->availableCount;
    slot->stage = BTB_VQ_PUBLISHED;
    return BTB_VQ_OK;
}
BtbVqStatus BtbVqCancelRequested(BtbVq *queue, uint32_t owner, uint64_t token)
{
    if (queue == NULL || owner == 0U) return BTB_VQ_INVALID_ARGUMENT;
    if (queue->resetPending) return BTB_VQ_BUSY;
    BtbVqSlot *slot = NULL;
    BtbVqStatus status = Find(queue, token, &slot);
    if (status != BTB_VQ_OK) return status;
    if (slot->owner != owner) return BTB_VQ_WRONG_OWNER;
    if (slot->stage != BTB_VQ_PUBLISHED) return BTB_VQ_WRONG_STATE;
    slot->cancelRequested = 1;
    return BTB_VQ_OK;
}
BtbVqStatus BtbVqSimulateComplete(BtbVq *queue, uint64_t token,
                                  uint32_t deviceStatus, uint32_t completedBytes)
{
    if (queue == NULL) return BTB_VQ_INVALID_ARGUMENT;
    if (queue->resetPending) return BTB_VQ_BUSY;
    BtbVqSlot *slot = NULL;
    BtbVqStatus status = Find(queue, token, &slot);
    if (status != BTB_VQ_OK) return status;
    if (slot->stage != BTB_VQ_PUBLISHED) return BTB_VQ_WRONG_STATE;
    if (queue->availableCount == 0U ||
        queue->available[queue->availableHead] != token) return BTB_VQ_WRONG_ORDER;
    if (completedBytes > slot->payloadBytes || queue->usedCount >= BTB_VQ_SLOT_COUNT)
        return BTB_VQ_INVALID_ARGUMENT;
    queue->available[queue->availableHead] = 0U;
    queue->availableHead = (queue->availableHead + 1U) % BTB_VQ_SLOT_COUNT;
    --queue->availableCount;
    const uint32_t tail = (queue->usedHead + queue->usedCount) % BTB_VQ_SLOT_COUNT;
    queue->used[tail] = token;
    ++queue->usedCount;
    slot->deviceStatus = deviceStatus;
    slot->completedBytes = completedBytes;
    slot->stage = BTB_VQ_COMPLETED;
    return BTB_VQ_OK;
}
BtbVqStatus BtbVqCollect(BtbVq *queue, uint32_t owner,
                         uint64_t token, BtbVqCompletion *outCompletion)
{
    if (queue == NULL || owner == 0U || outCompletion == NULL)
        return BTB_VQ_INVALID_ARGUMENT;
    if (queue->resetPending) return BTB_VQ_BUSY;
    BtbVqSlot *slot = NULL;
    BtbVqStatus status = Find(queue, token, &slot);
    if (status != BTB_VQ_OK) return status;
    if (slot->owner != owner) return BTB_VQ_WRONG_OWNER;
    if (slot->stage != BTB_VQ_COMPLETED) return BTB_VQ_WRONG_STATE;
    if (queue->usedCount == 0U || queue->used[queue->usedHead] != token)
        return BTB_VQ_WRONG_ORDER;
    const BtbVqCompletion result = {
        .token = token, .owner = owner, .requestedBytes = slot->payloadBytes,
        .completedBytes = slot->completedBytes, .deviceStatus = slot->deviceStatus,
        .cancellationWasRequested = slot->cancelRequested
    };
    queue->used[queue->usedHead] = 0U;
    queue->usedHead = (queue->usedHead + 1U) % BTB_VQ_SLOT_COUNT;
    --queue->usedCount;
    ClearSlot(slot);
    *outCompletion = result;
    return BTB_VQ_OK;
}
BtbVqStatus BtbVqRequestReset(BtbVq *queue)
{
    if (queue == NULL) return BTB_VQ_INVALID_ARGUMENT;
    if (queue->resetPending) return BTB_VQ_BUSY;
    queue->resetPending = 1;
    /* Do not free or reuse published buffers. Reset request is not reset ACK. */
    return BTB_VQ_OK;
}
BtbVqStatus BtbVqSimulateResetAcknowledged(BtbVq *queue)
{
    if (queue == NULL) return BTB_VQ_INVALID_ARGUMENT;
    if (!queue->resetPending) return BTB_VQ_WRONG_STATE;
    for (size_t i = 0U; i < BTB_VQ_SLOT_COUNT; ++i) {
        BtbVqSlot *slot = &queue->slots[i];
        if (slot->stage != BTB_VQ_RETIRED) ClearSlot(slot);
    }
    memset(queue->available, 0, sizeof(queue->available));
    memset(queue->used, 0, sizeof(queue->used));
    queue->availableHead = queue->availableCount = 0U;
    queue->usedHead = queue->usedCount = 0U;
    queue->resetPending = 0;
    return BTB_VQ_OK;
}
