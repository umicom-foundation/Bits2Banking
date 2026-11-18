/*-----------------------------------------------------------------------------
 * Umicom Bits2Banking
 * File: labs/languages/native-language-boundary/test_boundary.c
 *
 * PURPOSE:
 *   Teach and verify a fixed-width C ABI without transferring allocation ownership.
 *
 * AUTHOR AND ORGANISATION:
 * Sammy Hegab
 * Umicom Foundation
 *
 * LICENCE:
 * MIT
 *---------------------------------------------------------------------------*/

#include "boundary.h"
#include <limits.h>
#include <stddef.h>
#include <stdio.h>
#define CHECK(c) do { if (!(c)) { fprintf(stderr, "line %d: %s\n", __LINE__, #c); return 1; } } while (0)
int main(void)
{
    int32_t result = -7;
    CHECK(bounded_progress(2, 8, &result) == 0 && result == 25);
    CHECK(bounded_progress(1, 3, &result) == 0 && result == 33);
    CHECK(bounded_progress(INT32_MAX, INT32_MAX, &result) == 0 && result == 100);
    CHECK(bounded_progress(0, 8, &result) == 0 && result == 0);
    result = 19;
    CHECK(bounded_progress(1, 0, &result) == 1 && result == 19);
    CHECK(bounded_progress(-1, 8, &result) == 1 && result == 19);
    CHECK(bounded_progress(9, 8, &result) == 1 && result == 19);
    CHECK(bounded_progress(1, -8, &result) == 1 && result == 19);
    CHECK(bounded_progress(1, 8, NULL) == 1);
    puts("C boundary checks passed");
    return 0;
}
