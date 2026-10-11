/* Bits2Banking | Umicom Foundation | MIT | Prove waiting and resource lifetimes. */
#include "session.h"
#include <stdio.h>
#include <string.h>
#define CHECK(x) do { if (!(x)) { fprintf(stderr, "FAIL %s:%d: %s\n", __FILE__, __LINE__, #x); return 1; } } while(0)
static int Delivery(void)
{
    BtbRoundRobin queue; BtbRoundRobinInit(&queue);
    BtbChannel channel; BtbChannelInit(&channel);
    BtbTaskHandle receiver=0U, running=0U;
    CHECK(BtbRoundRobinAdmit(&queue, &receiver) == BTB_SCHED_OK);
    CHECK(BtbRoundRobinNext(&queue, &running) == BTB_SCHED_OK && running == receiver);
    BtbServiceSession service = {0};
    CHECK(BtbSessionInit(&service, &queue, &channel, receiver, 10U, 20U, 8U) == BTB_SESSION_OK);
    CHECK(BtbSessionWaitForMessage(&service) == BTB_SESSION_WOULD_BLOCK);
    BtbSchedSnapshot snapshot = {0};
    CHECK(BtbRoundRobinSnapshotRead(&queue, &snapshot) == BTB_SCHED_OK);
    CHECK(snapshot.waiting == 1U && snapshot.ready == 0U && snapshot.running == 0U);
    CHECK(BtbSessionPoll(&service) == BTB_SESSION_WOULD_BLOCK);
    BtbTaskHandle sentinel = UINT64_C(987654321);
    CHECK(BtbRoundRobinNext(&queue, &sentinel) == BTB_SCHED_EMPTY && sentinel == UINT64_C(987654321));
    char input[] = "Save Notes";
    uint64_t sent=0U, received=0U;
    CHECK(BtbSessionSend(&service, input, strlen(input), &sent) == BTB_SESSION_OK);
    input[0] = '!'; /* Queued bytes must be an independent copy. */
    CHECK(BtbSessionPoll(&service) == BTB_SESSION_READY);
    CHECK(BtbSessionPoll(&service) == BTB_SESSION_BAD_STATE);
    CHECK(BtbRoundRobinNext(&queue, &running) == BTB_SCHED_OK && running == receiver);
    uint32_t from=UINT32_MAX; size_t length=SIZE_MAX; char output[64] = {0};
    CHECK(BtbSessionReceive(&service, output, 2U, &from, &length, &received) == BTB_SESSION_SMALL_BUFFER);
    CHECK(BtbChannelPending(&channel) == 1U && from == UINT32_MAX && length == SIZE_MAX);
    CHECK(BtbSessionReceive(&service, output, sizeof(output), &from, &length, &received) == BTB_SESSION_OK);
    CHECK(length == strlen("Save Notes") && memcmp(output, "Save Notes", length) == 0 &&
          from == 10U && received == sent && BtbChannelPending(&channel) == 0U);
    CHECK(BtbSessionClose(&service) == BTB_SESSION_OK);
    CHECK(BtbSessionWaitForMessage(&service) == BTB_SESSION_CLOSED);
    CHECK(BtbSessionSend(&service, output, length, &sent) == BTB_SESSION_CLOSED);
    CHECK(BtbRoundRobinYield(&queue, receiver) == BTB_SCHED_STALE);
    puts("[OK] Wait, copied payload, wake, checked output and closure.");
    return 0;
}
static int Cancellation(void)
{
    BtbRoundRobin queue; BtbRoundRobinInit(&queue);
    BtbChannel channel; BtbChannelInit(&channel);
    BtbTaskHandle receiver=0U, running=0U;
    CHECK(BtbRoundRobinAdmit(&queue, &receiver) == BTB_SCHED_OK);
    CHECK(BtbRoundRobinNext(&queue, &running) == BTB_SCHED_OK);
    BtbServiceSession service = {0};
    CHECK(BtbSessionInit(&service, &queue, &channel, receiver, 11U, 21U, 5U) == BTB_SESSION_OK);
    CHECK(BtbSessionWaitForMessage(&service) == BTB_SESSION_WOULD_BLOCK);
    uint64_t seq=0U;
    const unsigned char bytes[] = {1U,2U,3U,4U};
    CHECK(BtbSessionSend(&service, bytes, sizeof(bytes), &seq) == BTB_SESSION_OK);
    CHECK(BtbSessionClose(&service) == BTB_SESSION_OK);
    CHECK(BtbChannelPending(&channel) == 1U); /* Closing a consumer doesn't erase the queue. */
    CHECK(BtbSessionPoll(&service) == BTB_SESSION_CLOSED);
    uint32_t sender=0U; size_t size=0U; unsigned char output[4] = {0}; uint64_t receipt=0U;
    CHECK(BtbChannelReceive(&channel, 21U, output, sizeof(output), &sender, &size, &receipt) == BTB_CHANNEL_OK);
    CHECK(sender == 11U && size == 4U && receipt == seq && memcmp(output, bytes, 4U) == 0);
    BtbSchedSnapshot snapshot = {0};
    CHECK(BtbRoundRobinSnapshotRead(&queue, &snapshot) == BTB_SCHED_OK && snapshot.live == 0U);
    puts("[OK] Cancellation stops the waiter without consuming an accepted message.");
    return 0;
}
int main(int argc, char **argv)
{
    if (argc != 2) return 2;
    if (strcmp(argv[1], "delivery") == 0) return Delivery();
    if (strcmp(argv[1], "cancellation") == 0) return Cancellation();
    return 2;
}
