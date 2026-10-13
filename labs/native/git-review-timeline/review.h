/*-----------------------------------------------------------------------------
 * Bits to Banking | Umicom Foundation | Sammy Hegab | MIT
 * File: labs/native/git-review-timeline/review.h
 * PURPOSE: Examine caller-supplied, versioned Git observation and verification
 *          evidence without executing Git or reproducing Framework VCS logic.
 *
 * OWNERSHIP: Caller owns all buffers. Timeline stores copies, never borrows.
 * SECURITY:  A clear report means internally consistent *reported* evidence,
 *            NOT that a repository is safe to push or that remote history is
 *            verified. Umicom Framework remains the Git observation authority.
 *---------------------------------------------------------------------------*/
#ifndef BTB_GIT_REVIEW_TIMELINE_H
#define BTB_GIT_REVIEW_TIMELINE_H

#include <stddef.h>
#include <stdint.h>

/* Git SHA-1 uses 40 hexadecimal digits; SHA-256 uses 64. Include terminator. */
#define BTB_REVIEW_SHA_CAPACITY 65U

typedef enum BtbReviewResult {
    BTB_REVIEW_OK = 0,
    BTB_REVIEW_INVALID,
    BTB_REVIEW_STALE,
    BTB_REVIEW_NOT_OBSERVED
} BtbReviewResult;

typedef enum BtbReviewProof {
    BTB_REVIEW_PROOF_NOT_RUN = 0,
    BTB_REVIEW_PROOF_PASSED,
    BTB_REVIEW_PROOF_FAILED
} BtbReviewProof;

typedef enum BtbReviewEvidenceKind {
    BTB_REVIEW_EVIDENCE_BUILD = 1,
    BTB_REVIEW_EVIDENCE_TEST = 2
} BtbReviewEvidenceKind;

typedef enum BtbReviewNextCheck {
    BTB_REVIEW_CHECK_NONE = 0,
    BTB_REVIEW_CHECK_REFRESH_OBSERVATION,
    BTB_REVIEW_CHECK_CONFLICTS,
    BTB_REVIEW_CHECK_LOCAL_COMMITS,
    BTB_REVIEW_CHECK_CHILD_STATUS,
    BTB_REVIEW_CHECK_REMOTE_ANCESTRY,
    BTB_REVIEW_CHECK_WORKTREE,
    BTB_REVIEW_CHECK_BUILD,
    BTB_REVIEW_CHECK_TEST,
    BTB_REVIEW_CHECK_STAGED_DIFF
} BtbReviewNextCheck;

/* All issue flags describe deficiencies; no flag grants permission to push. */
#define BTB_REVIEW_ISSUE_STALE            (UINT64_C(1) << 0)
#define BTB_REVIEW_ISSUE_UNBORN           (UINT64_C(1) << 1)
#define BTB_REVIEW_ISSUE_DETACHED         (UINT64_C(1) << 2)
#define BTB_REVIEW_ISSUE_BRANCH_UNKNOWN   (UINT64_C(1) << 3)
#define BTB_REVIEW_ISSUE_NOT_MAIN         (UINT64_C(1) << 4)
#define BTB_REVIEW_ISSUE_REMOTE_UNCHECKED (UINT64_C(1) << 5)
#define BTB_REVIEW_ISSUE_DIVERGENCE       (UINT64_C(1) << 6)
#define BTB_REVIEW_ISSUE_BEHIND           (UINT64_C(1) << 7)
#define BTB_REVIEW_ISSUE_CONFLICTS        (UINT64_C(1) << 8)
#define BTB_REVIEW_ISSUE_UNTRACKED        (UINT64_C(1) << 9)
#define BTB_REVIEW_ISSUE_MODIFIED         (UINT64_C(1) << 10)
#define BTB_REVIEW_ISSUE_CHILD_DIRTY      (UINT64_C(1) << 11)
#define BTB_REVIEW_ISSUE_BUILD_NOT_RUN    (UINT64_C(1) << 12)
#define BTB_REVIEW_ISSUE_BUILD_FAILED     (UINT64_C(1) << 13)
#define BTB_REVIEW_ISSUE_TEST_NOT_RUN     (UINT64_C(1) << 14)
#define BTB_REVIEW_ISSUE_TEST_FAILED      (UINT64_C(1) << 15)

/* Advisory flags are not themselves release gates. */
#define BTB_REVIEW_ADVISORY_AHEAD         (UINT64_C(1) << 0)
#define BTB_REVIEW_ADVISORY_STAGED        (UINT64_C(1) << 1)
#define BTB_REVIEW_ADVISORY_CHILD_GITLINK (UINT64_C(1) << 2)

typedef struct BtbReviewObservation {
    uint64_t observationId;
    char commit[BTB_REVIEW_SHA_CAPACITY];
    int branchKnown;
    int onMain;
    int detached;
    int unborn;
    /* Supplied by caller AFTER a remote-ref refresh; Framework status alone
     * cannot prove the freshness of the remote observation. */
    int remoteFresh;
    int divergenceKnown;
    size_t ahead;
    size_t behind;
    size_t entries;
    size_t staged;
    size_t untracked;
    size_t conflicts;
    size_t childCommits;
    size_t dirtyChildren;
} BtbReviewObservation;

typedef struct BtbReviewEvidence {
    BtbReviewEvidenceKind kind;
    BtbReviewProof proof;
    uint64_t observationId;
    char commit[BTB_REVIEW_SHA_CAPACITY];
} BtbReviewEvidence;

typedef struct BtbReviewTimeline {
    BtbReviewObservation observation;
    BtbReviewProof buildProof;
    BtbReviewProof testProof;
    int hasObservation;
    size_t observationsReceived;
} BtbReviewTimeline;

typedef struct BtbReviewReport {
    uint64_t observationId;
    uint64_t issues;
    uint64_t advisories;
    BtbReviewNextCheck nextCheck;
    BtbReviewProof buildProof;
    BtbReviewProof testProof;
} BtbReviewReport;

/* Only a properly initialised timeline may be observed or evaluated. */
BtbReviewResult BtbReviewInit(BtbReviewTimeline *timeline);

/* The new observation ID must increase. Every observation invalidates any
 * previously claimed build/test results, even when the HEAD SHA is unchanged.
 * Invalid input leaves timeline unchanged. */
BtbReviewResult BtbReviewObserve(BtbReviewTimeline *timeline,
                                  const BtbReviewObservation *observation);

/* Evidence must identify exactly the currently observed SHA and ID; rejected
 * evidence cannot mutate timeline. NOT_RUN is not a valid submitted proof. */
BtbReviewResult BtbReviewRecordEvidence(BtbReviewTimeline *timeline,
                                         const BtbReviewEvidence *evidence);

/* The caller supplies the ID and SHA it believes are current. A mismatched
 * expectation is reported as a stale issue, not silently accepted. Invalid
 * input leaves the caller's report untouched. */
BtbReviewResult BtbReviewEvaluate(const BtbReviewTimeline *timeline,
                                   uint64_t expectedObservationId,
                                   const char *expectedCommit,
                                   BtbReviewReport *outReport);

/* Read-only explanatory commands. No command is ever executed by this lab. */
const char *BtbReviewNextCheckCommand(BtbReviewNextCheck check);
const char *BtbReviewIssueName(uint64_t oneBit);

#endif
