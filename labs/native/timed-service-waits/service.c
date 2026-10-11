/*-----------------------------------------------------------------------------
 * Bits to Banking — Umicom Foundation
 * File: labs/native/timed-service-waits/service.c
 * PURPOSE: Join one existing scheduler task with one owned deadline.
 * AUTHOR AND ORGANISATION: Sammy Hegab, Umicom Foundation
 * LICENCE: MIT
 *---------------------------------------------------------------------------*/
#include "service.h"
#include <stddef.h>

static int Running(BtbTimedWaitService *service)
{
    BtbSchedSnapshot snapshot = {0};
    return BtbRoundRobinSnapshotRead(service->scheduler, &snapshot) == BTB_SCHED_OK &&
           snapshot.runningTask == service->task;
}
BtbTimedStatus BtbTimedWaitInit(BtbTimedWaitService *service,
    BtbRoundRobin *scheduler, BtbLogicalClock *clock, BtbTaskHandle task,
    uint32_t eventKey)
{
    if (service == NULL || scheduler == NULL || clock == NULL ||
        task == 0U || eventKey == 0U) return BTB_TIMED_INVALID;
    BtbSchedSnapshot snapshot = {0};
    if (BtbRoundRobinSnapshotRead(scheduler, &snapshot) != BTB_SCHED_OK ||
        snapshot.runningTask != task) return BTB_TIMED_BAD_STATE;
    BtbTimedWaitService next = {0};
    next.scheduler = scheduler;
    next.clock = clock;
    next.task = task;
    next.eventKey = eventKey;
    BtbDeadlineInit(&next.deadline);
    *service = next;
    return BTB_TIMED_OK;
}
BtbTimedStatus BtbTimedWaitStart(BtbTimedWaitService *service, uint64_t ticks)
{
    if (service == NULL || service->scheduler == NULL || service->clock == NULL)
        return BTB_TIMED_INVALID;
    if (service->waiting || !Running(service)) return BTB_TIMED_BAD_STATE;
    /* Check timer arithmetic before changing scheduler state; the task must
     * remain running after any rejected overflow or oversized interval. */
    BtbDeadline preparedTimer = service->deadline;
    const BtbTimerResult armed = BtbDeadlineArm(&preparedTimer, service->clock, ticks);
    if (armed == BTB_TIMER_OVERFLOW) return BTB_TIMED_OVERFLOW;
    if (armed != BTB_TIMER_OK) return BTB_TIMED_INVALID;
    if (BtbRoundRobinWait(service->scheduler, service->task, service->eventKey) != BTB_SCHED_OK)
        return BTB_TIMED_BAD_STATE;
    /* The scheduler accepted the wait. No allocation, callback or other owner
     * can intervene before the prepared timer becomes the published timer. */
    service->deadline = preparedTimer;
    service->waiting = 1;
    service->outcome = BTB_WAIT_NO_RESULT;
    return BTB_TIMED_PENDING;
}
BtbTimedStatus BtbTimedWaitSignal(BtbTimedWaitService *service, uint32_t eventKey)
{
    if (service == NULL || service->clock == NULL || service->scheduler == NULL)
        return BTB_TIMED_INVALID;
    if (!service->waiting) return BTB_TIMED_BAD_STATE;
    if (eventKey != service->eventKey) return BTB_TIMED_WRONG_EVENT;
    const BtbTimerResult due = BtbDeadlineStatus(&service->deadline, service->clock);
    if (due == BTB_TIMER_DUE) return BTB_TIMED_DUE;
    if (due != BTB_TIMER_NOT_DUE) return BTB_TIMED_BAD_STATE;
    BtbDeadline completedTimer = service->deadline;
    if (BtbDeadlineCancel(&completedTimer, service->clock) != BTB_TIMER_OK)
        return BTB_TIMED_BAD_STATE;
    if (BtbRoundRobinWake(service->scheduler, service->task, service->eventKey) != BTB_SCHED_OK)
        return BTB_TIMED_BAD_STATE;
    service->deadline = completedTimer;
    service->waiting = 0;
    service->outcome = BTB_WAIT_EVENT;
    return BTB_TIMED_OK;
}
BtbTimedStatus BtbTimedWaitPump(BtbTimedWaitService *service)
{
    if (service == NULL || service->clock == NULL || service->scheduler == NULL)
        return BTB_TIMED_INVALID;
    if (!service->waiting) return BTB_TIMED_BAD_STATE;
    const BtbTimerResult status = BtbDeadlineStatus(&service->deadline, service->clock);
    if (status == BTB_TIMER_NOT_DUE) return BTB_TIMED_PENDING;
    if (status != BTB_TIMER_DUE) return BTB_TIMED_BAD_STATE;
    BtbDeadline completedTimer = service->deadline;
    if (BtbDeadlineFire(&completedTimer, service->clock) != BTB_TIMER_OK)
        return BTB_TIMED_BAD_STATE;
    if (BtbRoundRobinWake(service->scheduler, service->task, service->eventKey) != BTB_SCHED_OK)
        return BTB_TIMED_BAD_STATE;
    service->deadline = completedTimer;
    service->waiting = 0;
    service->outcome = BTB_WAIT_TIMEOUT;
    return BTB_TIMED_TIMEOUT;
}
BtbTimedStatus BtbTimedWaitCancel(BtbTimedWaitService *service)
{
    if (service == NULL || service->clock == NULL || service->scheduler == NULL)
        return BTB_TIMED_INVALID;
    if (!service->waiting) return BTB_TIMED_BAD_STATE;
    const BtbTimerResult status = BtbDeadlineStatus(&service->deadline, service->clock);
    if (status == BTB_TIMER_DUE) return BTB_TIMED_DUE;
    if (status != BTB_TIMER_NOT_DUE) return BTB_TIMED_BAD_STATE;
    BtbDeadline completedTimer = service->deadline;
    if (BtbDeadlineCancel(&completedTimer, service->clock) != BTB_TIMER_OK)
        return BTB_TIMED_BAD_STATE;
    if (BtbRoundRobinCancelWait(service->scheduler, service->task, service->eventKey) != BTB_SCHED_OK)
        return BTB_TIMED_BAD_STATE;
    service->deadline = completedTimer;
    service->waiting = 0;
    service->outcome = BTB_WAIT_CANCELLED;
    return BTB_TIMED_CANCELLED;
}
