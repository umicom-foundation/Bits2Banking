/*-----------------------------------------------------------------------------
 * Bits2Banking | Umicom Foundation | Sammy Hegab | MIT
 * File: labs/native/git-release-evidence/test_gate.c
 * PURPOSE: Deterministic, standalone C23 release gate verification.
 *---------------------------------------------------------------------------*/
#include "gate.h"
#include <stdio.h>
#include <string.h>

static BtbGateSnapshot MakeReady(BtbGateAction action)
{
    BtbGateSnapshot snapshot = {
        .action = action,
        .observationId = 9001U,
        .expectedObservationId = 9001U,
        .onMain = 1,
        .remoteChecked = 1,
        .divergenceKnown = 1,
        .ahead = 1U,
        .staged = action == BTB_GATE_ACTION_PUSH ? 0U : 1U,
        .stagingReviewed = 1,
        .buildProof = BTB_GATE_PROOF_PASSED,
        .testsProof = BTB_GATE_PROOF_PASSED,
        .docsProof = BTB_GATE_PROOF_PASSED,
        .onlyGitlinkStaged = 1,
        .childWorkingTreeClean = 1,
        .childCommitPublished = 1,
        .childTestsProof = BTB_GATE_PROOF_PASSED,
        .requestedChildCommit = "abcdef0123456789abcdef0123456789abcdef01",
        .validatedChildCommit = "abcdef0123456789abcdef0123456789abcdef01"
    };
    return snapshot;
}

static int Ready(const BtbGateSnapshot *snapshot)
{
    BtbGateReport report = {0};
    return BtbGateEvaluate(snapshot, &report) == BTB_GATE_READY &&
           report.verdict == BTB_GATE_READY && report.issues == 0U &&
           report.issueCount == 0U && report.action == snapshot->action &&
           report.observationId == snapshot->observationId;
}

static int Blocked(const BtbGateSnapshot *snapshot, uint64_t expectedIssue)
{
    BtbGateReport report = {0};
    return BtbGateEvaluate(snapshot, &report) == BTB_GATE_BLOCKED &&
           report.verdict == BTB_GATE_BLOCKED &&
           (report.issues & expectedIssue) != 0U && report.issueCount >= 1U;
}

static int Preserved(const BtbGateSnapshot *snapshot)
{
    BtbGateReport report = {
        .action = BTB_GATE_ACTION_PIN,
        .observationId = UINT64_C(0x1122334455667788),
        .issues = UINT64_C(0x55aa),
        .issueCount = 17U,
        .verdict = BTB_GATE_BLOCKED
    };
    const BtbGateReport original = report;
    return BtbGateEvaluate(snapshot, &report) == BTB_GATE_INVALID &&
           memcmp(&report, &original, sizeof(report)) == 0;
}

static int DeterministicMutations(void)
{
    /* Each mutation adds a blocker to a known-good snapshot. This is a
     * metamorphic test: a hazard must never improve a safety decision. */
    for (size_t i = 0U; i < 100000U; ++i) {
        BtbGateSnapshot snapshot = MakeReady(BTB_GATE_ACTION_PUSH);
        const size_t mode = i % 10U;
        uint64_t expected = 0U;
        switch (mode) {
        case 0U: snapshot.detached = 1; expected = BTB_GATE_DETACHED_HEAD; break;
        case 1U: snapshot.behind = 3U; expected = BTB_GATE_BEHIND_REMOTE; break;
        case 2U: snapshot.conflicts = 1U; expected = BTB_GATE_CONFLICTS; break;
        case 3U: snapshot.staged = 2U; expected = BTB_GATE_INDEX_NOT_EMPTY; break;
        case 4U: snapshot.untracked = 1U; expected = BTB_GATE_UNTRACKED_FILES; break;
        case 5U: snapshot.buildProof = BTB_GATE_PROOF_FAILED;
                 expected = BTB_GATE_BUILD_FAILED; break;
        case 6U: snapshot.testsProof = BTB_GATE_PROOF_NOT_RUN;
                 expected = BTB_GATE_TESTS_NOT_RUN; break;
        case 7U: snapshot.docsProof = BTB_GATE_PROOF_FAILED;
                 expected = BTB_GATE_DOCS_FAILED; break;
        case 8U: snapshot.ahead = 0U;
                 expected = BTB_GATE_NO_OUTGOING_COMMIT; break;
        default: snapshot.expectedObservationId = 9002U;
                 expected = BTB_GATE_STALE_SNAPSHOT; break;
        }
        const BtbGateSnapshot original = snapshot;
        BtbGateReport first = {0};
        BtbGateReport second = {0};
        if (!Blocked(&snapshot, expected) ||
            BtbGateEvaluate(&snapshot, &first) != BTB_GATE_BLOCKED ||
            BtbGateEvaluate(&snapshot, &second) != BTB_GATE_BLOCKED ||
            memcmp(&first, &second, sizeof(first)) != 0 ||
            memcmp(&snapshot, &original, sizeof(snapshot)) != 0) {
            return 0;
        }
    }
    return 1;
}

static int RunScenario(const char *name)
{
    BtbGateSnapshot snapshot = MakeReady(BTB_GATE_ACTION_COMMIT);
    if (strcmp(name, "commit_ready") == 0) return Ready(&snapshot);
    if (strcmp(name, "push_ready") == 0) {
        snapshot = MakeReady(BTB_GATE_ACTION_PUSH); return Ready(&snapshot);
    }
    if (strcmp(name, "pin_ready") == 0) {
        snapshot = MakeReady(BTB_GATE_ACTION_PIN); return Ready(&snapshot);
    }
    if (strcmp(name, "detached") == 0) {
        snapshot.detached = 1; return Blocked(&snapshot, BTB_GATE_DETACHED_HEAD);
    }
    if (strcmp(name, "behind") == 0) {
        snapshot.behind = 2U; return Blocked(&snapshot, BTB_GATE_BEHIND_REMOTE);
    }
    if (strcmp(name, "unknown_remote") == 0) {
        snapshot.remoteChecked = 0;
        snapshot.divergenceKnown = 0;
        BtbGateReport report = {0};
        const uint64_t expected = BTB_GATE_DIVERGENCE_UNKNOWN |
                                  BTB_GATE_REMOTE_UNCHECKED;
        return BtbGateEvaluate(&snapshot, &report) == BTB_GATE_BLOCKED &&
               (report.issues & expected) == expected;
    }
    if (strcmp(name, "conflicting_index") == 0) {
        snapshot.conflicts = 1U; return Blocked(&snapshot, BTB_GATE_CONFLICTS);
    }
    if (strcmp(name, "untracked") == 0) {
        snapshot.untracked = 1U; return Blocked(&snapshot, BTB_GATE_UNTRACKED_FILES);
    }
    if (strcmp(name, "unstaged") == 0) {
        snapshot.unstaged = 1U; return Blocked(&snapshot, BTB_GATE_UNSTAGED_CHANGES);
    }
    if (strcmp(name, "no_staged") == 0) {
        snapshot.staged = 0U; return Blocked(&snapshot, BTB_GATE_NOTHING_STAGED);
    }
    if (strcmp(name, "unreviewed") == 0) {
        snapshot.stagingReviewed = 0; return Blocked(&snapshot, BTB_GATE_STAGING_NOT_REVIEWED);
    }
    if (strcmp(name, "push_index") == 0) {
        snapshot = MakeReady(BTB_GATE_ACTION_PUSH);
        snapshot.staged = 1U; return Blocked(&snapshot, BTB_GATE_INDEX_NOT_EMPTY);
    }
    if (strcmp(name, "push_no_ahead") == 0) {
        snapshot = MakeReady(BTB_GATE_ACTION_PUSH);
        snapshot.ahead = 0U; return Blocked(&snapshot, BTB_GATE_NO_OUTGOING_COMMIT);
    }
    if (strcmp(name, "failed_build") == 0) {
        snapshot.buildProof = BTB_GATE_PROOF_FAILED;
        return Blocked(&snapshot, BTB_GATE_BUILD_FAILED);
    }
    if (strcmp(name, "unrun_tests") == 0) {
        snapshot.testsProof = BTB_GATE_PROOF_NOT_RUN;
        return Blocked(&snapshot, BTB_GATE_TESTS_NOT_RUN);
    }
    if (strcmp(name, "failed_docs") == 0) {
        snapshot.docsProof = BTB_GATE_PROOF_FAILED;
        return Blocked(&snapshot, BTB_GATE_DOCS_FAILED);
    }
    if (strcmp(name, "dirty_child") == 0) {
        snapshot = MakeReady(BTB_GATE_ACTION_PIN);
        snapshot.childWorkingTreeClean = 0;
        return Blocked(&snapshot, BTB_GATE_CHILD_DIRTY);
    }
    if (strcmp(name, "unpublished_child") == 0) {
        snapshot = MakeReady(BTB_GATE_ACTION_PIN);
        snapshot.childCommitPublished = 0;
        return Blocked(&snapshot, BTB_GATE_CHILD_NOT_PUBLISHED);
    }
    if (strcmp(name, "mismatch_sha") == 0) {
        snapshot = MakeReady(BTB_GATE_ACTION_PIN);
        snapshot.validatedChildCommit[5] = '0';
        return Blocked(&snapshot, BTB_GATE_CHILD_SHA_MISMATCH);
    }
    if (strcmp(name, "malformed_sha") == 0) {
        snapshot = MakeReady(BTB_GATE_ACTION_PIN);
        snapshot.validatedChildCommit[2] = 'z';
        return Preserved(&snapshot);
    }
    if (strcmp(name, "malformed_input") == 0) {
        BtbGateReport unused = {0};
        if (BtbGateEvaluate(NULL, &unused) != BTB_GATE_INVALID ||
            BtbGateEvaluate(&snapshot, NULL) != BTB_GATE_INVALID) return 0;
        snapshot.onMain = -1;
        if (!Preserved(&snapshot)) return 0;
        snapshot = MakeReady(BTB_GATE_ACTION_COMMIT);
        snapshot.testsProof = (BtbGateProof)27;
        if (!Preserved(&snapshot)) return 0;
        snapshot = MakeReady(BTB_GATE_ACTION_COMMIT);
        snapshot.action = (BtbGateAction)99;
        return Preserved(&snapshot);
    }
    if (strcmp(name, "stale_snapshot") == 0) {
        snapshot.expectedObservationId = 9000U;
        return Blocked(&snapshot, BTB_GATE_STALE_SNAPSHOT);
    }
    if (strcmp(name, "pin_unrelated_stage") == 0) {
        snapshot = MakeReady(BTB_GATE_ACTION_PIN);
        snapshot.staged = 2U;
        snapshot.onlyGitlinkStaged = 0;
        return Blocked(&snapshot, BTB_GATE_GITLINK_NOT_SOLE);
    }
    if (strcmp(name, "child_tests_not_run") == 0) {
        snapshot = MakeReady(BTB_GATE_ACTION_PIN);
        snapshot.childTestsProof = BTB_GATE_PROOF_NOT_RUN;
        return Blocked(&snapshot, BTB_GATE_CHILD_TESTS_NOT_RUN);
    }
    if (strcmp(name, "child_tests_failed") == 0) {
        snapshot = MakeReady(BTB_GATE_ACTION_PIN);
        snapshot.childTestsProof = BTB_GATE_PROOF_FAILED;
        return Blocked(&snapshot, BTB_GATE_CHILD_TESTS_FAILED);
    }
    if (strcmp(name, "build_not_run") == 0) {
        snapshot.buildProof = BTB_GATE_PROOF_NOT_RUN;
        return Blocked(&snapshot, BTB_GATE_BUILD_NOT_RUN);
    }
    if (strcmp(name, "docs_not_run") == 0) {
        snapshot.docsProof = BTB_GATE_PROOF_NOT_RUN;
        return Blocked(&snapshot, BTB_GATE_DOCS_NOT_RUN);
    }
    if (strcmp(name, "tests_failed") == 0) {
        snapshot.testsProof = BTB_GATE_PROOF_FAILED;
        return Blocked(&snapshot, BTB_GATE_TESTS_FAILED);
    }
    if (strcmp(name, "malformed_unterminated_sha") == 0) {
        snapshot = MakeReady(BTB_GATE_ACTION_PIN);
        snapshot.validatedChildCommit[40] = 'f';
        return Preserved(&snapshot);
    }
    if (strcmp(name, "malformed_zero_sha") == 0) {
        snapshot = MakeReady(BTB_GATE_ACTION_PIN);
        (void)memset(snapshot.validatedChildCommit, '0', 40U);
        return Preserved(&snapshot);
    }
    if (strcmp(name, "many_issues") == 0) {
        snapshot = MakeReady(BTB_GATE_ACTION_PIN);
        snapshot.observationId = 10U;
        snapshot.onMain = 0;
        snapshot.detached = 1;
        snapshot.remoteChecked = 0;
        snapshot.divergenceKnown = 0;
        snapshot.conflicts = 4U;
        snapshot.untracked = 8U;
        snapshot.staged = 3U;
        snapshot.stagingReviewed = 0;
        snapshot.onlyGitlinkStaged = 0;
        snapshot.childWorkingTreeClean = 0;
        snapshot.childCommitPublished = 0;
        snapshot.childTestsProof = BTB_GATE_PROOF_FAILED;
        snapshot.docsProof = BTB_GATE_PROOF_NOT_RUN;
        BtbGateReport report = {0};
        return BtbGateEvaluate(&snapshot, &report) == BTB_GATE_BLOCKED &&
               report.issueCount >= 12U &&
               (report.issues & BTB_GATE_CHILD_TESTS_FAILED) != 0U &&
               strcmp(BtbGateIssueName(BTB_GATE_CHILD_TESTS_FAILED),
                      "submodule tests failed") == 0 &&
               strcmp(BtbGateIssueName(UINT64_C(1) << 50),
                      "unknown issue") == 0;
    }
    if (strcmp(name, "failure_atomic") == 0) {
        snapshot.observationId = 0U; return Preserved(&snapshot);
    }
    if (strcmp(name, "deterministic_mutations") == 0) {
        return DeterministicMutations();
    }
    return 0;
}

int main(int argc, char **argv)
{
    if (argc != 2 || !RunScenario(argv[1])) {
        (void)fprintf(stderr, "FAIL: release gate scenario %s\n",
                      argc > 1 ? argv[1] : "(missing)");
        return 1;
    }
    (void)printf("PASS: %s\n", argv[1]);
    return 0;
}
