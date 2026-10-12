/*-----------------------------------------------------------------------------
 * Bits2Banking | Umicom Foundation
 * File: labs/native/work-dispatch/dispatch.c
 * PURPOSE: Single-owner, in-memory completion delivery by library composition.
 * AUTHOR: Sammy Hegab | LICENCE: MIT
 *
 * The earlier handoff.c and completion queue.c remain intact and are linked
 * as dependencies. This adapter owns their integration and no process threads.
 *---------------------------------------------------------------------------*/
#include "dispatch.h"
#include <limits.h>
#include <string.h>

/* This digest is for deterministic exercises and debugging ONLY. It is not
 * suitable for signatures, tamper evidence, passwords or financial controls. */
static uint64_t BtbDiagnosticDigest(const unsigned char *bytes, size_t length)
{
    uint64_t value = UINT64_C(14695981039346656037);
    for (size_t i = 0U; i < length; ++i) {
        value ^= (uint64_t)bytes[i];
        value *= UINT64_C(1099511628211);
    }
    return value;
}

static int BtbSameIdentity(BtbDispatchIdentity lhs, BtbDispatchIdentity rhs)
{
    return lhs.requestId == rhs.requestId &&
           lhs.token.slot == rhs.token.slot &&
           lhs.token.generation == rhs.token.generation;
}

static int BtbNotificationValid(const BtbDispatch *dispatcher,
                                BtbCompletion completion)
{
    if (completion.requestId == 0U || completion.result > BTB_COMPLETION_CANCELLED)
        return 0;
    for (size_t i = 0U; i < BTB_WORK_CAPACITY; ++i) {
        const BtbDispatchRecord *record = &dispatcher->records[i];
        if (!record->occupied || record->identity.requestId != completion.requestId)
            continue;
        const BtbWorkItem *item = &dispatcher->work.items[i];
        return item->generation == record->identity.token.generation &&
               ((completion.result == BTB_COMPLETION_SUCCESS &&
                 item->state == BTB_WORK_COMPLETE &&
                 completion.bytesTransferred == record->requestLength) ||
                (completion.result == BTB_COMPLETION_CANCELLED &&
                 item->state == BTB_WORK_CANCELLED &&
                 completion.bytesTransferred == 0U));
    }
    return 0;
}

int BtbDispatchInvariants(const BtbDispatch *dispatcher)
{
    if (dispatcher == NULL || dispatcher->nextRequestId == 0U ||
        dispatcher->work.maxActive != 1U ||
        !BtbWorkInvariants(&dispatcher->work) ||
        dispatcher->work.active != 0U ||
        dispatcher->notifications.count > BTB_COMPLETION_CAPACITY ||
        dispatcher->notifications.head >= BTB_COMPLETION_CAPACITY)
        return 0;

    size_t occupied = 0U;
    size_t terminal = 0U;
    for (size_t i = 0U; i < BTB_WORK_CAPACITY; ++i) {
        const BtbDispatchRecord *record = &dispatcher->records[i];
        const BtbWorkItem *item = &dispatcher->work.items[i];
        if (item->state == BTB_WORK_FREE) {
            if (record->occupied) return 0;
            continue;
        }
        ++occupied;
        if (!record->occupied || record->identity.token.slot != i ||
            record->identity.token.generation != item->generation ||
            record->identity.requestId == 0U ||
            record->identity.requestId >= dispatcher->nextRequestId ||
            record->connectionId != item->connectionId ||
            record->requestLength != item->length)
            return 0;
        if (item->state == BTB_WORK_COMPLETE || item->state == BTB_WORK_CANCELLED)
            ++terminal;
    }
    if (terminal != dispatcher->notifications.count ||
        dispatcher->accepted != dispatcher->delivered + (uint64_t)occupied ||
        dispatcher->succeeded + dispatcher->cancelled !=
            dispatcher->delivered + (uint64_t)terminal)
        return 0;

    /* Every terminal work item has precisely one notification, and each
     * notification refers to one record, not merely an reused array slot. */
    for (size_t i = 0U; i < dispatcher->notifications.count; ++i) {
        const size_t position =
            (dispatcher->notifications.head + i) % BTB_COMPLETION_CAPACITY;
        const BtbCompletion completion = dispatcher->notifications.entries[position];
        if (!BtbNotificationValid(dispatcher, completion)) return 0;
        for (size_t j = i + 1U; j < dispatcher->notifications.count; ++j) {
            const size_t other =
                (dispatcher->notifications.head + j) % BTB_COMPLETION_CAPACITY;
            if (completion.requestId ==
                dispatcher->notifications.entries[other].requestId) return 0;
        }
    }
    return 1;
}

BtbDispatchStatus BtbDispatchInit(BtbDispatch *dispatcher)
{
    if (dispatcher == NULL) return BTB_DISPATCH_INVALID;
    memset(dispatcher, 0, sizeof(*dispatcher));
    if (BtbWorkInit(&dispatcher->work, 1U) != BTB_WORK_OK ||
        BtbCompletionQueueInit(&dispatcher->notifications) != BTB_QUEUE_OK)
        return BTB_DISPATCH_INTEGRITY;
    dispatcher->nextRequestId = 1U;
    return BTB_DISPATCH_OK;
}

BtbDispatchStatus BtbDispatchSubmit(BtbDispatch *dispatcher,
                                    uint64_t connectionId,
                                    const void *bytes,
                                    size_t length,
                                    BtbDispatchIdentity *outIdentity)
{
    if (dispatcher == NULL || outIdentity == NULL || connectionId == 0U ||
        bytes == NULL || length == 0U || length > BTB_WORK_BYTES)
        return BTB_DISPATCH_INVALID;
    if (!BtbDispatchInvariants(dispatcher)) return BTB_DISPATCH_INTEGRITY;
    if (dispatcher->work.quiescing) return BTB_DISPATCH_QUIESCING;
    if (dispatcher->nextRequestId == UINT32_MAX) return BTB_DISPATCH_ID_EXHAUSTED;
    BtbWorkToken token = {0};
    const BtbWorkResult result =
        BtbWorkSubmit(&dispatcher->work, connectionId, bytes, length, &token);
    if (result == BTB_WORK_FULL) return BTB_DISPATCH_FULL;
    if (result != BTB_WORK_OK) return BTB_DISPATCH_INTEGRITY;
    const BtbDispatchIdentity identity = { dispatcher->nextRequestId++, token };
    dispatcher->records[token.slot] = (BtbDispatchRecord){
        .identity = identity,
        .connectionId = connectionId,
        .requestLength = length,
        .occupied = 1
    };
    ++dispatcher->accepted;
    *outIdentity = identity;
    return BTB_DISPATCH_OK;
}

BtbDispatchStatus BtbDispatchStep(BtbDispatch *dispatcher)
{
    if (dispatcher == NULL) return BTB_DISPATCH_INVALID;
    if (!BtbDispatchInvariants(dispatcher)) return BTB_DISPATCH_INTEGRITY;
    if (dispatcher->work.queued == 0U) return BTB_DISPATCH_EMPTY;
    if (BtbCompletionQueueCount(&dispatcher->notifications) ==
        BTB_COMPLETION_CAPACITY) return BTB_DISPATCH_BACKPRESSURE;

    BtbWorkToken token = {0};
    const BtbWorkItem *borrowed = NULL;
    if (BtbWorkAcquire(&dispatcher->work, &token, &borrowed) != BTB_WORK_OK ||
        borrowed == NULL) return BTB_DISPATCH_INTEGRITY;
    const BtbDispatchRecord *record = &dispatcher->records[token.slot];
    const uint64_t digest = BtbDiagnosticDigest(borrowed->payload, borrowed->length);
    const uint32_t processed = (uint32_t)borrowed->length; /* <= 96 by contract. */

    /* The completion queue is known to have capacity. These transitions are
     * adjacent and non-preemptible because one owner invokes the dispatcher. */
    if (BtbWorkComplete(&dispatcher->work, token) != BTB_WORK_OK)
        return BTB_DISPATCH_INTEGRITY;
    if (BtbCompletionQueuePush(&dispatcher->notifications, (BtbCompletion){
            .requestId = record->identity.requestId,
            .bytesTransferred = processed,
            .result = BTB_COMPLETION_SUCCESS
        }) != BTB_QUEUE_OK)
        return BTB_DISPATCH_INTEGRITY;

    dispatcher->records[token.slot].diagnosticDigest = digest;
    ++dispatcher->succeeded;
    return BTB_DISPATCH_OK;
}

BtbDispatchStatus BtbDispatchRun(BtbDispatch *dispatcher, size_t budget,
                                 size_t *outRun)
{
    if (dispatcher == NULL || outRun == NULL ||
        budget == 0U || budget > BTB_WORK_CAPACITY)
        return BTB_DISPATCH_INVALID;
    size_t progressed = 0U;
    BtbDispatchStatus last = BTB_DISPATCH_EMPTY;
    for (size_t i = 0U; i < budget; ++i) {
        last = BtbDispatchStep(dispatcher);
        if (last != BTB_DISPATCH_OK) break;
        ++progressed;
    }
    if (last == BTB_DISPATCH_INTEGRITY || last == BTB_DISPATCH_INVALID)
        return last;
    *outRun = progressed;
    return progressed != 0U ? BTB_DISPATCH_OK : last;
}

BtbDispatchStatus BtbDispatchCancel(BtbDispatch *dispatcher,
                                    BtbDispatchIdentity identity)
{
    if (dispatcher == NULL || identity.token.slot >= BTB_WORK_CAPACITY ||
        identity.token.generation == 0U || identity.requestId == 0U)
        return BTB_DISPATCH_INVALID;
    if (!BtbDispatchInvariants(dispatcher)) return BTB_DISPATCH_INTEGRITY;
    const BtbDispatchRecord *record = &dispatcher->records[identity.token.slot];
    if (!record->occupied || !BtbSameIdentity(record->identity, identity))
        return BTB_DISPATCH_STALE;
    if (dispatcher->work.items[identity.token.slot].state != BTB_WORK_QUEUED)
        return BTB_DISPATCH_FINAL;
    if (BtbCompletionQueueCount(&dispatcher->notifications) ==
        BTB_COMPLETION_CAPACITY) return BTB_DISPATCH_BACKPRESSURE;

    if (BtbWorkCancel(&dispatcher->work, identity.token) != BTB_WORK_OK)
        return BTB_DISPATCH_INTEGRITY;
    if (BtbCompletionQueuePush(&dispatcher->notifications, (BtbCompletion){
            .requestId = identity.requestId,
            .bytesTransferred = 0U,
            .result = BTB_COMPLETION_CANCELLED
        }) != BTB_QUEUE_OK)
        return BTB_DISPATCH_INTEGRITY;
    ++dispatcher->cancelled;
    return BTB_DISPATCH_OK;
}

BtbDispatchStatus BtbDispatchReceive(BtbDispatch *dispatcher,
                                     BtbDispatchReceipt *outReceipt)
{
    if (dispatcher == NULL || outReceipt == NULL) return BTB_DISPATCH_INVALID;
    if (!BtbDispatchInvariants(dispatcher)) return BTB_DISPATCH_INTEGRITY;
    if (BtbCompletionQueueCount(&dispatcher->notifications) == 0U)
        return BTB_DISPATCH_EMPTY;

    const BtbCompletion upcoming =
        dispatcher->notifications.entries[dispatcher->notifications.head];
    for (size_t i = 0U; i < BTB_WORK_CAPACITY; ++i) {
        BtbDispatchRecord *record = &dispatcher->records[i];
        if (!record->occupied || record->identity.requestId != upcoming.requestId)
            continue;
        const BtbDispatchReceipt owned = {
            .identity = record->identity,
            .connectionId = record->connectionId,
            .requestLength = record->requestLength,
            .diagnosticDigest = record->diagnosticDigest,
            .result = upcoming.result
        };
        /* Preflight invariants ensure both transitions are valid; a corrupt
         * internal state is reported, never silently "repaired". */
        BtbCompletion popped = {0};
        if (BtbCompletionQueuePop(&dispatcher->notifications, &popped) !=
                BTB_QUEUE_OK || popped.requestId != upcoming.requestId ||
            BtbWorkRelease(&dispatcher->work, owned.identity.token) != BTB_WORK_OK)
            return BTB_DISPATCH_INTEGRITY;
        *record = (BtbDispatchRecord){0};
        ++dispatcher->delivered;
        *outReceipt = owned;
        return BTB_DISPATCH_OK;
    }
    return BTB_DISPATCH_INTEGRITY;
}

BtbDispatchStatus BtbDispatchQuiesce(BtbDispatch *dispatcher)
{
    if (dispatcher == NULL) return BTB_DISPATCH_INVALID;
    if (!BtbDispatchInvariants(dispatcher)) return BTB_DISPATCH_INTEGRITY;
    BtbWorkQuiesce(&dispatcher->work);
    return BTB_DISPATCH_OK;
}

int BtbDispatchDrained(const BtbDispatch *dispatcher)
{
    if (!BtbDispatchInvariants(dispatcher) ||
        !BtbWorkDrained(&dispatcher->work) ||
        dispatcher->notifications.count != 0U)
        return 0;
    for (size_t i = 0U; i < BTB_WORK_CAPACITY; ++i)
        if (dispatcher->work.items[i].state != BTB_WORK_FREE) return 0;
    return 1;
}
