/*-----------------------------------------------------------------------------
 * Bits to Banking | Umicom Foundation | Sammy Hegab | MIT
 * File: labs/native/git-review-timeline/framework_bridge.h
 * PURPOSE: Optional compile-time adapter for the existing Framework VCS API.
 * This is a teaching adapter, NOT another Git provider or parser.
 *---------------------------------------------------------------------------*/
#ifndef BTB_GIT_REVIEW_FRAMEWORK_BRIDGE_H
#define BTB_GIT_REVIEW_FRAMEWORK_BRIDGE_H
#include "review.h"

typedef struct UmiVcsWorkingTreeSummary UmiVcsWorkingTreeSummary;

/* Framework produces summary using UmiVcsWorkingTreeDescribe(); this adapter
 * copies only relevant evidence. remoteFresh is independently asserted by
 * the caller; the summary alone cannot prove a prior 'git fetch'. On failure
 * the output is left unchanged. */
BtbReviewResult BtbReviewFromFramework(const UmiVcsWorkingTreeSummary *summary,
                                       uint64_t observationId, int remoteFresh,
                                       BtbReviewObservation *outObservation);
#endif
