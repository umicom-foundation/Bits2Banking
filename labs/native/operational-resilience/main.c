/*-----------------------------------------------------------------------------
 * Bits2Banking | Umicom Foundation | Sammy Hegab | MIT
 * File: labs/native/operational-resilience/main.c
 * PURPOSE: Explain fictional operational readiness without touching a host.
 *---------------------------------------------------------------------------*/
#include "operations_fixture.h"
#include <stdio.h>

int main(void)
{
    BtbOpsReview review;
    BtbOpsDecision decision;
    uint64_t nextDue = 0U;
    if (!BtbOpsTrainingReview(&review, 0, 1) ||
        BtbOpsEvaluate(&review, &decision) != BTB_OPS_OK ||
        decision.status != BTB_OPS_REVIEWABLE) return 1;
    printf("Fictional Notes baseline: %s, missing=0x%08x\n",
           BtbOpsStatusText(decision.status), (unsigned)decision.missingEvidence);
    review.evidence.onCallOwnerAssigned = 0;
    if (BtbOpsEvaluate(&review, &decision) != BTB_OPS_OK ||
        decision.status != BTB_OPS_BLOCKED ||
        (decision.missingEvidence & BTB_OPS_ON_CALL_UNASSIGNED) == 0U)
        return 1;
    printf("Unassigned response owner: %s, missing=0x%08x\n",
           BtbOpsStatusText(decision.status), (unsigned)decision.missingEvidence);
    if (BtbOpsNextDue(1200U, 300U, &nextDue) != BTB_OPS_OK ||
        nextDue != 1500U) return 1;
    printf("Next scheduled check (logical seconds): %llu\n",
           (unsigned long long)nextDue);
    if (!BtbOpsTrainingReview(&review, 2, 1) ||
        BtbOpsEvaluate(&review, &decision) != BTB_OPS_OK ||
        decision.status != BTB_OPS_RESTORED_ONLY) return 1;
    printf("Old generation independently restored: %s (not a successful upgrade)\n",
           BtbOpsStatusText(decision.status));
    return 0;
}
