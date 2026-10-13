/*-----------------------------------------------------------------------------
 * Bits to Banking | Umicom Foundation | Sammy Hegab | MIT
 * File: labs/native/build-evidence/evidence.c
 * PURPOSE: Deterministic bounded diagnostic comparison and evidence review.
 *
 * Architectural rationale: work with normalised records that Framework has
 * already produced; do not add another Git client or compiler-line grammar.
 * Every published result is all-or-nothing and owns its returned data.
 *---------------------------------------------------------------------------*/
#include "evidence.h"

#include <string.h>
#include <stdint.h>

static int IsBoolean(int value) { return value == 0 || value == 1; }

static int IsText(const char *text, size_t capacity, int emptyAllowed)
{
    size_t index;
    if (text == NULL || capacity == 0U) return 0;
    for (index = 0U; index < capacity; ++index) {
        unsigned char ch = (unsigned char)text[index];
        if (ch == 0U) return emptyAllowed || index > 0U;
        /* Names, paths and diagnostics must not carry terminal controls. */
        if (ch < 32U || ch == 127U) return 0;
    }
    return 0; /* Missing terminator is always a hard failure. */
}

static int ValidSha(const char *sha, size_t capacity)
{
    size_t count = 0U;
    if (sha == NULL || capacity < 65U) return 0;
    while (count < capacity && sha[count] != '\0') {
        unsigned char ch = (unsigned char)sha[count];
        if (!((ch >= (unsigned char)'0' && ch <= (unsigned char)'9') ||
              (ch >= (unsigned char)'a' && ch <= (unsigned char)'f') ||
              (ch >= (unsigned char)'A' && ch <= (unsigned char)'F'))) return 0;
        ++count;
    }
    return count < capacity && (count == 40U || count == 64U);
}

static int EqualSha(const char *left, const char *right)
{
    size_t index = 0U;
    /* Hexadecimal Git object identifiers are case-insensitive as digit
     * sequences. Do not report an uppercase rendering as a new revision. */
    for (;;) {
        unsigned char a = (unsigned char)left[index];
        unsigned char b = (unsigned char)right[index];
        if (a >= (unsigned char)'A' && a <= (unsigned char)'F')
            a = (unsigned char)(a + (unsigned char)('a' - 'A'));
        if (b >= (unsigned char)'A' && b <= (unsigned char)'F')
            b = (unsigned char)(b + (unsigned char)('a' - 'A'));
        if (a != b) return 0;
        if (a == 0U) return 1;
        ++index;
    }
}

static int ValidIdentity(const BtbEvidenceIdentity *identity)
{
    return identity != NULL &&
        ValidSha(identity->commit, sizeof identity->commit) &&
        IsText(identity->profile, sizeof identity->profile, 0) &&
        IsText(identity->toolchain, sizeof identity->toolchain, 0) &&
        identity->observationSequence != UINT64_C(0);
}

static int ValidProblem(const BtbEvidenceProblem *item)
{
    return item != NULL &&
        item->stage >= BTB_EVIDENCE_CONFIGURE &&
        item->stage <= BTB_EVIDENCE_PACKAGE &&
        item->severity >= BTB_EVIDENCE_NOTE &&
        item->severity <= BTB_EVIDENCE_FATAL &&
        IsText(item->path, sizeof item->path, 1) &&
        IsText(item->code, sizeof item->code, 1) &&
        IsText(item->message, sizeof item->message, 0);
}

static int CanAdd4(size_t a, size_t b, size_t c, size_t d)
{
    if (b > SIZE_MAX - a) return 0;
    a += b;
    if (c > SIZE_MAX - a) return 0;
    a += c;
    return d <= SIZE_MAX - a;
}

int BtbEvidenceRunValid(const BtbEvidenceRun *run)
{
    size_t i;
    if (run == NULL || !ValidIdentity(&run->identity) ||
        run->problemCount > BTB_EVIDENCE_MAX_PROBLEMS ||
        !IsBoolean(run->buildRecorded) || !IsBoolean(run->testsRecorded) ||
        !IsBoolean(run->sealed) ||
        (run->sealed && !run->buildRecorded) ||
        (run->testsRecorded && !run->buildRecorded) ||
        (!run->buildRecorded && (run->buildExitCode != 0 ||
                                 run->droppedDiagnostics != 0U)) ||
        (!run->testsRecorded &&
            (run->testsPassed != 0U || run->testsFailed != 0U ||
             run->testsSkipped != 0U || run->testsNotRun != 0U)) ||
        !CanAdd4(run->testsPassed, run->testsFailed,
                 run->testsSkipped, run->testsNotRun)) return 0;
    for (i = 0U; i < run->problemCount; ++i) {
        if (!ValidProblem(&run->problems[i])) return 0;
    }
    return 1;
}

BtbEvidenceResult BtbEvidenceRunInit(BtbEvidenceRun *out,
                                      const BtbEvidenceIdentity *identity)
{
    BtbEvidenceRun prepared = {0};
    if (out == NULL || !ValidIdentity(identity)) return BTB_EVIDENCE_INVALID;
    prepared.identity = *identity;
    *out = prepared;
    return BTB_EVIDENCE_OK;
}

BtbEvidenceResult BtbEvidenceAddProblem(BtbEvidenceRun *run,
                                        const BtbEvidenceProblem *problem)
{
    if (!BtbEvidenceRunValid(run) || !ValidProblem(problem))
        return BTB_EVIDENCE_INVALID;
    if (run->sealed || run->buildRecorded) return BTB_EVIDENCE_LOCKED;
    if (run->problemCount == BTB_EVIDENCE_MAX_PROBLEMS) return BTB_EVIDENCE_FULL;
    /* This is a copy. The original Framework diagnostic may now be freed. */
    run->problems[run->problemCount] = *problem;
    ++run->problemCount;
    return BTB_EVIDENCE_OK;
}

BtbEvidenceResult BtbEvidenceRecordBuild(BtbEvidenceRun *run,
                                         int processExitCode, size_t dropped)
{
    if (!BtbEvidenceRunValid(run) || processExitCode < 0)
        return BTB_EVIDENCE_INVALID;
    if (run->sealed || run->buildRecorded) return BTB_EVIDENCE_LOCKED;
    run->buildExitCode = processExitCode;
    run->droppedDiagnostics = dropped;
    run->buildRecorded = 1;
    return BTB_EVIDENCE_OK;
}

BtbEvidenceResult BtbEvidenceRecordTests(BtbEvidenceRun *run, size_t passed,
                                         size_t failed, size_t skipped,
                                         size_t notRun)
{
    if (!BtbEvidenceRunValid(run) ||
        !CanAdd4(passed, failed, skipped, notRun)) return BTB_EVIDENCE_INVALID;
    if (!run->buildRecorded) return BTB_EVIDENCE_INVALID;
    if (run->sealed || run->testsRecorded) return BTB_EVIDENCE_LOCKED;
    run->testsPassed = passed;
    run->testsFailed = failed;
    run->testsSkipped = skipped;
    run->testsNotRun = notRun;
    run->testsRecorded = 1;
    return BTB_EVIDENCE_OK;
}

BtbEvidenceResult BtbEvidenceSeal(BtbEvidenceRun *run)
{
    if (!BtbEvidenceRunValid(run) || !run->buildRecorded)
        return BTB_EVIDENCE_INVALID;
    if (run->sealed) return BTB_EVIDENCE_LOCKED;
    run->sealed = 1;
    return BTB_EVIDENCE_OK;
}

static int EqualProblem(const BtbEvidenceProblem *left,
                        const BtbEvidenceProblem *right)
{
    return left->stage == right->stage &&
           left->severity == right->severity &&
           left->line == right->line &&
           left->column == right->column &&
           strcmp(left->path, right->path) == 0 &&
           strcmp(left->code, right->code) == 0 &&
           strcmp(left->message, right->message) == 0;
}

BtbEvidenceResult BtbEvidenceAssess(const BtbEvidenceRun *run,
    const char *expectedCommit, const char *expectedProfile,
    size_t allowedWarnings, BtbEvidenceAssessment *out)
{
    BtbEvidenceAssessment candidate = {0};
    size_t i;
    if (!BtbEvidenceRunValid(run) || !run->sealed || out == NULL ||
        !ValidSha(expectedCommit, BTB_EVIDENCE_SHA_CAPACITY) ||
        !IsText(expectedProfile, BTB_EVIDENCE_NAME_CAPACITY, 0))
        return BTB_EVIDENCE_INVALID;
    if (!EqualSha(run->identity.commit, expectedCommit))
        candidate.reviewFlags |= BTB_REVIEW_STALE_REVISION;
    if (strcmp(run->identity.profile, expectedProfile) != 0)
        candidate.reviewFlags |= BTB_REVIEW_PROFILE_MISMATCH;
    if (run->buildExitCode != 0)
        candidate.reviewFlags |= BTB_REVIEW_BUILD_FAILURE;
    if (run->droppedDiagnostics != 0U)
        candidate.reviewFlags |= BTB_REVIEW_DROPPED_DIAGNOSTICS;
    if (!run->testsRecorded ||
        (run->testsPassed == 0U && run->testsFailed == 0U &&
         run->testsSkipped == 0U && run->testsNotRun == 0U))
        candidate.reviewFlags |= BTB_REVIEW_TESTS_MISSING;
    if (run->testsRecorded && run->testsFailed != 0U)
        candidate.reviewFlags |= BTB_REVIEW_TESTS_FAILED;
    if (run->testsRecorded && run->testsNotRun != 0U)
        candidate.reviewFlags |= BTB_REVIEW_TESTS_NOT_RUN;
    if (run->testsRecorded && run->testsSkipped != 0U)
        candidate.reviewFlags |= BTB_REVIEW_TESTS_SKIPPED;
    for (i = 0U; i < run->problemCount; ++i) {
        const BtbEvidenceProblem *p = &run->problems[i];
        if (p->severity == BTB_EVIDENCE_FATAL) ++candidate.fatals;
        else if (p->severity == BTB_EVIDENCE_ERROR) ++candidate.errors;
        else if (p->severity == BTB_EVIDENCE_WARNING) ++candidate.warnings;
        else ++candidate.notes;
        if (p->severity >= BTB_EVIDENCE_ERROR &&
            (candidate.earliestErrorStage == 0 ||
             p->stage < candidate.earliestErrorStage))
            candidate.earliestErrorStage = p->stage;
    }
    if (candidate.errors != 0U || candidate.fatals != 0U)
        candidate.reviewFlags |= BTB_REVIEW_COMPILER_ERRORS;
    if (candidate.warnings > allowedWarnings)
        candidate.reviewFlags |= BTB_REVIEW_WARNING_BUDGET;
    candidate.readyForHumanReview = candidate.reviewFlags == 0U;
    *out = candidate;
    return BTB_EVIDENCE_OK;
}

BtbEvidenceResult BtbEvidenceCompare(const BtbEvidenceRun *previous,
                                     const BtbEvidenceRun *current,
                                     BtbEvidenceComparison *out)
{
    BtbEvidenceComparison candidate = {0};
    unsigned char matchedPrevious[BTB_EVIDENCE_MAX_PROBLEMS] = {0};
    size_t i, j;
    if (!BtbEvidenceRunValid(previous) || !BtbEvidenceRunValid(current) ||
        !previous->sealed || !current->sealed || out == NULL)
        return BTB_EVIDENCE_INVALID;
    if (strcmp(previous->identity.profile, current->identity.profile) != 0 ||
        strcmp(previous->identity.toolchain, current->identity.toolchain) != 0)
        return BTB_EVIDENCE_INCOMPARABLE;
    candidate.previousProblems = previous->problemCount;
    candidate.currentProblems = current->problemCount;
    candidate.currentEvidenceIncomplete = !current->testsRecorded ||
        current->droppedDiagnostics != 0U ||
        current->testsSkipped != 0U ||
        current->testsNotRun != 0U ||
        current->testsFailed != 0U ||
        (current->testsPassed == 0U && current->testsFailed == 0U &&
         current->testsSkipped == 0U && current->testsNotRun == 0U);
    for (i = 0U; i < current->problemCount; ++i) {
        int found = 0;
        const BtbEvidenceProblem *p = &current->problems[i];
        if (p->severity >= BTB_EVIDENCE_ERROR &&
            (candidate.earliestCurrentErrorStage == 0 ||
             p->stage < candidate.earliestCurrentErrorStage))
            candidate.earliestCurrentErrorStage = p->stage;
        for (j = 0U; j < previous->problemCount; ++j) {
            if (matchedPrevious[j] == 0U &&
                EqualProblem(p, &previous->problems[j])) {
                matchedPrevious[j] = 1U;
                found = 1;
                break;
            }
        }
        if (found) ++candidate.persisting;
        else {
            ++candidate.introduced;
            if (p->severity >= BTB_EVIDENCE_ERROR) ++candidate.introducedErrors;
        }
    }
    for (j = 0U; j < previous->problemCount; ++j) {
        if (matchedPrevious[j] == 0U) {
            ++candidate.resolved;
            if (previous->problems[j].severity >= BTB_EVIDENCE_ERROR)
                ++candidate.resolvedErrors;
        }
    }
    *out = candidate;
    return BTB_EVIDENCE_OK;
}

const char *BtbEvidenceResultText(BtbEvidenceResult value)
{
    switch (value) {
        case BTB_EVIDENCE_OK: return "OK";
        case BTB_EVIDENCE_INVALID: return "INVALID";
        case BTB_EVIDENCE_FULL: return "FULL";
        case BTB_EVIDENCE_LOCKED: return "LOCKED";
        case BTB_EVIDENCE_INCOMPARABLE: return "INCOMPARABLE";
        default: return "UNKNOWN";
    }
}

const char *BtbEvidenceStageText(BtbEvidenceStage value)
{
    switch (value) {
        case BTB_EVIDENCE_CONFIGURE: return "configure";
        case BTB_EVIDENCE_COMPILE: return "compile";
        case BTB_EVIDENCE_LINK: return "link";
        case BTB_EVIDENCE_TEST: return "test";
        case BTB_EVIDENCE_PACKAGE: return "package";
        default: return "unknown";
    }
}
