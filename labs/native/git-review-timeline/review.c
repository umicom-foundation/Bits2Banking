/*-----------------------------------------------------------------------------
 * Bits to Banking | Umicom Foundation | Sammy Hegab | MIT
 * File: labs/native/git-review-timeline/review.c
 * PURPOSE: Failure-atomic C23 observation timeline and non-mutating triage.
 * ARCHITECTURE: Does not parse Git output, query remotes or stage gitlinks.
 *---------------------------------------------------------------------------*/
#include "review.h"

#include <string.h>

static int IsBoolean(int value)
{
    return value == 0 || value == 1;
}

/* A bounded scanner avoids reading beyond caller-supplied fixed storage.
 * SHA-1 and SHA-256 object IDs are supported; abbreviated hashes are not. */
static int IsFullCommit(const char commit[BTB_REVIEW_SHA_CAPACITY], int allowEmpty)
{
    size_t length = 0U;
    if (commit == NULL) return 0;
    while (length < BTB_REVIEW_SHA_CAPACITY && commit[length] != '\0') {
        const unsigned char ch = (unsigned char)commit[length];
        if (!((ch >= (unsigned char)'0' && ch <= (unsigned char)'9') ||
              (ch >= (unsigned char)'a' && ch <= (unsigned char)'f') ||
              (ch >= (unsigned char)'A' && ch <= (unsigned char)'F'))) return 0;
        ++length;
    }
    if (length >= BTB_REVIEW_SHA_CAPACITY) return 0;
    if (allowEmpty && length == 0U) return 1;
    if (length != 40U && length != 64U) return 0;
    for (size_t i = 0U; i < length; ++i) {
        if (commit[i] != '0') return 1;
    }
    return 0;
}

static int IsValidObservation(const BtbReviewObservation *observation)
{
    if (observation == NULL || observation->observationId == 0U ||
        !IsBoolean(observation->branchKnown) || !IsBoolean(observation->onMain) ||
        !IsBoolean(observation->detached) || !IsBoolean(observation->unborn) ||
        !IsBoolean(observation->remoteFresh) ||
        !IsBoolean(observation->divergenceKnown) ||
        observation->staged > observation->entries ||
        observation->untracked > observation->entries ||
        observation->conflicts > observation->entries ||
        (observation->branchKnown == 0 && observation->onMain != 0) ||
        (observation->detached != 0 && observation->onMain != 0) ||
        (observation->unborn != 0 && observation->detached != 0) ||
        !IsFullCommit(observation->commit, observation->unborn)) {
        return 0;
    }
    if (observation->unborn != 0 && observation->commit[0] != '\0') return 0;
    if (observation->unborn == 0 && observation->commit[0] == '\0') return 0;
    if (observation->divergenceKnown == 0 &&
        (observation->ahead != 0U || observation->behind != 0U)) return 0;
    return 1;
}

BtbReviewResult BtbReviewInit(BtbReviewTimeline *timeline)
{
    if (timeline == NULL) return BTB_REVIEW_INVALID;
    *timeline = (BtbReviewTimeline){0};
    timeline->buildProof = BTB_REVIEW_PROOF_NOT_RUN;
    timeline->testProof = BTB_REVIEW_PROOF_NOT_RUN;
    return BTB_REVIEW_OK;
}

BtbReviewResult BtbReviewObserve(BtbReviewTimeline *timeline,
                                  const BtbReviewObservation *observation)
{
    if (timeline == NULL || !IsValidObservation(observation) ||
        (timeline->hasObservation != 0 &&
         observation->observationId <= timeline->observation.observationId) ||
        timeline->observationsReceived == SIZE_MAX) return BTB_REVIEW_INVALID;
    const BtbReviewObservation snapshot = *observation;
    timeline->observation = snapshot;
    timeline->hasObservation = 1;
    timeline->buildProof = BTB_REVIEW_PROOF_NOT_RUN;
    timeline->testProof = BTB_REVIEW_PROOF_NOT_RUN;
    ++timeline->observationsReceived;
    return BTB_REVIEW_OK;
}

BtbReviewResult BtbReviewRecordEvidence(BtbReviewTimeline *timeline,
                                         const BtbReviewEvidence *evidence)
{
    if (timeline == NULL || evidence == NULL ||
        (evidence->kind != BTB_REVIEW_EVIDENCE_BUILD &&
         evidence->kind != BTB_REVIEW_EVIDENCE_TEST) ||
        (evidence->proof != BTB_REVIEW_PROOF_PASSED &&
         evidence->proof != BTB_REVIEW_PROOF_FAILED) ||
        evidence->observationId == 0U ||
        !IsFullCommit(evidence->commit, 0)) return BTB_REVIEW_INVALID;
    if (timeline->hasObservation == 0) return BTB_REVIEW_NOT_OBSERVED;
    if (evidence->observationId != timeline->observation.observationId ||
        strcmp(evidence->commit, timeline->observation.commit) != 0)
        return BTB_REVIEW_STALE;
    if (evidence->kind == BTB_REVIEW_EVIDENCE_BUILD) {
        timeline->buildProof = evidence->proof;
        /* Rebuilding changes test validity; require tests again. */
        timeline->testProof = BTB_REVIEW_PROOF_NOT_RUN;
    } else {
        timeline->testProof = evidence->proof;
    }
    return BTB_REVIEW_OK;
}

static BtbReviewNextCheck ChooseNext(uint64_t issues)
{
    if ((issues & BTB_REVIEW_ISSUE_STALE) != 0U)
        return BTB_REVIEW_CHECK_REFRESH_OBSERVATION;
    if ((issues & BTB_REVIEW_ISSUE_CONFLICTS) != 0U)
        return BTB_REVIEW_CHECK_CONFLICTS;
    if ((issues & BTB_REVIEW_ISSUE_DETACHED) != 0U)
        return BTB_REVIEW_CHECK_LOCAL_COMMITS;
    if ((issues & BTB_REVIEW_ISSUE_CHILD_DIRTY) != 0U)
        return BTB_REVIEW_CHECK_CHILD_STATUS;
    if ((issues & (BTB_REVIEW_ISSUE_REMOTE_UNCHECKED |
                   BTB_REVIEW_ISSUE_DIVERGENCE |
                   BTB_REVIEW_ISSUE_BEHIND)) != 0U)
        return BTB_REVIEW_CHECK_REMOTE_ANCESTRY;
    if ((issues & (BTB_REVIEW_ISSUE_UNTRACKED |
                   BTB_REVIEW_ISSUE_MODIFIED)) != 0U)
        return BTB_REVIEW_CHECK_WORKTREE;
    if ((issues & (BTB_REVIEW_ISSUE_BUILD_NOT_RUN |
                   BTB_REVIEW_ISSUE_BUILD_FAILED)) != 0U)
        return BTB_REVIEW_CHECK_BUILD;
    if ((issues & (BTB_REVIEW_ISSUE_TEST_NOT_RUN |
                   BTB_REVIEW_ISSUE_TEST_FAILED)) != 0U)
        return BTB_REVIEW_CHECK_TEST;
    if (issues != 0U) return BTB_REVIEW_CHECK_REFRESH_OBSERVATION;
    return BTB_REVIEW_CHECK_STAGED_DIFF;
}

BtbReviewResult BtbReviewEvaluate(const BtbReviewTimeline *timeline,
                                   uint64_t expectedObservationId,
                                   const char *expectedCommit,
                                   BtbReviewReport *outReport)
{
    if (timeline == NULL || outReport == NULL || expectedObservationId == 0U)
        return BTB_REVIEW_INVALID;
    if (timeline->hasObservation == 0) return BTB_REVIEW_NOT_OBSERVED;
    if (!IsFullCommit(expectedCommit, timeline->observation.unborn))
        return BTB_REVIEW_INVALID;
    const BtbReviewObservation *observation = &timeline->observation;
    uint64_t issues = 0U;
    uint64_t advisories = 0U;
    if (observation->observationId != expectedObservationId ||
        strcmp(expectedCommit, observation->commit) != 0)
        issues |= BTB_REVIEW_ISSUE_STALE;
    if (observation->unborn != 0) issues |= BTB_REVIEW_ISSUE_UNBORN;
    if (observation->detached != 0) issues |= BTB_REVIEW_ISSUE_DETACHED;
    if (observation->branchKnown == 0) issues |= BTB_REVIEW_ISSUE_BRANCH_UNKNOWN;
    else if (observation->onMain == 0 && observation->detached == 0)
        issues |= BTB_REVIEW_ISSUE_NOT_MAIN;
    if (observation->remoteFresh == 0) issues |= BTB_REVIEW_ISSUE_REMOTE_UNCHECKED;
    if (observation->divergenceKnown == 0) issues |= BTB_REVIEW_ISSUE_DIVERGENCE;
    else if (observation->behind > 0U) issues |= BTB_REVIEW_ISSUE_BEHIND;
    if (observation->conflicts > 0U) issues |= BTB_REVIEW_ISSUE_CONFLICTS;
    if (observation->untracked > 0U) issues |= BTB_REVIEW_ISSUE_UNTRACKED;
    if (observation->entries > 0U) issues |= BTB_REVIEW_ISSUE_MODIFIED;
    if (observation->dirtyChildren > 0U) issues |= BTB_REVIEW_ISSUE_CHILD_DIRTY;
    if (timeline->buildProof == BTB_REVIEW_PROOF_NOT_RUN)
        issues |= BTB_REVIEW_ISSUE_BUILD_NOT_RUN;
    else if (timeline->buildProof == BTB_REVIEW_PROOF_FAILED)
        issues |= BTB_REVIEW_ISSUE_BUILD_FAILED;
    if (timeline->testProof == BTB_REVIEW_PROOF_NOT_RUN)
        issues |= BTB_REVIEW_ISSUE_TEST_NOT_RUN;
    else if (timeline->testProof == BTB_REVIEW_PROOF_FAILED)
        issues |= BTB_REVIEW_ISSUE_TEST_FAILED;
    if (observation->ahead > 0U) advisories |= BTB_REVIEW_ADVISORY_AHEAD;
    if (observation->staged > 0U) advisories |= BTB_REVIEW_ADVISORY_STAGED;
    if (observation->childCommits > 0U)
        advisories |= BTB_REVIEW_ADVISORY_CHILD_GITLINK;
    const BtbReviewReport report = {
        .observationId = observation->observationId,
        .issues = issues,
        .advisories = advisories,
        .nextCheck = ChooseNext(issues),
        .buildProof = timeline->buildProof,
        .testProof = timeline->testProof
    };
    *outReport = report;
    return BTB_REVIEW_OK;
}

const char *BtbReviewNextCheckCommand(BtbReviewNextCheck check)
{
    switch (check) {
    case BTB_REVIEW_CHECK_NONE: return "no command selected";
    case BTB_REVIEW_CHECK_REFRESH_OBSERVATION:
        return "git status --porcelain=v2 --branch";
    case BTB_REVIEW_CHECK_CONFLICTS:
        return "git diff --name-only --diff-filter=U";
    case BTB_REVIEW_CHECK_LOCAL_COMMITS:
        return "git log --oneline origin/main..HEAD";
    case BTB_REVIEW_CHECK_CHILD_STATUS:
        return "git -C framework status --short";
    case BTB_REVIEW_CHECK_REMOTE_ANCESTRY:
        return "git log --oneline --left-right HEAD...origin/main";
    case BTB_REVIEW_CHECK_WORKTREE:
        return "git status --short";
    case BTB_REVIEW_CHECK_BUILD:
        return "cmake --build --preset <configured-preset>";
    case BTB_REVIEW_CHECK_TEST:
        return "ctest --preset <configured-preset> --output-on-failure";
    case BTB_REVIEW_CHECK_STAGED_DIFF:
        return "git diff --cached --check";
    default: return "unknown diagnostic command";
    }
}

const char *BtbReviewIssueName(uint64_t oneBit)
{
    switch (oneBit) {
    case BTB_REVIEW_ISSUE_STALE: return "stale observation or commit reference";
    case BTB_REVIEW_ISSUE_UNBORN: return "repository has no commit";
    case BTB_REVIEW_ISSUE_DETACHED: return "detached HEAD requires history inspection";
    case BTB_REVIEW_ISSUE_BRANCH_UNKNOWN: return "branch identity unknown";
    case BTB_REVIEW_ISSUE_NOT_MAIN: return "checkout is not on main";
    case BTB_REVIEW_ISSUE_REMOTE_UNCHECKED: return "remote freshness not evidenced";
    case BTB_REVIEW_ISSUE_DIVERGENCE: return "upstream ancestry not known";
    case BTB_REVIEW_ISSUE_BEHIND: return "local history is behind upstream";
    case BTB_REVIEW_ISSUE_CONFLICTS: return "unresolved merge conflicts";
    case BTB_REVIEW_ISSUE_UNTRACKED: return "untracked paths must be reviewed";
    case BTB_REVIEW_ISSUE_MODIFIED: return "working tree or index has changes";
    case BTB_REVIEW_ISSUE_CHILD_DIRTY: return "submodule working tree dirty";
    case BTB_REVIEW_ISSUE_BUILD_NOT_RUN: return "build evidence not recorded";
    case BTB_REVIEW_ISSUE_BUILD_FAILED: return "build evidence failed";
    case BTB_REVIEW_ISSUE_TEST_NOT_RUN: return "test evidence not recorded";
    case BTB_REVIEW_ISSUE_TEST_FAILED: return "test evidence failed";
    default: return "unknown issue bit";
    }
}
