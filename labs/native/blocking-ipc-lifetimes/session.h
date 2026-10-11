/*-----------------------------------------------------------------------------
 * Bits to Banking — Umicom Foundation
 * File: labs/native/blocking-ipc-lifetimes/session.h
 * PURPOSE: Compose, rather than duplicate, prior C23 queue and scheduler labs.
 * AUTHOR AND ORGANISATION: Sammy Hegab, Umicom Foundation
 * LICENCE: MIT
 *---------------------------------------------------------------------------*/
#ifndef BTB_BLOCKING_SESSION_H
#define BTB_BLOCKING_SESSION_H
#include "round_robin.h"
#include "channel.h"

typedef enum BtbSessionStatus {
    BTB_SESSION_OK = 0,
    BTB_SESSION_READY = 1,
    BTB_SESSION_WOULD_BLOCK = 2,
    BTB_SESSION_CLOSED = 3,
    BTB_SESSION_INVALID = 4,
    BTB_SESSION_BAD_STATE = 5,
    BTB_SESSION_FULL = 6,
    BTB_SESSION_DENIED = 7,
    BTB_SESSION_SMALL_BUFFER = 8
} BtbSessionStatus;

typedef struct BtbServiceSession {
    BtbRoundRobin *scheduler; /* Borrowed; owner must keep alive, single-threaded. */
    BtbChannel *channel;     /* Borrowed; queue ownership remains with caller. */
    BtbTaskHandle receiverTask;
    uint32_t senderIdentity;
    uint32_t receiverIdentity;
    uint32_t waitKey;
    int waiting;
    int closed;
} BtbServiceSession;

/* A newly created service is initialised while its receiving task is running.
 * Exactly one owner may call these functions; there are no background threads,
 * callbacks or asynchronous socket/kernel operations in this training model. */
BtbSessionStatus BtbSessionInit(BtbServiceSession *session, BtbRoundRobin *scheduler,
    BtbChannel *channel, BtbTaskHandle receiverTask, uint32_t senderIdentity,
    uint32_t receiverIdentity, uint32_t waitKey);
BtbSessionStatus BtbSessionWaitForMessage(BtbServiceSession *session);
BtbSessionStatus BtbSessionPoll(BtbServiceSession *session);
BtbSessionStatus BtbSessionSend(BtbServiceSession *session,
    const void *payload, size_t length, uint64_t *outSequence);
BtbSessionStatus BtbSessionReceive(BtbServiceSession *session,
    void *destination, size_t capacity, uint32_t *outSender,
    size_t *outLength, uint64_t *outSequence);
/* Close the running or waiting service task. This does not destroy the shared
 * queue or retract messages already accepted. The caller still owns channel. */
BtbSessionStatus BtbSessionClose(BtbServiceSession *session);
#endif
