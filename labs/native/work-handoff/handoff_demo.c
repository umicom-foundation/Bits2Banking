/* Bits2Banking | Umicom Foundation | Sammy Hegab | MIT */
#include "handoff.h"
#include <stdio.h>
int main(void)
{
    BtbWorkQueue queue;
    if (BtbWorkInit(&queue, 2U) != BTB_WORK_OK) return 1;
    BtbWorkToken first, second, active;
    const BtbWorkItem *job;
    if (BtbWorkSubmit(&queue, 1001U, "GET /api/courses", 16U, &first) != BTB_WORK_OK ||
        BtbWorkSubmit(&queue, 1002U, "GET /index.html", 15U, &second) != BTB_WORK_OK)
        return 1;
    printf("Queued requests: %zu\n", queue.queued);
    while (BtbWorkAcquire(&queue, &active, &job) == BTB_WORK_OK) {
        printf("Processing connection %llu: %.*s\n",
               (unsigned long long)job->connectionId, (int)job->length,
               (const char *)job->payload);
        if (BtbWorkComplete(&queue, active) != BTB_WORK_OK ||
            BtbWorkRelease(&queue, active) != BTB_WORK_OK) return 1;
    }
    BtbWorkQuiesce(&queue);
    puts(BtbWorkDrained(&queue) ? "Shutdown drained: yes" : "Shutdown drained: no");
    return BtbWorkDrained(&queue) ? 0 : 1;
}
