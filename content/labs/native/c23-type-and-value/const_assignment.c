/*-----------------------------------------------------------------------------
 * Umicom Bits2Banking
 * File: content/labs/native/c23-type-and-value/const_assignment.c
 *
 * PURPOSE:
 *   Demonstrate the required refusal to modify a const-qualified type query result.
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
    const unsigned char channel = 6;
    typeof(channel) original = channel;

    /* This deliberate constraint violation is for a syntax-only test. */
    original = 42;
    return original;
}
