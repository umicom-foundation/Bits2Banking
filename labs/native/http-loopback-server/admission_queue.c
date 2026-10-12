/*-----------------------------------------------------------------------------
 * Bits2Banking | Umicom Foundation
 * File: labs/native/http-loopback-server/admission_queue.c
 * PURPOSE: Model fixed-capacity FIFO admission, cancellation and completion.
 * AUTHOR: Sammy Hegab | LICENCE: MIT
 *---------------------------------------------------------------------------*/
#include "admission_queue.h"
#include <string.h>

static int BtbAdmissionReady(const BtbAdmissionQueue *queue)
{
    return queue != NULL && queue->self == queue &&
        BtbAdmissionValidate(queue);
}
int BtbAdmissionValidate(const BtbAdmissionQueue *queue)
{
    if (queue == NULL || queue->self != queue || queue->nextTicket == 0U ||
        queue->maxActive == 0U || queue->maxActive > BTB_ADMISSION_CAPACITY ||
        queue->count > BTB_ADMISSION_CAPACITY || queue->active > queue->count ||
        queue->active > queue->maxActive) return 0;
    size_t active = 0U;
    for (size_t i = 0U; i < queue->count; ++i) {
        const BtbAdmissionItem *item = &queue->items[i];
        if (item->ticket == 0U || item->ticket >= queue->nextTicket || item->requestId == 0U ||
            (item->phase != BTB_ADMISSION_QUEUED && item->phase != BTB_ADMISSION_ACTIVE) ||
            (item->phase == BTB_ADMISSION_QUEUED && item->cancellationRequested != 0U)) return 0;
        active += item->phase == BTB_ADMISSION_ACTIVE ? 1U : 0U;
        for (size_t earlier = 0U; earlier < i; ++earlier)
            if (queue->items[earlier].ticket == item->ticket ||
                queue->items[earlier].requestId == item->requestId) return 0;
    }
    return active == queue->active;
}
BtbAdmissionStatus BtbAdmissionInit(BtbAdmissionQueue *queue, size_t maxActive)
{
    if (queue == NULL || queue->self != NULL || maxActive == 0U ||
        maxActive > BTB_ADMISSION_CAPACITY) return BTB_ADMISSION_INVALID;
    /* Once initialised, do not reset: a reused ticket would name old work. */
    BtbAdmissionQueue prepared = {0};
    prepared.maxActive = maxActive;
    prepared.nextTicket = 1U;
    *queue = prepared;
    queue->self = queue;
    return BTB_ADMISSION_OK;
}
BtbAdmissionStatus BtbAdmissionSubmit(BtbAdmissionQueue *queue,
                                      uint64_t requestId, uint64_t *outTicket)
{
    if (!BtbAdmissionReady(queue) || requestId == 0U || outTicket == NULL)
        return BTB_ADMISSION_INVALID;
    if (queue->count == BTB_ADMISSION_CAPACITY) return BTB_ADMISSION_FULL;
    if (queue->nextTicket == UINT64_MAX || queue->admitted == UINT64_MAX)
        return BTB_ADMISSION_EXHAUSTED;
    for (size_t i = 0U; i < queue->count; ++i)
        if (queue->items[i].requestId == requestId) return BTB_ADMISSION_INVALID;
    const uint64_t ticket = queue->nextTicket;
    queue->items[queue->count++] = (BtbAdmissionItem){
        .ticket = ticket, .requestId = requestId, .phase = BTB_ADMISSION_QUEUED};
    ++queue->nextTicket;
    ++queue->admitted;
    *outTicket = ticket;
    return BTB_ADMISSION_OK;
}
BtbAdmissionStatus BtbAdmissionStart(BtbAdmissionQueue *queue,
                                     uint64_t *outTicket, uint64_t *outRequestId)
{
    if (!BtbAdmissionReady(queue) || outTicket == NULL || outRequestId == NULL)
        return BTB_ADMISSION_INVALID;
    if (queue->active >= queue->maxActive) return BTB_ADMISSION_BUSY;
    for (size_t i = 0U; i < queue->count; ++i) {
        BtbAdmissionItem *item = &queue->items[i];
        if (item->phase == BTB_ADMISSION_QUEUED) {
            item->phase = BTB_ADMISSION_ACTIVE;
            ++queue->active;
            *outTicket = item->ticket;
            *outRequestId = item->requestId;
            return BTB_ADMISSION_OK;
        }
    }
    return BTB_ADMISSION_EMPTY;
}
static void BtbAdmissionErase(BtbAdmissionQueue *queue, size_t index)
{
    if (index + 1U < queue->count)
        memmove(&queue->items[index], &queue->items[index + 1U],
                (queue->count - index - 1U) * sizeof(queue->items[0]));
    --queue->count;
    queue->items[queue->count] = (BtbAdmissionItem){0};
}
BtbAdmissionStatus BtbAdmissionCancel(BtbAdmissionQueue *queue, uint64_t ticket)
{
    if (!BtbAdmissionReady(queue) || ticket == 0U) return BTB_ADMISSION_INVALID;
    for (size_t i = 0U; i < queue->count; ++i) {
        BtbAdmissionItem *item = &queue->items[i];
        if (item->ticket != ticket) continue;
        if (item->phase == BTB_ADMISSION_ACTIVE) {
            /* An active request may already be completing. Mark intent only;
             * its owner must observe and finish before resources can be freed. */
            item->cancellationRequested = 1U;
            return BTB_ADMISSION_OK;
        }
        if (queue->removed == UINT64_MAX) return BTB_ADMISSION_EXHAUSTED;
        BtbAdmissionErase(queue, i);
        ++queue->removed;
        return BTB_ADMISSION_OK;
    }
    return BTB_ADMISSION_STALE;
}
BtbAdmissionStatus BtbAdmissionComplete(BtbAdmissionQueue *queue, uint64_t ticket)
{
    if (!BtbAdmissionReady(queue) || ticket == 0U) return BTB_ADMISSION_INVALID;
    for (size_t i = 0U; i < queue->count; ++i) {
        if (queue->items[i].ticket != ticket) continue;
        if (queue->items[i].phase != BTB_ADMISSION_ACTIVE) return BTB_ADMISSION_BUSY;
        if (queue->completed == UINT64_MAX) return BTB_ADMISSION_EXHAUSTED;
        BtbAdmissionErase(queue, i);
        --queue->active;
        ++queue->completed;
        return BTB_ADMISSION_OK;
    }
    return BTB_ADMISSION_STALE;
}
