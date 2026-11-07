/*-----------------------------------------------------------------------------
 * Umicom Bits2Banking
 * File: labs/native/framework-http-contracts/framing.c
 *
 * PURPOSE:
 *   Observe complete, incomplete and invalid requests through Framework framing.
 *
 * AUTHOR AND ORGANISATION:
 * Sammy Hegab
 * Umicom Foundation
 *
 * LICENCE:
 * MIT
 *---------------------------------------------------------------------------*/

#include "check.h"
#include "umicom/web/connection.h"
#include <stdlib.h>
#include <string.h>
int main(void)
{
    const char wire[] = "POST /echo HTTP/1.1\r\nHost: localhost\r\nContent-Length: 3\r\n\r\nA\0B";
    const size_t length = sizeof(wire) - 1U;
    UmiWebRequestFrame frame = {0};
    REQUIRE(UmiWebRequestFrameRead(wire, length - 1U, 1024U, &frame) == UMI_STATUS_BUSY);
    REQUIRE(frame.message_bytes == 0U);
    REQUIRE(UmiWebRequestFrameRead(wire, length, 1024U, &frame) == UMI_STATUS_OK);
    REQUIRE(frame.body_bytes == 3U && frame.message_bytes == length);
    /* The Framework owns parsing policy; the lab owns only this destination. */
    UmiWebRequest *request = malloc(sizeof(*request));
    REQUIRE(request != NULL);
    const UmiStatus parsed = UmiWebRequestParseStrict(wire, length, 1024U, request);
    const int body_matches = parsed == UMI_STATUS_OK &&
        request->body_length == 3U && memcmp(request->body, "A\0B", 3U) == 0;
    free(request);
    REQUIRE(body_matches);
    const char duplicate[] = "GET / HTTP/1.1\r\nHost: localhost\r\nContent-Length: 0\r\nContent-Length: 0\r\n\r\n";
    REQUIRE(UmiWebRequestFrameRead(duplicate, sizeof(duplicate) - 1U, 1024U, &frame)
        == UMI_STATUS_PARSE_ERROR);
    puts("Incomplete, binary-body and duplicate-length expectations satisfied.");
    return 0;
}
