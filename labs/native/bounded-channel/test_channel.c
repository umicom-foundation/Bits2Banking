/*-----------------------------------------------------------------------------
 * Bits to Banking
 * File: labs/native/bounded-channel/test_channel.c
 * PURPOSE: Prove owned copies, capacity checks, FIFO ordering and unchanged failures.
 * AUTHOR AND ORGANISATION: Sammy Hegab, Umicom Foundation
 * LICENCE: MIT
 *---------------------------------------------------------------------------*/
#include "channel.h"
#include <stdio.h>
#include <string.h>
#define CHECK(test) do {if (!(test)) { fprintf(stderr, "failed line %d: %s\n", __LINE__, #test); return 1; }} while(0)
int main(void)
{
    BtbChannel channel;
    BtbChannelInit(&channel);
    CHECK(BtbChannelPending(&channel) == 0U);
    unsigned char source[4] = {'N','o','t','e'};
    uint64_t sequence = 999U;
    CHECK(BtbChannelSend(&channel, 10U, 20U, source, 4U, &sequence) == BTB_CHANNEL_OK);
    CHECK(sequence == 1U);
    source[0] = '!';
    unsigned char received[5] = {'x','x','x','x',0};
    uint32_t sender = 999U;
    size_t length = 777U;
    uint64_t responseSequence = 555U;
    CHECK(BtbChannelReceive(&channel, 30U, received, 4U, &sender, &length, &responseSequence) == BTB_CHANNEL_DENIED);
    CHECK(BtbChannelReceive(&channel, 20U, received, 3U, &sender, &length, &responseSequence) == BTB_CHANNEL_SMALL_BUFFER);
    CHECK(received[0] == 'x' && sender == 999U && length == 777U && responseSequence == 555U);
    CHECK(BtbChannelPending(&channel) == 1U);
    CHECK(BtbChannelReceive(&channel, 20U, received, 4U, &sender, &length, &responseSequence) == BTB_CHANNEL_OK);
    CHECK(sender == 10U && length == 4U && responseSequence == 1U);
    CHECK(memcmp(received, "Note", 4U) == 0 && BtbChannelPending(&channel) == 0U);
    CHECK(BtbChannelReceive(&channel, 20U, received, 4U, &sender, &length, &responseSequence) == BTB_CHANNEL_EMPTY);

    /* Fill ring after its first wrap, then refuse an overflow without evicting. */
    for (size_t i = 0U; i < BTB_CHANNEL_DEPTH; ++i) {
        source[0] = (unsigned char)('A' + (int)i);
        CHECK(BtbChannelSend(&channel, 10U, 20U, source, 4U, &sequence) == BTB_CHANNEL_OK);
    }
    const uint64_t last = sequence;
    CHECK(BtbChannelSend(&channel, 10U, 20U, source, 4U, &sequence) == BTB_CHANNEL_FULL);
    CHECK(sequence == last && BtbChannelPending(&channel) == BTB_CHANNEL_DEPTH);
    for (size_t i = 0U; i < BTB_CHANNEL_DEPTH; ++i) {
        CHECK(BtbChannelReceive(&channel, 20U, received, 4U, &sender, &length, &responseSequence) == BTB_CHANNEL_OK);
        CHECK(received[0] == (unsigned char)('A' + (int)i));
    }
    channel.nextSequence = UINT64_MAX;
    CHECK(BtbChannelSend(&channel, 10U, 20U, source, 4U, &sequence) == BTB_CHANNEL_SEQUENCE_EXHAUSTED);
    CHECK(BtbChannelPending(&channel) == 0U);
    CHECK(BtbChannelSend(&channel, 0U, 20U, source, 4U, &sequence) == BTB_CHANNEL_INVALID);
    CHECK(BtbChannelSend(&channel, 10U, 10U, source, 4U, &sequence) == BTB_CHANNEL_INVALID);
    puts("[OK] copied-message ownership and bounded FIFO checks");
    return 0;
}
