/*-----------------------------------------------------------------------------
 * Umicom Bits2Banking
 * File: content/labs/languages/reflection-workshop/practice/parameter_type.uc
 *
 * PURPOSE:
 *   Resolve declared parameter metadata in a checked Umicom C artifact that requires input.
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
    /* The compiler can already see the type of the parameter. The initializer
     * separately reads the particular value sent by the host. */
    typeof(input) sample = {input};
    return sample * 2 + 1;
}
