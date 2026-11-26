/*-----------------------------------------------------------------------------
 * Umicom Bits2Banking
 * File: content/labs/native/c23-type-and-value/empty_record.c
 *
 * PURPOSE:
 *   Check the values of every member of a default-initialized report record.
 *
 * AUTHOR AND ORGANISATION:
 * Sammy Hegab
 * Umicom Foundation
 *
 * LICENCE:
 * MIT
 *---------------------------------------------------------------------------*/

struct ReportSummary {
    int total;
    bool verified;
    int amounts[3];
};

int main(void)
{
    /* An empty initializer reaches every member, including each array item. */
    struct ReportSummary pending = {};
    struct ReportSummary reviewed = { .amounts = {42}, .verified = true };

    /* A partial initializer gives default values to the other members.
     * Compare the declared values without depending on padding bytes. */
    return pending.total != 0 || pending.verified ||
        pending.amounts[0] != 0 || pending.amounts[1] != 0 || pending.amounts[2] != 0 ||
        reviewed.total != 0 || !reviewed.verified ||
        reviewed.amounts[0] != 42 || reviewed.amounts[1] != 0 || reviewed.amounts[2] != 0;
}
