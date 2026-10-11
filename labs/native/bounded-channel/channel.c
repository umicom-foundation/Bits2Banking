/*-----------------------------------------------------------------------------
 * Bits to Banking
 * File: labs/native/bounded-channel/channel.c
 * PURPOSE: Demonstrate full-message copying and failure-atomic FIFO receive.
 * AUTHOR AND ORGANISATION: Sammy Hegab, Umicom Foundation
 * LICENCE: MIT
 *---------------------------------------------------------------------------*/
#include "channel.h"
#include <string.h>

void BtbChannelInit(BtbChannel *channel)
{
    if (channel != NULL) {
        *channel = (BtbChannel){0};
        channel->nextSequence = 1U;
    }
}
size_t BtbChannelPending(const BtbChannel *channel)
{
    return channel != NULL ? channel->count : 0U;
}
BtbChannelResult BtbChannelSend(BtbChannel *channel, uint32_t sender,
    uint32_t recipient, const void *data, size_t length, uint64_t *outSequence)
{
    if (channel == NULL || data == NULL || outSequence == NULL ||
        sender == 0U || recipient == 0U || sender == recipient ||
        length == 0U || length > BTB_CHANNEL_MESSAGE_BYTES)
        return BTB_CHANNEL_INVALID;
    if (channel->head >= BTB_CHANNEL_DEPTH || channel->count > BTB_CHANNEL_DEPTH ||
        channel->nextSequence == 0U)
        return BTB_CHANNEL_INVALID;
    if (channel->count == BTB_CHANNEL_DEPTH)
        return BTB_CHANNEL_FULL;
    if (channel->nextSequence == UINT64_MAX)
        return BTB_CHANNEL_SEQUENCE_EXHAUSTED;

    const size_t index = (channel->head + channel->count) % BTB_CHANNEL_DEPTH;
    BtbChannelMessage candidate = {0};
    candidate.sender = sender;
    candidate.recipient = recipient;
    candidate.sequence = channel->nextSequence;
    candidate.length = length;
    memcpy(candidate.bytes, data, length);
    /* Publish all bytes first; only then advance the queue and issue an ID. */
    channel->slots[index] = candidate;
    ++channel->count;
    ++channel->nextSequence;
    *outSequence = candidate.sequence;
    return BTB_CHANNEL_OK;
}
BtbChannelResult BtbChannelReceive(BtbChannel *channel, uint32_t recipient,
    void *destination, size_t capacity, uint32_t *outSender,
    size_t *outLength, uint64_t *outSequence)
{
    if (channel == NULL || recipient == 0U || destination == NULL ||
        outSender == NULL || outLength == NULL || outSequence == NULL ||
        channel->head >= BTB_CHANNEL_DEPTH || channel->count > BTB_CHANNEL_DEPTH)
        return BTB_CHANNEL_INVALID;
    if (channel->count == 0U)
        return BTB_CHANNEL_EMPTY;
    const BtbChannelMessage *message = &channel->slots[channel->head];
    if (message->recipient != recipient)
        return BTB_CHANNEL_DENIED;
    if (message->length == 0U || message->length > BTB_CHANNEL_MESSAGE_BYTES)
        return BTB_CHANNEL_INVALID;
    if (capacity < message->length)
        return BTB_CHANNEL_SMALL_BUFFER;
    /* Nothing is consumed until the entire caller-owned destination can hold
     * the message. The test exercises this failed-receive boundary explicitly. */
    memcpy(destination, message->bytes, message->length);
    *outSender = message->sender;
    *outLength = message->length;
    *outSequence = message->sequence;
    memset(&channel->slots[channel->head], 0, sizeof(channel->slots[channel->head]));
    channel->head = (channel->head + 1U) % BTB_CHANNEL_DEPTH;
    --channel->count;
    return BTB_CHANNEL_OK;
}
