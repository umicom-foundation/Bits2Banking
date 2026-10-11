/* Bits2Banking | Umicom Foundation | MIT | Simulated Notes service wait/wake. */
#include "session.h"
#include <stdio.h>
#include <string.h>
int main(void)
{
    BtbRoundRobin scheduler; BtbRoundRobinInit(&scheduler);
    BtbChannel messages; BtbChannelInit(&messages);
    BtbTaskHandle notes=0U, running=0U;
    if (BtbRoundRobinAdmit(&scheduler, &notes) != BTB_SCHED_OK ||
        BtbRoundRobinNext(&scheduler, &running) != BTB_SCHED_OK || running != notes) return 1;
    BtbServiceSession session = {0};
    if (BtbSessionInit(&session, &scheduler, &messages, notes, 10U, 20U, 7U) != BTB_SESSION_OK ||
        BtbSessionWaitForMessage(&session) != BTB_SESSION_WOULD_BLOCK) return 1;
    puts("Notes service is waiting; it is not runnable.");
    const char text[] = "Draft stored";
    uint64_t sent=0U, received=0U;
    if (BtbSessionSend(&session, text, strlen(text), &sent) != BTB_SESSION_OK ||
        BtbSessionPoll(&session) != BTB_SESSION_READY ||
        BtbRoundRobinNext(&scheduler, &running) != BTB_SCHED_OK) return 1;
    unsigned char buffer[64] = {0}; size_t length=0U; uint32_t sender=0U;
    if (BtbSessionReceive(&session, buffer, sizeof(buffer), &sender, &length, &received) != BTB_SESSION_OK ||
        length != strlen(text) || memcmp(buffer, text, length) != 0 || sent != received) return 1;
    printf("Notes service resumed; received %zu copied bytes.\n", length);
    return BtbSessionClose(&session) == BTB_SESSION_OK ? 0 : 1;
}
