/*-----------------------------------------------------------------------------
 * Bits2Banking | Umicom Foundation
 * File: labs/native/work-handoff/handoff.h
 * PURPOSE: Deterministic C23 bounded work handoff and ownership teaching API.
 * AUTHOR: Sammy Hegab | LICENCE: MIT
 *---------------------------------------------------------------------------*/
#ifndef BTB_HANDOFF_H
#define BTB_HANDOFF_H
#include <stddef.h>
#include <stdint.h>
#define BTB_WORK_CAPACITY 8U
#define BTB_WORK_BYTES 96U

typedef enum BtbWorkState {
    BTB_WORK_FREE = 0,
    BTB_WORK_QUEUED,
    BTB_WORK_ACTIVE,
    BTB_WORK_COMPLETE,
    BTB_WORK_CANCELLED
} BtbWorkState;

typedef struct BtbWorkToken {
    uint32_t slot;
    uint64_t generation;
} BtbWorkToken;

typedef struct BtbWorkItem {
    BtbWorkState state;
    uint64_t generation;
    uint64_t connectionId;
    size_t length;
    unsigned char payload[BTB_WORK_BYTES];
} BtbWorkItem;

typedef struct BtbWorkQueue {
    BtbWorkItem items[BTB_WORK_CAPACITY];
    uint32_t waiting[BTB_WORK_CAPACITY];
    size_t head;
    size_t queued;
    size_t active;
    size_t maxActive;
    int quiescing;
} BtbWorkQueue;

typedef enum BtbWorkResult {
    BTB_WORK_OK = 0,
    BTB_WORK_INVALID,
    BTB_WORK_FULL,
    BTB_WORK_BUSY,
    BTB_WORK_STALE,
    BTB_WORK_SHUTDOWN
} BtbWorkResult;

/* The queue owns copied request bytes until an explicit Release. A token
 * contains a generation that prevents a late completion targeting reused slots. */
BtbWorkResult BtbWorkInit(BtbWorkQueue *queue, size_t maxActive);
BtbWorkResult BtbWorkSubmit(BtbWorkQueue *queue, uint64_t connectionId,
                            const void *bytes, size_t length, BtbWorkToken *token);
BtbWorkResult BtbWorkAcquire(BtbWorkQueue *queue, BtbWorkToken *token,
                             const BtbWorkItem **borrowedItem);
BtbWorkResult BtbWorkComplete(BtbWorkQueue *queue, BtbWorkToken token);
BtbWorkResult BtbWorkCancel(BtbWorkQueue *queue, BtbWorkToken token);
BtbWorkResult BtbWorkRelease(BtbWorkQueue *queue, BtbWorkToken token);
void BtbWorkQuiesce(BtbWorkQueue *queue);
int BtbWorkDrained(const BtbWorkQueue *queue);
int BtbWorkInvariants(const BtbWorkQueue *queue);
#endif
