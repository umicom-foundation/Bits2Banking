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
#include "cache_validator.h"
#define BTB_HTTP_MAX_HEADER 4096U
#define BTB_HTTP_FIXED_PATH_LIMIT 128U
#define BTB_HTTP_MAX_PATH 1024U

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
    /* Optional cache validator for static-file requests only. Legacy fixed
     * handlers still answer without evaluating this field. */
    unsigned ifNoneMatchPresent;
    char ifNoneMatch[BTB_CACHE_CONDITION_CAPACITY];
} BtbHttpRequest;

/* Parses length-delimited network bytes, never a guessed C string. An
 * incomplete request is not an error while more bytes may arrive. On refusal
 * out is unchanged, so a partial parser cannot publish an accepted request. */
BtbHttpResult BtbHttpParse(const unsigned char *bytes, size_t byteCount,
                           BtbHttpRequest *out);
/* Extend the same parser for static-site paths with dot filenames and escaped
 * path bytes. This does not change the legacy fixed-route parser's acceptance
 * rules. The query is not part of the selected filesystem path. */
BtbHttpResult BtbHttpParseForFiles(const unsigned char *bytes, size_t byteCount,
                                   BtbHttpRequest *out);
/* Build static-file response headers only. The socket owner streams body bytes
 * separately; HEAD advertises the complete length but transmits no body. */
int BtbHttpStaticHeaders(unsigned code, const char *mediaType, uint64_t bodyBytes,
                         char *buffer, size_t capacity, size_t *outBytes);

/* Generates headers plus the body in a single caller buffer; HEAD has the same
 * Content-Length as GET but sends no body. Refusals leave outputs unchanged. */
int BtbHttpRespond(const BtbHttpRequest *request, BtbHttpResult parseResult,
                   unsigned expectedPort, char *buffer, size_t capacity,
                   size_t *outBytes);
const char *BtbHttpResultText(BtbHttpResult result);
#endif
