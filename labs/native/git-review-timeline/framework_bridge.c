/*-----------------------------------------------------------------------------
 * Bits to Banking | Umicom Foundation | Sammy Hegab | MIT
 * File: labs/native/git-review-timeline/framework_bridge.c
 * PURPOSE: Translate an Umicom Framework VCS observation into teaching facts.
 * Requires a local Framework checkout and is OFF in the standalone lab build.
 *---------------------------------------------------------------------------*/
#include "framework_bridge.h"
#include "umicom/vcs/working_tree.h"
#include <string.h>

static int IsBoolean(int value) { return value == 0 || value == 1; }

BtbReviewResult BtbReviewFromFramework(const UmiVcsWorkingTreeSummary *summary,
                                       uint64_t observationId, int remoteFresh,
                                       BtbReviewObservation *outObservation)
{
    if (summary == NULL || outObservation == NULL || observationId == 0U ||
        !IsBoolean(remoteFresh) || !IsBoolean(summary->branch_known) ||
        !IsBoolean(summary->commit_known) || !IsBoolean(summary->unborn) ||
        !IsBoolean(summary->detached) || !IsBoolean(summary->divergence_known))
        return BTB_REVIEW_INVALID;
    BtbReviewObservation observation = {0};
    observation.observationId = observationId;
    observation.branchKnown = summary->branch_known;
    observation.onMain = summary->branch_known && !summary->detached &&
        strncmp(summary->branch, "main", sizeof(summary->branch)) == 0;
    observation.detached = summary->detached;
    observation.unborn = summary->unborn;
    observation.remoteFresh = remoteFresh;
    observation.divergenceKnown = summary->divergence_known;
    observation.ahead = summary->ahead;
    observation.behind = summary->behind;
    observation.entries = summary->entries;
    observation.staged = summary->staged;
    observation.untracked = summary->untracked;
    observation.conflicts = summary->conflicts;
    observation.childCommits = summary->child_commits;
    observation.dirtyChildren = summary->dirty_children;
    if (summary->commit_known != 0 && summary->unborn == 0) {
        size_t count = 0U;
        while (count < sizeof(summary->commit_id) &&
               summary->commit_id[count] != '\0') ++count;
        if (count >= sizeof(summary->commit_id) ||
            count >= sizeof(observation.commit)) return BTB_REVIEW_INVALID;
        memcpy(observation.commit, summary->commit_id, count + 1U);
    } else if (summary->unborn == 0) {
        return BTB_REVIEW_INVALID;
    }
    /* BtbReviewObserve performs the full bounds, SHA and consistency check;
     * this function cannot assert freshness merely from a Framework summary.
     * Preserve caller-owned output if any field is nonsensical. */
    BtbReviewTimeline probe = {0};
    if (BtbReviewInit(&probe) != BTB_REVIEW_OK ||
        BtbReviewObserve(&probe, &observation) != BTB_REVIEW_OK)
        return BTB_REVIEW_INVALID;
    *outObservation = observation;
    return BTB_REVIEW_OK;
}
