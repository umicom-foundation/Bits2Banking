/*-----------------------------------------------------------------------------
 * Umicom Bits2Banking
 * File: labs/native/compiler-source-boundaries/assertion_message.c
 *
 * PURPOSE:
 *   Keep a static assertion readable across adjacent quoted fragments.
 *
 * AUTHOR AND ORGANISATION:
 * Sammy Hegab
 * Umicom Foundation
 *
 * LICENCE:
 * MIT
 *---------------------------------------------------------------------------*/

int main(void)
{
    /* The compiler checks the fixed condition before preparing execution. */
    static_assert(6 * 7 == 42, "The record " /* Keep the phrase readable. */
                              "contains 42 fields");
    return 42;
}
