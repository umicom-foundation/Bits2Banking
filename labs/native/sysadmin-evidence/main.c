/*-----------------------------------------------------------------------------
 * Bits2Banking | Umicom Foundation | Sammy Hegab | MIT
 * File: labs/native/sysadmin-evidence/main.c
 * PURPOSE: Demonstrate offline evidence review without touching real services.
 *---------------------------------------------------------------------------*/
#include "admin_evidence.h"
#include <stdio.h>

int main(void)
{
    BtbAdminReview review;
    BtbAdminReport report;
    const BtbAdminObservation observations[] = {
        {1U, 20261014U, BTB_ADMIN_PASS, "Learning workspace readable"},
        {2U, 20261014U, BTB_ADMIN_PASS, "Training backup copy verified"},
        {3U, 20261014U, BTB_ADMIN_WARNING, "Optional practice network unavailable"}
    };
    if (BtbAdminReviewInit(&review, 20261014U) != BTB_ADMIN_OK) return 1;
    for (size_t i = 0U; i < sizeof(observations)/sizeof(observations[0]); ++i) {
        if (BtbAdminReviewAdd(&review, &observations[i]) != BTB_ADMIN_OK) return 2;
    }
    /* Checks 1 and 2 are required; check 3 is an optional observation. */
    if (BtbAdminReviewEvaluate(&review, UINT32_C(0x3), &report) != BTB_ADMIN_OK)
        return 3;
    printf("Decision: %s\nPassed: %zu, warnings: %zu, missing required: %zu\n",
           BtbAdminDecisionText(report.decision), report.passed,
           report.warnings, report.missingRequired);
    return report.decision == BTB_ADMIN_REVIEW ? 0 : 4;
}
