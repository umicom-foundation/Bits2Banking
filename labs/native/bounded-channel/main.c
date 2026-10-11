/*-----------------------------------------------------------------------------
 * Bits to Banking
 * File: labs/native/bounded-channel/main.c
 * PURPOSE: Send a copied fictitious Notes event to a receiver.
 * AUTHOR AND ORGANISATION: Sammy Hegab, Umicom Foundation
 * LICENCE: MIT
 *---------------------------------------------------------------------------*/
#include "channel.h"
#include <inttypes.h>
#include <stdio.h>
int main(void)
{
    BtbChannel channel;
    BtbChannelInit(&channel);
    unsigned char draft[] = "Notes: save the weekly report";
    uint64_t sequence = 0U;
    if (BtbChannelSend(&channel, 11U, 22U, draft, sizeof(draft) - 1U,
                       &sequence) != BTB_CHANNEL_OK)
        return 1;
    draft[0] = 'X'; /* Message data is already copied by the channel. */
    unsigned char received[BTB_CHANNEL_MESSAGE_BYTES + 1U] = {0};
    uint32_t sender = 0U;
    size_t length = 0U;
    if (BtbChannelReceive(&channel, 22U, received, sizeof(received) - 1U,
                          &sender, &length, &sequence) != BTB_CHANNEL_OK)
        return 1;
    received[length] = 0U; /* Add a terminator for this printable demonstration. */
    printf("Receiver 22 accepted message %" PRIu64 " from %" PRIu32 ": %s\n",
           sequence, sender, (const char *)received);
    return 0;
}
