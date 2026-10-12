/*-----------------------------------------------------------------------------
 * Bits2Banking | Umicom Foundation
 * File: labs/native/http-loopback-server/http.h
 * PURPOSE: Parse one bounded HTTP/1.1 request and prepare a fixed response.
 * AUTHOR: Sammy Hegab | LICENCE: MIT
 *---------------------------------------------------------------------------*/
#ifndef BTB_HTTP_H
#define BTB_HTTP_H
#include <stddef.h>
#include <stdint.h>
#define BTB_HTTP_MAX_HEADER 4096U
#define BTB_HTTP_MAX_PATH 128U

typedef enum BtbHttpResult {
    BTB_HTTP_OK = 0,
    BTB_HTTP_INCOMPLETE,
    BTB_HTTP_INVALID,
    BTB_HTTP_TOO_LARGE,
    BTB_HTTP_METHOD_NOT_ALLOWED
} BtbHttpResult;

typedef enum BtbHttpMethod {
    BTB_HTTP_GET = 1,
    BTB_HTTP_HEAD = 2
} BtbHttpMethod;

typedef struct BtbHttpRequest {
    BtbHttpMethod method;
    char path[BTB_HTTP_MAX_PATH];
    unsigned hostPort; /* 0 means no port was written in Host. */
} BtbHttpRequest;

/* Parses length-delimited network bytes, never a guessed C string. An
 * incomplete request is not an error while more bytes may arrive. On refusal
 * out is unchanged, so a partial parser cannot publish an accepted request. */
BtbHttpResult BtbHttpParse(const unsigned char *bytes, size_t byteCount,
                           BtbHttpRequest *out);
/* Generates headers plus the body in a single caller buffer; HEAD has the same
 * Content-Length as GET but sends no body. Refusals leave outputs unchanged. */
int BtbHttpRespond(const BtbHttpRequest *request, BtbHttpResult parseResult,
                   unsigned expectedPort, char *buffer, size_t capacity,
                   size_t *outBytes);
const char *BtbHttpResultText(BtbHttpResult result);
#endif
