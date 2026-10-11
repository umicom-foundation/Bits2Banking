/*-----------------------------------------------------------------------------
 * Bits to Banking
 * File: labs/native/syscall-dispatch/test_dispatch.c
 * PURPOSE: Check copied input, denied rights, stale revisions and full logs.
 * AUTHOR AND ORGANISATION: Sammy Hegab, Umicom Foundation
 * LICENCE: MIT
 *---------------------------------------------------------------------------*/
#include "dispatch.h"
#include <stdio.h>
#include <string.h>
#define CHECK(condition) do { if (!(condition)) { fprintf(stderr, "FAIL line %d: %s\n", __LINE__, #condition); return 1; } } while (0)

int main(void)
{
    BtbServiceState state;
    BtbServiceInit(&state, 321U);
    const BtbServiceState initial = state;
    BtbServiceReply reply = {.value = 777U, .revision = 888U};
    const BtbServiceReply sentinel = reply;
    char text[] = "Save Notes";
    BtbServiceRequest request = {.caller = 1U, .operation = BTB_SERVICE_PUBLISH_EVENT,
                                 .expectedRevision = 1U, .input = text,
                                 .inputLength = sizeof(text) - 1U};
    CHECK(BtbServiceDispatch(&state, &request, &reply) == BTB_SERVICE_DENIED);
    CHECK(state.ticks == initial.ticks && state.revision == initial.revision &&
          state.eventCount == initial.eventCount &&
          reply.value == sentinel.value && reply.revision == sentinel.revision);
    request.rights = BTB_SERVICE_RIGHT_PUBLISH;
    request.expectedRevision = 2U;
    CHECK(BtbServiceDispatch(&state, &request, &reply) == BTB_SERVICE_CONFLICT);
    CHECK(state.eventCount == 0U && reply.value == sentinel.value);
    request.expectedRevision = 1U;
    CHECK(BtbServiceDispatch(&state, &request, &reply) == BTB_SERVICE_OK);
    text[0] = '!'; /* A different caller buffer cannot change accepted bytes. */
    CHECK(strcmp(state.events[0], "Save Notes") == 0);
    CHECK(state.eventCount == 1U && state.revision == 2U);
    request.input = "Bad\nline";
    request.inputLength = 8U;
    request.expectedRevision = 2U;
    const BtbServiceState before = state;
    const BtbServiceReply beforeReply = reply;
    CHECK(BtbServiceDispatch(&state, &request, &reply) == BTB_SERVICE_INVALID);
    CHECK(state.ticks == before.ticks && state.revision == before.revision &&
          state.eventCount == before.eventCount &&
          strcmp(state.events[0], before.events[0]) == 0 &&
          reply.value == beforeReply.value && reply.revision == beforeReply.revision);
    request.input = "ok";
    request.inputLength = 2U;
    for (size_t index = 1U; index < BTB_SERVICE_EVENT_SLOTS; ++index) {
        request.expectedRevision = state.revision;
        CHECK(BtbServiceDispatch(&state, &request, &reply) == BTB_SERVICE_OK);
    }
    CHECK(state.eventCount == BTB_SERVICE_EVENT_SLOTS);
    request.expectedRevision = state.revision;
    CHECK(BtbServiceDispatch(&state, &request, &reply) == BTB_SERVICE_FULL);
    CHECK(state.eventCount == BTB_SERVICE_EVENT_SLOTS);
    BtbServiceRequest get = {.caller = 22U, .operation = BTB_SERVICE_GET_TICKS};
    CHECK(BtbServiceDispatch(&state, &get, &reply) == BTB_SERVICE_OK);
    CHECK(reply.value == 321U && reply.revision == state.revision);
    get.operation = (BtbServiceCall)99U;
    CHECK(BtbServiceDispatch(&state, &get, &reply) == BTB_SERVICE_INVALID);
    puts("[OK] rights, copy, revisions, failure-atomic service calls");
    return 0;
}
