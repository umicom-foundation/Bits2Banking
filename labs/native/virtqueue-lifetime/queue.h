/*-----------------------------------------------------------------------------
 * Bits2Banking — Virtqueue Lifetime Laboratory
 * File: labs/native/virtqueue-lifetime/queue.h
 * PURPOSE: Model buffer ownership around a bounded device-request queue.
 * AUTHOR AND ORGANISATION: Sammy Hegab, Umicom Foundation
 * LICENCE: MIT
 *---------------------------------------------------------------------------*/
#ifndef BTB_VIRTQUEUE_LIFETIME_H
#define BTB_VIRTQUEUE_LIFETIME_H
#include <stddef.h>
#include <stdint.h>

#define BTB_VQ_SLOT_COUNT 4U
#define BTB_VQ_PAYLOAD_CAPACITY 256U

typedef enum BtbVqStatus {
    BTB_VQ_OK = 0,
    BTB_VQ_INVALID_ARGUMENT,
    BTB_VQ_BUSY,
    BTB_VQ_FULL,
    BTB_VQ_STALE_TOKEN,
    BTB_VQ_WRONG_OWNER,
    BTB_VQ_WRONG_STATE,
    BTB_VQ_WRONG_ORDER
} BtbVqStatus;

typedef enum BtbVqStage {
    BTB_VQ_FREE = 0,
    BTB_VQ_PREPARED,
    BTB_VQ_PUBLISHED,
    BTB_VQ_COMPLETED,
    BTB_VQ_RETIRED
} BtbVqStage;

typedef struct BtbVqSlot {
    BtbVqStage stage;
    uint32_t generation;
    uint32_t owner;
    uint32_t payloadBytes;
    uint32_t completedBytes;
    uint32_t deviceStatus;
    int cancelRequested;
    unsigned char payload[BTB_VQ_PAYLOAD_CAPACITY];
} BtbVqSlot;

typedef struct BtbVq {
    BtbVqSlot slots[BTB_VQ_SLOT_COUNT];
    uint64_t available[BTB_VQ_SLOT_COUNT];
    uint64_t used[BTB_VQ_SLOT_COUNT];
    uint32_t availableHead;
    uint32_t availableCount;
    uint32_t usedHead;
    uint32_t usedCount;
    int resetPending;
} BtbVq;

typedef struct BtbVqCompletion {
    uint64_t token;
    uint32_t owner;
    uint32_t requestedBytes;
    uint32_t completedBytes;
    uint32_t deviceStatus;
    int cancellationWasRequested;
} BtbVqCompletion;

/* Caller owns the stable queue and may not copy/reinitialize while active. */
void BtbVqInit(BtbVq *queue);
BtbVqStatus BtbVqPrepare(BtbVq *queue, uint32_t owner,
                         const void *bytes, size_t length, uint64_t *outToken);
BtbVqStatus BtbVqPublish(BtbVq *queue, uint32_t owner, uint64_t token);
BtbVqStatus BtbVqCancelRequested(BtbVq *queue, uint32_t owner, uint64_t token);
/* Educational fake device, not a real VirtIO MMIO/DMA implementation. */
BtbVqStatus BtbVqSimulateComplete(BtbVq *queue, uint64_t token,
                                  uint32_t deviceStatus, uint32_t completedBytes);
BtbVqStatus BtbVqCollect(BtbVq *queue, uint32_t owner,
                         uint64_t token, BtbVqCompletion *outCompletion);
/* This step requests reset; it does not prove hardware stopped using memory. */
BtbVqStatus BtbVqRequestReset(BtbVq *queue);
/* Call only after the fake device test has separately observed a reset ACK.
 * A production driver must obtain this proof from actual hardware. */
BtbVqStatus BtbVqSimulateResetAcknowledged(BtbVq *queue);

#endif
