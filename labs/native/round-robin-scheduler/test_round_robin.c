/* Bits2Banking | Umicom Foundation | MIT | Verify single-thread scheduling. */
#include "round_robin.h"
#include <stdio.h>
#include <string.h>
#define CHECK(x) do { if (!(x)) { fprintf(stderr, "FAIL %s:%d: %s\n", __FILE__, __LINE__, #x); return 1; } } while(0)
static int Sequence(void)
{
    BtbRoundRobin scheduler; BtbRoundRobinInit(&scheduler);
    BtbTaskHandle notes=0, reports=0, running=0;
    CHECK(BtbRoundRobinAdmit(&scheduler, &notes) == BTB_SCHED_OK);
    CHECK(BtbRoundRobinAdmit(&scheduler, &reports) == BTB_SCHED_OK);
    CHECK(BtbRoundRobinNext(&scheduler, &running) == BTB_SCHED_OK && running == notes);
    CHECK(BtbRoundRobinWait(&scheduler, notes, 17U) == BTB_SCHED_OK);
    CHECK(BtbRoundRobinNext(&scheduler, &running) == BTB_SCHED_OK && running == reports);
    CHECK(BtbRoundRobinYield(&scheduler, reports) == BTB_SCHED_OK);
    CHECK(BtbRoundRobinWake(&scheduler, notes, 17U) == BTB_SCHED_OK);
    /* Reports was ready before Notes was woken: FIFO fairness. */
    CHECK(BtbRoundRobinNext(&scheduler, &running) == BTB_SCHED_OK && running == reports);
    CHECK(BtbRoundRobinExit(&scheduler, reports) == BTB_SCHED_OK);
    CHECK(BtbRoundRobinNext(&scheduler, &running) == BTB_SCHED_OK && running == notes);
    CHECK(BtbRoundRobinExit(&scheduler, notes) == BTB_SCHED_OK);
    BtbSchedSnapshot snapshot = {0};
    CHECK(BtbRoundRobinSnapshotRead(&scheduler, &snapshot) == BTB_SCHED_OK);
    CHECK(snapshot.live == 0U && snapshot.ready == 0U && snapshot.waiting == 0U);
    BtbTaskHandle next = 0U;
    CHECK(BtbRoundRobinAdmit(&scheduler, &next) == BTB_SCHED_OK);
    CHECK(next != notes && BtbRoundRobinYield(&scheduler, notes) == BTB_SCHED_STALE);
    puts("[OK] FIFO ready order, blocked tasks, wake-up, generation and exits.");
    return 0;
}
static int Refusals(void)
{
    BtbRoundRobin s; BtbRoundRobinInit(&s);
    BtbTaskHandle a=0U, active=777U;
    CHECK(BtbRoundRobinNext(&s, &active) == BTB_SCHED_EMPTY && active == 777U);
    CHECK(BtbRoundRobinAdmit(&s, &a) == BTB_SCHED_OK);
    CHECK(BtbRoundRobinYield(&s, a) == BTB_SCHED_BAD_STATE);
    CHECK(BtbRoundRobinNext(&s, &active) == BTB_SCHED_OK && active == a);
    CHECK(BtbRoundRobinNext(&s, &active) == BTB_SCHED_BUSY);
    CHECK(BtbRoundRobinWait(&s, a, 0U) == BTB_SCHED_INVALID);
    CHECK(BtbRoundRobinWait(&s, a, 8U) == BTB_SCHED_OK);
    CHECK(BtbRoundRobinWake(&s, a, 7U) == BTB_SCHED_BAD_STATE);
    CHECK(BtbRoundRobinCancelWait(&s, a, 7U) == BTB_SCHED_BAD_STATE);
    CHECK(BtbRoundRobinCancelWait(&s, a, 8U) == BTB_SCHED_OK);
    CHECK(BtbRoundRobinWake(&s, a, 8U) == BTB_SCHED_STALE);
    BtbSchedSnapshot snap = {0};
    CHECK(BtbRoundRobinSnapshotRead(&s, &snap) == BTB_SCHED_OK && snap.live == 0U);
    /* Full queue and intentionally unreusable old handle; state must survive. */
    BtbTaskHandle handles[BTB_RR_TASK_LIMIT];
    for (size_t i=0U; i<BTB_RR_TASK_LIMIT; ++i)
        CHECK(BtbRoundRobinAdmit(&s, &handles[i]) == BTB_SCHED_OK);
    BtbTaskHandle sentinel = UINT64_C(0x12345678);
    CHECK(BtbRoundRobinAdmit(&s, &sentinel) == BTB_SCHED_CAPACITY &&
          sentinel == UINT64_C(0x12345678));
    CHECK(BtbRoundRobinSnapshotRead(&s, &snap) == BTB_SCHED_OK && snap.live == BTB_RR_TASK_LIMIT);
    puts("[OK] Refusals leave results and queued tasks unchanged.");
    return 0;
}
int main(int argc, char **argv)
{
    if (argc != 2) return 2;
    if (strcmp(argv[1], "sequence") == 0) return Sequence();
    if (strcmp(argv[1], "refusals") == 0) return Refusals();
    return 2;
}
