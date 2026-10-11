/*-----------------------------------------------------------------------------
 * Bits to Banking — Umicom Foundation
 * File: labs/native/blocking-ipc-lifetimes/session.c
 * PURPOSE: Demonstrate wait registration, wake checks and separate resource
 *          ownership by composing existing, tested C23 teaching libraries.
 * AUTHOR AND ORGANISATION: Sammy Hegab, Umicom Foundation
 * LICENCE: MIT
 *---------------------------------------------------------------------------*/
#include "session.h"

static int Running(BtbServiceSession *session)
{
    BtbSchedSnapshot snapshot = {0};
    return BtbRoundRobinSnapshotRead(session->scheduler, &snapshot) == BTB_SCHED_OK &&
        snapshot.running == 1U && snapshot.runningTask == session->receiverTask;
}
BtbSessionStatus BtbSessionInit(BtbServiceSession *session, BtbRoundRobin *scheduler,
    BtbChannel *channel, BtbTaskHandle receiverTask, uint32_t senderIdentity,
    uint32_t receiverIdentity, uint32_t waitKey)
{
    if (session == NULL || scheduler == NULL || channel == NULL ||
        receiverTask == 0U || senderIdentity == 0U || receiverIdentity == 0U ||
        senderIdentity == receiverIdentity || waitKey == 0U)
        return BTB_SESSION_INVALID;
    BtbSchedSnapshot state = {0};
    if (BtbRoundRobinSnapshotRead(scheduler, &state) != BTB_SCHED_OK ||
        state.runningTask != receiverTask) return BTB_SESSION_BAD_STATE;
    BtbServiceSession next = {0};
    next.scheduler = scheduler;
    next.channel = channel;
    next.receiverTask = receiverTask;
    next.senderIdentity = senderIdentity;
    next.receiverIdentity = receiverIdentity;
    next.waitKey = waitKey;
    *session = next;
    return BTB_SESSION_OK;
}
BtbSessionStatus BtbSessionWaitForMessage(BtbServiceSession *session)
{
    if (session == NULL) return BTB_SESSION_INVALID;
    if (session->closed) return BTB_SESSION_CLOSED;
    if (session->waiting || !Running(session)) return BTB_SESSION_BAD_STATE;
    /* Checking the queue and registering the wait happen together on one
     * owner thread. There is no possible send interleaving inside this call.
     * Real Kernel IPC requires its own protection against that race. */
    if (BtbChannelPending(session->channel) != 0U) return BTB_SESSION_READY;
    if (BtbRoundRobinWait(session->scheduler, session->receiverTask,
                           session->waitKey) != BTB_SCHED_OK)
        return BTB_SESSION_BAD_STATE;
    session->waiting = 1;
    return BTB_SESSION_WOULD_BLOCK;
}
BtbSessionStatus BtbSessionPoll(BtbServiceSession *session)
{
    if (session == NULL) return BTB_SESSION_INVALID;
    if (session->closed) return BTB_SESSION_CLOSED;
    if (!session->waiting) return BTB_SESSION_BAD_STATE;
    if (BtbChannelPending(session->channel) == 0U) return BTB_SESSION_WOULD_BLOCK;
    /* A queue entry is the authority; no standalone notification can wake
     * the task while the queue is empty. The task remains non-running after
     * wake until the scheduler dispatches it normally. */
    if (BtbRoundRobinWake(session->scheduler, session->receiverTask,
                           session->waitKey) != BTB_SCHED_OK)
        return BTB_SESSION_BAD_STATE;
    session->waiting = 0;
    return BTB_SESSION_READY;
}
BtbSessionStatus BtbSessionSend(BtbServiceSession *session,
    const void *payload, size_t length, uint64_t *outSequence)
{
    if (session == NULL) return BTB_SESSION_INVALID;
    if (session->closed) return BTB_SESSION_CLOSED;
    BtbChannelResult sent = BtbChannelSend(session->channel,
        session->senderIdentity, session->receiverIdentity,
        payload, length, outSequence);
    if (sent == BTB_CHANNEL_OK) return BTB_SESSION_OK;
    if (sent == BTB_CHANNEL_FULL) return BTB_SESSION_FULL;
    return BTB_SESSION_INVALID;
}
BtbSessionStatus BtbSessionReceive(BtbServiceSession *session,
    void *destination, size_t capacity, uint32_t *outSender,
    size_t *outLength, uint64_t *outSequence)
{
    if (session == NULL) return BTB_SESSION_INVALID;
    if (session->closed) return BTB_SESSION_CLOSED;
    if (session->waiting || !Running(session)) return BTB_SESSION_BAD_STATE;
    const BtbChannelResult value = BtbChannelReceive(session->channel,
        session->receiverIdentity, destination, capacity, outSender, outLength, outSequence);
    if (value == BTB_CHANNEL_OK) return BTB_SESSION_OK;
    if (value == BTB_CHANNEL_EMPTY) return BTB_SESSION_WOULD_BLOCK;
    if (value == BTB_CHANNEL_SMALL_BUFFER) return BTB_SESSION_SMALL_BUFFER;
    if (value == BTB_CHANNEL_DENIED) return BTB_SESSION_DENIED;
    return BTB_SESSION_INVALID;
}
BtbSessionStatus BtbSessionClose(BtbServiceSession *session)
{
    if (session == NULL) return BTB_SESSION_INVALID;
    if (session->closed) return BTB_SESSION_CLOSED;
    BtbSchedResult status;
    if (session->waiting) {
        status = BtbRoundRobinCancelWait(session->scheduler, session->receiverTask,
                                         session->waitKey);
    } else if (Running(session)) {
        status = BtbRoundRobinExit(session->scheduler, session->receiverTask);
    } else return BTB_SESSION_BAD_STATE;
    if (status != BTB_SCHED_OK) return BTB_SESSION_BAD_STATE;
    /* The channel remains caller-owned. Unread messages may still be inspected
     * by the owner; this service simply cannot consume or publish more. */
    session->waiting = 0;
    session->closed = 1;
    return BTB_SESSION_OK;
}
