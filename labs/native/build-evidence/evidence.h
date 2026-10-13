/*-----------------------------------------------------------------------------
 * Bits to Banking | Umicom Foundation | Sammy Hegab | MIT
 * File: labs/native/build-evidence/evidence.h
 * PURPOSE: Bounded C23 review of already-normalised build and test evidence.
 *
 * ARCHITECTURE:
 *   The canonical Umicom Framework owns Git inspection, compiler diagnostic
 *   parsing, build execution and test execution. This educational component
 *   consumes copied facts. It does NOT parse Git or compiler output, launch
 *   tools, change repositories, stage commits or certify production releases.
 *---------------------------------------------------------------------------*/
#ifndef BTB_BUILD_EVIDENCE_H
#define BTB_BUILD_EVIDENCE_H

#include <stddef.h>
#include <stdint.h>

#define BTB_EVIDENCE_MAX_PROBLEMS 24U
#define BTB_EVIDENCE_SHA_CAPACITY 65U
#define BTB_EVIDENCE_NAME_CAPACITY 80U
#define BTB_EVIDENCE_PATH_CAPACITY 256U
#define BTB_EVIDENCE_CODE_CAPACITY 64U
#define BTB_EVIDENCE_MESSAGE_CAPACITY 256U

typedef enum BtbEvidenceResult {
    BTB_EVIDENCE_OK = 0,
    BTB_EVIDENCE_INVALID,
    BTB_EVIDENCE_FULL,
    BTB_EVIDENCE_LOCKED,
    BTB_EVIDENCE_INCOMPARABLE
} BtbEvidenceResult;

typedef enum BtbEvidenceStage {
    BTB_EVIDENCE_CONFIGURE = 1,
    BTB_EVIDENCE_COMPILE = 2,
    BTB_EVIDENCE_LINK = 3,
    BTB_EVIDENCE_TEST = 4,
    BTB_EVIDENCE_PACKAGE = 5
} BtbEvidenceStage;

typedef enum BtbEvidenceSeverity {
    BTB_EVIDENCE_NOTE = 0,
    BTB_EVIDENCE_WARNING = 1,
    BTB_EVIDENCE_ERROR = 2,
    BTB_EVIDENCE_FATAL = 3
} BtbEvidenceSeverity;

typedef struct BtbEvidenceIdentity {
    /* 40-hex SHA-1 or 64-hex SHA-256, never an abbreviated commit hash. */
    char commit[BTB_EVIDENCE_SHA_CAPACITY];
    char profile[BTB_EVIDENCE_NAME_CAPACITY];
    char toolchain[BTB_EVIDENCE_NAME_CAPACITY];
    uint64_t observationSequence; /* supplied by owner; not a timestamp */
} BtbEvidenceIdentity;

typedef struct BtbEvidenceProblem {
    BtbEvidenceStage stage;
    BtbEvidenceSeverity severity;
    size_t line;   /* one-based position; zero if not reported */
    size_t column; /* position as reported by producer; not UTF-8 normalized */
    char path[BTB_EVIDENCE_PATH_CAPACITY];
    char code[BTB_EVIDENCE_CODE_CAPACITY];
    char message[BTB_EVIDENCE_MESSAGE_CAPACITY];
} BtbEvidenceProblem;

typedef struct BtbEvidenceRun {
    BtbEvidenceIdentity identity;
    BtbEvidenceProblem problems[BTB_EVIDENCE_MAX_PROBLEMS];
    size_t problemCount;
    size_t droppedDiagnostics;
    int buildRecorded;
    int buildExitCode;
    int testsRecorded;
    size_t testsPassed;
    size_t testsFailed;
    size_t testsSkipped;
    size_t testsNotRun;
    int sealed;
} BtbEvidenceRun;

/* Nonzero review flags mean the run needs manual investigation, not release. */
#define BTB_REVIEW_STALE_REVISION UINT32_C(0x0001)
#define BTB_REVIEW_PROFILE_MISMATCH UINT32_C(0x0002)
#define BTB_REVIEW_BUILD_FAILURE UINT32_C(0x0004)
#define BTB_REVIEW_COMPILER_ERRORS UINT32_C(0x0008)
#define BTB_REVIEW_DROPPED_DIAGNOSTICS UINT32_C(0x0010)
#define BTB_REVIEW_TESTS_MISSING UINT32_C(0x0020)
#define BTB_REVIEW_TESTS_FAILED UINT32_C(0x0040)
#define BTB_REVIEW_TESTS_NOT_RUN UINT32_C(0x0080)
#define BTB_REVIEW_WARNING_BUDGET UINT32_C(0x0100)
#define BTB_REVIEW_TESTS_SKIPPED UINT32_C(0x0200)

typedef struct BtbEvidenceAssessment {
    uint32_t reviewFlags;
    size_t notes;
    size_t warnings;
    size_t errors;
    size_t fatals;
    BtbEvidenceStage earliestErrorStage; /* 0 if no error was recorded */
    int readyForHumanReview; /* NOT approval to commit or push */
} BtbEvidenceAssessment;

typedef struct BtbEvidenceComparison {
    size_t previousProblems;
    size_t currentProblems;
    size_t persisting;
    size_t introduced;
    size_t resolved;
    size_t introducedErrors;
    size_t resolvedErrors;
    BtbEvidenceStage earliestCurrentErrorStage;
    int currentEvidenceIncomplete;
} BtbEvidenceComparison;

/* Inputs are copied; all storage belongs to the caller. No heap, threads,
 * Git commands, filesystem I/O or parser are used by these functions.
 * INVALID/FULL/LOCKED/INCOMPARABLE preserve their documented output object. */
BtbEvidenceResult BtbEvidenceRunInit(BtbEvidenceRun *out,
                                      const BtbEvidenceIdentity *identity);
BtbEvidenceResult BtbEvidenceAddProblem(BtbEvidenceRun *run,
                                        const BtbEvidenceProblem *problem);
BtbEvidenceResult BtbEvidenceRecordBuild(BtbEvidenceRun *run,
                                         int processExitCode, size_t dropped);
BtbEvidenceResult BtbEvidenceRecordTests(BtbEvidenceRun *run, size_t passed,
                                         size_t failed, size_t skipped,
                                         size_t notRun);
BtbEvidenceResult BtbEvidenceSeal(BtbEvidenceRun *run);
int BtbEvidenceRunValid(const BtbEvidenceRun *run);
BtbEvidenceResult BtbEvidenceAssess(const BtbEvidenceRun *run,
    const char *expectedCommit, const char *expectedProfile,
    size_t allowedWarnings, BtbEvidenceAssessment *out);
/* Equal diagnostic identity means equal stage, severity, location, code and
 * message bytes. Duplicates are occurrences: each matches at most once.
 * A line number shift intentionally appears as one resolved and one new item.
 * Different profile/toolchain => INCOMPARABLE, even if SHAs match. */
BtbEvidenceResult BtbEvidenceCompare(const BtbEvidenceRun *previous,
                                     const BtbEvidenceRun *current,
                                     BtbEvidenceComparison *out);
const char *BtbEvidenceResultText(BtbEvidenceResult value);
const char *BtbEvidenceStageText(BtbEvidenceStage value);

#endif
