/* Bits to Banking | Umicom Foundation | MIT
 * A Notes task waits for a simulated event, then receives a timeout. */
#include "service.h"
#include <stdio.h>
int main(void)
{
    BtbRoundRobin scheduler;
    BtbLogicalClock clock;
    BtbTaskHandle task = 0U, next = 0U;
    BtbTimedWaitService service = {0};
    BtbRoundRobinInit(&scheduler);
    BtbClockInit(&clock);
    if (BtbRoundRobinAdmit(&scheduler, &task) != BTB_SCHED_OK ||
        BtbRoundRobinNext(&scheduler, &next) != BTB_SCHED_OK || next != task ||
        BtbTimedWaitInit(&service, &scheduler, &clock, task, 42U) != BTB_TIMED_OK ||
        BtbClockAdvance(&clock, 100U) != BTB_TIMER_OK ||
        BtbTimedWaitStart(&service, 5U) != BTB_TIMED_PENDING ||
        BtbClockAdvance(&clock, 105U) != BTB_TIMER_OK ||
        BtbTimedWaitPump(&service) != BTB_TIMED_TIMEOUT)
        return 1;
    printf("Notes timed out at tick %llu; status is READY, not RUNNING.\n",
           (unsigned long long)clock.now);
    if (BtbRoundRobinNext(&scheduler, &next) != BTB_SCHED_OK || next != task ||
        BtbRoundRobinExit(&scheduler, task) != BTB_SCHED_OK) return 1;
    puts("The scheduler dispatched Notes and completed its lifetime.");
    return 0;
}
