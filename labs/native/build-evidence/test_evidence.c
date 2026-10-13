/*-----------------------------------------------------------------------------
 * Bits to Banking | Umicom Foundation | Sammy Hegab | MIT
 * File: labs/native/build-evidence/test_evidence.c
 * PURPOSE: Named native C23 regression and negative-boundary tests.
 *---------------------------------------------------------------------------*/
#include "evidence.h"
#include <stdint.h>
#include <stdio.h>
#include <string.h>

#define CHECK(expression) do { if (!(expression)) { \
    fprintf(stderr, "%s:%d: failed: %s\n", __FILE__, __LINE__, #expression); \
    return 1; } } while (0)
#define OK(expression) CHECK((expression) == BTB_EVIDENCE_OK)
#define SHA_A "0123456789abcdef0123456789abcdef01234567"
#define SHA_B "abcdef0123456789abcdef0123456789abcdef01"
#define SHA_256 "abcdef0123456789abcdef0123456789abcdef0123456789abcdef0123456789"

static BtbEvidenceIdentity MakeId(void)
{
    BtbEvidenceIdentity identity = {0};
    (void)snprintf(identity.commit, sizeof identity.commit, "%s", SHA_A);
    (void)snprintf(identity.profile, sizeof identity.profile, "%s", "windows-ucrt64-all-debug");
    (void)snprintf(identity.toolchain, sizeof identity.toolchain, "%s", "gcc-16.1-ucrt64");
    identity.observationSequence = 1U;
    return identity;
}

static BtbEvidenceProblem MakeProblem(void)
{
    BtbEvidenceProblem value = {0};
    value.stage = BTB_EVIDENCE_COMPILE;
    value.severity = BTB_EVIDENCE_WARNING;
    value.line = 16U;
    value.column = 4U;
    (void)snprintf(value.path, sizeof value.path, "%s", "framework/src/notes.c");
    (void)snprintf(value.code, sizeof value.code, "%s", "-Wshadow");
    (void)snprintf(value.message, sizeof value.message, "%s", "fictional shadowed variable");
    return value;
}

static int CleanRun(BtbEvidenceRun *run)
{
    BtbEvidenceIdentity identity = MakeId();
    if (BtbEvidenceRunInit(run, &identity) != BTB_EVIDENCE_OK ||
        BtbEvidenceRecordBuild(run, 0, 0U) != BTB_EVIDENCE_OK ||
        BtbEvidenceRecordTests(run, 12U, 0U, 0U, 0U) != BTB_EVIDENCE_OK ||
        BtbEvidenceSeal(run) != BTB_EVIDENCE_OK) return 0;
    return 1;
}

static int Review(const BtbEvidenceRun *run, size_t budget,
                  BtbEvidenceAssessment *out)
{
    return BtbEvidenceAssess(run, SHA_A, "windows-ucrt64-all-debug", budget, out)
        == BTB_EVIDENCE_OK;
}

static int TestCase(const char *name)
{
    BtbEvidenceRun run = {0}, previous = {0};
    BtbEvidenceIdentity id = MakeId();
    BtbEvidenceProblem item = MakeProblem();
    BtbEvidenceAssessment assessment = {0};
    BtbEvidenceComparison comparison = {0};
    BtbEvidenceRun snapshot = {0};
    size_t i;

    if (strcmp(name, "sha40") == 0) {
        OK(BtbEvidenceRunInit(&run, &id)); CHECK(BtbEvidenceRunValid(&run));
    } else if (strcmp(name, "sha256") == 0) {
        (void)snprintf(id.commit, sizeof id.commit, "%s", SHA_256);
        OK(BtbEvidenceRunInit(&run, &id)); CHECK(BtbEvidenceRunValid(&run));
    } else if (strcmp(name, "sha_uppercase") == 0) {
        (void)snprintf(id.commit, sizeof id.commit, "%s", "ABCDEF0123456789ABCDEF0123456789ABCDEF01");
        OK(BtbEvidenceRunInit(&run, &id));
    } else if (strcmp(name, "sha_short_rejected") == 0) {
        (void)snprintf(id.commit, sizeof id.commit, "%s", "1234567");
        CHECK(BtbEvidenceRunInit(&run, &id) == BTB_EVIDENCE_INVALID);
    } else if (strcmp(name, "sha_nonhex_rejected") == 0) {
        id.commit[8] = 'x';
        CHECK(BtbEvidenceRunInit(&run, &id) == BTB_EVIDENCE_INVALID);
    } else if (strcmp(name, "sha_unterminated_rejected") == 0) {
        (void)memset(id.commit, 'f', sizeof id.commit);
        CHECK(BtbEvidenceRunInit(&run, &id) == BTB_EVIDENCE_INVALID);
    } else if (strcmp(name, "identity_requires_profile") == 0) {
        id.profile[0] = '\0';
        CHECK(BtbEvidenceRunInit(&run, &id) == BTB_EVIDENCE_INVALID);
    } else if (strcmp(name, "identity_requires_toolchain") == 0) {
        id.toolchain[0] = '\0';
        CHECK(BtbEvidenceRunInit(&run, &id) == BTB_EVIDENCE_INVALID);
    } else if (strcmp(name, "identity_requires_sequence") == 0) {
        id.observationSequence = 0U;
        CHECK(BtbEvidenceRunInit(&run, &id) == BTB_EVIDENCE_INVALID);
    } else if (strcmp(name, "identity_rejects_controls") == 0) {
        id.profile[4] = '\n';
        CHECK(BtbEvidenceRunInit(&run, &id) == BTB_EVIDENCE_INVALID);
    } else if (strcmp(name, "init_failure_atomic") == 0) {
        (void)memset(&run, 0x31, sizeof run);
        snapshot = run; id.profile[0] = '\0';
        CHECK(BtbEvidenceRunInit(&run, &id) == BTB_EVIDENCE_INVALID);
        CHECK(memcmp(&run, &snapshot, sizeof run) == 0);
    } else if (strcmp(name, "copied_problem_ownership") == 0) {
        OK(BtbEvidenceRunInit(&run, &id));
        OK(BtbEvidenceAddProblem(&run, &item));
        item.message[0] = 'X';
        CHECK(run.problems[0].message[0] == 'f');
    } else if (strcmp(name, "invalid_stage_atomic") == 0) {
        OK(BtbEvidenceRunInit(&run, &id)); snapshot = run;
        item.stage = (BtbEvidenceStage)0;
        CHECK(BtbEvidenceAddProblem(&run, &item) == BTB_EVIDENCE_INVALID);
        CHECK(memcmp(&run, &snapshot, sizeof run) == 0);
    } else if (strcmp(name, "invalid_severity_atomic") == 0) {
        OK(BtbEvidenceRunInit(&run, &id)); snapshot = run;
        item.severity = (BtbEvidenceSeverity)9;
        CHECK(BtbEvidenceAddProblem(&run, &item) == BTB_EVIDENCE_INVALID);
        CHECK(memcmp(&run, &snapshot, sizeof run) == 0);
    } else if (strcmp(name, "unterminated_message_atomic") == 0) {
        OK(BtbEvidenceRunInit(&run, &id)); snapshot = run;
        (void)memset(item.message, 'x', sizeof item.message);
        CHECK(BtbEvidenceAddProblem(&run, &item) == BTB_EVIDENCE_INVALID);
        CHECK(memcmp(&run, &snapshot, sizeof run) == 0);
    } else if (strcmp(name, "control_character_atomic") == 0) {
        OK(BtbEvidenceRunInit(&run, &id)); snapshot = run;
        item.message[5] = '\r';
        CHECK(BtbEvidenceAddProblem(&run, &item) == BTB_EVIDENCE_INVALID);
        CHECK(memcmp(&run, &snapshot, sizeof run) == 0);
    } else if (strcmp(name, "capacity_exact") == 0) {
        OK(BtbEvidenceRunInit(&run, &id));
        for (i = 0U; i < BTB_EVIDENCE_MAX_PROBLEMS; ++i) {
            item.line = i + 1U; OK(BtbEvidenceAddProblem(&run, &item));
        }
        CHECK(run.problemCount == BTB_EVIDENCE_MAX_PROBLEMS);
    } else if (strcmp(name, "full_failure_atomic") == 0) {
        OK(BtbEvidenceRunInit(&run, &id));
        for (i = 0U; i < BTB_EVIDENCE_MAX_PROBLEMS; ++i) OK(BtbEvidenceAddProblem(&run, &item));
        snapshot = run;
        CHECK(BtbEvidenceAddProblem(&run, &item) == BTB_EVIDENCE_FULL);
        CHECK(memcmp(&run, &snapshot, sizeof run) == 0);
    } else if (strcmp(name, "tests_before_build_refused") == 0) {
        OK(BtbEvidenceRunInit(&run, &id)); snapshot = run;
        CHECK(BtbEvidenceRecordTests(&run, 1U, 0U, 0U, 0U) == BTB_EVIDENCE_INVALID);
        CHECK(memcmp(&run, &snapshot, sizeof run) == 0);
    } else if (strcmp(name, "negative_exit_rejected") == 0) {
        OK(BtbEvidenceRunInit(&run, &id)); snapshot = run;
        CHECK(BtbEvidenceRecordBuild(&run, -1, 0U) == BTB_EVIDENCE_INVALID);
        CHECK(memcmp(&run, &snapshot, sizeof run) == 0);
    } else if (strcmp(name, "build_recorded_once") == 0) {
        OK(BtbEvidenceRunInit(&run, &id));
        OK(BtbEvidenceRecordBuild(&run, 1, 0U)); snapshot = run;
        CHECK(BtbEvidenceRecordBuild(&run, 0, 0U) == BTB_EVIDENCE_LOCKED);
        CHECK(memcmp(&run, &snapshot, sizeof run) == 0);
    } else if (strcmp(name, "problems_locked_after_build") == 0) {
        OK(BtbEvidenceRunInit(&run, &id));
        OK(BtbEvidenceRecordBuild(&run, 0, 0U)); snapshot = run;
        CHECK(BtbEvidenceAddProblem(&run, &item) == BTB_EVIDENCE_LOCKED);
        CHECK(memcmp(&run, &snapshot, sizeof run) == 0);
    } else if (strcmp(name, "tests_sum_overflow") == 0) {
        OK(BtbEvidenceRunInit(&run, &id));
        OK(BtbEvidenceRecordBuild(&run, 0, 0U)); snapshot = run;
        CHECK(BtbEvidenceRecordTests(&run, SIZE_MAX, 1U, 0U, 0U) == BTB_EVIDENCE_INVALID);
        CHECK(memcmp(&run, &snapshot, sizeof run) == 0);
    } else if (strcmp(name, "tests_recorded_once") == 0) {
        OK(BtbEvidenceRunInit(&run, &id));
        OK(BtbEvidenceRecordBuild(&run, 0, 0U));
        OK(BtbEvidenceRecordTests(&run, 1U, 0U, 0U, 0U)); snapshot = run;
        CHECK(BtbEvidenceRecordTests(&run, 2U, 0U, 0U, 0U) == BTB_EVIDENCE_LOCKED);
        CHECK(memcmp(&run, &snapshot, sizeof run) == 0);
    } else if (strcmp(name, "seal_requires_build") == 0) {
        OK(BtbEvidenceRunInit(&run, &id)); snapshot = run;
        CHECK(BtbEvidenceSeal(&run) == BTB_EVIDENCE_INVALID);
        CHECK(memcmp(&run, &snapshot, sizeof run) == 0);
    } else if (strcmp(name, "seal_once") == 0) {
        CHECK(CleanRun(&run)); snapshot = run;
        CHECK(BtbEvidenceSeal(&run) == BTB_EVIDENCE_LOCKED);
        CHECK(memcmp(&run, &snapshot, sizeof run) == 0);
    } else if (strcmp(name, "assessment_clean") == 0) {
        CHECK(CleanRun(&run)); CHECK(Review(&run, 0U, &assessment));
        CHECK(assessment.readyForHumanReview == 1 && assessment.reviewFlags == 0U);
    } else if (strcmp(name, "assessment_missing_tests") == 0) {
        OK(BtbEvidenceRunInit(&run, &id)); OK(BtbEvidenceRecordBuild(&run, 0, 0U));
        OK(BtbEvidenceSeal(&run)); CHECK(Review(&run, 0U, &assessment));
        CHECK(assessment.reviewFlags & BTB_REVIEW_TESTS_MISSING);
    } else if (strcmp(name, "assessment_zero_tests") == 0) {
        OK(BtbEvidenceRunInit(&run, &id)); OK(BtbEvidenceRecordBuild(&run, 0, 0U));
        OK(BtbEvidenceRecordTests(&run, 0U, 0U, 0U, 0U)); OK(BtbEvidenceSeal(&run));
        CHECK(Review(&run, 0U, &assessment));
        CHECK(assessment.reviewFlags & BTB_REVIEW_TESTS_MISSING);
    } else if (strcmp(name, "assessment_dropped") == 0) {
        OK(BtbEvidenceRunInit(&run, &id)); OK(BtbEvidenceRecordBuild(&run, 0, 4U));
        OK(BtbEvidenceRecordTests(&run, 2U, 0U, 0U, 0U)); OK(BtbEvidenceSeal(&run));
        CHECK(Review(&run, 0U, &assessment));
        CHECK(assessment.reviewFlags & BTB_REVIEW_DROPPED_DIAGNOSTICS);
    } else if (strcmp(name, "assessment_build_failed") == 0) {
        OK(BtbEvidenceRunInit(&run, &id)); OK(BtbEvidenceRecordBuild(&run, 5, 0U));
        OK(BtbEvidenceSeal(&run)); CHECK(Review(&run, 0U, &assessment));
        CHECK(assessment.reviewFlags & BTB_REVIEW_BUILD_FAILURE);
    } else if (strcmp(name, "assessment_compiler_error") == 0) {
        item.severity = BTB_EVIDENCE_ERROR; OK(BtbEvidenceRunInit(&run, &id));
        OK(BtbEvidenceAddProblem(&run, &item)); OK(BtbEvidenceRecordBuild(&run, 0, 0U));
        OK(BtbEvidenceRecordTests(&run, 1U, 0U, 0U, 0U)); OK(BtbEvidenceSeal(&run));
        CHECK(Review(&run, 0U, &assessment));
        CHECK(assessment.reviewFlags & BTB_REVIEW_COMPILER_ERRORS);
    } else if (strcmp(name, "assessment_warning_budget") == 0) {
        OK(BtbEvidenceRunInit(&run, &id)); OK(BtbEvidenceAddProblem(&run, &item));
        OK(BtbEvidenceRecordBuild(&run, 0, 0U));
        OK(BtbEvidenceRecordTests(&run, 1U, 0U, 0U, 0U)); OK(BtbEvidenceSeal(&run));
        CHECK(Review(&run, 0U, &assessment));
        CHECK(assessment.reviewFlags & BTB_REVIEW_WARNING_BUDGET);
        CHECK(Review(&run, 1U, &assessment)); CHECK(assessment.reviewFlags == 0U);
    } else if (strcmp(name, "assessment_failed_tests") == 0) {
        OK(BtbEvidenceRunInit(&run, &id)); OK(BtbEvidenceRecordBuild(&run, 0, 0U));
        OK(BtbEvidenceRecordTests(&run, 1U, 1U, 0U, 0U)); OK(BtbEvidenceSeal(&run));
        CHECK(Review(&run, 0U, &assessment));
        CHECK(assessment.reviewFlags & BTB_REVIEW_TESTS_FAILED);
    } else if (strcmp(name, "assessment_not_run_tests") == 0) {
        OK(BtbEvidenceRunInit(&run, &id)); OK(BtbEvidenceRecordBuild(&run, 0, 0U));
        OK(BtbEvidenceRecordTests(&run, 1U, 0U, 0U, 1U)); OK(BtbEvidenceSeal(&run));
        CHECK(Review(&run, 0U, &assessment));
        CHECK(assessment.reviewFlags & BTB_REVIEW_TESTS_NOT_RUN);
    } else if (strcmp(name, "assessment_skipped_tests") == 0) {
        OK(BtbEvidenceRunInit(&run, &id)); OK(BtbEvidenceRecordBuild(&run, 0, 0U));
        OK(BtbEvidenceRecordTests(&run, 1U, 0U, 1U, 0U)); OK(BtbEvidenceSeal(&run));
        CHECK(Review(&run, 0U, &assessment));
        CHECK(assessment.reviewFlags & BTB_REVIEW_TESTS_SKIPPED);
    } else if (strcmp(name, "assessment_all_skipped") == 0) {
        OK(BtbEvidenceRunInit(&run, &id)); OK(BtbEvidenceRecordBuild(&run, 0, 0U));
        OK(BtbEvidenceRecordTests(&run, 0U, 0U, 12U, 0U)); OK(BtbEvidenceSeal(&run));
        CHECK(Review(&run, 0U, &assessment));
        CHECK(!assessment.readyForHumanReview);
        CHECK(assessment.reviewFlags & BTB_REVIEW_TESTS_SKIPPED);
    } else if (strcmp(name, "assessment_stale_sha") == 0) {
        CHECK(CleanRun(&run));
        OK(BtbEvidenceAssess(&run, SHA_B, run.identity.profile, 0U, &assessment));
        CHECK(assessment.reviewFlags & BTB_REVIEW_STALE_REVISION);
    } else if (strcmp(name, "assessment_uppercase_sha_equivalent") == 0) {
        CHECK(CleanRun(&run));
        OK(BtbEvidenceAssess(&run,
          "0123456789ABCDEF0123456789ABCDEF01234567",
          run.identity.profile, 0U, &assessment));
        CHECK((assessment.reviewFlags & BTB_REVIEW_STALE_REVISION) == 0U);
    } else if (strcmp(name, "assessment_other_profile") == 0) {
        CHECK(CleanRun(&run));
        OK(BtbEvidenceAssess(&run, SHA_A, "headless-debug", 0U, &assessment));
        CHECK(assessment.reviewFlags & BTB_REVIEW_PROFILE_MISMATCH);
    } else if (strcmp(name, "assessment_earliest_stage") == 0) {
        OK(BtbEvidenceRunInit(&run, &id));
        item.stage = BTB_EVIDENCE_LINK; item.severity = BTB_EVIDENCE_FATAL;
        OK(BtbEvidenceAddProblem(&run, &item));
        item.stage = BTB_EVIDENCE_CONFIGURE; item.severity = BTB_EVIDENCE_ERROR;
        OK(BtbEvidenceAddProblem(&run, &item));
        OK(BtbEvidenceRecordBuild(&run, 1, 0U)); OK(BtbEvidenceSeal(&run));
        CHECK(Review(&run, 0U, &assessment));
        CHECK(assessment.earliestErrorStage == BTB_EVIDENCE_CONFIGURE);
    } else if (strcmp(name, "assessment_invalid_output_atomic") == 0) {
        CHECK(CleanRun(&run));
        (void)memset(&assessment, 0x5a, sizeof assessment);
        BtbEvidenceAssessment prior = assessment;
        CHECK(BtbEvidenceAssess(&run, "bad", run.identity.profile, 0U, &assessment)
              == BTB_EVIDENCE_INVALID);
        CHECK(memcmp(&assessment, &prior, sizeof assessment) == 0);
    } else if (strcmp(name, "compare_resolved") == 0) {
        OK(BtbEvidenceRunInit(&previous, &id)); OK(BtbEvidenceAddProblem(&previous, &item));
        OK(BtbEvidenceRecordBuild(&previous, 0, 0U)); OK(BtbEvidenceSeal(&previous));
        CHECK(CleanRun(&run)); OK(BtbEvidenceCompare(&previous, &run, &comparison));
        CHECK(comparison.resolved == 1U && comparison.introduced == 0U);
    } else if (strcmp(name, "compare_introduced") == 0) {
        CHECK(CleanRun(&previous)); OK(BtbEvidenceRunInit(&run, &id));
        OK(BtbEvidenceAddProblem(&run, &item)); OK(BtbEvidenceRecordBuild(&run, 0, 0U));
        OK(BtbEvidenceSeal(&run)); OK(BtbEvidenceCompare(&previous, &run, &comparison));
        CHECK(comparison.introduced == 1U && comparison.resolved == 0U);
    } else if (strcmp(name, "compare_persisting") == 0) {
        OK(BtbEvidenceRunInit(&previous, &id)); OK(BtbEvidenceAddProblem(&previous, &item));
        OK(BtbEvidenceRecordBuild(&previous, 0, 0U)); OK(BtbEvidenceSeal(&previous));
        run = previous; run.identity.observationSequence = 2U;
        OK(BtbEvidenceCompare(&previous, &run, &comparison));
        CHECK(comparison.persisting == 1U && comparison.resolved == 0U);
    } else if (strcmp(name, "compare_duplicate_multiset") == 0) {
        OK(BtbEvidenceRunInit(&previous, &id)); OK(BtbEvidenceAddProblem(&previous, &item));
        OK(BtbEvidenceAddProblem(&previous, &item));
        OK(BtbEvidenceRecordBuild(&previous, 0, 0U)); OK(BtbEvidenceSeal(&previous));
        run = previous; run.problemCount = 1U;
        OK(BtbEvidenceCompare(&previous, &run, &comparison));
        CHECK(comparison.persisting == 1U && comparison.resolved == 1U);
    } else if (strcmp(name, "compare_line_shift") == 0) {
        OK(BtbEvidenceRunInit(&previous, &id)); OK(BtbEvidenceAddProblem(&previous, &item));
        OK(BtbEvidenceRecordBuild(&previous, 0, 0U)); OK(BtbEvidenceSeal(&previous));
        OK(BtbEvidenceRunInit(&run, &id)); item.line = 99U;
        OK(BtbEvidenceAddProblem(&run, &item));
        OK(BtbEvidenceRecordBuild(&run, 0, 0U)); OK(BtbEvidenceSeal(&run));
        OK(BtbEvidenceCompare(&previous, &run, &comparison));
        CHECK(comparison.introduced == 1U && comparison.resolved == 1U);
    } else if (strcmp(name, "compare_profile_refused") == 0) {
        CHECK(CleanRun(&previous)); run = previous;
        (void)snprintf(run.identity.profile, sizeof run.identity.profile, "%s", "gtk4-debug");
        CHECK(BtbEvidenceCompare(&previous, &run, &comparison) == BTB_EVIDENCE_INCOMPARABLE);
    } else if (strcmp(name, "compare_toolchain_refused") == 0) {
        CHECK(CleanRun(&previous)); run = previous;
        (void)snprintf(run.identity.toolchain, sizeof run.identity.toolchain, "%s", "clang-21");
        CHECK(BtbEvidenceCompare(&previous, &run, &comparison) == BTB_EVIDENCE_INCOMPARABLE);
    } else if (strcmp(name, "compare_invalid_atomic") == 0) {
        CHECK(CleanRun(&previous)); CHECK(CleanRun(&run));
        run.problems[0].stage = BTB_EVIDENCE_CONFIGURE; run.problemCount = 1U;
        (void)memset(&comparison, 0x5a, sizeof comparison);
        const BtbEvidenceComparison saved = comparison;
        CHECK(BtbEvidenceCompare(&previous, &run, &comparison) == BTB_EVIDENCE_INVALID);
        CHECK(memcmp(&comparison, &saved, sizeof comparison) == 0);
    } else if (strcmp(name, "compare_incomplete_current") == 0) {
        CHECK(CleanRun(&previous)); OK(BtbEvidenceRunInit(&run, &id));
        OK(BtbEvidenceRecordBuild(&run, 0, 1U)); OK(BtbEvidenceSeal(&run));
        OK(BtbEvidenceCompare(&previous, &run, &comparison));
        CHECK(comparison.currentEvidenceIncomplete);
    } else if (strcmp(name, "compare_skipped_current") == 0) {
        CHECK(CleanRun(&previous)); OK(BtbEvidenceRunInit(&run, &id));
        OK(BtbEvidenceRecordBuild(&run, 0, 0U));
        OK(BtbEvidenceRecordTests(&run, 4U, 0U, 1U, 0U));
        OK(BtbEvidenceSeal(&run));
        OK(BtbEvidenceCompare(&previous, &run, &comparison));
        CHECK(comparison.currentEvidenceIncomplete);
    } else if (strcmp(name, "tamper_sealed_without_build") == 0) {
        OK(BtbEvidenceRunInit(&run, &id)); run.sealed = 1;
        CHECK(!BtbEvidenceRunValid(&run));
    } else if (strcmp(name, "tamper_invalid_problem") == 0) {
        OK(BtbEvidenceRunInit(&run, &id)); OK(BtbEvidenceAddProblem(&run, &item));
        run.problems[0].severity = (BtbEvidenceSeverity)9;
        CHECK(!BtbEvidenceRunValid(&run));
    } else if (strcmp(name, "mutation_50000") == 0) {
        uint32_t value = UINT32_C(0x9e3779b9);
        for (i = 0U; i < 50000U; ++i) {
            BtbEvidenceRun ephemeral = {0};
            BtbEvidenceAssessment check = {0};
            BtbEvidenceProblem entry = MakeProblem();
            value ^= value << 13; value ^= value >> 17; value ^= value << 5;
            CHECK(CleanRun(&ephemeral));
            CHECK(Review(&ephemeral, 0U, &check));
            CHECK(check.reviewFlags == 0U);
            /* Creating a defective copy must not mutate the valid source. */
            BtbEvidenceRun modified = ephemeral;
            modified.identity.commit[0] = 'z';
            CHECK(!BtbEvidenceRunValid(&modified));
            CHECK(BtbEvidenceRunValid(&ephemeral));
            if ((value & 3U) == 0U) {
                BtbEvidenceRun other = ephemeral;
                BtbEvidenceComparison diff;
                entry.line = (size_t)(value % 1000U) + 1U;
                other.sealed = 0; other.buildRecorded = 0; other.testsRecorded = 0;
                other.testsPassed = 0U;
                OK(BtbEvidenceAddProblem(&other, &entry));
                OK(BtbEvidenceRecordBuild(&other, 0, 0U));
                OK(BtbEvidenceSeal(&other));
                OK(BtbEvidenceCompare(&ephemeral, &other, &diff));
                CHECK(diff.introduced == 1U && diff.resolved == 0U);
            }
        }
    } else {
        fprintf(stderr, "Unknown test case: %s\n", name);
        return 2;
    }
    return 0;
}

int main(int argc, char **argv)
{
    return argc == 2 ? TestCase(argv[1]) : 2;
}
