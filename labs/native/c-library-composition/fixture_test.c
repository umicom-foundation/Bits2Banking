/*-----------------------------------------------------------------------------
 * Umicom Bits2Banking
 * File: labs/native/c-library-composition/fixture_test.c
 *
 * PURPOSE:
 *   Check literal byte boundaries, unsigned octet views and signed-zero observations.
 *
 * AUTHOR AND ORGANISATION:
 * Sammy Hegab
 * Umicom Foundation
 *
 * LICENCE:
 * MIT
 *---------------------------------------------------------------------------*/

#include <math.h>
#include <stdio.h>
#include <string.h>
#define CHECK(condition) do { if (!(condition)) { \
    fprintf(stderr, "line %d: %s\n", __LINE__, #condition); return 1; \
} } while (0)
int main(int argc, char **argv)
{
    if (argc != 2) return 2;
    if (strcmp(argv[1], "hex-boundary") == 0) {
        /* End each numeric escape before a following hexadecimal character.
         * Independent numeric byte expectations avoid repeating the literal. */
        const unsigned char fence[] = "\x60\x60\x60" "c\n";
        const unsigned char expected[] = {96U, 96U, 96U, 99U, 10U, 0U};
        CHECK(sizeof fence == sizeof expected);
        CHECK(memcmp(fence, expected, sizeof expected) == 0);
    } else if (strcmp(argv[1], "utf8-octets") == 0) {
        const char path[] = "caf\xc3\xa9/tool";
        const unsigned char *octets = (const unsigned char *)path;
        CHECK(strlen(path) == 10U);
        CHECK(octets[3] == 195U && octets[4] == 169U);
        CHECK(path[5] == '/' && path[10] == '\0');
    } else if (strcmp(argv[1], "signed-zero") == 0) {
        const double negative = -0.0, positive = +0.0;
        CHECK(negative == positive);
        CHECK(copysign(1.0, negative) == -1.0);
        CHECK(copysign(1.0, positive) == +1.0);
    } else return 2;
    return 0;
}
