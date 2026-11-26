/*-----------------------------------------------------------------------------
 * Umicom Bits2Banking
 * File: content/labs/native/c23-type-and-value/named_type.c
 *
 * PURPOSE:
 *   Compare checked C23 qualified and unqualified local type queries.
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
    /* The original describes a read-only channel. Both new variables are
     * separate objects whose values are set by their own initializers. */
    const unsigned char channel = {6};
    typeof(channel) original = {channel};
    typeof_unqual(channel) next = {};

    /* The unqualified type makes next mutable while retaining its byte type. */
    next = original * 7;
    return original != 6 || next != 42;
}
