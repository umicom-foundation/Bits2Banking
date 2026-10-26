/*-----------------------------------------------------------------------------
 * Bits2Banking
 * File: labs/native/first-c-programs/test_borrowed_counts.c
 *
 * PURPOSE:
 *   Check borrowing boundaries, caller storage and rejected lengths without invalid reads.
 *
 * AUTHOR AND ORGANISATION:
 * Sammy Hegab
 * Umicom Foundation
 *
 * LICENCE:
 * MIT
 *---------------------------------------------------------------------------*/
#include "borrowed_counts.h"

#include <limits.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>

#define CHECK(expression) do { if (!(expression)) { \
    (void)fprintf(stderr, "Line %d: %s\n", __LINE__, #expression); return 1; \
} } while (0)

int main(void)
{
    int values[] = {2, 1, 3};
    int original[3];
    memcpy(original, values, sizeof values);
    CHECK(BtbSumCounts(values, 3) == 6);
    CHECK(memcmp(values, original, sizeof values) == 0);
    CHECK(BtbSumCounts(values, 2) == 3);
    CHECK(BtbSumCounts(NULL, 0) == 0);
    CHECK(BtbSumCounts(values, 0) == 0);
    CHECK(BtbSumCounts(NULL, 1) == -1);
    /* Reject excessive lengths before touching the supplied valid single
       element. Do not construct invalid pointer values for a rejection test. */
    int one = 1000;
    CHECK(BtbSumCounts(&one, 17) == -1);
    CHECK(BtbSumCounts(&one, SIZE_MAX) == -1);
    int maximum[16];
    for (size_t i = 0; i < 16; ++i) maximum[i] = 1000;
    CHECK(BtbSumCounts(maximum, 16) == 16000);
    maximum[15] = -1;
    CHECK(BtbSumCounts(maximum, 16) == -1);
    CHECK(maximum[15] == -1);
    maximum[15] = 1001;
    CHECK(BtbSumCounts(maximum, 16) == -1);
    maximum[0] = INT_MIN;
    CHECK(BtbSumCounts(maximum, 16) == -1);
    maximum[0] = INT_MAX;
    CHECK(BtbSumCounts(maximum, 16) == -1);
    CHECK(BtbSumCounts(values, 3) == 6);
    CHECK(memcmp(values, original, sizeof values) == 0);
    return 0;
}
