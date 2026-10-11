/*-----------------------------------------------------------------------------
 * Bits to Banking — Umicom Foundation
 * File: labs/native/monotonic-deadlines/deadline.h
 * PURPOSE: Own a deterministic logical clock and a checked one-shot timer.
 * AUTHOR AND ORGANISATION: Sammy Hegab, Umicom Foundation
 * LICENCE: MIT
 *---------------------------------------------------------------------------*/
#ifndef BTB_DEADLINE_H
#define BTB_DEADLINE_H
#include <stdint.h>
#define BTB_TIMER_MAX_INTERVAL UINT64_C(10000000)
typedef enum BtbTimerResult {
    BTB_TIMER_OK = 0,
    BTB_TIMER_INVALID = 1,
    BTB_TIMER_STATE = 2,
    BTB_TIMER_OVERFLOW = 3,
    BTB_TIMER_NOT_DUE = 4,
    BTB_TIMER_DUE = 5
} BtbTimerResult;
typedef enum BtbTimerState {
    BTB_TIMER_IDLE = 0,
    BTB_TIMER_PENDING = 1,
    BTB_TIMER_FIRED = 2,
    BTB_TIMER_CANCELLED = 3
} BtbTimerState;
typedef struct BtbLogicalClock {
    uint64_t now;
} BtbLogicalClock;
typedef struct BtbDeadline {
    uint64_t until;       /* Zero denotes no finite deadline. */
    BtbTimerState state;
} BtbDeadline;

/* Pure, hosted C23 teaching model, not an operating-system clock. Never
 * pretend a logical tick represents a millisecond or a particular frequency. */
void BtbClockInit(BtbLogicalClock *clock);
BtbTimerResult BtbClockAdvance(BtbLogicalClock *clock, uint64_t nextTick);
void BtbDeadlineInit(BtbDeadline *timer);
/* A zero interval arms an unbounded wait. Positive intervals must fit
 * 1..10,000,000 logical ticks and must not overflow the clock. Rejected calls
 * preserve the timer. A prior fired/cancelled timer may be rearmed explicitly. */
BtbTimerResult BtbDeadlineArm(BtbDeadline *timer, const BtbLogicalClock *clock,
                              uint64_t interval);
BtbTimerResult BtbDeadlineStatus(const BtbDeadline *timer,
                                 const BtbLogicalClock *clock);
BtbTimerResult BtbDeadlineFire(BtbDeadline *timer, const BtbLogicalClock *clock);
BtbTimerResult BtbDeadlineCancel(BtbDeadline *timer, const BtbLogicalClock *clock);
#endif
