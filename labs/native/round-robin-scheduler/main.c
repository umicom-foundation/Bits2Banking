/* Bits2Banking | Umicom Foundation | MIT | Notes and reporting ready queue. */
#include "round_robin.h"
#include <stdio.h>
int main(void)
{
    BtbRoundRobin queue; BtbRoundRobinInit(&queue);
    BtbTaskHandle notes=0U, report=0U, current=0U;
    if (BtbRoundRobinAdmit(&queue, &notes) != BTB_SCHED_OK ||
        BtbRoundRobinAdmit(&queue, &report) != BTB_SCHED_OK ||
        BtbRoundRobinNext(&queue, &current) != BTB_SCHED_OK) return 1;
    puts("Notes is running.");
    if (current != notes || BtbRoundRobinWait(&queue, notes, 7U) != BTB_SCHED_OK ||
        BtbRoundRobinNext(&queue, &current) != BTB_SCHED_OK ||
        current != report || BtbRoundRobinYield(&queue, report) != BTB_SCHED_OK ||
        BtbRoundRobinWake(&queue, notes, 7U) != BTB_SCHED_OK ||
        BtbRoundRobinNext(&queue, &current) != BTB_SCHED_OK ||
        current != report) return 1;
    puts("Reports runs before the newly woken Notes task.");
    return 0;
}
