/*-----------------------------------------------------------------------------
 * Bits to Banking
 * File: labs/native/syscall-dispatch/dispatch.c
 * PURPOSE: Learn syscall validation and failure-atomic updates in hosted C23.
 * AUTHOR AND ORGANISATION: Sammy Hegab, Umicom Foundation
 * LICENCE: MIT
 *---------------------------------------------------------------------------*/
#include "dispatch.h"
#include <string.h>

void BtbServiceInit(BtbServiceState *state, uint64_t ticks)
{
    if (state != NULL) {
        *state = (BtbServiceState){0};
        state->ticks = ticks;
        state->revision = 1U;
    }
}

BtbServiceStatus BtbServiceDispatch(BtbServiceState *state,
    const BtbServiceRequest *request, BtbServiceReply *reply)
{
    if (state == NULL || request == NULL || reply == NULL || request->caller == 0U ||
        state->revision == 0U || state->eventCount > BTB_SERVICE_EVENT_SLOTS)
        return BTB_SERVICE_INVALID;
    if (request->operation == BTB_SERVICE_GET_TICKS) {
        if (request->input != NULL || request->inputLength != 0U)
            return BTB_SERVICE_INVALID;
        *reply = (BtbServiceReply){.value = state->ticks, .revision = state->revision};
        return BTB_SERVICE_OK;
    }
    if (request->operation != BTB_SERVICE_PUBLISH_EVENT)
        return BTB_SERVICE_INVALID;
    if ((request->rights & BTB_SERVICE_RIGHT_PUBLISH) == 0U)
        return BTB_SERVICE_DENIED;
    if (request->expectedRevision != state->revision)
        return BTB_SERVICE_CONFLICT;
    if (request->input == NULL || request->inputLength == 0U ||
        request->inputLength >= BTB_SERVICE_EVENT_BYTES ||
        state->revision == UINT64_MAX)
        return BTB_SERVICE_INVALID;
    if (state->eventCount == BTB_SERVICE_EVENT_SLOTS)
        return BTB_SERVICE_FULL;
    char text[BTB_SERVICE_EVENT_BYTES] = {0};
    for (size_t index = 0U; index < request->inputLength; ++index) {
        unsigned char value = (unsigned char)request->input[index];
        if (value < 0x20U || value > 0x7eU)
            return BTB_SERVICE_INVALID;
        text[index] = (char)value;
    }
    /* Publish complete text in the next slot; then update revision and reply.
     * No partial mutation occurs for invalid text, rights or stale versions. */
    memcpy(state->events[state->eventCount], text, sizeof(text));
    ++state->eventCount;
    ++state->revision;
    *reply = (BtbServiceReply){.value = (uint64_t)state->eventCount,
                               .revision = state->revision};
    return BTB_SERVICE_OK;
}
