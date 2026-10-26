/*-----------------------------------------------------------------------------
 * Bits2Banking
 * File: labs/native/first-c-programs/borrowing.c
 *
 * PURPOSE:
 *   Call a bounded function while keeping ownership of an array.
 *
 * AUTHOR AND ORGANISATION:
 * Sammy Hegab
 * Umicom Foundation
 *
 * LICENCE:
 * MIT
 *---------------------------------------------------------------------------*/
#include "borrowed_counts.h"

#include <stdio.h>

int main(void)
{
    const int activities[] = {2, 1, 3};
    const size_t count = sizeof activities / sizeof activities[0];
    const int total = BtbSumCounts(activities, count);
    if (total < 0) {
        (void)fputs("The activity counts were rejected.\n", stderr);
        return 1;
    }
    if (printf("Borrowed total: %d\n", total) < 0 || fflush(stdout) == EOF) {
        return 1;
    }
    return 0;
}
