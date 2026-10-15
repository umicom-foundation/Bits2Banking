/*-----------------------------------------------------------------------------
 * Bits2Banking | Umicom Foundation | Sammy Hegab | MIT
 * File: labs/native/security-operations-review/main.c
 * PURPOSE: Print explainable fictional security review decisions.
 *---------------------------------------------------------------------------*/
#include "training_fixture.h"
#include <stdio.h>

int main(void)
{
    BtbSecurityReview review;
    BtbSecurityDecision decision;
    if (!BtbSecurityTrainingComplete(&review, 0) ||
        BtbSecurityEvaluate(&review, &decision) != BTB_SECURITY_OK ||
        decision.status != BTB_SECURITY_REVIEWABLE) return 1;
    printf("Practice Notes: %s; unresolved=0x%08x\n",
           BtbSecurityStatusText(decision.status),
           (unsigned)decision.missingEvidence);
    /* A missing restore test blocks, but neither the host nor its snapshots
     * are mutated by the review. */
    review.evidence.independentRestoreTestRecorded = 0;
    if (BtbSecurityEvaluate(&review, &decision) != BTB_SECURITY_OK ||
        decision.status != BTB_SECURITY_BLOCKED ||
        (decision.missingEvidence & BTB_SECURITY_MISSING_RESTORE_TEST) == 0U)
        return 1;
    printf("Restore evidence withheld: %s; unresolved=0x%08x\n",
           BtbSecurityStatusText(decision.status),
           (unsigned)decision.missingEvidence);
    return 0;
}
