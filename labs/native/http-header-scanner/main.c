/*-----------------------------------------------------------------------------
 * Bits to Banking | Umicom Foundation | Sammy Hegab | MIT
 * File: labs/native/http-header-scanner/main.c
 * PURPOSE: Demonstrate a bounded HTTP CRLF scanner with no socket privileges.
 *---------------------------------------------------------------------------*/
#include "scanner.h"
#include <stdio.h>
int main(void)
{
    static const unsigned char request[] = "GET / HTTP/1.1\r\nHost: localhost\r\n";
    const size_t count = sizeof(request) - 1U;
    const int found = BitsHttpContainsCrlfC(request, count);
    printf("C scanner found a CRLF line ending: %s\n", found ? "yes" : "no");
#if defined(BITS_HTTP_HAVE_ASSEMBLY)
    const int assemblyFound = BitsHttpContainsCrlfAsm(request, count);
    printf("Assembly scanner agrees: %s\n", assemblyFound == found ? "yes" : "no");
    return assemblyFound == found ? 0 : 1;
#else
    puts("Assembly extension disabled: portable C scanner remains available.");
    return 0;
#endif
}
