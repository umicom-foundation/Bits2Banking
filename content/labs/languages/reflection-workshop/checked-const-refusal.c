/*-----------------------------------------------------------------------------
 * Umicom Bits2Banking
 * File: content/labs/languages/reflection-workshop/checked-const-refusal.c
 *
 * PURPOSE:
 *   Provide a checked C fixture that shows a refused write to a const local.
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
    /* This intentional diagnostic fixture checks that typeof keeps the
     * source qualifier. The increment below should be refused. */
    const unsigned char seed = {27};
    typeof(seed) stored = {8};
    ++stored;
    return stored;
}
