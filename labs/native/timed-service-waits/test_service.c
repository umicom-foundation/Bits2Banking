/* Bits to Banking | Umicom Foundation | MIT
 * Checked wake-up, exact-deadline tie, cancellation and arithmetic rollback. */
#include "service.h"
#include <stdint.h>
#include <stdio.h>
#define CHECK(c) do { if (!(c)) { fprintf(stderr,"FAIL %s:%d %s\n",__FILE__,__LINE__,#c); return 1; } } while (0)
static int Setup(BtbRoundRobin *scheduler, BtbLogicalClock *clock,
                 BtbTimedWaitService *service, BtbTaskHandle *task)
{
    BtbTaskHandle selected = 0U;
    BtbRoundRobinInit(scheduler); BtbClockInit(clock);
    CHECK(BtbRoundRobinAdmit(scheduler, task) == BTB_SCHED_OK);
    CHECK(BtbRoundRobinNext(scheduler, &selected) == BTB_SCHED_OK);
    CHECK(selected == *task);
    CHECK(BtbTimedWaitInit(service, scheduler, clock, *task, 11U) == BTB_TIMED_OK);
    return 0;
}
static int Delivery(void)
{
    BtbRoundRobin scheduler;
    BtbLogicalClock clock;
    BtbTimedWaitService service = {0};
    BtbTaskHandle task = 0U, selected = 0U;
    CHECK(Setup(&scheduler, &clock, &service, &task) == 0);
    CHECK(BtbClockAdvance(&clock, 100U) == BTB_TIMER_OK);
    CHECK(BtbTimedWaitStart(&service, 5U) == BTB_TIMED_PENDING);
    CHECK(BtbTimedWaitSignal(&service, 12U) == BTB_TIMED_WRONG_EVENT);
    BtbSchedSnapshot snapshot = {0};
    CHECK(BtbRoundRobinSnapshotRead(&scheduler, &snapshot) == BTB_SCHED_OK);
    CHECK(snapshot.waiting == 1U && snapshot.ready == 0U);
    CHECK(BtbClockAdvance(&clock, 104U) == BTB_TIMER_OK);
    CHECK(BtbTimedWaitSignal(&service, 11U) == BTB_TIMED_OK);
    CHECK(service.outcome == BTB_WAIT_EVENT && service.waiting == 0);
    CHECK(BtbRoundRobinSnapshotRead(&scheduler, &snapshot) == BTB_SCHED_OK);
    CHECK(snapshot.ready == 1U && snapshot.waiting == 0U && snapshot.running == 0U);
    CHECK(BtbRoundRobinNext(&scheduler, &selected) == BTB_SCHED_OK && selected == task);
    CHECK(BtbRoundRobinExit(&scheduler, task) == BTB_SCHED_OK);
    CHECK(BtbTimedWaitSignal(&service, 11U) == BTB_TIMED_BAD_STATE);
    return 0;
}
static int TimeoutTies(void)
{
    BtbRoundRobin scheduler;
    BtbLogicalClock clock;
    BtbTimedWaitService service = {0};
    BtbTaskHandle task = 0U, selected = 0U;
    CHECK(Setup(&scheduler, &clock, &service, &task) == 0);
    CHECK(BtbClockAdvance(&clock, 200U) == BTB_TIMER_OK);
    CHECK(BtbTimedWaitStart(&service, 3U) == BTB_TIMED_PENDING);
    CHECK(BtbTimedWaitPump(&service) == BTB_TIMED_PENDING);
    CHECK(BtbClockAdvance(&clock, 203U) == BTB_TIMER_OK);
    CHECK(BtbTimedWaitSignal(&service, 11U) == BTB_TIMED_DUE);
    CHECK(BtbTimedWaitCancel(&service) == BTB_TIMED_DUE);
    CHECK(BtbTimedWaitPump(&service) == BTB_TIMED_TIMEOUT);
    CHECK(service.outcome == BTB_WAIT_TIMEOUT);
    CHECK(BtbRoundRobinNext(&scheduler, &selected) == BTB_SCHED_OK && selected == task);
    CHECK(BtbRoundRobinExit(&scheduler, task) == BTB_SCHED_OK);
    return 0;
}
static int CancelAndOverflow(void)
{
    BtbRoundRobin scheduler;
    BtbLogicalClock clock;
    BtbTimedWaitService service = {0};
    BtbTaskHandle task = 0U, selected = 0U;
    CHECK(Setup(&scheduler, &clock, &service, &task) == 0);
    CHECK(BtbClockAdvance(&clock, UINT64_MAX) == BTB_TIMER_OK);
    CHECK(BtbTimedWaitStart(&service, 1U) == BTB_TIMED_OVERFLOW);
    BtbSchedSnapshot snapshot = {0};
    CHECK(BtbRoundRobinSnapshotRead(&scheduler, &snapshot) == BTB_SCHED_OK);
    CHECK(snapshot.runningTask == task && snapshot.waiting == 0U);
    CHECK(BtbTimedWaitStart(&service, 0U) == BTB_TIMED_PENDING);
    CHECK(BtbTimedWaitCancel(&service) == BTB_TIMED_CANCELLED);
    CHECK(service.outcome == BTB_WAIT_CANCELLED);
    CHECK(BtbTimedWaitPump(&service) == BTB_TIMED_BAD_STATE);
    CHECK(BtbRoundRobinNext(&scheduler, &selected) == BTB_SCHED_EMPTY);
    return 0;
}
int main(int argc, char **argv)
{
    if (argc != 2) return 2;
    if (argv[1][0] == 'd') return Delivery();
    if (argv[1][0] == 't') return TimeoutTies();
    if (argv[1][0] == 'c') return CancelAndOverflow();
    return 2;
}
