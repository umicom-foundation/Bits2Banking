/*-----------------------------------------------------------------------------
 * Umicom Bits2Banking
 * File: content/courses/learning-aarch64-assembly/examples/caller.c
 *
 * PURPOSE:
 *   Make an independent ARM64 caller for offline linking on both object formats.
 *
 * AUTHOR AND ORGANISATION:
 * Sammy Hegab
 * Umicom Foundation
 *
 * LICENCE:
 * MIT
 *---------------------------------------------------------------------------*/

extern int umc_constant_return(void);

int btb_arm_entry(void)
{
    /* The observed object must provide this function for the link to succeed. */
    return umc_constant_return();
}
