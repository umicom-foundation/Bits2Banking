/*-----------------------------------------------------------------------------
 * Bits to Banking | Umicom Foundation | Sammy Hegab | MIT
 * File: labs/native/build-evidence/framework_bridge.h
 * PURPOSE: Optional, source-compatible consumer of REAL Umicom Framework APIs.
 * This header is used ONLY when the Framework SDK is installed and enabled.
 *---------------------------------------------------------------------------*/
#ifndef BTB_BUILD_FRAMEWORK_BRIDGE_H
#define BTB_BUILD_FRAMEWORK_BRIDGE_H

#include "evidence.h"
#include "umicom/vcs/working_tree.h"
#include "umicom/build/diagnostic.h"

/* This copies a canonical Framework observation. It does not establish that
 * 'origin/main' was fetched or that the revision is publishable. A detached
 * HEAD is a valid build identity, but not a suitable push target by itself. */
BtbEvidenceResult BtbEvidenceFromFrameworkSummary(
    const UmiVcsWorkingTreeSummary *summary,
    const char *profile, const char *toolchain, uint64_t observationSequence,
    BtbEvidenceRun *out);

/* Takes a Framework-owned *already parsed* list and projects it atomically to
 * small teaching records. Long fields / excess entries are REFUSED, never
 * truncated. No extra compiler parser and no side effects. */
BtbEvidenceResult BtbEvidenceFromFrameworkDiagnostics(
    BtbEvidenceRun *run, const UmiBuildDiagnosticList *diagnostics,
    BtbEvidenceStage stage);

#endif
