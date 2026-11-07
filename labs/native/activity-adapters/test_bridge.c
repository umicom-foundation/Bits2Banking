/*-----------------------------------------------------------------------------
 * Umicom Bits2Banking
 * File: labs/native/activity-adapters/test_bridge.c
 *
 * PURPOSE:
 *   Check platform input conversion and shared activity boundary results.
 *
 * AUTHOR AND ORGANISATION:
 * Sammy Hegab
 * Umicom Foundation
 *
 * LICENCE:
 * MIT
 *---------------------------------------------------------------------------*/

#include "bridge.h"
#include <limits.h>
#include <stdio.h>
int main(void)
{
    const int input[] = {-1, INT_MIN, 0, 1, 999, 1000, 1001, INT_MAX};
    const int expected[] = {-1, -1, 1, 2, 1000, -1, -1, -1};
    for (unsigned i = 0U; i < sizeof input / sizeof input[0]; ++i) {
        int actual = BtbActivityNext(input[i]);
        if (actual != expected[i]) {
            fprintf(stderr, "input %d: expected %d, got %d\n",
                    input[i], expected[i], actual);
            return 1;
        }
    }
    return 0;
}

