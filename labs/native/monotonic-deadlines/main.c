/* Bits to Banking | Umicom Foundation | MIT
 * Demonstrate deadline precedence without sleeping or busy waiting. */
#include "deadline.h"
#include <stdio.h>
int main(void)
{
    BtbLogicalClock clock;
    BtbDeadline timer;
    BtbClockInit(&clock);
    BtbDeadlineInit(&timer);
    if (BtbClockAdvance(&clock, 100U) != BTB_TIMER_OK ||
        BtbDeadlineArm(&timer, &clock, 5U) != BTB_TIMER_OK)
        return 1;
    printf("Notes service deadline: tick %llu\n",
           (unsigned long long)timer.until);
    if (BtbClockAdvance(&clock, 105U) != BTB_TIMER_OK ||
        BtbDeadlineFire(&timer, &clock) != BTB_TIMER_OK)
        return 1;
    puts("Timer expired at tick 105. The task may now be made Ready.");
    return 0;
}
