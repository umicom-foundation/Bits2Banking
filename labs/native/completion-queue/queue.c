/*-----------------------------------------------------------------------------
 * Bits2Banking | Umicom Foundation | Sammy Hegab | MIT
 * File: labs/native/completion-queue/queue.c
 * PURPOSE: Bounded, copied and failure-atomic FIFO for terminal I/O results.
 *---------------------------------------------------------------------------*/
#include "queue.h"
#include <string.h>
static int ValidQueue(const BtbCompletionQueue *queue)
{
    return queue != NULL && queue->head < BTB_COMPLETION_CAPACITY &&
        queue->count <= BTB_COMPLETION_CAPACITY;
}
BtbQueueStatus BtbCompletionQueueInit(BtbCompletionQueue *queue)
{
    if (queue == NULL) return BTB_QUEUE_INVALID_ARGUMENT;
    *queue = (BtbCompletionQueue){0};
    return BTB_QUEUE_OK;
}
BtbQueueStatus BtbCompletionQueuePush(BtbCompletionQueue *queue, BtbCompletion value)
{
    if (!ValidQueue(queue) || value.requestId == 0U ||
        value.result > BTB_COMPLETION_CANCELLED ||
        (value.result != BTB_COMPLETION_SUCCESS && value.bytesTransferred != 0U))
        return BTB_QUEUE_INVALID_ARGUMENT;
    if (queue->count == BTB_COMPLETION_CAPACITY) return BTB_QUEUE_FULL;
    const size_t slot = (queue->head + queue->count) % BTB_COMPLETION_CAPACITY;
    queue->entries[slot] = value;
    ++queue->count;
    return BTB_QUEUE_OK;
}
BtbQueueStatus BtbCompletionQueuePop(BtbCompletionQueue *queue, BtbCompletion *out)
{
    if (!ValidQueue(queue) || out == NULL) return BTB_QUEUE_INVALID_ARGUMENT;
    if (queue->count == 0U) return BTB_QUEUE_EMPTY;
    const BtbCompletion next = queue->entries[queue->head];
    memset(&queue->entries[queue->head], 0, sizeof(queue->entries[queue->head]));
    queue->head = (queue->head + 1U) % BTB_COMPLETION_CAPACITY;
    --queue->count;
    *out = next;
    return BTB_QUEUE_OK;
}
size_t BtbCompletionQueueCount(const BtbCompletionQueue *queue)
{
    return ValidQueue(queue) ? queue->count : 0U;
}
