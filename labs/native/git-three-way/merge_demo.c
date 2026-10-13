/*-----------------------------------------------------------------------------
 * Bits2Banking | Umicom Foundation | Sammy Hegab | MIT
 * File: labs/native/git-three-way/merge_demo.c
 * PURPOSE: Demonstrate safe review of a fictional Umicom code merge.
 *---------------------------------------------------------------------------*/
#include "merge.h"
#include <stdio.h>

static const char *KindName(BtbMergeKind kind)
{
    switch (kind) {
        case BTB_MERGE_UNCHANGED: return "unchanged";
        case BTB_MERGE_IDENTICAL_CHANGE: return "identical change";
        case BTB_MERGE_OURS_ONLY: return "ours only";
        case BTB_MERGE_THEIRS_ONLY: return "theirs only";
        case BTB_MERGE_NEEDS_REVIEW: return "CONFLICT: manual review required";
        default: return "invalid";
    }
}

int main(void)
{
    BtbMergeSnapshot base = {0}, ours = {0}, theirs = {0}, finished = {0};
    BtbMergePlan plan = {0};
    if (BtbMergeSnapshotAdd(&base, "bank/ledger.c", "accounting-valid-v1") ||
        BtbMergeSnapshotAdd(&ours, "bank/ledger.c", "fixed-point-c23-v2") ||
        BtbMergeSnapshotAdd(&theirs, "bank/ledger.c", "audit-control-v3") ||
        BtbMergeSnapshotAdd(&ours, "studio/panel.c", "new-preview") ||
        BtbMergeSnapshotAdd(&theirs, "tms/risk.c", "new-risk-check") ||
        BtbMergePlanBuild(&base, &ours, &theirs, &plan) != BTB_MERGE_OK) {
        (void)fprintf(stderr, "Unable to construct review plan\n");
        return 1;
    }
    (void)printf("Records: %zu; conflicts: %zu\n", plan.count, plan.conflictCount);
    for (size_t i = 0U; i < plan.count; ++i) {
        const BtbMergeDecision *entry = BtbMergeDecisionAt(&plan, i);
        if (entry == NULL) return 1;
        (void)printf("%-20s %s\n", entry->key, KindName(entry->kind));
    }
    if (BtbMergeMaterialise(&plan, &finished) != BTB_MERGE_CONFLICT_PENDING) {
        (void)fprintf(stderr, "Expected explicit conflict review before export\n");
        return 1;
    }
    /* This choice is deliberately shown as human review in a MODEL only.
     * An actual source merge must retain both implementations until approved. */
    if (BtbMergeResolve(&plan, "bank/ledger.c", BTB_CHOOSE_BASE) != BTB_MERGE_OK ||
        BtbMergeMaterialise(&plan, &finished) != BTB_MERGE_OK) return 1;
    (void)printf("Review completed; %zu owned records materialised.\n", finished.count);
    return 0;
}
