/*-----------------------------------------------------------------------------
 * Bits2Banking
 * File: labs/native/first-c-programs/repetition.c
 *
 * PURPOSE:
 *   Trace a bounded loop one iteration at a time.
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
    /* The counter starts at one, is checked before each body, and advances
       after it. A small bound lets learners trace every state on paper. */
    for (int step = 1; step <= 3; step = step + 1) {
        if (printf("Step %d\n", step) < 0) {
            return 1;
        }
    }
    if (fflush(stdout) == EOF) {
        return 1;
    }
    return 0;
}
