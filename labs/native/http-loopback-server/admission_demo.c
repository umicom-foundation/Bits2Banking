/* Bits2Banking | Sammy Hegab, Umicom Foundation | MIT
 * Deterministic backpressure exercise; does not create threads or sockets. */
#include "admission_queue.h"
#include <stdio.h>
int main(void)
{
    BtbAdmissionQueue queue = {0};
    if (BtbAdmissionInit(&queue, 2U) != BTB_ADMISSION_OK) return 1;
    uint64_t tickets[4] = {0};
    for (uint64_t id = 1U; id <= 4U; ++id)
        if (BtbAdmissionSubmit(&queue, id, &tickets[id - 1U]) != BTB_ADMISSION_OK)
            return 1;
    uint64_t current = 0U, request = 0U;
    if (BtbAdmissionStart(&queue, &current, &request) != BTB_ADMISSION_OK || request != 1U)
        return 1;
    if (BtbAdmissionStart(&queue, &current, &request) != BTB_ADMISSION_OK || request != 2U)
        return 1;
    printf("Capacity: 4; maximum simulated in-flight: 2; queued: %zu\n",
           queue.count - queue.active);
    if (BtbAdmissionComplete(&queue, tickets[0]) != BTB_ADMISSION_OK ||
        BtbAdmissionStart(&queue, &current, &request) != BTB_ADMISSION_OK ||
        request != 3U) return 1;
    printf("Next admitted request: %llu; active: %zu\n",
           (unsigned long long)request, queue.active);
    return 0;
}
