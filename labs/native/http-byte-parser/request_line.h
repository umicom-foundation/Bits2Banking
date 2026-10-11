/*-----------------------------------------------------------------------------
 * Bits to Banking | Umicom Foundation
 * File: labs/native/http-byte-parser/request_line.h
 * PURPOSE: Teach bounded HTTP request-line inspection on raw byte spans.
 * AUTHOR AND ORGANISATION: Sammy Hegab, Umicom Foundation
 * LICENCE: MIT
 *---------------------------------------------------------------------------*/
#ifndef BTB_HTTP_BYTE_PARSER_H
#define BTB_HTTP_BYTE_PARSER_H
#include <stddef.h>
#include <stdint.h>
#ifdef __cplusplus
extern "C" {
#endif
#define BTB_HTTP_LINE_MAX_BYTES 200U
#define BTB_HTTP_PATH_MAX_BYTES 120U

typedef enum BtbHttpResult {
    BTB_HTTP_OK = 0,
    BTB_HTTP_INVALID = 1,
    BTB_HTTP_TOO_LONG = 2,
    BTB_HTTP_UNSUPPORTED = 3
} BtbHttpResult;
typedef struct BtbHttpRequestLine {
    char method[5];
    char path[BTB_HTTP_PATH_MAX_BYTES + 1U];
    unsigned major;
    unsigned minor;
} BtbHttpRequestLine;

/* Only GET and HEAD, HTTP/1.0 or 1.1, and an ASCII path without a query.
 * Input may contain NUL bytes and need not be terminated. The parser handles
 * exactly one request line ending in CRLF, not a complete HTTP request.
 * Refused input leaves *out byte-for-byte unchanged. This is an educational
 * parser; Umicom Framework owns production routing and HTTP security policy. */
BtbHttpResult BtbParseRequestLine(const uint8_t *bytes, size_t byteCount,
                                  BtbHttpRequestLine *out);
#ifdef __cplusplus
}
#endif
#endif
