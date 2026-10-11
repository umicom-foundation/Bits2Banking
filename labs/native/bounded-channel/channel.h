/*-----------------------------------------------------------------------------
 * Bits to Banking
 * File: labs/native/bounded-channel/channel.h
 * PURPOSE: Single-threaded copied-message queue for studying IPC ownership.
 * AUTHOR AND ORGANISATION: Sammy Hegab, Umicom Foundation
 * LICENCE: MIT
 *---------------------------------------------------------------------------*/
#ifndef BTB_BOUNDED_CHANNEL_H
#define BTB_BOUNDED_CHANNEL_H
#include <stddef.h>
#include <stdint.h>

#define BTB_CHANNEL_DEPTH 4U
#define BTB_CHANNEL_MESSAGE_BYTES 64U

typedef enum BtbChannelResult {
    BTB_CHANNEL_OK = 0,
    BTB_CHANNEL_INVALID = 1,
    BTB_CHANNEL_FULL = 2,
    BTB_CHANNEL_EMPTY = 3,
    BTB_CHANNEL_DENIED = 4,
    BTB_CHANNEL_SMALL_BUFFER = 5,
    BTB_CHANNEL_SEQUENCE_EXHAUSTED = 6
} BtbChannelResult;

typedef struct BtbChannelMessage {
    uint32_t sender;
    uint32_t recipient;
    uint64_t sequence;
    size_t length;
    unsigned char bytes[BTB_CHANNEL_MESSAGE_BYTES];
} BtbChannelMessage;

typedef struct BtbChannel {
    BtbChannelMessage slots[BTB_CHANNEL_DEPTH];
    size_t head;
    size_t count;
    uint64_t nextSequence;
} BtbChannel;

/* Call once on caller-owned storage. This model is NOT thread safe, and is not
 * the privileged Umicom Kernel message service. Pointers to a live channel
 * must not be retained in unrelated threads or passed in message payloads. */
void BtbChannelInit(BtbChannel *channel);
size_t BtbChannelPending(const BtbChannel *channel);

/* Copies the entire payload; input may be reused immediately after success.
 * Sender and recipient must be distinct positive identities. Failure does not
 * change the queue or outSequence. Input must not overlap channel storage. */
BtbChannelResult BtbChannelSend(BtbChannel *channel, uint32_t sender,
    uint32_t recipient, const void *data, size_t length, uint64_t *outSequence);

/* Only the named recipient may consume the oldest message. The destination
 * must hold the complete payload. Failure leaves the queue and outputs intact.
 * Outputs/destination must be caller-owned and not overlap channel storage. */
BtbChannelResult BtbChannelReceive(BtbChannel *channel, uint32_t recipient,
    void *destination, size_t capacity, uint32_t *outSender,
    size_t *outLength, uint64_t *outSequence);
#endif
