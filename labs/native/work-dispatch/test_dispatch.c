/*-----------------------------------------------------------------------------
 * Bits2Banking | Umicom Foundation | Sammy Hegab | MIT
 * File: labs/native/work-dispatch/test_dispatch.c
 * PURPOSE: deterministic contract, negative and bounded mutation tests.
 * Test failures return nonzero even when compiled with NDEBUG.
 *---------------------------------------------------------------------------*/
#include "dispatch.h"
#include <inttypes.h>
#include <stdio.h>
#include <string.h>
#include <limits.h>

#define BTB_REQUIRE(condition) do { \
    if (!(condition)) { \
        (void)fprintf(stderr, "%s:%d: failed: %s\n", \
                      __FILE__, __LINE__, #condition); \
        return 1; \
    } \
} while (0)

static int TestFifo(void)
{
    BtbDispatch dispatcher;
    BTB_REQUIRE(BtbDispatchInit(&dispatcher) == BTB_DISPATCH_OK);
    BtbDispatchIdentity ids[4] = {0};
    const char *requests[4] = {
        "BANK|GBP|1", "BANK|USD|2", "TMS|BOOK|3", "BANK|EUR|4"
    };
    for (size_t i = 0U; i < 4U; ++i) {
        BTB_REQUIRE(BtbDispatchSubmit(&dispatcher, (uint64_t)i + 10U,
                    requests[i], strlen(requests[i]), &ids[i]) == BTB_DISPATCH_OK);
    }
    size_t executed = SIZE_MAX;
    BTB_REQUIRE(BtbDispatchRun(&dispatcher, 4U, &executed) == BTB_DISPATCH_OK);
    BTB_REQUIRE(executed == 4U);
    BTB_REQUIRE(dispatcher.work.queued == 0U);
    BTB_REQUIRE(dispatcher.notifications.count == 4U);
    BTB_REQUIRE(BtbDispatchInvariants(&dispatcher));
    for (size_t i = 0U; i < 4U; ++i) {
        BtbDispatchReceipt receipt = {0};
        BTB_REQUIRE(BtbDispatchReceive(&dispatcher, &receipt) == BTB_DISPATCH_OK);
        BTB_REQUIRE(receipt.identity.requestId == ids[i].requestId);
        BTB_REQUIRE(receipt.identity.token.slot == ids[i].token.slot);
        BTB_REQUIRE(receipt.connectionId == (uint64_t)i + 10U);
        BTB_REQUIRE(receipt.requestLength == strlen(requests[i]));
        BTB_REQUIRE(receipt.result == BTB_COMPLETION_SUCCESS);
        BTB_REQUIRE(receipt.diagnosticDigest != 0U);
        BTB_REQUIRE(BtbDispatchInvariants(&dispatcher));
    }
    BTB_REQUIRE(dispatcher.accepted == 4U);
    BTB_REQUIRE(dispatcher.succeeded == 4U);
    BTB_REQUIRE(dispatcher.cancelled == 0U);
    BTB_REQUIRE(dispatcher.delivered == 4U);
    return 0;
}

static int TestCapacity(void)
{
    BtbDispatch dispatcher;
    BTB_REQUIRE(BtbDispatchInit(&dispatcher) == BTB_DISPATCH_OK);
    BtbDispatchIdentity ids[BTB_WORK_CAPACITY] = {0};
    for (size_t i = 0U; i < BTB_WORK_CAPACITY; ++i) {
        unsigned char data = (unsigned char)i;
        BTB_REQUIRE(BtbDispatchSubmit(&dispatcher, (uint64_t)i + 1U,
                    &data, sizeof(data), &ids[i]) == BTB_DISPATCH_OK);
    }
    BtbDispatchIdentity unchanged = { .requestId = 999U,
                                      .token = {77U, 88U} };
    BTB_REQUIRE(BtbDispatchSubmit(&dispatcher, 500U, "X", 1U, &unchanged) ==
                BTB_DISPATCH_FULL);
    BTB_REQUIRE(unchanged.requestId == 999U);
    BTB_REQUIRE(unchanged.token.slot == 77U);
    size_t ran = 0U;
    BTB_REQUIRE(BtbDispatchRun(&dispatcher, 8U, &ran) == BTB_DISPATCH_OK);
    BTB_REQUIRE(ran == BTB_COMPLETION_CAPACITY);
    BTB_REQUIRE(BtbDispatchStep(&dispatcher) == BTB_DISPATCH_BACKPRESSURE);
    BTB_REQUIRE(BtbDispatchCancel(&dispatcher, ids[6]) ==
                BTB_DISPATCH_BACKPRESSURE);
    BTB_REQUIRE(dispatcher.work.items[ids[6].token.slot].state == BTB_WORK_QUEUED);
    BTB_REQUIRE(BtbDispatchInvariants(&dispatcher));
    BtbDispatchReceipt receipt = {0};
    BTB_REQUIRE(BtbDispatchReceive(&dispatcher, &receipt) == BTB_DISPATCH_OK);
    BTB_REQUIRE(BtbDispatchCancel(&dispatcher, ids[6]) == BTB_DISPATCH_OK);
    BTB_REQUIRE(BtbDispatchStep(&dispatcher) == BTB_DISPATCH_BACKPRESSURE);
    while (BtbDispatchReceive(&dispatcher, &receipt) == BTB_DISPATCH_OK) {}
    BTB_REQUIRE(BtbDispatchRun(&dispatcher, 8U, &ran) == BTB_DISPATCH_OK);
    BTB_REQUIRE(ran == 3U);
    while (BtbDispatchReceive(&dispatcher, &receipt) == BTB_DISPATCH_OK) {}
    BTB_REQUIRE(dispatcher.delivered == 8U);
    BTB_REQUIRE(dispatcher.cancelled == 1U);
    BTB_REQUIRE(BtbDispatchInvariants(&dispatcher));
    return 0;
}

static int TestCancel(void)
{
    BtbDispatch dispatcher;
    BTB_REQUIRE(BtbDispatchInit(&dispatcher) == BTB_DISPATCH_OK);
    BtbDispatchIdentity first, second, third;
    BTB_REQUIRE(BtbDispatchSubmit(&dispatcher, 11U, "A", 1U, &first) == BTB_DISPATCH_OK);
    BTB_REQUIRE(BtbDispatchSubmit(&dispatcher, 12U, "B", 1U, &second) == BTB_DISPATCH_OK);
    BTB_REQUIRE(BtbDispatchSubmit(&dispatcher, 13U, "C", 1U, &third) == BTB_DISPATCH_OK);
    BTB_REQUIRE(BtbDispatchCancel(&dispatcher, second) == BTB_DISPATCH_OK);
    BTB_REQUIRE(BtbDispatchCancel(&dispatcher, second) == BTB_DISPATCH_FINAL);
    BTB_REQUIRE(BtbDispatchStep(&dispatcher) == BTB_DISPATCH_OK);
    BTB_REQUIRE(BtbDispatchStep(&dispatcher) == BTB_DISPATCH_OK);
    BTB_REQUIRE(BtbDispatchStep(&dispatcher) == BTB_DISPATCH_EMPTY);
    BtbDispatchReceipt r = {0};
    BTB_REQUIRE(BtbDispatchReceive(&dispatcher, &r) == BTB_DISPATCH_OK);
    BTB_REQUIRE(r.result == BTB_COMPLETION_CANCELLED);
    BTB_REQUIRE(r.identity.requestId == second.requestId);
    BTB_REQUIRE(r.requestLength == 1U);
    BTB_REQUIRE(r.diagnosticDigest == 0U);
    BTB_REQUIRE(BtbDispatchReceive(&dispatcher, &r) == BTB_DISPATCH_OK);
    BTB_REQUIRE(r.identity.requestId == first.requestId);
    BTB_REQUIRE(r.result == BTB_COMPLETION_SUCCESS);
    BTB_REQUIRE(BtbDispatchReceive(&dispatcher, &r) == BTB_DISPATCH_OK);
    BTB_REQUIRE(r.identity.requestId == third.requestId);
    BTB_REQUIRE(r.result == BTB_COMPLETION_SUCCESS);
    BTB_REQUIRE(dispatcher.accepted == 3U && dispatcher.cancelled == 1U);
    BTB_REQUIRE(dispatcher.succeeded == 2U && dispatcher.delivered == 3U);
    BTB_REQUIRE(BtbDispatchInvariants(&dispatcher));
    return 0;
}

static int TestStale(void)
{
    BtbDispatch dispatcher;
    BTB_REQUIRE(BtbDispatchInit(&dispatcher) == BTB_DISPATCH_OK);
    BtbDispatchIdentity first, next;
    BTB_REQUIRE(BtbDispatchSubmit(&dispatcher, 700U, "A", 1U, &first) == BTB_DISPATCH_OK);
    BTB_REQUIRE(BtbDispatchStep(&dispatcher) == BTB_DISPATCH_OK);
    BTB_REQUIRE(BtbDispatchCancel(&dispatcher, first) == BTB_DISPATCH_FINAL);
    BtbDispatchReceipt receipt;
    BTB_REQUIRE(BtbDispatchReceive(&dispatcher, &receipt) == BTB_DISPATCH_OK);
    BTB_REQUIRE(BtbDispatchCancel(&dispatcher, first) == BTB_DISPATCH_STALE);
    BTB_REQUIRE(BtbDispatchSubmit(&dispatcher, 701U, "B", 1U, &next) == BTB_DISPATCH_OK);
    BTB_REQUIRE(first.token.slot == next.token.slot);
    BTB_REQUIRE(first.token.generation != next.token.generation);
    BTB_REQUIRE(first.requestId != next.requestId);
    BTB_REQUIRE(BtbDispatchCancel(&dispatcher, first) == BTB_DISPATCH_STALE);
    BTB_REQUIRE(BtbDispatchCancel(&dispatcher, next) == BTB_DISPATCH_OK);
    BTB_REQUIRE(BtbDispatchReceive(&dispatcher, &receipt) == BTB_DISPATCH_OK);
    BTB_REQUIRE(BtbDispatchInvariants(&dispatcher));
    return 0;
}

static int TestQuiesce(void)
{
    BtbDispatch dispatcher;
    BTB_REQUIRE(BtbDispatchInit(&dispatcher) == BTB_DISPATCH_OK);
    BtbDispatchIdentity token, untouched = { .requestId = 77U };
    BTB_REQUIRE(BtbDispatchSubmit(&dispatcher, 900U, "AUDIT", 5U, &token) == BTB_DISPATCH_OK);
    BTB_REQUIRE(BtbDispatchQuiesce(&dispatcher) == BTB_DISPATCH_OK);
    BTB_REQUIRE(BtbDispatchSubmit(&dispatcher, 901U, "NO", 2U, &untouched) ==
                BTB_DISPATCH_QUIESCING);
    BTB_REQUIRE(untouched.requestId == 77U);
    BTB_REQUIRE(!BtbDispatchDrained(&dispatcher));
    BTB_REQUIRE(BtbDispatchStep(&dispatcher) == BTB_DISPATCH_OK);
    BTB_REQUIRE(BtbWorkDrained(&dispatcher.work));
    BTB_REQUIRE(!BtbDispatchDrained(&dispatcher)); /* Results not delivered. */
    BtbDispatchReceipt receipt;
    BTB_REQUIRE(BtbDispatchReceive(&dispatcher, &receipt) == BTB_DISPATCH_OK);
    BTB_REQUIRE(BtbDispatchDrained(&dispatcher));
    BTB_REQUIRE(BtbDispatchQuiesce(&dispatcher) == BTB_DISPATCH_OK);
    BTB_REQUIRE(BtbDispatchInvariants(&dispatcher));
    return 0;
}

static int TestInvalid(void)
{
    BTB_REQUIRE(BtbDispatchInit(NULL) == BTB_DISPATCH_INVALID);
    BTB_REQUIRE(BtbDispatchStep(NULL) == BTB_DISPATCH_INVALID);
    BTB_REQUIRE(BtbDispatchQuiesce(NULL) == BTB_DISPATCH_INVALID);
    BtbDispatch dispatcher;
    BTB_REQUIRE(BtbDispatchInit(&dispatcher) == BTB_DISPATCH_OK);
    BtbDispatchIdentity unchanged = { .requestId = 88U };
    BTB_REQUIRE(BtbDispatchSubmit(&dispatcher, 0U, "x", 1U, &unchanged) ==
                BTB_DISPATCH_INVALID);
    BTB_REQUIRE(BtbDispatchSubmit(&dispatcher, 1U, NULL, 1U, &unchanged) ==
                BTB_DISPATCH_INVALID);
    BTB_REQUIRE(BtbDispatchSubmit(&dispatcher, 1U, "x", 0U, &unchanged) ==
                BTB_DISPATCH_INVALID);
    BTB_REQUIRE(BtbDispatchSubmit(&dispatcher, 1U, "x", BTB_WORK_BYTES+1U,
                                  &unchanged) == BTB_DISPATCH_INVALID);
    BTB_REQUIRE(BtbDispatchSubmit(&dispatcher, 1U, "x", 1U, NULL) ==
                BTB_DISPATCH_INVALID);
    BTB_REQUIRE(unchanged.requestId == 88U);
    BtbDispatchReceipt receipt = { .connectionId = UINT64_C(998877) };
    BTB_REQUIRE(BtbDispatchReceive(&dispatcher, &receipt) == BTB_DISPATCH_EMPTY);
    BTB_REQUIRE(receipt.connectionId == UINT64_C(998877));
    size_t ran = 77U;
    BTB_REQUIRE(BtbDispatchRun(&dispatcher, 0U, &ran) == BTB_DISPATCH_INVALID);
    BTB_REQUIRE(BtbDispatchRun(&dispatcher, BTB_WORK_CAPACITY + 1U, &ran) ==
                BTB_DISPATCH_INVALID);
    BTB_REQUIRE(ran == 77U);
    dispatcher.nextRequestId = UINT32_MAX;
    BTB_REQUIRE(BtbDispatchSubmit(&dispatcher, 1U, "x", 1U, &unchanged) ==
                BTB_DISPATCH_ID_EXHAUSTED);
    BTB_REQUIRE(dispatcher.work.queued == 0U);
    BTB_REQUIRE(BtbDispatchInvariants(&dispatcher));
    return 0;
}

static int TestOwnership(void)
{
    BtbDispatch dispatcher;
    BTB_REQUIRE(BtbDispatchInit(&dispatcher) == BTB_DISPATCH_OK);
    char source[] = "CASH|GBP|ACCOUNT-A";
    BtbDispatchIdentity identity;
    BTB_REQUIRE(BtbDispatchSubmit(&dispatcher, 300U, source, strlen(source), &identity) ==
                BTB_DISPATCH_OK);
    memset(source, '*', strlen(source));
    const BtbWorkItem *item = &dispatcher.work.items[identity.token.slot];
    BTB_REQUIRE(item->payload[0] == (unsigned char)'C');
    BTB_REQUIRE(BtbDispatchStep(&dispatcher) == BTB_DISPATCH_OK);
    BtbDispatchReceipt receipt, retained;
    BTB_REQUIRE(BtbDispatchReceive(&dispatcher, &receipt) == BTB_DISPATCH_OK);
    retained = receipt;
    BTB_REQUIRE(receipt.diagnosticDigest == UINT64_C(0x6f9ff089e7a575f0));
    BTB_REQUIRE(item->state == BTB_WORK_FREE);
    BTB_REQUIRE(item->length == 0U);
    BTB_REQUIRE(retained.diagnosticDigest == receipt.diagnosticDigest);
    BTB_REQUIRE(BtbDispatchInvariants(&dispatcher));
    return 0;
}

static uint32_t NextRandom(uint32_t *state)
{
    *state = *state * UINT32_C(1664525) + UINT32_C(1013904223);
    return *state;
}

static int TestStress(void)
{
    BtbDispatch dispatcher;
    BTB_REQUIRE(BtbDispatchInit(&dispatcher) == BTB_DISPATCH_OK);
    uint32_t state = UINT32_C(119203);
    for (size_t step = 0U; step < 80000U; ++step) {
        const uint32_t op = NextRandom(&state) % 5U;
        if (op == 0U) {
            BtbDispatchIdentity identity;
            const char sample[] = "BANK|GBP|PENDING";
            (void)BtbDispatchSubmit(&dispatcher, (uint64_t)step + 1U,
                                    sample, sizeof(sample)-1U, &identity);
        } else if (op == 1U) {
            (void)BtbDispatchStep(&dispatcher);
        } else if (op == 2U) {
            BtbDispatchReceipt receipt;
            (void)BtbDispatchReceive(&dispatcher, &receipt);
        } else if (op == 3U) {
            const uint32_t slot = NextRandom(&state) % BTB_WORK_CAPACITY;
            if (dispatcher.records[slot].occupied) {
                const BtbDispatchIdentity identity = dispatcher.records[slot].identity;
                (void)BtbDispatchCancel(&dispatcher, identity);
            }
        } else {
            size_t ran;
            (void)BtbDispatchRun(&dispatcher, 3U, &ran);
        }
        BTB_REQUIRE(BtbDispatchInvariants(&dispatcher));
    }
    BTB_REQUIRE(BtbDispatchQuiesce(&dispatcher) == BTB_DISPATCH_OK);
    for (size_t i = 0U; i < 200U && !BtbDispatchDrained(&dispatcher); ++i) {
        BtbDispatchReceipt receipt;
        (void)BtbDispatchReceive(&dispatcher, &receipt);
        (void)BtbDispatchStep(&dispatcher);
        BTB_REQUIRE(BtbDispatchInvariants(&dispatcher));
    }
    BTB_REQUIRE(BtbDispatchDrained(&dispatcher));
    BTB_REQUIRE(dispatcher.accepted == dispatcher.delivered);
    BTB_REQUIRE(dispatcher.succeeded + dispatcher.cancelled == dispatcher.delivered);
    return 0;
}

int main(int argc, char **argv)
{
    int result = 1;
    const char *mode = argc > 1 ? argv[1] : "all";
    if (strcmp(mode, "fifo") == 0) result = TestFifo();
    else if (strcmp(mode, "capacity") == 0) result = TestCapacity();
    else if (strcmp(mode, "cancel") == 0) result = TestCancel();
    else if (strcmp(mode, "stale") == 0) result = TestStale();
    else if (strcmp(mode, "quiesce") == 0) result = TestQuiesce();
    else if (strcmp(mode, "invalid") == 0) result = TestInvalid();
    else if (strcmp(mode, "ownership") == 0) result = TestOwnership();
    else if (strcmp(mode, "stress") == 0) result = TestStress();
    else if (strcmp(mode, "all") == 0) {
        result = TestFifo() || TestCapacity() || TestCancel() || TestStale() ||
                 TestQuiesce() || TestInvalid() || TestOwnership() || TestStress();
    } else {
        (void)fprintf(stderr, "Unknown test case: %s\n", mode);
        return 2;
    }
    if (result == 0)
        (void)printf("Bits2Banking C23 dispatch test %s: PASS\n", mode);
    return result;
}
