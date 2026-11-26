/*
 * Umicom Bits2Banking
 * File: brew-time-return-caller.c
 *
 * PURPOSE:
 * Call a native constant-return object through a normal C declaration.
 *
 * AUTHOR AND ORGANISATION:
 * Sammy Hegab
 * Umicom Foundation
 *
 * LICENCE:
 * MIT
 */

#include <stdio.h>

/* The object exports this symbol with the Windows x64 C calling convention. */
extern int umc_constant_return(void);

int main(void)
{
    const int seconds = umc_constant_return();
    if (seconds != 255) {
        fprintf(stderr, "Expected 255 seconds, got %d.\n", seconds);
        return 1;
    }
    printf("Native return: %d seconds.\n", seconds);
    return 0;
}
