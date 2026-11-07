/*-----------------------------------------------------------------------------
 * Umicom Bits2Banking
 * File: labs/native/framework-http-contracts/response.c
 *
 * PURPOSE:
 *   Compare GET and HEAD response framing and unchanged output on capacity failure.
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
    UmiWebResponse *response = malloc(sizeof(*response));
    REQUIRE(response != NULL);
    umi_web_response_init(response);
    UmiStatus status = umi_web_response_set_text(response, 200, "text/plain", "ready");
    unsigned char get[1024] = {0}, head[1024] = {0};
    size_t get_length = 0U, head_length = 0U;
    if (status == UMI_STATUS_OK)
        status = UmiWebResponseFormatClosed(response, false, get, sizeof(get) - 1U, &get_length);
    if (status == UMI_STATUS_OK)
        status = UmiWebResponseFormatClosed(response, true, head, sizeof(head) - 1U, &head_length);
    unsigned char tiny[4] = {0x55U, 0x55U, 0x55U, 0x55U};
    const unsigned char before[4] = {0x55U, 0x55U, 0x55U, 0x55U};
    size_t tiny_length = 99U;
    const UmiStatus small = UmiWebResponseFormatClosed(response, false, tiny, sizeof(tiny), &tiny_length);
    free(response);
    REQUIRE(status == UMI_STATUS_OK);
    REQUIRE(get_length == head_length + 5U);
    REQUIRE(strstr((const char *)head, "Content-Length: 5\r\n") != NULL);
    REQUIRE(strstr((const char *)head, "Connection: close\r\n") != NULL);
    REQUIRE(memcmp(get + get_length - 5U, "ready", 5U) == 0);
    REQUIRE(small == UMI_STATUS_CAPACITY_EXCEEDED && tiny_length == 0U);
    REQUIRE(memcmp(tiny, before, sizeof(tiny)) == 0);
    puts("GET, HEAD and unchanged-output expectations satisfied.");
    return 0;
}
