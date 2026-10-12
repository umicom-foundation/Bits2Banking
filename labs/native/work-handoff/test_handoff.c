/* Bits2Banking | Umicom Foundation | Sammy Hegab | MIT
 * Deterministic contract tests; no Python, sockets or concurrent threads. */
#include "handoff.h"
#include <assert.h>
#include <stdio.h>
#include <string.h>

static void BtbTestFifo(void)
{
    BtbWorkQueue q;
    assert(BtbWorkInit(&q, 2U) == BTB_WORK_OK);
    BtbWorkToken tokens[BTB_WORK_CAPACITY];
    for (size_t i = 0U; i < BTB_WORK_CAPACITY; ++i) {
        const unsigned char request = (unsigned char)(i + 1U);
        assert(BtbWorkSubmit(&q, (uint64_t)i + 1U, &request, 1U, &tokens[i]) == BTB_WORK_OK);
    }
    BtbWorkToken rejected;
    assert(BtbWorkSubmit(&q, 12U, "x", 1U, &rejected) == BTB_WORK_FULL);
    assert(BtbWorkInvariants(&q));
    BtbWorkToken current;
    const BtbWorkItem *item;
    for (size_t i = 0U; i < BTB_WORK_CAPACITY; ++i) {
        assert(BtbWorkAcquire(&q, &current, &item) == BTB_WORK_OK);
        assert(item->connectionId == i + 1U);
        assert(item->payload[0] == (unsigned char)(i + 1U));
        assert(BtbWorkComplete(&q, current) == BTB_WORK_OK);
        assert(BtbWorkRelease(&q, current) == BTB_WORK_OK);
        assert(BtbWorkInvariants(&q));
    }
}

static void BtbTestCancellation(void)
{
    BtbWorkQueue q;
    assert(BtbWorkInit(&q, 1U) == BTB_WORK_OK);
    BtbWorkToken a, b, c, current;
    const BtbWorkItem *item;
    assert(BtbWorkSubmit(&q, 1U, "A", 1U, &a) == BTB_WORK_OK);
    assert(BtbWorkSubmit(&q, 2U, "B", 1U, &b) == BTB_WORK_OK);
    assert(BtbWorkSubmit(&q, 3U, "C", 1U, &c) == BTB_WORK_OK);
    assert(BtbWorkCancel(&q, b) == BTB_WORK_OK);
    assert(BtbWorkRelease(&q, b) == BTB_WORK_OK);
    assert(BtbWorkAcquire(&q, &current, &item) == BTB_WORK_OK);
    assert(current.generation == a.generation && current.slot == a.slot);
    assert(BtbWorkAcquire(&q, &current, &item) == BTB_WORK_BUSY);
    assert(BtbWorkCancel(&q, a) == BTB_WORK_OK);
    assert(BtbWorkRelease(&q, a) == BTB_WORK_OK);
    assert(BtbWorkAcquire(&q, &current, &item) == BTB_WORK_OK);
    assert(current.slot == c.slot && current.generation == c.generation);
    assert(BtbWorkComplete(&q, current) == BTB_WORK_OK);
    assert(BtbWorkRelease(&q, current) == BTB_WORK_OK);
    assert(BtbWorkInvariants(&q));
}

static void BtbTestGenerationAndShutdown(void)
{
    BtbWorkQueue q;
    assert(BtbWorkInit(&q, 1U) == BTB_WORK_OK);
    BtbWorkToken old, newer, active;
    const BtbWorkItem *item;
    assert(BtbWorkSubmit(&q, 7U, "x", 1U, &old) == BTB_WORK_OK);
    assert(BtbWorkAcquire(&q, &active, &item) == BTB_WORK_OK);
    assert(BtbWorkComplete(&q, active) == BTB_WORK_OK);
    assert(BtbWorkRelease(&q, active) == BTB_WORK_OK);
    assert(BtbWorkSubmit(&q, 8U, "y", 1U, &newer) == BTB_WORK_OK);
    assert(newer.slot == old.slot && newer.generation != old.generation);
    assert(BtbWorkComplete(&q, old) == BTB_WORK_STALE);
    BtbWorkQuiesce(&q);
    assert(BtbWorkSubmit(&q, 9U, "z", 1U, &active) == BTB_WORK_SHUTDOWN);
    assert(!BtbWorkDrained(&q));
    assert(BtbWorkCancel(&q, newer) == BTB_WORK_OK);
    assert(BtbWorkDrained(&q));
    assert(BtbWorkRelease(&q, newer) == BTB_WORK_OK);
    assert(BtbWorkInvariants(&q));
}

static uint32_t BtbNext(uint32_t *seed)
{
    *seed = *seed * UINT32_C(1664525) + UINT32_C(1013904223);
    return *seed;
}

static void BtbTestMutations(void)
{
    BtbWorkQueue q;
    BtbWorkToken known[BTB_WORK_CAPACITY];
    assert(BtbWorkInit(&q, 3U) == BTB_WORK_OK);
    memset(known, 0, sizeof(known));
    uint32_t seed = UINT32_C(729);
    for (size_t step = 0U; step < 50000U; ++step) {
        const uint32_t op = BtbNext(&seed) % 4U;
        if (op == 0U) {
            BtbWorkToken token;
            if (BtbWorkSubmit(&q, (uint64_t)step + 1U, "job", 3U, &token) == BTB_WORK_OK)
                known[token.slot] = token;
        } else if (op == 1U) {
            BtbWorkToken active;
            const BtbWorkItem *item;
            (void)BtbWorkAcquire(&q, &active, &item);
        } else {
            const uint32_t slot = BtbNext(&seed) % BTB_WORK_CAPACITY;
            if (known[slot].generation != 0U) {
                BtbWorkItem *item = &q.items[slot];
                if (item->state == BTB_WORK_QUEUED || item->state == BTB_WORK_ACTIVE)
                    (void)BtbWorkCancel(&q, known[slot]);
                else if (item->state == BTB_WORK_COMPLETE || item->state == BTB_WORK_CANCELLED)
                    (void)BtbWorkRelease(&q, known[slot]);
            }
        }
        assert(BtbWorkInvariants(&q));
    }
}

int main(int argc, char **argv)
{
    if (argc > 1 && strcmp(argv[1], "fifo") == 0) BtbTestFifo();
    else if (argc > 1 && strcmp(argv[1], "cancel") == 0) BtbTestCancellation();
    else if (argc > 1 && strcmp(argv[1], "generation") == 0) BtbTestGenerationAndShutdown();
    else if (argc > 1 && strcmp(argv[1], "mutations") == 0) BtbTestMutations();
    else { BtbTestFifo(); BtbTestCancellation(); BtbTestGenerationAndShutdown(); BtbTestMutations(); }
    puts("Bits2Banking C23 handoff contract: PASS");
    return 0;
}
