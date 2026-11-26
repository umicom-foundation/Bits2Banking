/*-----------------------------------------------------------------------------
 * Umicom Bits2Banking
 * File: content/courses/learning-aarch64-assembly/examples/provider.c
 *
 * PURPOSE:
 *   Provide the external function directly for the independent Clang and ELF link.
 *
 * AUTHOR AND ORGANISATION:
 * Sammy Hegab
 * Umicom Foundation
 *
 * LICENCE:
 * MIT
 *---------------------------------------------------------------------------*/

int umc_constant_return(void)
{
    /* Match the emitter's result while letting a separate compiler own it. */
    return -70000;
}
