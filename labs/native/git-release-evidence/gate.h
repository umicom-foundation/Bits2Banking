/*-----------------------------------------------------------------------------
 * Bits2Banking | Umicom Foundation | Sammy Hegab | MIT
 * File: labs/native/git-release-evidence/gate.h
 * PURPOSE: Teaching-only C23 release evidence policy. This is NOT a Git client.
 *
 * Architecture: Real working-tree observation, commit ancestry, Git transport
 * and submodule control belong to Umicom Framework. This independent lab only
 * evaluates a caller-supplied, bounded and immutable evidence snapshot.
 *---------------------------------------------------------------------------*/
#ifndef BTB_RELEASE_GATE_H
#define BTB_RELEASE_GATE_H

#include <stddef.h>
#include <stdint.h>

#define BTB_GATE_SHA_CAPACITY 41U

typedef enum BtbGateAction {
    BTB_GATE_ACTION_COMMIT = 1,
    BTB_GATE_ACTION_PUSH = 2,
    BTB_GATE_ACTION_PIN = 3
} BtbGateAction;

typedef enum BtbGateProof {
    BTB_GATE_PROOF_NOT_RUN = 0,
    BTB_GATE_PROOF_PASSED = 1,
    BTB_GATE_PROOF_FAILED = 2
} BtbGateProof;

typedef enum BtbGateStatus {
    BTB_GATE_INVALID = 0,
    BTB_GATE_READY = 1,
    BTB_GATE_BLOCKED = 2
} BtbGateStatus;

/* Each issue occupies one bit. Multiple simultaneous failures are retained. */
typedef enum BtbGateIssue {
    BTB_GATE_STALE_SNAPSHOT       = UINT64_C(1) << 0,
    BTB_GATE_DETACHED_HEAD        = UINT64_C(1) << 1,
    BTB_GATE_NOT_MAIN             = UINT64_C(1) << 2,
    BTB_GATE_REMOTE_UNCHECKED     = UINT64_C(1) << 3,
    BTB_GATE_DIVERGENCE_UNKNOWN   = UINT64_C(1) << 4,
    BTB_GATE_BEHIND_REMOTE        = UINT64_C(1) << 5,
    BTB_GATE_CONFLICTS            = UINT64_C(1) << 6,
    BTB_GATE_UNSTAGED_CHANGES     = UINT64_C(1) << 7,
    BTB_GATE_UNTRACKED_FILES      = UINT64_C(1) << 8,
    BTB_GATE_NOTHING_STAGED       = UINT64_C(1) << 9,
    BTB_GATE_STAGING_NOT_REVIEWED = UINT64_C(1) << 10,
    BTB_GATE_INDEX_NOT_EMPTY      = UINT64_C(1) << 11,
    BTB_GATE_NO_OUTGOING_COMMIT   = UINT64_C(1) << 12,
    BTB_GATE_BUILD_NOT_RUN        = UINT64_C(1) << 13,
    BTB_GATE_BUILD_FAILED         = UINT64_C(1) << 14,
    BTB_GATE_TESTS_NOT_RUN        = UINT64_C(1) << 15,
    BTB_GATE_TESTS_FAILED         = UINT64_C(1) << 16,
    BTB_GATE_DOCS_NOT_RUN         = UINT64_C(1) << 17,
    BTB_GATE_DOCS_FAILED          = UINT64_C(1) << 18,
    BTB_GATE_GITLINK_NOT_SOLE     = UINT64_C(1) << 19,
    BTB_GATE_CHILD_DIRTY          = UINT64_C(1) << 20,
    BTB_GATE_CHILD_NOT_PUBLISHED  = UINT64_C(1) << 21,
    BTB_GATE_CHILD_TESTS_NOT_RUN  = UINT64_C(1) << 22,
    BTB_GATE_CHILD_TESTS_FAILED   = UINT64_C(1) << 23,
    BTB_GATE_CHILD_SHA_MISMATCH   = UINT64_C(1) << 24
} BtbGateIssue;

typedef struct BtbGateSnapshot {
    BtbGateAction action;
    /* The producer issues the identifier; consumers must supply the expected
     * one from the latest observation. This is an identity check, not a clock. */
    uint64_t observationId;
    uint64_t expectedObservationId;

    int onMain;
    int detached;
    int remoteChecked;
    int divergenceKnown;
    uint32_t ahead;
    uint32_t behind;

    size_t conflicts;
    size_t staged;
    size_t unstaged;
    size_t untracked;
    int stagingReviewed;

    BtbGateProof buildProof;
    BtbGateProof testsProof;
    BtbGateProof docsProof;

    /* PIN only. A pin is a parent repository's *reviewed staged* gitlink.
     * Other staged changes are not allowed in this teaching release model. */
    int onlyGitlinkStaged;
    int childWorkingTreeClean;
    int childCommitPublished;
    BtbGateProof childTestsProof;
    char requestedChildCommit[BTB_GATE_SHA_CAPACITY];
    char validatedChildCommit[BTB_GATE_SHA_CAPACITY];
} BtbGateSnapshot;

typedef struct BtbGateReport {
    BtbGateAction action;
    uint64_t observationId;
    uint64_t issues;
    unsigned issueCount;
    BtbGateStatus verdict;
} BtbGateReport;

/* Reject malformed snapshots without modifying *out_report. On valid input,
 * return READY or BLOCKED and replace the complete caller-owned report. The
 * input is read-only, no pointers are retained, no file is written and no Git
 * command is executed. This is NOT a guarantee of remote-state freshness. */
BtbGateStatus BtbGateEvaluate(const BtbGateSnapshot *snapshot,
                              BtbGateReport *out_report);

/* Exact single-bit issue names. Unknown values return "unknown issue". */
const char *BtbGateIssueName(uint64_t issueBit);

#endif
