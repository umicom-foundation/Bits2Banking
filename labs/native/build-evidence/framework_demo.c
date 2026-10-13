/*-----------------------------------------------------------------------------
 * Bits to Banking | Umicom Foundation | Sammy Hegab | MIT
 * File: labs/native/build-evidence/framework_demo.c
 * PURPOSE: Link the real Umicom Framework VCS and build parser APIs.
 * The default execution is synthetic and safe. --repo PATH reads Git status
 * via Framework only; it does NOT stage, fetch, commit, push or modify files.
 *---------------------------------------------------------------------------*/
#include "framework_bridge.h"
#include "umicom/build/parser.h"

#include <stdio.h>
#include <string.h>

int main(int argc, char **argv)
{
    UmiVcsWorkingTreeSummary summary = {0};
    UmiBuildDiagnosticList *list = NULL;
    BtbEvidenceRun run;
    BtbEvidenceAssessment assessment;
    UmiBuildDiagnostic diagnostic;
    BtbEvidenceResult result;
    UmiStatus status;
    UmiVcsWorkingTree *tree = NULL;
    static UmiBuildDiagnosticList stableList; /* Framework's 256-item list is large. */
    list = &stableList;
    if (argc == 3 && strcmp(argv[1], "--repo") == 0) {
        const UmiVcsWorkingTreeRequest request = {
            .repository_root = argv[2],
            .git_program = NULL,
            .timeout_ms = 30000U,
            .cancellation = NULL
        };
        status = UmiVcsWorkingTreeRead(&request, &tree);
        if (status != UMI_STATUS_OK) {
            fputs("Framework could not read the repository; nothing changed.\n", stderr);
            return 2;
        }
        status = UmiVcsWorkingTreeDescribe(tree, &summary);
        UmiVcsWorkingTreeDestroy(tree);
        if (status != UMI_STATUS_OK) return 3;
        /* The caller can still inspect a detached commit in read-only mode. */
    } else if (argc == 1) {
        (void)snprintf(summary.commit_id, sizeof summary.commit_id,
            "%s", "0123456789abcdef0123456789abcdef01234567");
        summary.commit_known = 1;
        summary.branch_known = 1;
        (void)snprintf(summary.branch, sizeof summary.branch, "%s", "main");
        summary.divergence_known = 1;
    } else {
        fputs("Usage: btb-evidence-framework-demo [--repo REPO_PATH]\n", stderr);
        return 2;
    }
    result = BtbEvidenceFromFrameworkSummary(&summary, "headless-debug", "gcc", 1U, &run);
    if (result != BTB_EVIDENCE_OK) {
        fputs("No complete commit identity was available.\n", stderr);
        return 3;
    }
    /* Real Framework parser: this application does not duplicate its grammar. */
    status = umi_build_parse_diagnostic_line(
        "C:/umicom/Umicom-Applications/framework/examples/notes.c:8:5: warning: unused variable",
        &diagnostic);
    if (status != UMI_STATUS_OK) return 4;
    umi_build_diagnostic_list_init(list);
    status = umi_build_diagnostic_list_add(list, &diagnostic);
    if (status != UMI_STATUS_OK) return 5;
    if (BtbEvidenceFromFrameworkDiagnostics(&run, list, BTB_EVIDENCE_COMPILE) != BTB_EVIDENCE_OK ||
        BtbEvidenceRecordBuild(&run, 0, list->dropped) != BTB_EVIDENCE_OK ||
        BtbEvidenceRecordTests(&run, 1U, 0U, 0U, 0U) != BTB_EVIDENCE_OK ||
        BtbEvidenceSeal(&run) != BTB_EVIDENCE_OK ||
        BtbEvidenceAssess(&run, run.identity.commit, run.identity.profile,
                          1U, &assessment) != BTB_EVIDENCE_OK) return 6;
    printf("Framework consumer: %zu warning(s), review flags=%u, detached=%d\n",
        assessment.warnings, (unsigned)assessment.reviewFlags, summary.detached);
    return assessment.readyForHumanReview ? 0 : 7;
}
