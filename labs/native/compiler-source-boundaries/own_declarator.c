/*-----------------------------------------------------------------------------
 * Umicom Bits2Banking
 * File: labs/native/compiler-source-boundaries/own_declarator.c
 *
 * PURPOSE:
 *   Use the declared type before the new integer has a stored value.
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
    /* The operand names its type while byte_count is being initialized. */
    const int byte_count = sizeof byte_count;
    /* A normalized comparison gives the same answer at different int widths. */
    return byte_count == sizeof(int);
}
