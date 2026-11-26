/*-----------------------------------------------------------------------------
 * Umicom Bits2Banking
 * File: content/labs/native/c23-type-and-value/empty_scalar.c
 *
 * PURPOSE:
 *   Check C23 default and explicit initialization in the shared scalar subset.
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
    /* The empty initializer supplies zero or false before any calculation. */
    int processed = {};
    bool retry = {};
    unsigned char channel = {42,};
    if (processed != 0 || retry) return 1;

    /* A later assignment changes only processed. The trailing comma in the
     * channel declaration separates no additional value. */
    processed = channel;
    return retry || processed != 42;
}
