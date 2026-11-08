/*-----------------------------------------------------------------------------
 * Umicom Bits2Banking
 * File: labs/native/framework-http-contracts/stream.c
 *
 * PURPOSE:
 *   Follow incomplete input, owned bytes, terminal refusal and explicit request-stream reuse.
 *
 * AUTHOR AND ORGANISATION:
 * Sammy Hegab
 * Umicom Foundation
 *
 * LICENCE:
 * MIT
 *---------------------------------------------------------------------------*/

#include "check.h"
#include "umicom/web/request_stream.h"
#include <stdlib.h>
#include <string.h>

int main(void)
{
    const char header[] = "POST /sample HTTP/1.1\r\nHost: localhost\r\nContent-Length: 3\r\n\r\n";
    unsigned char body[] = {'A', 0U, 'B'};
    UmiWebRequestStream *stream = NULL;
    REQUIRE(UmiWebRequestStreamCreate(1024U, &stream) == UMI_STATUS_OK);
    /* A header can declare a complete frame size while its body is absent.
     * The stream owns a copy, so a temporary input span may then be reused. */
    REQUIRE(UmiWebRequestStreamFeed(stream, header, sizeof(header) - 1U) == UMI_STATUS_BUSY);
    UmiWebRequestStreamSnapshot snapshot;
    REQUIRE(UmiWebRequestStreamInspect(stream, &snapshot) == UMI_STATUS_OK);
    REQUIRE(snapshot.frame.body_bytes == 3U);
    REQUIRE(snapshot.frame.message_bytes == sizeof(header) - 1U + sizeof(body));
    printf("Header received: %zu bytes; expected message: %zu bytes.\n",
           snapshot.received_bytes, snapshot.frame.message_bytes);
    REQUIRE(UmiWebRequestStreamFeed(stream, body, 1U) == UMI_STATUS_BUSY);
    body[0] = 'X'; /* The already copied A must remain A inside the stream. */
    REQUIRE(UmiWebRequestStreamFeed(stream, body + 1U, 2U) == UMI_STATUS_OK);

    /* The existing request value is large; allocate it on the heap. Parse
     * produces owned storage rather than borrowing the stream's allocation. */
    UmiWebRequest *request = malloc(sizeof(*request));
    REQUIRE(request != NULL);
    REQUIRE(UmiWebRequestStreamParse(stream, request) == UMI_STATUS_OK);
    REQUIRE(request->body_length == 3U && memcmp(request->body, "A\0B", 3U) == 0);
    printf("Owned body length: %zu; bytes: %02x %02x %02x.\n", request->body_length,
           (unsigned)(unsigned char)request->body[0], (unsigned)(unsigned char)request->body[1],
           (unsigned)(unsigned char)request->body[2]);

    /* Extra bytes do not start a hidden second request. The failure is sticky,
     * and an unsuccessful parse must not overwrite the earlier owned result. */
    REQUIRE(UmiWebRequestStreamFeed(stream, "x", 1U) == UMI_STATUS_PARSE_ERROR);
    REQUIRE(UmiWebRequestStreamParse(stream, request) == UMI_STATUS_PARSE_ERROR);
    REQUIRE(request->body_length == 3U && memcmp(request->body, "A\0B", 3U) == 0);
    REQUIRE(UmiWebRequestStreamFeed(stream, NULL, 0U) == UMI_STATUS_PARSE_ERROR);
    REQUIRE(UmiWebRequestStreamReset(stream) == UMI_STATUS_OK);
    REQUIRE(UmiWebRequestStreamInspect(stream, &snapshot) == UMI_STATUS_OK);
    REQUIRE(snapshot.received_bytes == 0U && snapshot.frame.message_bytes == 0U);
    REQUIRE(snapshot.status == UMI_STATUS_BUSY && snapshot.maximum_bytes == 1024U);
    /* Reset concerns the parser only. This program has no socket to retain,
     * no handler to dispatch and no browser response to deliver. */
    UmiWebRequestStreamDestroy(stream);
    REQUIRE(request->body_length == 3U && memcmp(request->body, "A\0B", 3U) == 0);
    free(request);
    puts("Incremental ownership and explicit reset expectations satisfied.");
    return 0;
}
