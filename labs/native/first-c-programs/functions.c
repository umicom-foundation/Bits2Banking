/*-----------------------------------------------------------------------------
 * Bits2Banking
 * File: labs/native/first-c-programs/functions.c
 *
 * PURPOSE:
 *   Call a separately implemented count function and handle rejection.
 *
 * AUTHOR AND ORGANISATION:
 * Sammy Hegab
 * Umicom Foundation
 *
 * LICENCE:
 * MIT
 *---------------------------------------------------------------------------*/
#include "counts.h"

#include <stdio.h>

int main(void)
{
    const int remaining = BtbRemainingCount(5, 2);

    /* Negative one is reserved for rejection by this deliberately small API.
       It cannot be confused with a valid result, which is never negative. */
    if (remaining < 0) {
        (void)fputs("Counts do not fit the rule.\n", stderr);
        return 1;
    }
    if (printf("Remaining: %d\n", remaining) < 0 || fflush(stdout) == EOF) {
        return 1;
    }
    return 0;
}
