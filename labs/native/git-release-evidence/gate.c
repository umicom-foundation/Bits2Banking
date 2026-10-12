/*-----------------------------------------------------------------------------
 * Bits2Banking | Umicom Foundation | Sammy Hegab | MIT
 * File: labs/native/git-release-evidence/gate.c
 * PURPOSE: Deterministic, failure-atomic C23 evidence qualification engine.
 *
 * IMPORTANT: Never obtain Git state here. The Umicom Framework VCS and
 * repository-control services own observations and real gitlink operations.
 *---------------------------------------------------------------------------*/
#include "gate.h"

#include <string.h>

static int IsBoolean(int value)
{
    return value == 0 || value == 1;
}

static int IsProof(BtbGateProof proof)
{
    return proof >= BTB_GATE_PROOF_NOT_RUN && proof <= BTB_GATE_PROOF_FAILED;
}

static int IsCommitSha(const char sha[BTB_GATE_SHA_CAPACITY])
{
    int nonzero = 0;
    for (size_t i = 0U; i < BTB_GATE_SHA_CAPACITY - 1U; ++i) {
        const unsigned char character = (unsigned char)sha[i];
        if (character >= (unsigned char)'1' && character <= (unsigned char)'9') {
            nonzero = 1;
        } else if (character >= (unsigned char)'a' && character <= (unsigned char)'f') {
            nonzero = 1;
        } else if (character >= (unsigned char)'A' && character <= (unsigned char)'F') {
            nonzero = 1;
        } else if (character != (unsigned char)'0') {
            return 0;
        }
    }
    return sha[BTB_GATE_SHA_CAPACITY - 1U] == '\0' && nonzero;
}

static int IsValid(const BtbGateSnapshot *snapshot, const BtbGateReport *out_report)
{
    if (snapshot == NULL || out_report == NULL ||
        (snapshot->action != BTB_GATE_ACTION_COMMIT &&
         snapshot->action != BTB_GATE_ACTION_PUSH &&
         snapshot->action != BTB_GATE_ACTION_PIN) ||
        snapshot->observationId == 0U || snapshot->expectedObservationId == 0U ||
        !IsBoolean(snapshot->onMain) || !IsBoolean(snapshot->detached) ||
        !IsBoolean(snapshot->remoteChecked) || !IsBoolean(snapshot->divergenceKnown) ||
        !IsBoolean(snapshot->stagingReviewed) ||
        !IsBoolean(snapshot->onlyGitlinkStaged) ||
        !IsBoolean(snapshot->childWorkingTreeClean) ||
        !IsBoolean(snapshot->childCommitPublished) ||
        !IsProof(snapshot->buildProof) || !IsProof(snapshot->testsProof) ||
        !IsProof(snapshot->docsProof) || !IsProof(snapshot->childTestsProof)) {
        return 0;
    }
    if (snapshot->action == BTB_GATE_ACTION_PIN &&
        (!IsCommitSha(snapshot->requestedChildCommit) ||
         !IsCommitSha(snapshot->validatedChildCommit))) {
        return 0;
    }
    return 1;
}

static void IncludeProof(uint64_t *issues, BtbGateProof proof,
                         uint64_t notRunBit, uint64_t failedBit)
{
    if (proof == BTB_GATE_PROOF_NOT_RUN) {
        *issues |= notRunBit;
    } else if (proof == BTB_GATE_PROOF_FAILED) {
        *issues |= failedBit;
    }
}

static unsigned CountIssues(uint64_t issues)
{
    unsigned count = 0U;
    while (issues != 0U) {
        issues &= issues - UINT64_C(1);
        ++count;
    }
    return count;
}

BtbGateStatus BtbGateEvaluate(const BtbGateSnapshot *snapshot,
                              BtbGateReport *out_report)
{
    /* Stage all evaluation locally, then publish once. Invalid input does
     * not corrupt or partially update a previous caller-owned report. */
    if (!IsValid(snapshot, out_report)) {
        return BTB_GATE_INVALID;
    }
    uint64_t issues = 0U;
    if (snapshot->observationId != snapshot->expectedObservationId) {
        issues |= BTB_GATE_STALE_SNAPSHOT;
    }
    if (snapshot->detached != 0) {
        issues |= BTB_GATE_DETACHED_HEAD;
    }
    if (snapshot->onMain == 0) {
        issues |= BTB_GATE_NOT_MAIN;
    }
    if (snapshot->remoteChecked == 0) {
        issues |= BTB_GATE_REMOTE_UNCHECKED;
    }
    if (snapshot->divergenceKnown == 0) {
        issues |= BTB_GATE_DIVERGENCE_UNKNOWN;
    } else if (snapshot->behind > 0U) {
        issues |= BTB_GATE_BEHIND_REMOTE;
    }
    if (snapshot->conflicts != 0U) {
        issues |= BTB_GATE_CONFLICTS;
    }
    if (snapshot->unstaged != 0U) {
        issues |= BTB_GATE_UNSTAGED_CHANGES;
    }
    if (snapshot->untracked != 0U) {
        issues |= BTB_GATE_UNTRACKED_FILES;
    }
    IncludeProof(&issues, snapshot->buildProof,
                 BTB_GATE_BUILD_NOT_RUN, BTB_GATE_BUILD_FAILED);
    IncludeProof(&issues, snapshot->testsProof,
                 BTB_GATE_TESTS_NOT_RUN, BTB_GATE_TESTS_FAILED);
    IncludeProof(&issues, snapshot->docsProof,
                 BTB_GATE_DOCS_NOT_RUN, BTB_GATE_DOCS_FAILED);

    switch (snapshot->action) {
    case BTB_GATE_ACTION_COMMIT:
        if (snapshot->staged == 0U) {
            issues |= BTB_GATE_NOTHING_STAGED;
        }
        if (snapshot->stagingReviewed == 0) {
            issues |= BTB_GATE_STAGING_NOT_REVIEWED;
        }
        break;
    case BTB_GATE_ACTION_PUSH:
        if (snapshot->staged != 0U) {
            issues |= BTB_GATE_INDEX_NOT_EMPTY;
        }
        if (snapshot->ahead == 0U) {
            issues |= BTB_GATE_NO_OUTGOING_COMMIT;
        }
        break;
    case BTB_GATE_ACTION_PIN:
        if (snapshot->staged != 1U || snapshot->onlyGitlinkStaged == 0) {
            issues |= BTB_GATE_GITLINK_NOT_SOLE;
        }
        if (snapshot->stagingReviewed == 0) {
            issues |= BTB_GATE_STAGING_NOT_REVIEWED;
        }
        if (snapshot->childWorkingTreeClean == 0) {
            issues |= BTB_GATE_CHILD_DIRTY;
        }
        if (snapshot->childCommitPublished == 0) {
            issues |= BTB_GATE_CHILD_NOT_PUBLISHED;
        }
        IncludeProof(&issues, snapshot->childTestsProof,
                     BTB_GATE_CHILD_TESTS_NOT_RUN, BTB_GATE_CHILD_TESTS_FAILED);
        if (strcmp(snapshot->requestedChildCommit,
                   snapshot->validatedChildCommit) != 0) {
            issues |= BTB_GATE_CHILD_SHA_MISMATCH;
        }
        break;
    default:
        /* Already excluded by IsValid. */
        return BTB_GATE_INVALID;
    }

    const BtbGateReport next = {
        .action = snapshot->action,
        .observationId = snapshot->observationId,
        .issues = issues,
        .issueCount = CountIssues(issues),
        .verdict = issues == 0U ? BTB_GATE_READY : BTB_GATE_BLOCKED
    };
    *out_report = next;
    return next.verdict;
}

const char *BtbGateIssueName(uint64_t issueBit)
{
    switch (issueBit) {
    case BTB_GATE_STALE_SNAPSHOT:       return "stale observation identifier";
    case BTB_GATE_DETACHED_HEAD:        return "detached HEAD";
    case BTB_GATE_NOT_MAIN:             return "not on main";
    case BTB_GATE_REMOTE_UNCHECKED:     return "remote was not freshly inspected";
    case BTB_GATE_DIVERGENCE_UNKNOWN:   return "remote ancestry unknown";
    case BTB_GATE_BEHIND_REMOTE:        return "local branch behind upstream";
    case BTB_GATE_CONFLICTS:            return "unresolved index conflicts";
    case BTB_GATE_UNSTAGED_CHANGES:     return "unstaged changes remain";
    case BTB_GATE_UNTRACKED_FILES:      return "untracked files remain";
    case BTB_GATE_NOTHING_STAGED:       return "nothing staged for commit";
    case BTB_GATE_STAGING_NOT_REVIEWED: return "staged changes not reviewed";
    case BTB_GATE_INDEX_NOT_EMPTY:      return "index contains uncommitted changes";
    case BTB_GATE_NO_OUTGOING_COMMIT:   return "no outgoing commit to publish";
    case BTB_GATE_BUILD_NOT_RUN:        return "build verification not run";
    case BTB_GATE_BUILD_FAILED:         return "build verification failed";
    case BTB_GATE_TESTS_NOT_RUN:        return "native tests not run";
    case BTB_GATE_TESTS_FAILED:         return "native tests failed";
    case BTB_GATE_DOCS_NOT_RUN:         return "documentation checks not run";
    case BTB_GATE_DOCS_FAILED:          return "documentation checks failed";
    case BTB_GATE_GITLINK_NOT_SOLE:     return "gitlink not sole staged parent change";
    case BTB_GATE_CHILD_DIRTY:          return "submodule working tree is dirty";
    case BTB_GATE_CHILD_NOT_PUBLISHED:  return "submodule commit not verified on remote";
    case BTB_GATE_CHILD_TESTS_NOT_RUN:  return "submodule tests not run";
    case BTB_GATE_CHILD_TESTS_FAILED:   return "submodule tests failed";
    case BTB_GATE_CHILD_SHA_MISMATCH:   return "requested gitlink differs from tested commit";
    default:                            return "unknown issue";
    }
}
