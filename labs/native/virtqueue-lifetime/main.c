/*-----------------------------------------------------------------------------
 * Bits2Banking — Virtqueue Lifetime Laboratory
 * File: labs/native/virtqueue-lifetime/main.c
 * PURPOSE: Demonstrate safe stages of fictional device submission.
 * AUTHOR AND ORGANISATION: Sammy Hegab, Umicom Foundation
 * LICENCE: MIT
 *---------------------------------------------------------------------------*/
#include "queue.h"
#include <inttypes.h>
#include <stdio.h>
int main(void)
{
    BtbVq queue;
    BtbVqInit(&queue);
    const unsigned char note[] = "First Notes document";
    uint64_t token = 0U;
    if (BtbVqPrepare(&queue, 11U, note, sizeof(note) - 1U, &token) != BTB_VQ_OK ||
        BtbVqPublish(&queue, 11U, token) != BTB_VQ_OK ||
        BtbVqCancelRequested(&queue, 11U, token) != BTB_VQ_OK ||
        BtbVqSimulateComplete(&queue, token, 0U, (uint32_t)(sizeof(note) - 1U)) != BTB_VQ_OK)
        return 1;
    BtbVqCompletion result = {0};
    if (BtbVqCollect(&queue, 11U, token, &result) != BTB_VQ_OK) return 1;
    printf("Request %" PRIu64 ": completed %" PRIu32 " of %" PRIu32 " bytes.\n",
           result.token, result.completedBytes, result.requestedBytes);
    printf("Cancellation requested: %s; device completion was still observed.\n",
           result.cancellationWasRequested ? "yes" : "no");
    puts("A simulated completion does not demonstrate hardware durability.");
    return 0;
}
