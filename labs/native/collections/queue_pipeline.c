/*-----------------------------------------------------------------------------
 * Umicom Bits2Banking
 * File: labs/native/collections/queue_pipeline.c
 *
 * PURPOSE:
 *   Trace a bounded producer and consumer without losing rejected work.
 *
 * AUTHOR AND ORGANISATION:
 * Sammy Hegab
 * Umicom Foundation
 *
 * LICENCE:
 * MIT
 *---------------------------------------------------------------------------*/

#include "collections.h"
#include <stdio.h>

int main(void)
{
    BtbQueue jobs = {0};
    int next_job = 1;
    int expected_job = 1;
    unsigned pauses = 0;
    while (expected_job <= 20) {
        if (next_job <= 20) {
            BtbResult result = BtbQueuePush(&jobs, next_job);
            if (result == BTB_OK) ++next_job;
            else if (result == BTB_FULL) ++pauses;
            else return 1;
        }
        /* A slow consumer accepts one job after each third attempt.
           Full means retry later with the same job, never skip its identity. */
        if (next_job > 20 || pauses != 0 || next_job % 3 == 0) {
            int received = -1;
            if (BtbQueuePop(&jobs, &received) != BTB_OK) return 2;
            if (received != expected_job) return 3;
            printf("received %d; queued %zu\n", received, jobs.count);
            ++expected_job;
        }
    }
    if (next_job != 21 || jobs.count != 0 || pauses == 0) return 4;
    puts("all 20 jobs arrived in order");
    return 0;
}
