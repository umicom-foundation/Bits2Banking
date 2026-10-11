/*-----------------------------------------------------------------------------
 * Bits to Banking — Umicom Foundation
 * File: labs/native/timed-service-waits/service.h
 * PURPOSE: Compose the existing scheduler and logical timer without copying
 *          their state machines or pretending to implement kernel interrupts.
 * AUTHOR AND ORGANISATION: Sammy Hegab, Umicom Foundation
 * LICENCE: MIT
 *---------------------------------------------------------------------------*/
#ifndef BTB_TIMED_SERVICE_H
#define BTB_TIMED_SERVICE_H
#include "round_robin.h"
#include "deadline.h"

typedef enum BtbTimedStatus {
    BTB_TIMED_OK = 0,
    BTB_TIMED_PENDING = 1,
    BTB_TIMED_TIMEOUT = 2,
    BTB_TIMED_CANCELLED = 3,
    BTB_TIMED_INVALID = 4,
    BTB_TIMED_BAD_STATE = 5,
    BTB_TIMED_OVERFLOW = 6,
    BTB_TIMED_WRONG_EVENT = 7,
    BTB_TIMED_DUE = 8
} BtbTimedStatus;
typedef enum BtbWaitOutcome {
    BTB_WAIT_NO_RESULT = 0,
    BTB_WAIT_EVENT = 1,
    BTB_WAIT_TIMEOUT = 2,
    BTB_WAIT_CANCELLED = 3
} BtbWaitOutcome;
typedef struct BtbTimedWaitService {
    BtbRoundRobin *scheduler; /* Borrowed, single-threaded, not freed here. */
    BtbLogicalClock *clock;  /* Borrowed; source of time is caller-owned. */
    BtbTaskHandle task;
    uint32_t eventKey;
    BtbDeadline deadline;   /* Service owns the one pending timer. */
    BtbWaitOutcome outcome;
    int waiting;
} BtbTimedWaitService;

/* The caller creates/disposes scheduler and clock. No real timer, message,
 * process or thread is created by these functions. The caller invokes Pump
 * explicitly when advancing logical time. Only one owner may mutate state. */
BtbTimedStatus BtbTimedWaitInit(BtbTimedWaitService *service,
    BtbRoundRobin *scheduler, BtbLogicalClock *clock, BtbTaskHandle task,
    uint32_t eventKey);
BtbTimedStatus BtbTimedWaitStart(BtbTimedWaitService *service, uint64_t ticks);
/* A wrong key cannot wake the task. A signal at the deadline cannot beat a
 * due timeout. A wake marks task READY, not RUNNING. */
BtbTimedStatus BtbTimedWaitSignal(BtbTimedWaitService *service, uint32_t eventKey);
BtbTimedStatus BtbTimedWaitPump(BtbTimedWaitService *service);
BtbTimedStatus BtbTimedWaitCancel(BtbTimedWaitService *service);
#endif
