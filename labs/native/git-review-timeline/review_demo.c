/*-----------------------------------------------------------------------------
 * Bits to Banking | Umicom Foundation | Sammy Hegab | MIT
 * File: labs/native/git-review-timeline/review_demo.c
 * PURPOSE: Inspect a fictional OS submodule incident; never touches Git.
 *---------------------------------------------------------------------------*/
#include "review.h"
#include <stdio.h>

int main(void)
{
    BtbReviewTimeline timeline = {0};
    BtbReviewObservation observation = {
        .observationId = 41U,
        .commit = "0d40b2d9222d0a0a0eaf912b8594e0e29fbb2796",
        .branchKnown = 0,
        .onMain = 0,
        .detached = 1,
        .unborn = 0,
        .remoteFresh = 0,
        .divergenceKnown = 0,
        .entries = 2U,
        .untracked = 1U,
        .childCommits = 0U,
        .dirtyChildren = 0U
    };
    BtbReviewReport report = {0};
    if (BtbReviewInit(&timeline) != BTB_REVIEW_OK ||
        BtbReviewObserve(&timeline, &observation) != BTB_REVIEW_OK ||
        BtbReviewEvaluate(&timeline, observation.observationId,
                          observation.commit, &report) != BTB_REVIEW_OK)
        return 1;
    printf("Fictional Umicom OS Framework incident\n");
    printf("Observation ID: %llu\n", (unsigned long long)report.observationId);
    printf("Blocking/inspection flags: 0x%llx\n", (unsigned long long)report.issues);
    printf("First read-only check: %s\n", BtbReviewNextCheckCommand(report.nextCheck));
    puts("This model neither checks nor modifies a live Git repository.");
    return (report.issues & BTB_REVIEW_ISSUE_DETACHED) != 0U ? 0 : 1;
}
