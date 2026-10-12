/*-----------------------------------------------------------------------------
 * Bits2Banking — Virtqueue Lifetime Laboratory
 * File: labs/native/virtqueue-lifetime/test_queue.c
 * PURPOSE: Check buffer retention, resets, FIFO and stale-token rejection.
 * AUTHOR AND ORGANISATION: Sammy Hegab, Umicom Foundation
 * LICENCE: MIT
 *---------------------------------------------------------------------------*/
#include "queue.h"
#include <stdio.h>
#include <string.h>
#define CHECK(cond) do { if (!(cond)) { \
    fprintf(stderr, "FAIL %s:%d: %s\n", __FILE__, __LINE__, #cond); return 1; \
} } while (0)

static int TestLifecycle(void)
{
    BtbVq queue;
    BtbVqInit(&queue);
    unsigned char payload[3] = {1U, 2U, 3U};
    uint64_t token = UINT64_C(0xfedcba9876543210);
    CHECK(BtbVqPrepare(&queue, 0U, payload, sizeof(payload), &token) == BTB_VQ_INVALID_ARGUMENT);
    CHECK(token == UINT64_C(0xfedcba9876543210));
    CHECK(BtbVqPrepare(&queue, 17U, payload, sizeof(payload), &token) == BTB_VQ_OK);
    CHECK(queue.slots[0].payload[0] == 1U);
    payload[0] = 0xffU;
    CHECK(queue.slots[0].payload[0] == 1U); /* copied ownership */
    CHECK(BtbVqCollect(&queue, 17U, token, &(BtbVqCompletion){0}) == BTB_VQ_WRONG_STATE);
    CHECK(BtbVqPublish(&queue, 18U, token) == BTB_VQ_WRONG_OWNER);
    CHECK(BtbVqPublish(&queue, 17U, token) == BTB_VQ_OK);
    CHECK(BtbVqCancelRequested(&queue, 17U, token) == BTB_VQ_OK);
    CHECK(queue.slots[0].stage == BTB_VQ_PUBLISHED && queue.slots[0].payload[0] == 1U);
    CHECK(BtbVqSimulateComplete(&queue, token, 0U, 4U) == BTB_VQ_INVALID_ARGUMENT);
    CHECK(BtbVqSimulateComplete(&queue, token, 0U, 3U) == BTB_VQ_OK);
    BtbVqCompletion result = {0};
    CHECK(BtbVqCollect(&queue, 18U, token, &result) == BTB_VQ_WRONG_OWNER);
    CHECK(result.token == 0U);
    CHECK(BtbVqCollect(&queue, 17U, token, &result) == BTB_VQ_OK);
    CHECK(result.token == token && result.cancellationWasRequested == 1);
    CHECK(result.completedBytes == 3U && result.requestedBytes == 3U);
    CHECK(queue.slots[0].payload[0] == 0U);
    CHECK(BtbVqCollect(&queue, 17U, token, &result) == BTB_VQ_STALE_TOKEN);
    return 0;
}
static int TestOrderAndReset(void)
{
    BtbVq queue;
    BtbVqInit(&queue);
    uint64_t tokens[BTB_VQ_SLOT_COUNT] = {0};
    const unsigned char letter = 'A';
    for (uint32_t i = 0U; i < BTB_VQ_SLOT_COUNT; ++i) {
        CHECK(BtbVqPrepare(&queue, i + 1U, &letter, 1U, &tokens[i]) == BTB_VQ_OK);
        CHECK(BtbVqPublish(&queue, i + 1U, tokens[i]) == BTB_VQ_OK);
    }
    uint64_t refused = 4321U;
    CHECK(BtbVqPrepare(&queue, 9U, &letter, 1U, &refused) == BTB_VQ_FULL);
    CHECK(refused == 4321U);
    CHECK(BtbVqSimulateComplete(&queue, tokens[1], 0U, 1U) == BTB_VQ_WRONG_ORDER);
    CHECK(BtbVqSimulateComplete(&queue, tokens[0], 0U, 1U) == BTB_VQ_OK);
    CHECK(BtbVqSimulateComplete(&queue, tokens[1], 0U, 1U) == BTB_VQ_OK);
    BtbVqCompletion completed = {0};
    CHECK(BtbVqCollect(&queue, 2U, tokens[1], &completed) == BTB_VQ_WRONG_ORDER);
    CHECK(BtbVqCollect(&queue, 1U, tokens[0], &completed) == BTB_VQ_OK);
    CHECK(BtbVqCollect(&queue, 2U, tokens[1], &completed) == BTB_VQ_OK);
    CHECK(BtbVqRequestReset(&queue) == BTB_VQ_OK);
    CHECK(BtbVqRequestReset(&queue) == BTB_VQ_BUSY);
    CHECK(BtbVqPrepare(&queue, 5U, &letter, 1U, &refused) == BTB_VQ_BUSY);
    CHECK(queue.slots[2].stage == BTB_VQ_PUBLISHED);
    CHECK(queue.slots[2].payload[0] == letter); /* retained until ACK */
    CHECK(BtbVqSimulateComplete(&queue, tokens[2], 0U, 1U) == BTB_VQ_BUSY);
    CHECK(BtbVqSimulateResetAcknowledged(&queue) == BTB_VQ_OK);
    CHECK(queue.availableCount == 0U && queue.usedCount == 0U);
    CHECK(queue.slots[2].stage == BTB_VQ_FREE && queue.slots[2].payload[0] == 0U);
    CHECK(BtbVqSimulateResetAcknowledged(&queue) == BTB_VQ_WRONG_STATE);
    CHECK(BtbVqPublish(&queue, 3U, tokens[2]) == BTB_VQ_STALE_TOKEN);
    return 0;
}
static int TestRepeatedWrap(void)
{
    BtbVq queue;
    BtbVqInit(&queue);
    const unsigned char payload = 8U;
    uint64_t old = 0U;
    for (size_t i = 0U; i < 200U; ++i) {
        uint64_t token = 0U;
        CHECK(BtbVqPrepare(&queue, 1U, &payload, 1U, &token) == BTB_VQ_OK);
        CHECK(token != old);
        CHECK(BtbVqPublish(&queue, 1U, token) == BTB_VQ_OK);
        CHECK(BtbVqSimulateComplete(&queue, token, 0U, 1U) == BTB_VQ_OK);
        BtbVqCompletion result = {0};
        CHECK(BtbVqCollect(&queue, 1U, token, &result) == BTB_VQ_OK);
        CHECK(result.token == token);
        old = token;
    }
    return 0;
}
int main(void)
{
    if (TestLifecycle() != 0 || TestOrderAndReset() != 0 || TestRepeatedWrap() != 0)
        return 1;
    puts("Virtqueue lifetime: copied payloads, FIFO, cancellation, reset and stale tokens passed.");
    return 0;
}
