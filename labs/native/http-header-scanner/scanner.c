/*-----------------------------------------------------------------------------
 * Bits to Banking | Umicom Foundation | Sammy Hegab | MIT
 * File: labs/native/http-header-scanner/scanner.c
 * PURPOSE: Portable C reference implementation for the HTTP scanner lesson.
 *---------------------------------------------------------------------------*/
#include "scanner.h"
int BitsHttpContainsCrlfC(const unsigned char *bytes, size_t count)
{
    if (bytes == NULL || count < 2U) return 0;
    for (size_t i = 0U; i < count - 1U; ++i) {
        if (bytes[i] == 13U && bytes[i + 1U] == 10U) return 1;
    }
    return 0;
}
