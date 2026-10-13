/*-----------------------------------------------------------------------------
 * Bits to Banking | Umicom Foundation | Sammy Hegab | MIT
 * File: labs/native/build-evidence/framework_bridge.c
 * PURPOSE: Translate owned Framework Git/build records, WITHOUT re-parsing.
 *---------------------------------------------------------------------------*/
#include "framework_bridge.h"

#include <string.h>

static int IsBoolean(int value) { return value == 0 || value == 1; }

static int CopyBounded(char *destination, size_t capacity,
                       const char *source, size_t sourceCapacity)
{
    const char *end;
    size_t length;
    if (destination == NULL || source == NULL || sourceCapacity == 0U) return 0;
    end = (const char *)memchr(source, '\0', sourceCapacity);
    if (end == NULL) return 0;
    length = (size_t)(end - source);
    if (length >= capacity) return 0;
    memcpy(destination, source, length + 1U);
    return 1;
}

static int CopyParameter(char *destination, size_t capacity, const char *source)
{
    size_t n;
    if (destination == NULL || source == NULL || capacity == 0U) return 0;
    for (n = 0U; n < capacity; ++n) {
        if (source[n] == '\0') {
            memcpy(destination, source, n + 1U);
            return 1;
        }
    }
    return 0;
}

BtbEvidenceResult BtbEvidenceFromFrameworkSummary(
    const UmiVcsWorkingTreeSummary *summary, const char *profile,
    const char *toolchain, uint64_t observationSequence, BtbEvidenceRun *out)
{
    BtbEvidenceIdentity identity = {0};
    /* Framework's branch and divergence flags are observed, not invented.
     * Treat malformed or unborn revisions as unavailable for a build identity. */
    if (summary == NULL || out == NULL || profile == NULL || toolchain == NULL ||
        !IsBoolean(summary->commit_known) || !IsBoolean(summary->unborn) ||
        !IsBoolean(summary->detached) || !IsBoolean(summary->branch_known) ||
        !IsBoolean(summary->divergence_known) ||
        !summary->commit_known || summary->unborn ||
        !CopyBounded(identity.commit, sizeof identity.commit,
                     summary->commit_id, sizeof summary->commit_id))
        return BTB_EVIDENCE_INVALID;
    /* These two values are caller-owned, NUL-terminated configuration names. */
    if (!CopyParameter(identity.profile, sizeof identity.profile, profile) ||
        !CopyParameter(identity.toolchain, sizeof identity.toolchain, toolchain))
        return BTB_EVIDENCE_INVALID;
    identity.observationSequence = observationSequence;
    return BtbEvidenceRunInit(out, &identity);
}

BtbEvidenceResult BtbEvidenceFromFrameworkDiagnostics(
    BtbEvidenceRun *run, const UmiBuildDiagnosticList *diagnostics,
    BtbEvidenceStage stage)
{
    BtbEvidenceRun candidate;
    size_t i;
    if (!BtbEvidenceRunValid(run) || diagnostics == NULL ||
        stage < BTB_EVIDENCE_CONFIGURE || stage > BTB_EVIDENCE_PACKAGE ||
        diagnostics->count > UMI_BUILD_MAX_DIAGNOSTICS)
        return BTB_EVIDENCE_INVALID;
    if (diagnostics->count > BTB_EVIDENCE_MAX_PROBLEMS - run->problemCount)
        return BTB_EVIDENCE_FULL;
    candidate = *run;
    for (i = 0U; i < diagnostics->count; ++i) {
        const UmiBuildDiagnostic *src = &diagnostics->items[i];
        BtbEvidenceProblem entry = {0};
        if (src->severity < UMI_BUILD_DIAGNOSTIC_NOTE ||
            src->severity > UMI_BUILD_DIAGNOSTIC_FATAL ||
            !CopyBounded(entry.path, sizeof entry.path,
                         src->file, sizeof src->file) ||
            !CopyBounded(entry.code, sizeof entry.code,
                         src->code, sizeof src->code) ||
            !CopyBounded(entry.message, sizeof entry.message,
                         src->message, sizeof src->message))
            return BTB_EVIDENCE_INVALID;
        entry.stage = stage;
        entry.severity = (BtbEvidenceSeverity)src->severity;
        entry.line = src->line;
        entry.column = src->column;
        if (BtbEvidenceAddProblem(&candidate, &entry) != BTB_EVIDENCE_OK)
            return BTB_EVIDENCE_INVALID;
    }
    *run = candidate;
    return BTB_EVIDENCE_OK;
}
