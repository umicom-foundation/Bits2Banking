/* Bits to Banking | Umicom Foundation | MIT
 * Deterministic tests for time overflow, lifetime, deadline ties and rollback. */
#include "deadline.h"
#include <stdint.h>
#include <stdio.h>
#include <string.h>
#define CHECK(c) do { if (!(c)) { fprintf(stderr, "FAIL %s:%d %s\n",__FILE__,__LINE__,#c); return 1; } } while (0)
static int Boundary(void)
{
    BtbLogicalClock clock;
    BtbDeadline timer;
    BtbClockInit(&clock); BtbDeadlineInit(&timer);
    CHECK(BtbClockAdvance(&clock, 10U) == BTB_TIMER_OK);
    CHECK(BtbDeadlineArm(&timer, &clock, 5U) == BTB_TIMER_OK);
    CHECK(BtbDeadlineStatus(&timer, &clock) == BTB_TIMER_NOT_DUE);
    CHECK(BtbClockAdvance(&clock, 14U) == BTB_TIMER_OK);
    CHECK(BtbDeadlineStatus(&timer, &clock) == BTB_TIMER_NOT_DUE);
    CHECK(BtbClockAdvance(&clock, 15U) == BTB_TIMER_OK);
    CHECK(BtbDeadlineStatus(&timer, &clock) == BTB_TIMER_DUE);
    CHECK(BtbDeadlineCancel(&timer, &clock) == BTB_TIMER_DUE);
    CHECK(BtbDeadlineFire(&timer, &clock) == BTB_TIMER_OK);
    CHECK(timer.state == BTB_TIMER_FIRED);
    CHECK(BtbDeadlineFire(&timer, &clock) == BTB_TIMER_STATE);
    CHECK(BtbDeadlineArm(&timer, &clock, 0U) == BTB_TIMER_OK);
    CHECK(BtbDeadlineStatus(&timer, &clock) == BTB_TIMER_NOT_DUE);
    CHECK(BtbClockAdvance(&clock, UINT64_MAX) == BTB_TIMER_OK);
    CHECK(BtbDeadlineStatus(&timer, &clock) == BTB_TIMER_NOT_DUE);
    CHECK(BtbDeadlineCancel(&timer, &clock) == BTB_TIMER_OK);
    BtbDeadline previous = timer;
    CHECK(BtbDeadlineArm(&timer, &clock, 1U) == BTB_TIMER_OVERFLOW);
    CHECK(memcmp(&timer, &previous, sizeof(previous)) == 0);
    CHECK(BtbClockAdvance(&clock, 9U) == BTB_TIMER_STATE);
    CHECK(clock.now == UINT64_MAX);
    return 0;
}
static int Calculations(void)
{
    /* Every rejected attempt keeps the caller's prior state intact. */
    for (uint64_t now = 1U; now < 1024U; ++now) {
        BtbLogicalClock clock = {now};
        BtbDeadline timer = {0};
        CHECK(BtbDeadlineArm(&timer, &clock, 3U) == BTB_TIMER_OK);
        const BtbDeadline prior = timer;
        CHECK(BtbDeadlineArm(&timer, &clock, 4U) == BTB_TIMER_STATE);
        CHECK(memcmp(&timer, &prior, sizeof(prior)) == 0);
        CHECK(BtbClockAdvance(&clock, now + 2U) == BTB_TIMER_OK);
        CHECK(BtbDeadlineStatus(&timer, &clock) == BTB_TIMER_NOT_DUE);
        CHECK(BtbClockAdvance(&clock, now + 3U) == BTB_TIMER_OK);
        CHECK(BtbDeadlineFire(&timer, &clock) == BTB_TIMER_OK);
        CHECK(timer.until == now + 3U);
    }
    return 0;
}
int main(void)
{
    CHECK(Boundary() == 0);
    CHECK(Calculations() == 0);
    puts("Monotonic deadlines: passed.");
    return 0;
}
