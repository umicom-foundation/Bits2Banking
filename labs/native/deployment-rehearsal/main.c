/*-----------------------------------------------------------------------------
 * Bits2Banking | Umicom Foundation | Sammy Hegab | MIT
 * File: labs/native/deployment-rehearsal/main.c
 * PURPOSE: Display a harmless preview of staged-release evidence.
 *---------------------------------------------------------------------------*/
#include "deployment_review.h"
#include <stdio.h>
#include <string.h>
int main(void)
{
    const char source[] = "0123456789abcdef0123456789abcdef01234567";
    const char artifact[] =
        "abcdef0123456789abcdef0123456789abcdef0123456789abcdef0123456789";
    const char config[] =
        "fedcba9876543210fedcba9876543210fedcba9876543210fedcba9876543210";
    BtbServiceSummary before = {0};
    before.captureId = 100U; before.count = 1U; before.ready = 1U;
    before.items[0].serviceId = 1U;
    before.items[0].decision = BTB_ADMIN_READY;
    BtbMaintenanceReview maintenance;
    if (BtbMaintenanceInit(&maintenance, "NotesRelease", source, "OperatorA", &before)
        != BTB_MAINTENANCE_OK) return 1;
    BtbDeploymentPlan plan = {0};
    (void)snprintf(plan.releaseId, sizeof plan.releaseId, "%s", "NotesTrainingRelease");
    (void)snprintf(plan.sourceRevision, sizeof plan.sourceRevision, "%s", source);
    (void)snprintf(plan.packageSha256, sizeof plan.packageSha256, "%s", artifact);
    (void)snprintf(plan.configurationSha256,
                   sizeof plan.configurationSha256, "%s", config);
    (void)snprintf(plan.privateStage, sizeof plan.privateStage,
                   "%s", "practice-notes-stage");
    BtbDeploymentReview review;
    if (BtbDeploymentInit(&review, &plan, &maintenance) != BTB_DEPLOYMENT_OK)
        return 1;
    BtbDeploymentDecision result;
    if (BtbDeploymentEvaluate(&review, &result) != BTB_DEPLOYMENT_OK) return 1;
    printf("Before staging: %s (missing=0x%08x)\n",
           BtbDeploymentStatusText(result.status), (unsigned)result.missingEvidence);
    if (result.status != BTB_DEPLOYMENT_PENDING) return 1;
    if (BtbMaintenanceApprove(&maintenance, "ReviewerB", 1, 1) != BTB_MAINTENANCE_OK ||
        BtbMaintenanceStart(&maintenance) != BTB_MAINTENANCE_OK) return 1;
    BtbServiceSummary after = before;
    after.captureId = 200U;
    if (BtbMaintenanceObserveAfter(&maintenance, &after) != BTB_MAINTENANCE_OK ||
        BtbMaintenanceComplete(&maintenance) != BTB_MAINTENANCE_OK ||
        BtbDeploymentUpdateMaintenance(&review, &maintenance) != BTB_DEPLOYMENT_OK)
        return 1;
    BtbDeploymentEvidence staged = {0};
    staged.stageCaptureId = 150U;
    staged.verificationCaptureId = 201U;
    (void)snprintf(staged.observedSourceRevision,
                   sizeof staged.observedSourceRevision, "%s", source);
    (void)snprintf(staged.observedPackageSha256,
                   sizeof staged.observedPackageSha256, "%s", artifact);
    staged.packageHashCompared = 1;
    staged.configurationReviewed = 1;
    staged.runtimeDependenciesChecked = 1;
    staged.privateStageInspected = 1;
    staged.entryPointProbed = 1;
    if (BtbDeploymentAttachStage(&review, &staged) != BTB_DEPLOYMENT_OK ||
        BtbDeploymentEvaluate(&review, &result) != BTB_DEPLOYMENT_OK) return 1;
    printf("After complete fictional evidence: %s (missing=0x%08x)\n",
           BtbDeploymentStatusText(result.status), (unsigned)result.missingEvidence);
    puts("Teaching only: no package installed; no real signature, service or system inspected.");
    return result.status == BTB_DEPLOYMENT_QUALIFIED ? 0 : 1;
}
