/*-----------------------------------------------------------------------------
 * Bits to Banking | Umicom Foundation | Sammy Hegab | MIT
 * File: labs/native/http-header-scanner/test_scanner.c
 * PURPOSE: Verify both implementations, including bounds and embedded NUL.
 *---------------------------------------------------------------------------*/
#include "scanner.h"
#include <stddef.h>
#include <stdio.h>
static int Check(const unsigned char *bytes, size_t count, int expected)
{
    const int reference = BitsHttpContainsCrlfC(bytes, count);
    if (reference != expected) return 1;
#if defined(BITS_HTTP_HAVE_ASSEMBLY)
    if (BitsHttpContainsCrlfAsm(bytes, count) != reference) return 1;
#endif
    return 0;
}
int main(void)
{
    static const unsigned char cases[][8] = {
        {13U, 10U, 0U, 0U, 0U, 0U, 0U, 0U},
        {65U, 66U, 13U, 10U, 0U, 0U, 0U, 0U},
        {13U, 13U, 10U, 0U, 0U, 0U, 0U, 0U},
        {65U, 66U, 67U, 13U, 10U, 88U, 89U, 90U},
        {10U, 13U, 10U, 0U, 0U, 0U, 0U, 0U}
    };
    const int expected[] = {1, 1, 1, 1, 1};
    for (size_t i = 0U; i < sizeof(cases) / sizeof(cases[0]); ++i) {
        if (Check(cases[i], sizeof(cases[0]), expected[i])) return 1;
        for (size_t count = 0U; count <= sizeof(cases[0]); ++count) {
            const int want = BitsHttpContainsCrlfC(cases[i], count);
            if (Check(cases[i], count, want)) return 1;
        }
    }
    static const unsigned char absent[] = {13U, 0U, 10U, 13U, 7U, 10U};
    if (Check(absent, sizeof(absent), 0)) return 1;
    if (Check(NULL, 0U, 0)) return 1;
    if (Check(absent, 1U, 0)) return 1;
    unsigned char variable[32] = {0};
    for (size_t length = 0U; length <= sizeof(variable); ++length) {
        for (size_t at = 0U; at < length; ++at) {
            variable[at] = (unsigned char)((at * 19U + length * 3U) % 256U);
        }
        if (Check(variable, length, BitsHttpContainsCrlfC(variable, length))) return 1;
    }
    puts("C and Assembly scanner agree on bounded input cases.");
    return 0;
}
