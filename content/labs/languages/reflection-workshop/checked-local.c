/*-----------------------------------------------------------------------------
 * Umicom Bits2Banking
 * File: content/labs/languages/reflection-workshop/checked-local.c
 *
 * PURPOSE:
 *   Show local type queries in the Umicom C checked C interpreter profile.
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
    /* Choose an unsigned byte as the source declaration. The two initializers
     * intentionally use different values to separate a type query from a read. */
    const unsigned char seed = {27};
    typeof(seed) stored = {8};
    typeof_unqual(seed) editable = {5};

    /* Only the unqualified local changes. The returned digits let the tool's
     * Result line show both the changed local and the original typed copy. */
    ++editable;
    return editable * 10 + stored;
}
