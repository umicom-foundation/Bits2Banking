/*-----------------------------------------------------------------------------
 * Bits to Banking | Umicom Foundation
 * File: labs/native/http-byte-parser/main.c
 * PURPOSE: Demonstrate a bounded request-line parser without networking.
 * AUTHOR AND ORGANISATION: Sammy Hegab, Umicom Foundation
 * LICENCE: MIT
 *---------------------------------------------------------------------------*/
#include "request_line.h"
#include <stdio.h>
#include <string.h>
int main(void)
{
    static const unsigned char REQUEST[] = "GET /lessons/ HTTP/1.1\r\n";
    BtbHttpRequestLine line = {0};
    if (BtbParseRequestLine(REQUEST, sizeof REQUEST - 1U, &line) != BTB_HTTP_OK) {
        fputs("The request line was rejected.\n", stderr);
        return 1;
    }
    printf("Method: %s\nPath: %s\nVersion: HTTP/%u.%u\n",
           line.method, line.path, line.major, line.minor);
    return 0;
}
