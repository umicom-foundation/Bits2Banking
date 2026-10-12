/*-----------------------------------------------------------------------------
 * Bits2Banking | Umicom Foundation
 * File: labs/native/work-dispatch/dispatch.h
 * PURPOSE: Compose existing bounded C23 handoff and completion libraries.
 * AUTHOR: Sammy Hegab | LICENCE: MIT
 *
 * EDUCATIONAL BOUNDARY: This is a single-owner, synchronous dispatcher.
 * It uses no threads, sockets, callbacks or application-specific VCS wrappers.
 * Production scheduling/transport belongs in Umicom Framework.
 *---------------------------------------------------------------------------*/
#ifndef BTB_DISPATCH_H
#define BTB_DISPATCH_H

#include "handoff.h"  /* Existing Update 29 public teaching contract. */
#include "queue.h"    /* Existing C23 completion FIFO teaching contract. */
#include <stddef.h>
#include <stdint.h>

/* The completion queue allows four outstanding notices, even though the
 * handoff queue has eight work slots. The smaller downstream capacity causes
 * deliberate, testable backpressure; neither queue is reimplemented here. */
typedef enum BtbDispatchStatus {
    BTB_DISPATCH_OK = 0,
    BTB_DISPATCH_INVALID,
    BTB_DISPATCH_FULL,
    BTB_DISPATCH_BACKPRESSURE,
    BTB_DISPATCH_EMPTY,
    BTB_DISPATCH_STALE,
    BTB_DISPATCH_FINAL,
    BTB_DISPATCH_QUIESCING,
    BTB_DISPATCH_ID_EXHAUSTED,
    BTB_DISPATCH_INTEGRITY
} BtbDispatchStatus;

typedef struct BtbDispatchIdentity {
    uint32_t requestId;
    BtbWorkToken token;
} BtbDispatchIdentity;

/* A receipt is copied into caller-owned memory on successful Receive.
 * Its diagnostic digest is FNV-1a, NOT a cryptographic integrity proof. */
typedef struct BtbDispatchReceipt {
    BtbDispatchIdentity identity;
    uint64_t connectionId;
    size_t requestLength;
    uint64_t diagnosticDigest;
    BtbCompletionResult result;
} BtbDispatchReceipt;

typedef struct BtbDispatchRecord {
    BtbDispatchIdentity identity;
    uint64_t connectionId;
    uint64_t diagnosticDigest;
    size_t requestLength;
    int occupied;
} BtbDispatchRecord;

typedef struct BtbDispatch {
    BtbWorkQueue work;
    BtbCompletionQueue notifications;
    BtbDispatchRecord records[BTB_WORK_CAPACITY];
    uint32_t nextRequestId;
    uint64_t accepted;
    uint64_t succeeded;
    uint64_t cancelled;
    uint64_t delivered;
} BtbDispatch;

/* Initialises caller-owned storage. Only one owner may call these functions.
 * Submit deep-copies bytes via the existing handoff implementation. */
BtbDispatchStatus BtbDispatchInit(BtbDispatch *dispatcher);
BtbDispatchStatus BtbDispatchSubmit(BtbDispatch *dispatcher,
                                    uint64_t connectionId,
                                    const void *bytes,
                                    size_t length,
                                    BtbDispatchIdentity *outIdentity);

/* Step executes at most ONE queued item synchronously. Never runs a task if
 * the downstream completion queue is full. Work is only a deterministic
 * diagnostic digest of the copied bytes, not a real HTTP or banking action. */
BtbDispatchStatus BtbDispatchStep(BtbDispatch *dispatcher);

/* Run processes up to budget items (1..BTB_WORK_CAPACITY). If any were run,
 * returns OK and writes the run count. Otherwise returns EMPTY or
 * BACKPRESSURE. Rejected arguments leave *outRun unchanged. */
BtbDispatchStatus BtbDispatchRun(BtbDispatch *dispatcher, size_t budget,
                                 size_t *outRun);

/* Cancel accepts QUEUED work only: Step has no asynchronously cancellable
 * phase. If the completion queue is full, cancellation refuses without
 * changing the work state or losing a notice. */
BtbDispatchStatus BtbDispatchCancel(BtbDispatch *dispatcher,
                                    BtbDispatchIdentity identity);

/* Receive copies one terminal result, consumes its queued notice, and
 * releases the original handoff slot. EMPTY leaves *outReceipt unchanged.
 * Successful receipts outlive the dispatcher and contain no borrowed pointers. */
BtbDispatchStatus BtbDispatchReceive(BtbDispatch *dispatcher,
                                     BtbDispatchReceipt *outReceipt);

/* Quiesce closes admission but permits existing work to run, cancel or drain.
 * Drained means zero active/queued work AND zero unacknowledged results. */
BtbDispatchStatus BtbDispatchQuiesce(BtbDispatch *dispatcher);
int BtbDispatchDrained(const BtbDispatch *dispatcher);

/* Read-only consistency check; does not repair corrupt state. */
int BtbDispatchInvariants(const BtbDispatch *dispatcher);

#endif
