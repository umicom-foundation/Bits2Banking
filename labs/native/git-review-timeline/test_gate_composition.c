/*-----------------------------------------------------------------------------
 * Bits to Banking | Umicom Foundation | Sammy Hegab | MIT
 * File: labs/native/git-review-timeline/test_gate_composition.c
 * PURPOSE: Compose Update 33 observation with EXISTING Update 32 release gate.
 * No Git implementation, release policy or source file is copied or replaced.
 *---------------------------------------------------------------------------*/
#include "review.h"
#include "../git-release-evidence/gate.h"
#include <stdio.h>

#define REQUIRE(condition) do { if (!(condition)) { \
    fprintf(stderr, "failed line %d: %s\n", __LINE__, #condition); return 1; \
} } while (0)

int main(void)
{
    BtbReviewTimeline timeline = {0};
    BtbReviewObservation observation = {
        .observationId = 22U,
        .commit = "0d40b2d9222d0a0a0eaf912b8594e0e29fbb2796",
        .branchKnown = 1, .onMain = 1, .remoteFresh = 1,
        .divergenceKnown = 1, .ahead = 1U
    };
    BtbReviewReport readReport = {0};
    BtbGateSnapshot gateSnapshot = {
        .action = BTB_GATE_ACTION_PUSH,
        .observationId = 22U,
        .expectedObservationId = 22U,
        .onMain = 1,
        .remoteChecked = 1,
        .divergenceKnown = 1,
        .ahead = 1U,
        .buildProof = BTB_GATE_PROOF_PASSED,
        .testsProof = BTB_GATE_PROOF_PASSED,
        /* Tests alone cannot substitute for documentation quality. */
        .docsProof = BTB_GATE_PROOF_NOT_RUN
    };
    BtbGateReport gateReport = {0};
    BtbReviewEvidence build = {
        .kind = BTB_REVIEW_EVIDENCE_BUILD,
        .proof = BTB_REVIEW_PROOF_PASSED,
        .observationId = 22U,
        .commit = "0d40b2d9222d0a0a0eaf912b8594e0e29fbb2796"
    };
    BtbReviewEvidence test = build;
    test.kind = BTB_REVIEW_EVIDENCE_TEST;
    REQUIRE(BtbReviewInit(&timeline) == BTB_REVIEW_OK);
    REQUIRE(BtbReviewObserve(&timeline, &observation) == BTB_REVIEW_OK);
    REQUIRE(BtbReviewRecordEvidence(&timeline, &build) == BTB_REVIEW_OK);
    REQUIRE(BtbReviewRecordEvidence(&timeline, &test) == BTB_REVIEW_OK);
    REQUIRE(BtbReviewEvaluate(&timeline, 22U, observation.commit, &readReport)
            == BTB_REVIEW_OK);
    REQUIRE(readReport.issues == 0U);
    REQUIRE(BtbGateEvaluate(&gateSnapshot, &gateReport) == BTB_GATE_BLOCKED);
    REQUIRE((gateReport.issues & BTB_GATE_DOCS_NOT_RUN) != 0U);
    gateSnapshot.docsProof = BTB_GATE_PROOF_PASSED;
    REQUIRE(BtbGateEvaluate(&gateSnapshot, &gateReport) == BTB_GATE_READY);
    /* Even READY is teaching evidence, not a remotely verified Git push. */
    return 0;
}
