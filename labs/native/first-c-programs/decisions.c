/*-----------------------------------------------------------------------------
 * Bits2Banking
 * File: labs/native/first-c-programs/decisions.c
 *
 * PURPOSE:
 *   Choose a result only after checking a count's allowed range.
 *
 * AUTHOR AND ORGANISATION:
 * Sammy Hegab
 * Umicom Foundation
 *
 * LICENCE:
 * MIT
 *---------------------------------------------------------------------------*/
#include <stdio.h>

int main(void)
{
    const int total = 5;
    const int completed = 7;
    int written;

    /* Reject the state before subtracting: a completed count cannot exceed the
       total. This example reports rejection as an expected teaching outcome. */
    if (total < 0 || total > 1000 || completed < 0 || completed > total) {
        written = puts("Counts do not fit the rule.");
    } else {
        written = printf("Remaining: %d\n", total - completed);
    }
    if (written < 0 || fflush(stdout) == EOF) {
        return 1;
    }
    return 0;
}
