/*-----------------------------------------------------------------------------
 * Bits to Banking
 * File: labs/native/syscall-dispatch/main.c
 * PURPOSE: Show a simulated service call with explicit permission checks.
 * AUTHOR AND ORGANISATION: Sammy Hegab, Umicom Foundation
 * LICENCE: MIT
 *---------------------------------------------------------------------------*/
#include "dispatch.h"
#include <inttypes.h>
#include <stdio.h>
int main(void)
{
    BtbServiceState service;
    BtbServiceInit(&service, 125U);
    BtbServiceRequest get = {.caller = 101U, .operation = BTB_SERVICE_GET_TICKS};
    BtbServiceReply reply = {0};
    if (BtbServiceDispatch(&service, &get, &reply) != BTB_SERVICE_OK)
        return 1;
    printf("Training service ticks: %" PRIu64 "\n", reply.value);
    const char event[] = "Notes document saved";
    BtbServiceRequest publish = {.caller = 101U,
                                 .rights = BTB_SERVICE_RIGHT_PUBLISH,
                                 .operation = BTB_SERVICE_PUBLISH_EVENT,
                                 .expectedRevision = service.revision,
                                 .input = event,
                                 .inputLength = sizeof(event) - 1U};
    if (BtbServiceDispatch(&service, &publish, &reply) != BTB_SERVICE_OK)
        return 1;
    printf("Training events: %" PRIu64 "; revision: %" PRIu64 "\n",
           reply.value, reply.revision);
    return 0;
}
