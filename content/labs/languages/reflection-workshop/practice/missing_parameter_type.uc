/*-----------------------------------------------------------------------------
 * Umicom Bits2Banking
 * File: content/labs/languages/reflection-workshop/practice/missing_parameter_type.uc
 *
 * PURPOSE:
 *   Verify that a checked input artifact is refused when the queried name is absent.
 *
 * AUTHOR AND ORGANISATION:
 * Sammy Hegab
 * Umicom Foundation
 *
 * LICENCE:
 * MIT
 *---------------------------------------------------------------------------*/

int umicom_run(int input)
{
    /* Deliberate refusal: the requested name is absent from the local scope.
     * There is no type to copy even though an input value would be available. */
    typeof(missing) sample = {input};
    return sample;
}
