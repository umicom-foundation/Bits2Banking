/*-----------------------------------------------------------------------------
 * Bits to Banking — Umicom Foundation
 * File: labs/native/monotonic-deadlines/deadline.c
 * PURPOSE: Refuse time reversal and overflow before updating owned state.
 * AUTHOR AND ORGANISATION: Sammy Hegab, Umicom Foundation
 * LICENCE: MIT
 *---------------------------------------------------------------------------*/
#include "deadline.h"
void BtbClockInit(BtbLogicalClock *clock)
{
    if (clock != 0) clock->now = 0U;
}
BtbTimerResult BtbClockAdvance(BtbLogicalClock *clock, uint64_t nextTick)
{
    if (clock == 0) return BTB_TIMER_INVALID;
    if (nextTick <= clock->now) return BTB_TIMER_STATE;
    clock->now = nextTick;
    return BTB_TIMER_OK;
}
void BtbDeadlineInit(BtbDeadline *timer)
{
    if (timer != 0) *timer = (BtbDeadline){0};
}
BtbTimerResult BtbDeadlineArm(BtbDeadline *timer, const BtbLogicalClock *clock,
                              uint64_t interval)
{
    if (timer == 0 || clock == 0) return BTB_TIMER_INVALID;
    if (timer->state == BTB_TIMER_PENDING) return BTB_TIMER_STATE;
    if (interval > BTB_TIMER_MAX_INTERVAL) return BTB_TIMER_INVALID;
    if (interval != 0U && clock->now > UINT64_MAX - interval)
        return BTB_TIMER_OVERFLOW;
    const BtbDeadline ready = {
        .until = interval == 0U ? 0U : clock->now + interval,
        .state = BTB_TIMER_PENDING
    };
    *timer = ready;
    return BTB_TIMER_OK;
}
BtbTimerResult BtbDeadlineStatus(const BtbDeadline *timer,
                                 const BtbLogicalClock *clock)
{
    if (timer == 0 || clock == 0) return BTB_TIMER_INVALID;
    if (timer->state != BTB_TIMER_PENDING) return BTB_TIMER_STATE;
    return timer->until != 0U && clock->now >= timer->until ?
        BTB_TIMER_DUE : BTB_TIMER_NOT_DUE;
}
BtbTimerResult BtbDeadlineFire(BtbDeadline *timer, const BtbLogicalClock *clock)
{
    const BtbTimerResult status = BtbDeadlineStatus(timer, clock);
    if (status != BTB_TIMER_DUE) return status;
    timer->state = BTB_TIMER_FIRED;
    return BTB_TIMER_OK;
}
BtbTimerResult BtbDeadlineCancel(BtbDeadline *timer, const BtbLogicalClock *clock)
{
    const BtbTimerResult status = BtbDeadlineStatus(timer, clock);
    if (status != BTB_TIMER_NOT_DUE) return status;
    timer->state = BTB_TIMER_CANCELLED;
    return BTB_TIMER_OK;
}
