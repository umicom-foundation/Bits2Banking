/*-----------------------------------------------------------------------------
 * Bits2Banking | Umicom Foundation
 * File: labs/native/http-loopback-server/route_service.h
 * PURPOSE: Bounded GET/HEAD routing with explicit service and response lifetimes.
 * AUTHOR: Sammy Hegab | LICENCE: MIT
 *---------------------------------------------------------------------------*/
#ifndef BTB_ROUTE_SERVICE_H
#define BTB_ROUTE_SERVICE_H
#include "http.h"
#include <stddef.h>
#include <stdint.h>

#define BTB_ROUTE_LIMIT 8U
#define BTB_ROUTE_BODY_LIMIT 2048U
#define BTB_ROUTE_PATH_LIMIT 96U

typedef enum BtbRouteResult {
    BTB_ROUTE_OK = 0,
    BTB_ROUTE_INVALID,
    BTB_ROUTE_CAPACITY,
    BTB_ROUTE_DUPLICATE,
    BTB_ROUTE_NOT_FOUND,
    BTB_ROUTE_BAD_STATE,
    BTB_ROUTE_BUSY
} BtbRouteResult;

typedef enum BtbRouteMedia {
    BTB_ROUTE_PLAIN_TEXT = 1,
    BTB_ROUTE_JSON = 2,
    BTB_ROUTE_HTML = 3
} BtbRouteMedia;

typedef struct BtbRouteResponse {
    unsigned statusCode;
    BtbRouteMedia media;
    size_t bodyLength;
    unsigned char body[BTB_ROUTE_BODY_LIMIT];
} BtbRouteResponse;

typedef BtbRouteResult (*BtbRouteHandler)(const BtbHttpRequest *request,
                                          BtbRouteResponse *out, void *context);

typedef struct BtbRouteEntry {
    char path[BTB_ROUTE_PATH_LIMIT];
    BtbRouteHandler handler;
    void *context; /* Borrowed: caller keeps it alive through Stop. */
} BtbRouteEntry;

typedef enum BtbRouteState {
    BTB_ROUTE_UNINITIALISED = 0,
    BTB_ROUTE_CONFIGURING,
    BTB_ROUTE_READY,
    BTB_ROUTE_STOPPED
} BtbRouteState;

typedef struct BtbRouteService {
    const struct BtbRouteService *self; /* Reject accidental copies of a live owner. */
    BtbRouteState state;
    size_t count;
    unsigned busy;
    uint64_t dispatched;
    BtbRouteEntry routes[BTB_ROUTE_LIMIT];
} BtbRouteService;

/* Initialise zero-filled, stable, caller-owned storage. Never reset live state.
 * A started service rejects registration. Only one request runs at a time. */
BtbRouteResult BtbRouteServiceInit(BtbRouteService *service);
BtbRouteResult BtbRouteServiceRegister(BtbRouteService *service,
                                        const char *path, BtbRouteHandler handler,
                                        void *context);
BtbRouteResult BtbRouteServiceStart(BtbRouteService *service);
BtbRouteResult BtbRouteServiceStop(BtbRouteService *service);
BtbRouteResult BtbRouteServiceDispatch(BtbRouteService *service,
                                        const BtbHttpRequest *request,
                                        BtbRouteResponse *out);

/* Copy a complete length-delimited body into a privately owned response.
 * Allowed media types and status codes are fixed, not untrusted header text. */
BtbRouteResult BtbRouteResponseSet(BtbRouteResponse *out, unsigned status,
                                    BtbRouteMedia media, const void *body,
                                    size_t length);

/* Prepare exactly one closed HTTP response. HEAD announces the same body length
 * as GET but emits no body bytes. Failure leaves caller outputs untouched.
 * outHeaderBytes identifies the wire boundary for send-completion accounting. */
BtbRouteResult BtbRouteEncode(const BtbHttpRequest *request,
                               const BtbRouteResponse *response,
                               char *buffer, size_t capacity,
                               size_t *outBytes, size_t *outHeaderBytes);
const char *BtbRouteResultText(BtbRouteResult result);
#endif
