/*-----------------------------------------------------------------------------
 * Bits to Banking | Umicom Foundation
 * File: labs/native/http-byte-parser/test_request_line.c
 * PURPOSE: Verify byte bounds, refusal atomicity and accepted request lines.
 * AUTHOR AND ORGANISATION: Sammy Hegab, Umicom Foundation
 * LICENCE: MIT
 *---------------------------------------------------------------------------*/
#include "request_line.h"
#include <stdint.h>
#include <stdio.h>
#include <string.h>

#define CHECK(x) do { if (!(x)) { fprintf(stderr, "Failed at line %d: %s\n", __LINE__, #x); return 1; } } while (0)

static int RefusedUnchanged(const unsigned char *request, size_t count, BtbHttpResult expected)
{
    BtbHttpRequestLine output;
    memset(&output, 0xa5, sizeof output);
    BtbHttpRequestLine before = output;
    BtbHttpResult result = BtbParseRequestLine(request, count, &output);
    return result == expected && memcmp(&output, &before, sizeof output) == 0;
}
int main(void)
{
    static const unsigned char GOOD[] = "GET /lessons/ HTTP/1.1\r\n";
    static const unsigned char HEAD[] = "HEAD /books/index.html HTTP/1.0\r\n";
    static const unsigned char BAD_NO_CRLF[] = "GET / HTTP/1.1\n";
    static const unsigned char BAD_TRAVERSAL[] = "GET /private/../data HTTP/1.1\r\n";
    static const unsigned char BAD_SPACE[] = "GET  /books HTTP/1.1\r\n";
    static const unsigned char BAD_PERCENT[] = "GET /%2e%2e/ HTTP/1.1\r\n";
    static const unsigned char BAD_METHOD[] = "POST /api/send HTTP/1.1\r\n";
    static const unsigned char BAD_VERSION[] = "GET / HTTP/2.0\r\n";
    static const unsigned char BAD_NUL[] = {'G','E','T',' ','/','x',0,' ','H','T','T','P','/','1','.','1',13,10};
    BtbHttpRequestLine output = {0};
    CHECK(BtbParseRequestLine(GOOD, sizeof GOOD - 1U, &output) == BTB_HTTP_OK);
    CHECK(strcmp(output.method,"GET") == 0 && strcmp(output.path,"/lessons/") == 0);
    CHECK(output.major == 1U && output.minor == 1U);
    CHECK(BtbParseRequestLine(HEAD, sizeof HEAD - 1U, &output) == BTB_HTTP_OK);
    CHECK(strcmp(output.method,"HEAD") == 0 && output.minor == 0U);
    CHECK(RefusedUnchanged(BAD_NO_CRLF,sizeof BAD_NO_CRLF - 1U,BTB_HTTP_INVALID));
    CHECK(RefusedUnchanged(BAD_TRAVERSAL,sizeof BAD_TRAVERSAL - 1U,BTB_HTTP_INVALID));
    CHECK(RefusedUnchanged(BAD_SPACE,sizeof BAD_SPACE - 1U,BTB_HTTP_INVALID));
    CHECK(RefusedUnchanged(BAD_PERCENT,sizeof BAD_PERCENT - 1U,BTB_HTTP_INVALID));
    CHECK(RefusedUnchanged(BAD_METHOD,sizeof BAD_METHOD - 1U,BTB_HTTP_UNSUPPORTED));
    CHECK(RefusedUnchanged(BAD_VERSION,sizeof BAD_VERSION - 1U,BTB_HTTP_UNSUPPORTED));
    CHECK(RefusedUnchanged(BAD_NUL,sizeof BAD_NUL,BTB_HTTP_INVALID));
    CHECK(RefusedUnchanged(GOOD,sizeof GOOD - 2U,BTB_HTTP_INVALID));
    CHECK(RefusedUnchanged(GOOD,0U,BTB_HTTP_INVALID));
    CHECK(RefusedUnchanged(NULL,0U,BTB_HTTP_INVALID));
    static const unsigned char LONG[BTB_HTTP_LINE_MAX_BYTES+1U] = {0};
    CHECK(RefusedUnchanged(LONG,sizeof LONG,BTB_HTTP_TOO_LONG));
    puts("All request-line cases passed.");
    return 0;
}
