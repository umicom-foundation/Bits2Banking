/*-----------------------------------------------------------------------------
 * Bits to Banking | Umicom Foundation | Sammy Hegab | MIT
 * File: labs/native/build-evidence/evidence_demo.c
 * PURPOSE: Compare fictional Umicom Bank builds with owned C23 evidence.
 *---------------------------------------------------------------------------*/
#include "evidence.h"
#include <stdio.h>
#include <string.h>

static BtbEvidenceIdentity Identity(const char *sha, uint64_t observation)
{
    BtbEvidenceIdentity value = {0};
    (void)snprintf(value.commit, sizeof value.commit, "%s", sha);
    (void)snprintf(value.profile, sizeof value.profile, "%s", "windows-ucrt64-all-debug");
    (void)snprintf(value.toolchain, sizeof value.toolchain, "%s", "gcc-ucrt64");
    value.observationSequence = observation;
    return value;
}

int main(void)
{
    const char *oldSha = "0123456789abcdef0123456789abcdef01234567";
    const char *newSha = "abcdef0123456789abcdef0123456789abcdef01";
    const BtbEvidenceIdentity oldId = Identity(oldSha, 100U);
    const BtbEvidenceIdentity newId = Identity(newSha, 101U);
    BtbEvidenceRun before, after;
    BtbEvidenceProblem problem = {
        .stage = BTB_EVIDENCE_COMPILE,
        .severity = BTB_EVIDENCE_ERROR,
        .line = 72U,
        .column = 9U,
        .path = "framework/src/finance/decimal_arithmetic.c",
        .code = "-Wconversion",
        .message = "fictional example: narrowing conversion"
    };
    BtbEvidenceComparison comparison;
    BtbEvidenceAssessment assessment;
    if (BtbEvidenceRunInit(&before, &oldId) != BTB_EVIDENCE_OK ||
        BtbEvidenceAddProblem(&before, &problem) != BTB_EVIDENCE_OK ||
        BtbEvidenceRecordBuild(&before, 1, 0U) != BTB_EVIDENCE_OK ||
        BtbEvidenceSeal(&before) != BTB_EVIDENCE_OK ||
        BtbEvidenceRunInit(&after, &newId) != BTB_EVIDENCE_OK ||
        BtbEvidenceRecordBuild(&after, 0, 0U) != BTB_EVIDENCE_OK ||
        BtbEvidenceRecordTests(&after, 12U, 0U, 0U, 0U) != BTB_EVIDENCE_OK ||
        BtbEvidenceSeal(&after) != BTB_EVIDENCE_OK ||
        BtbEvidenceCompare(&before, &after, &comparison) != BTB_EVIDENCE_OK ||
        BtbEvidenceAssess(&after, newSha, newId.profile, 0U, &assessment) != BTB_EVIDENCE_OK)
        return 1;
    printf("Introduced: %zu, resolved: %zu, persistent: %zu\n",
        comparison.introduced, comparison.resolved, comparison.persisting);
    printf("Latest build: tests passed=12; review flags=%u; reviewable=%s\n",
        (unsigned)assessment.reviewFlags,
        assessment.readyForHumanReview ? "yes" : "no");
    /* An in-memory teaching judgement, NOT a permission to push to main. */
    return comparison.resolved == 1U && assessment.readyForHumanReview ? 0 : 2;
}
