/*-----------------------------------------------------------------------------
 * Bits2Banking
 * File: labs/native/kernel-bounded-input/main.c
 *
 * PURPOSE:
 *   Use the real Kernel parser with an unterminated bounded byte field.
 *
 * AUTHOR AND ORGANISATION:
 * Sammy Hegab
 * Umicom Foundation
 *
 * LICENCE:
 * MIT
 *---------------------------------------------------------------------------*/

#include "umicom/kernel/console_shell.h"
#include <inttypes.h>
#include <stdint.h>
#include <stdio.h>

int main(void)
{
    /* This buffer has no NUL. A length contract makes all three owned bytes
     * available without permitting a read of an unrelated fourth byte. */
    const char received[3] = {'1', '2', '3'};
    UmicomU64 value = 0U;
    if (!UmicomKernelShellUnsignedSpan(received, sizeof received, &value)) return 1;
    printf("Accepted bounded value: %" PRIu64 "\n", (uint64_t)value);
    puts("Hosted parser demonstration: no kernel or machine was booted.");
    return ferror(stdout) || fflush(stdout) ? 1 : 0;
}
