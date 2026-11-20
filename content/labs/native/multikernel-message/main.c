/*-----------------------------------------------------------------------------
 * Umicom Bits2Banking
 * File: content/labs/native/multikernel-message/main.c
 *
 * PURPOSE:
 *   Verify the revision, instance and exact byte bounds of a copied request.
 *
 * AUTHOR AND ORGANISATION:
 * Sammy Hegab
 * Umicom Foundation
 *
 * LICENCE:
 * MIT
 *---------------------------------------------------------------------------*/
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>

enum { ProtocolRevision = 1, HeaderSize = 6, MaximumPayload = 8 };

typedef enum {
    Accepted, InvalidLength, UnsupportedRevision, StaleGeneration, NoRequest
} Result;

typedef struct {
    uint16_t generation;
    uint16_t request;
    size_t length;
    uint8_t payload[MaximumPayload];
} Request;

/* These bytes follow a fixed network order regardless of the host compiler. */
static uint16_t Read16(const uint8_t bytes[static 2])
{
    return (uint16_t)(((uint16_t)bytes[0] << 8U) | (uint16_t)bytes[1]);
}

/* The caller supplies the generation already bound to its owned worker.
 * Return a copied request only after all wire values fit the local contract. */
static Result Decode(const uint8_t *bytes, size_t available, uint16_t current, Request *out)
{
    if (available < HeaderSize) return InvalidLength;
    if (bytes[0] != ProtocolRevision) return UnsupportedRevision;
    size_t length = bytes[5];
    if (length > MaximumPayload || available - HeaderSize != length) return InvalidLength;
    uint16_t generation = Read16(bytes + 1);
    if (generation != current) return StaleGeneration;
    uint16_t request = Read16(bytes + 3);
    if (request == 0U) return NoRequest;

    Request captured = {.generation = generation, .request = request, .length = length};
    memcpy(captured.payload, bytes + HeaderSize, length);
    *out = captured;
    return Accepted;
}

int main(int argc, char *argv[])
{
    if (argc != 2) return 2;
    const char *name = argv[1];
    /* Start from one known frame. Every failed case changes one property. */
    uint8_t wire[HeaderSize + MaximumPayload] = {1, 0, 7, 0, 42, 3, 7, 11, 24};
    size_t available = HeaderSize + 3U;
    Result expected = Accepted;
    if (strcmp(name, "wrong-revision") == 0) {
        wire[0] = 2U;
        expected = UnsupportedRevision;
    } else if (strcmp(name, "stale-peer") == 0) {
        wire[2] = 6U;
        expected = StaleGeneration;
    } else if (strcmp(name, "truncated") == 0) {
        --available;
        expected = InvalidLength;
    } else if (strcmp(name, "trailing") == 0) {
        ++available;
        expected = InvalidLength;
    } else if (strcmp(name, "oversized") == 0) {
        wire[5] = MaximumPayload + 1U;
        expected = InvalidLength;
    } else if (strcmp(name, "missing-request") == 0) {
        wire[4] = 0U;
        expected = NoRequest;
    } else if (strcmp(name, "complete") != 0) {
        return 2;
    }

    /* A refused packet must leave the caller's previous result intact. */
    Request request;
    memset(&request, 0x5a, sizeof request);
    uint8_t before[sizeof request];
    memcpy(before, &request, sizeof before);
    Result observed = Decode(wire, available, 7U, &request);
    if (observed != expected) {
        fprintf(stderr, "%s returned %d, expected %d\n", name, (int)observed, (int)expected);
        return 1;
    }
    if (observed != Accepted) {
        if (memcmp(&request, before, sizeof before) != 0) return 1;
        printf("%s refused. The earlier result was preserved.\n", name);
        return 0;
    }

    /* Change the input after decoding. The saved payload belongs to the reader. */
    wire[HeaderSize] = 0U;
    if (request.length != 3U || request.request != 42U || request.generation != 7U) return 1;
    unsigned sum = 0U;
    for (size_t index = 0; index < request.length; ++index) sum += request.payload[index];
    if (sum != 42U) return 1;
    printf("Request %u from generation %u produced sum %u.\n",
        (unsigned)request.request, (unsigned)request.generation, sum);
    return 0;
}
