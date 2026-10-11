/*-----------------------------------------------------------------------------
 * Bits to Banking
 * File: labs/native/syscall-dispatch/dispatch.h
 * PURPOSE: Simulate kernel-service requests with explicit caller rights.
 * AUTHOR AND ORGANISATION: Sammy Hegab, Umicom Foundation
 * LICENCE: MIT
 *---------------------------------------------------------------------------*/
#ifndef BTB_SYSCALL_DISPATCH_H
#define BTB_SYSCALL_DISPATCH_H
#include <stddef.h>
#include <stdint.h>
#define BTB_SERVICE_EVENT_SLOTS 4U
#define BTB_SERVICE_EVENT_BYTES 48U
#define BTB_SERVICE_RIGHT_PUBLISH 1U

typedef enum BtbServiceCall {
    BTB_SERVICE_GET_TICKS = 1,
    BTB_SERVICE_PUBLISH_EVENT = 2
} BtbServiceCall;
typedef enum BtbServiceStatus {
    BTB_SERVICE_OK = 0,
    BTB_SERVICE_INVALID = 1,
    BTB_SERVICE_DENIED = 2,
    BTB_SERVICE_FULL = 3,
    BTB_SERVICE_CONFLICT = 4
} BtbServiceStatus;

typedef struct BtbServiceState {
    uint64_t ticks;
    uint64_t revision;
    size_t eventCount;
    char events[BTB_SERVICE_EVENT_SLOTS][BTB_SERVICE_EVENT_BYTES];
} BtbServiceState;
typedef struct BtbServiceRequest {
    uint32_t caller;      /* Trusted by this classroom simulation ONLY. */
    uint32_t rights;      /* Real kernel must derive rights from a live handle. */
    BtbServiceCall operation;
    uint64_t expectedRevision;
    const char *input;
    size_t inputLength;
} BtbServiceRequest;
typedef struct BtbServiceReply {
    uint64_t value;
    uint64_t revision;
} BtbServiceReply;

void BtbServiceInit(BtbServiceState *state, uint64_t ticks);
/* GET_TICKS reads state. PUBLISH_EVENT requires a right, a matching expected
 * revision and 1..47 printable ASCII bytes. On any refusal, both the state and
 * reply are unchanged. No trap, privilege transition or OS call is performed.
 * Request buffers and replies must not alias the service state. */
BtbServiceStatus BtbServiceDispatch(BtbServiceState *state,
    const BtbServiceRequest *request, BtbServiceReply *reply);
#endif
