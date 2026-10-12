/*-----------------------------------------------------------------------------
 * Bits2Banking | Umicom Foundation | Sammy Hegab | MIT
 * File: labs/native/completion-queue/queue.h
 * PURPOSE: Fixed-capacity completion FIFO; values are copied, not borrowed.
 *---------------------------------------------------------------------------*/
#ifndef BTB_COMPLETION_QUEUE_H
#define BTB_COMPLETION_QUEUE_H
#include <stddef.h>
#include <stdint.h>
#define BTB_COMPLETION_CAPACITY 4U
typedef enum BtbQueueStatus {
    BTB_QUEUE_OK = 0,
    BTB_QUEUE_INVALID_ARGUMENT,
    BTB_QUEUE_FULL,
    BTB_QUEUE_EMPTY
} BtbQueueStatus;
typedef enum BtbCompletionResult {
    BTB_COMPLETION_SUCCESS = 0,
    BTB_COMPLETION_FAILURE = 1,
    BTB_COMPLETION_CANCELLED = 2
} BtbCompletionResult;
typedef struct BtbCompletion {
    uint32_t requestId;
    uint32_t bytesTransferred;
    BtbCompletionResult result;
} BtbCompletion;
typedef struct BtbCompletionQueue {
    BtbCompletion entries[BTB_COMPLETION_CAPACITY];
    size_t head;
    size_t count;
} BtbCompletionQueue;
/* Caller owns queue storage. Initialise before first use, and do not copy a
 * queue while another operation might act upon it. These routines do not
 * provide thread safety; the laboratory uses one serial execution context. */
BtbQueueStatus BtbCompletionQueueInit(BtbCompletionQueue *queue);
/* FULL or invalid input leaves the entire queue unchanged. */
BtbQueueStatus BtbCompletionQueuePush(BtbCompletionQueue *queue, BtbCompletion value);
/* EMPTY leaves the caller's output completely unchanged. */
BtbQueueStatus BtbCompletionQueuePop(BtbCompletionQueue *queue, BtbCompletion *out);
size_t BtbCompletionQueueCount(const BtbCompletionQueue *queue);
#endif
