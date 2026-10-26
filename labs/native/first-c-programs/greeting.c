/*-----------------------------------------------------------------------------
 * Bits2Banking
 * File: labs/native/first-c-programs/greeting.c
 *
 * PURPOSE:
 *   Introduce a hosted C entry point and checked text output.
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
    /* A successful call queues the greeting; flushing also checks delivery to
       the C stream. The environment decides where standard output goes. */
    if (puts("Hello, learner.") == EOF || fflush(stdout) == EOF) {
        return 1;
    }
    return 0;
}
