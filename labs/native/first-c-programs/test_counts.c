/*-----------------------------------------------------------------------------
 * Bits2Banking
 * File: labs/native/first-c-programs/test_counts.c
 *
 * PURPOSE:
 *   Check boundaries and rejected inputs independently of demonstration output.
 *
 * AUTHOR AND ORGANISATION:
 * Sammy Hegab
 * Umicom Foundation
 *
 * LICENCE:
 * MIT
 *---------------------------------------------------------------------------*/
#include "counts.h"

#include <limits.h>
#include <stdio.h>

/* Each row is an expectation derived from the published contract. Extreme
   values exercise rejection before arithmetic rather than copying its logic. */
int main(void)
{
    const int cases[][3] = {
        {5, 2, 3}, {0, 0, 0}, {1000, 0, 1000}, {1000, 1000, 0},
        {5, 5, 0}, {5, 6, -1}, {-1, 0, -1}, {1001, 0, -1},
        {5, -1, -1}, {INT_MIN, INT_MAX, -1}, {INT_MAX, INT_MIN, -1},
        {1000, INT_MIN, -1}, {0, INT_MAX, -1}
    };
    for (unsigned int i = 0; i < sizeof cases / sizeof cases[0]; ++i) {
        const int actual = BtbRemainingCount(cases[i][0], cases[i][1]);
        if (actual != cases[i][2]) {
            (void)fprintf(stderr, "Case %u: expected %d, received %d\n",
                          i, cases[i][2], actual);
            return 1;
        }
    }
    return 0;
}
