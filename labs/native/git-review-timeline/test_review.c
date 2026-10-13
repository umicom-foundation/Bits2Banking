/*-----------------------------------------------------------------------------
 * Bits to Banking | Umicom Foundation | Sammy Hegab | MIT
 * File: labs/native/git-review-timeline/test_review.c
 * PURPOSE: Named, deterministic C23 tests for safe observation evidence.
 *---------------------------------------------------------------------------*/
#include "review.h"
#include <stdint.h>
#include <stdio.h>
#include <string.h>

#define CHECK(expression) do { \
    if (!(expression)) { \
        fprintf(stderr, "%s:%d: check failed: %s\n", __FILE__, __LINE__, #expression); \
        return 1; \
    } \
} while (0)

static BtbReviewObservation BaseObservation(uint64_t observationId)
{
    BtbReviewObservation observation = {
        .observationId = observationId,
        .commit = "0d40b2d9222d0a0a0eaf912b8594e0e29fbb2796",
        .branchKnown = 1,
        .onMain = 1,
        .remoteFresh = 1,
        .divergenceKnown = 1
    };
    return observation;
}

static BtbReviewEvidence Evidence(BtbReviewEvidenceKind kind,
                                  BtbReviewProof proof, uint64_t observationId)
{
    BtbReviewEvidence evidence = {
        .kind = kind, .proof = proof, .observationId = observationId,
        .commit = "0d40b2d9222d0a0a0eaf912b8594e0e29fbb2796"
    };
    return evidence;
}

static int Prepare(BtbReviewTimeline *timeline, BtbReviewObservation observation)
{
    CHECK(BtbReviewInit(timeline) == BTB_REVIEW_OK);
    CHECK(BtbReviewObserve(timeline, &observation) == BTB_REVIEW_OK);
    return 0;
}

static int GetReport(const BtbReviewTimeline *timeline,
                     uint64_t observationId, BtbReviewReport *outReport)
{
    const BtbReviewResult status = BtbReviewEvaluate(timeline, observationId,
        "0d40b2d9222d0a0a0eaf912b8594e0e29fbb2796", outReport);
    CHECK(status == BTB_REVIEW_OK);
    return 0;
}

static int TestInit(void)
{
    BtbReviewTimeline timeline = {0};
    CHECK(BtbReviewInit(&timeline) == BTB_REVIEW_OK);
    CHECK(timeline.hasObservation == 0);
    CHECK(timeline.buildProof == BTB_REVIEW_PROOF_NOT_RUN);
    CHECK(timeline.testProof == BTB_REVIEW_PROOF_NOT_RUN);
    return 0;
}

static int TestInvalidInit(void)
{
    CHECK(BtbReviewInit(NULL) == BTB_REVIEW_INVALID);
    return 0;
}

static int TestMissingObservation(void)
{
    BtbReviewTimeline timeline = {0};
    BtbReviewReport report = {.issues = UINT64_C(0x1234)};
    CHECK(BtbReviewInit(&timeline) == BTB_REVIEW_OK);
    CHECK(BtbReviewEvaluate(&timeline, 1U,
        "0d40b2d9222d0a0a0eaf912b8594e0e29fbb2796", &report)
          == BTB_REVIEW_NOT_OBSERVED);
    CHECK(report.issues == UINT64_C(0x1234));
    return 0;
}

static int TestBaseWarnings(void)
{
    BtbReviewTimeline timeline = {0};
    BtbReviewReport report = {0};
    CHECK(Prepare(&timeline, BaseObservation(1U)) == 0);
    CHECK(GetReport(&timeline, 1U, &report) == 0);
    CHECK(report.issues == (BTB_REVIEW_ISSUE_BUILD_NOT_RUN |
                            BTB_REVIEW_ISSUE_TEST_NOT_RUN));
    CHECK(report.nextCheck == BTB_REVIEW_CHECK_BUILD);
    return 0;
}

static int TestProofsPassed(void)
{
    BtbReviewTimeline timeline = {0};
    BtbReviewReport report = {0};
    BtbReviewEvidence build = Evidence(BTB_REVIEW_EVIDENCE_BUILD,
                                        BTB_REVIEW_PROOF_PASSED, 1U);
    BtbReviewEvidence test = Evidence(BTB_REVIEW_EVIDENCE_TEST,
                                       BTB_REVIEW_PROOF_PASSED, 1U);
    CHECK(Prepare(&timeline, BaseObservation(1U)) == 0);
    CHECK(BtbReviewRecordEvidence(&timeline, &build) == BTB_REVIEW_OK);
    CHECK(BtbReviewRecordEvidence(&timeline, &test) == BTB_REVIEW_OK);
    CHECK(GetReport(&timeline, 1U, &report) == 0);
    CHECK(report.issues == 0U);
    CHECK(report.nextCheck == BTB_REVIEW_CHECK_STAGED_DIFF);
    return 0;
}

static int TestDetached(void)
{
    BtbReviewTimeline timeline = {0};
    BtbReviewObservation observation = BaseObservation(1U);
    BtbReviewReport report = {0};
    observation.onMain = 0;
    observation.branchKnown = 0;
    observation.detached = 1;
    CHECK(Prepare(&timeline, observation) == 0);
    CHECK(GetReport(&timeline, 1U, &report) == 0);
    CHECK((report.issues & BTB_REVIEW_ISSUE_DETACHED) != 0U);
    CHECK(report.nextCheck == BTB_REVIEW_CHECK_LOCAL_COMMITS);
    return 0;
}

static int TestBehind(void)
{
    BtbReviewTimeline timeline = {0};
    BtbReviewObservation observation = BaseObservation(1U);
    BtbReviewReport report = {0};
    observation.behind = 6U;
    CHECK(Prepare(&timeline, observation) == 0);
    CHECK(GetReport(&timeline, 1U, &report) == 0);
    CHECK((report.issues & BTB_REVIEW_ISSUE_BEHIND) != 0U);
    CHECK(report.nextCheck == BTB_REVIEW_CHECK_REMOTE_ANCESTRY);
    return 0;
}

static int TestRemoteNotFresh(void)
{
    BtbReviewTimeline timeline = {0};
    BtbReviewObservation observation = BaseObservation(1U);
    BtbReviewReport report = {0};
    observation.remoteFresh = 0;
    CHECK(Prepare(&timeline, observation) == 0);
    CHECK(GetReport(&timeline, 1U, &report) == 0);
    CHECK((report.issues & BTB_REVIEW_ISSUE_REMOTE_UNCHECKED) != 0U);
    return 0;
}

static int TestUnknownAncestry(void)
{
    BtbReviewTimeline timeline = {0};
    BtbReviewObservation observation = BaseObservation(1U);
    BtbReviewReport report = {0};
    observation.divergenceKnown = 0;
    CHECK(Prepare(&timeline, observation) == 0);
    CHECK(GetReport(&timeline, 1U, &report) == 0);
    CHECK((report.issues & BTB_REVIEW_ISSUE_DIVERGENCE) != 0U);
    return 0;
}

static int TestConflictPriority(void)
{
    BtbReviewTimeline timeline = {0};
    BtbReviewObservation observation = BaseObservation(1U);
    BtbReviewReport report = {0};
    observation.entries = 3U;
    observation.conflicts = 1U;
    observation.behind = 2U;
    CHECK(Prepare(&timeline, observation) == 0);
    CHECK(GetReport(&timeline, 1U, &report) == 0);
    CHECK(report.nextCheck == BTB_REVIEW_CHECK_CONFLICTS);
    return 0;
}

static int TestDirtyChild(void)
{
    BtbReviewTimeline timeline = {0};
    BtbReviewObservation observation = BaseObservation(1U);
    BtbReviewReport report = {0};
    observation.dirtyChildren = 2U;
    CHECK(Prepare(&timeline, observation) == 0);
    CHECK(GetReport(&timeline, 1U, &report) == 0);
    CHECK(report.nextCheck == BTB_REVIEW_CHECK_CHILD_STATUS);
    return 0;
}

static int TestUntracked(void)
{
    BtbReviewTimeline timeline = {0};
    BtbReviewObservation observation = BaseObservation(1U);
    BtbReviewReport report = {0};
    observation.entries = 2U;
    observation.untracked = 1U;
    CHECK(Prepare(&timeline, observation) == 0);
    CHECK(GetReport(&timeline, 1U, &report) == 0);
    CHECK((report.issues & BTB_REVIEW_ISSUE_UNTRACKED) != 0U);
    CHECK(report.nextCheck == BTB_REVIEW_CHECK_WORKTREE);
    return 0;
}

static int TestAdvisories(void)
{
    BtbReviewTimeline timeline = {0};
    BtbReviewObservation observation = BaseObservation(1U);
    BtbReviewReport report = {0};
    observation.entries = 2U;
    observation.staged = 1U;
    observation.ahead = 3U;
    observation.childCommits = 1U;
    CHECK(Prepare(&timeline, observation) == 0);
    CHECK(GetReport(&timeline, 1U, &report) == 0);
    CHECK(report.advisories == (BTB_REVIEW_ADVISORY_AHEAD |
                                BTB_REVIEW_ADVISORY_STAGED |
                                BTB_REVIEW_ADVISORY_CHILD_GITLINK));
    return 0;
}

static int TestFailedBuild(void)
{
    BtbReviewTimeline timeline = {0};
    BtbReviewReport report = {0};
    BtbReviewEvidence build = Evidence(BTB_REVIEW_EVIDENCE_BUILD,
                                        BTB_REVIEW_PROOF_FAILED, 1U);
    CHECK(Prepare(&timeline, BaseObservation(1U)) == 0);
    CHECK(BtbReviewRecordEvidence(&timeline, &build) == BTB_REVIEW_OK);
    CHECK(GetReport(&timeline, 1U, &report) == 0);
    CHECK((report.issues & BTB_REVIEW_ISSUE_BUILD_FAILED) != 0U);
    return 0;
}

static int TestFailedTest(void)
{
    BtbReviewTimeline timeline = {0};
    BtbReviewReport report = {0};
    BtbReviewEvidence build = Evidence(BTB_REVIEW_EVIDENCE_BUILD,
                                        BTB_REVIEW_PROOF_PASSED, 1U);
    BtbReviewEvidence test = Evidence(BTB_REVIEW_EVIDENCE_TEST,
                                       BTB_REVIEW_PROOF_FAILED, 1U);
    CHECK(Prepare(&timeline, BaseObservation(1U)) == 0);
    CHECK(BtbReviewRecordEvidence(&timeline, &build) == BTB_REVIEW_OK);
    CHECK(BtbReviewRecordEvidence(&timeline, &test) == BTB_REVIEW_OK);
    CHECK(GetReport(&timeline, 1U, &report) == 0);
    CHECK((report.issues & BTB_REVIEW_ISSUE_TEST_FAILED) != 0U);
    return 0;
}

static int TestStaleEvidence(void)
{
    BtbReviewTimeline timeline = {0};
    BtbReviewEvidence evidence = Evidence(BTB_REVIEW_EVIDENCE_TEST,
                                           BTB_REVIEW_PROOF_PASSED, 1U);
    CHECK(Prepare(&timeline, BaseObservation(2U)) == 0);
    CHECK(BtbReviewRecordEvidence(&timeline, &evidence) == BTB_REVIEW_STALE);
    CHECK(timeline.testProof == BTB_REVIEW_PROOF_NOT_RUN);
    return 0;
}

static int TestWrongCommitEvidence(void)
{
    BtbReviewTimeline timeline = {0};
    BtbReviewEvidence evidence = Evidence(BTB_REVIEW_EVIDENCE_BUILD,
                                           BTB_REVIEW_PROOF_PASSED, 1U);
    CHECK(Prepare(&timeline, BaseObservation(1U)) == 0);
    evidence.commit[0] = 'b';
    CHECK(BtbReviewRecordEvidence(&timeline, &evidence) == BTB_REVIEW_STALE);
    CHECK(timeline.buildProof == BTB_REVIEW_PROOF_NOT_RUN);
    return 0;
}

static int TestNewObservationInvalidatesProof(void)
{
    BtbReviewTimeline timeline = {0};
    BtbReviewObservation observation = BaseObservation(1U);
    BtbReviewEvidence evidence = Evidence(BTB_REVIEW_EVIDENCE_BUILD,
                                           BTB_REVIEW_PROOF_PASSED, 1U);
    CHECK(Prepare(&timeline, observation) == 0);
    CHECK(BtbReviewRecordEvidence(&timeline, &evidence) == BTB_REVIEW_OK);
    observation.observationId = 2U;
    CHECK(BtbReviewObserve(&timeline, &observation) == BTB_REVIEW_OK);
    CHECK(timeline.buildProof == BTB_REVIEW_PROOF_NOT_RUN);
    return 0;
}

static int TestRebuildInvalidatesTest(void)
{
    BtbReviewTimeline timeline = {0};
    BtbReviewEvidence build = Evidence(BTB_REVIEW_EVIDENCE_BUILD,
                                        BTB_REVIEW_PROOF_PASSED, 1U);
    BtbReviewEvidence test = Evidence(BTB_REVIEW_EVIDENCE_TEST,
                                       BTB_REVIEW_PROOF_PASSED, 1U);
    CHECK(Prepare(&timeline, BaseObservation(1U)) == 0);
    CHECK(BtbReviewRecordEvidence(&timeline, &build) == BTB_REVIEW_OK);
    CHECK(BtbReviewRecordEvidence(&timeline, &test) == BTB_REVIEW_OK);
    CHECK(BtbReviewRecordEvidence(&timeline, &build) == BTB_REVIEW_OK);
    CHECK(timeline.testProof == BTB_REVIEW_PROOF_NOT_RUN);
    return 0;
}

static int TestStaleReport(void)
{
    BtbReviewTimeline timeline = {0};
    BtbReviewReport report = {0};
    CHECK(Prepare(&timeline, BaseObservation(2U)) == 0);
    CHECK(GetReport(&timeline, 1U, &report) == 0);
    CHECK((report.issues & BTB_REVIEW_ISSUE_STALE) != 0U);
    CHECK(report.nextCheck == BTB_REVIEW_CHECK_REFRESH_OBSERVATION);
    return 0;
}

static int TestInvalidAtomic(void)
{
    BtbReviewTimeline timeline = {0};
    BtbReviewObservation observation = BaseObservation(1U);
    BtbReviewReport report = {.issues = UINT64_C(0xdeadbeef)};
    CHECK(Prepare(&timeline, observation) == 0);
    observation.observationId = 2U;
    observation.staged = 5U;
    observation.entries = 1U;
    CHECK(BtbReviewObserve(&timeline, &observation) == BTB_REVIEW_INVALID);
    CHECK(timeline.observation.observationId == 1U);
    CHECK(BtbReviewEvaluate(&timeline, 1U, "not-a-hash", &report)
          == BTB_REVIEW_INVALID);
    CHECK(report.issues == UINT64_C(0xdeadbeef));
    return 0;
}

static int TestSha256(void)
{
    BtbReviewTimeline timeline = {0};
    BtbReviewObservation observation = BaseObservation(1U);
    BtbReviewReport report = {0};
    memcpy(observation.commit,
           "0123456789abcdef0123456789abcdef0123456789abcdef0123456789abcdef", 65U);
    CHECK(Prepare(&timeline, observation) == 0);
    CHECK(BtbReviewEvaluate(&timeline, 1U, observation.commit, &report)
          == BTB_REVIEW_OK);
    return 0;
}

static int TestInvalidSha(void)
{
    BtbReviewTimeline timeline = {0};
    BtbReviewObservation observation = BaseObservation(1U);
    CHECK(BtbReviewInit(&timeline) == BTB_REVIEW_OK);
    observation.commit[8] = 'g';
    CHECK(BtbReviewObserve(&timeline, &observation) == BTB_REVIEW_INVALID);
    return 0;
}

static int TestContradictoryFacts(void)
{
    BtbReviewTimeline timeline = {0};
    BtbReviewObservation observation = BaseObservation(1U);
    CHECK(BtbReviewInit(&timeline) == BTB_REVIEW_OK);
    observation.detached = 1;
    CHECK(BtbReviewObserve(&timeline, &observation) == BTB_REVIEW_INVALID);
    CHECK(timeline.hasObservation == 0);
    return 0;
}

static int TestNonMonotonicObservation(void)
{
    BtbReviewTimeline timeline = {0};
    BtbReviewObservation observation = BaseObservation(2U);
    CHECK(Prepare(&timeline, observation) == 0);
    CHECK(BtbReviewObserve(&timeline, &observation) == BTB_REVIEW_INVALID);
    observation.observationId = 1U;
    CHECK(BtbReviewObserve(&timeline, &observation) == BTB_REVIEW_INVALID);
    CHECK(timeline.observationsReceived == 1U);
    return 0;
}

static int TestUnborn(void)
{
    BtbReviewTimeline timeline = {0};
    BtbReviewObservation observation = BaseObservation(1U);
    /* A repository with no first commit has no full object ID. The triage
     * still describes that condition rather than pretending the SHA exists. */
    BtbReviewReport report = {0};
    observation.unborn = 1;
    observation.commit[0] = '\0';
    CHECK(Prepare(&timeline, observation) == 0);
    CHECK(BtbReviewEvaluate(&timeline, 1U, "", &report)
         == BTB_REVIEW_OK);
    CHECK((report.issues & BTB_REVIEW_ISSUE_UNBORN) != 0U);
    CHECK((report.issues & BTB_REVIEW_ISSUE_STALE) == 0U);
    return 0;
}

static int TestReadOnlyCommands(void)
{
    CHECK(strstr(BtbReviewNextCheckCommand(BTB_REVIEW_CHECK_LOCAL_COMMITS),
                 "git log") != NULL);
    CHECK(strstr(BtbReviewNextCheckCommand(BTB_REVIEW_CHECK_CHILD_STATUS),
                 "status") != NULL);
    CHECK(strstr(BtbReviewNextCheckCommand(BTB_REVIEW_CHECK_STAGED_DIFF),
                 "diff") != NULL);
    return 0;
}

static int TestMutationSequence(void)
{
    BtbReviewTimeline timeline = {0};
    CHECK(BtbReviewInit(&timeline) == BTB_REVIEW_OK);
    for (uint64_t i = 1U; i <= UINT64_C(100000); ++i) {
        BtbReviewObservation observation = BaseObservation(i);
        BtbReviewReport report = {0};
        observation.onMain = i % 5U == 0U ? 0 : 1;
        observation.entries = (size_t)(i % 4U);
        observation.staged = observation.entries == 0U ? 0U : (size_t)(i % 2U);
        observation.untracked = observation.entries == 0U ? 0U : (size_t)(i % 2U);
        observation.conflicts = observation.entries == 0U ? 0U :
            (size_t)(i % 3U == 0U ? 1U : 0U);
        observation.behind = (size_t)(i % 7U == 0U ? 1U : 0U);
        CHECK(BtbReviewObserve(&timeline, &observation) == BTB_REVIEW_OK);
        CHECK(BtbReviewEvaluate(&timeline, i, observation.commit, &report)
              == BTB_REVIEW_OK);
        CHECK(report.observationId == i);
        CHECK((report.issues & BTB_REVIEW_ISSUE_BUILD_NOT_RUN) != 0U);
        if (observation.conflicts != 0U)
            CHECK((report.issues & BTB_REVIEW_ISSUE_CONFLICTS) != 0U);
        if (observation.behind != 0U)
            CHECK((report.issues & BTB_REVIEW_ISSUE_BEHIND) != 0U);
    }
    CHECK(timeline.observationsReceived == 100000U);
    return 0;
}

struct TestCase { const char *name; int (*run)(void); };
static const struct TestCase TESTS[] = {
    {"init", TestInit},
    {"invalid-init", TestInvalidInit},
    {"missing-observation", TestMissingObservation},
    {"baseline", TestBaseWarnings},
    {"proofs", TestProofsPassed},
    {"detached", TestDetached},
    {"behind", TestBehind},
    {"remote-not-fresh", TestRemoteNotFresh},
    {"unknown-ancestry", TestUnknownAncestry},
    {"conflict-priority", TestConflictPriority},
    {"dirty-child", TestDirtyChild},
    {"untracked", TestUntracked},
    {"advisories", TestAdvisories},
    {"failed-build", TestFailedBuild},
    {"failed-test", TestFailedTest},
    {"stale-evidence", TestStaleEvidence},
    {"wrong-commit-evidence", TestWrongCommitEvidence},
    {"observation-invalidates", TestNewObservationInvalidatesProof},
    {"rebuild-invalidates", TestRebuildInvalidatesTest},
    {"stale-report", TestStaleReport},
    {"invalid-atomic", TestInvalidAtomic},
    {"sha256", TestSha256},
    {"invalid-sha", TestInvalidSha},
    {"contradictory", TestContradictoryFacts},
    {"nonmonotonic", TestNonMonotonicObservation},
    {"unborn", TestUnborn},
    {"read-only", TestReadOnlyCommands},
    {"mutation-100k", TestMutationSequence}
};

int main(int argc, char **argv)
{
    if (argc != 2) {
        fprintf(stderr, "Usage: btb-git-review-test <case>\n");
        return 2;
    }
    for (size_t i = 0U; i < sizeof(TESTS) / sizeof(TESTS[0]); ++i) {
        if (strcmp(argv[1], TESTS[i].name) == 0) return TESTS[i].run();
    }
    fprintf(stderr, "Unknown test case: %s\n", argv[1]);
    return 2;
}
