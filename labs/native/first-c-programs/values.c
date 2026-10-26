/*-----------------------------------------------------------------------------
 * Bits2Banking
 * File: labs/native/first-c-programs/values.c
 *
 * PURPOSE:
 *   Calculate a small count using named integer values.
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
    const int completed = 2;
    const int remaining = total - completed;

    /* These fixed, small inputs make subtraction representable. Later lessons
       move input validation into a reusable function before doing arithmetic. */
    if (printf("Remaining: %d\n", remaining) < 0 || fflush(stdout) == EOF) {
        return 1;
    }
    return 0;
}
