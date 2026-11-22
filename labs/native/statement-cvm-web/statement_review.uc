/*-----------------------------------------------------------------------------
 * Umicom Bits2Banking
 * File: labs/native/statement-cvm-web/statement_review.uc
 *
 * PURPOSE:
 *   Apply one signed training adjustment to the reserve account's posted movement.
 *
 * AUTHOR AND ORGANISATION:
 * Sammy Hegab
 * Umicom Foundation
 *
 * LICENCE:
 * MIT
 *---------------------------------------------------------------------------*/
int umicom_run(int adjustment)
{
    /* The shared training ledger has two posted reserve entries. Its pending
     * entry joins the result only if the learner supplies it as the input. */
    int posted = 2600 - 850;
    return posted + adjustment;
}
