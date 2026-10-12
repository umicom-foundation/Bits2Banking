/*-----------------------------------------------------------------------------
 * Bits2Banking | Umicom Foundation | Sammy Hegab | MIT
 * File: labs/native/git-release-evidence/gate_demo.c
 * PURPOSE: Print explanatory release-gate evidence without changing Git state.
 *---------------------------------------------------------------------------*/
#include "gate.h"
#include <inttypes.h>
#include <stdio.h>

static void PrintReport(const BtbGateReport *report)
{
    const char *label = report->verdict == BTB_GATE_READY ? "READY" : "BLOCKED";
    (void)printf("%s | snapshot=%" PRIu64 " | issues=%u\n",
                 label, report->observationId, report->issueCount);
    for (unsigned position = 0U; position < 25U; ++position) {
        const uint64_t issue = UINT64_C(1) << position;
        if ((report->issues & issue) != 0U) {
            (void)printf("  - %s\n", BtbGateIssueName(issue));
        }
    }
}

int main(void)
{
    BtbGateSnapshot snapshot = {
        .action = BTB_GATE_ACTION_PUSH,
        .observationId = 42U,
        .expectedObservationId = 42U,
        .onMain = 1,
        .remoteChecked = 1,
        .divergenceKnown = 1,
        .ahead = 1U,
        .buildProof = BTB_GATE_PROOF_PASSED,
        .testsProof = BTB_GATE_PROOF_PASSED,
        .docsProof = BTB_GATE_PROOF_PASSED
    };
    BtbGateReport report = {0};
    if (BtbGateEvaluate(&snapshot, &report) != BTB_GATE_READY) {
        return 1;
    }
    PrintReport(&report);

    /* Model a later remote fetch finding a new upstream commit. The original
     * snapshot no longer authorises a push. No Git command is executed. */
    snapshot.observationId += 1U;
    snapshot.behind = 1U;
    if (BtbGateEvaluate(&snapshot, &report) != BTB_GATE_BLOCKED) {
        return 2;
    }
    PrintReport(&report);
    return 0;
}
