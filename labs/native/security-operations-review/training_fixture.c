/*-----------------------------------------------------------------------------
 * Bits2Banking | Umicom Foundation | Sammy Hegab | MIT
 * File: labs/native/security-operations-review/training_fixture.c
 * PURPOSE: Build an isolated, non-operational Umicom Notes review fixture.
 *
 * Reuses previous C23 APIs. Neither testing nor demonstrations pretend that
 * these values came from operating-system observations or authenticated tools.
 *---------------------------------------------------------------------------*/
#include "training_fixture.h"
#include <stdio.h>

static const char Revision[] = "0123456789abcdef0123456789abcdef01234567";
static const char Package[] = "abcdef0123456789abcdef0123456789abcdef0123456789abcdef0123456789";
static const char Config[] = "fedcba9876543210fedcba9876543210fedcba9876543210fedcba9876543210";
static const char Policy[] = "policy-2026-10-training";

static void Summary(BtbServiceSummary *summary, uint64_t captureId, int ready)
{
    *summary = (BtbServiceSummary){0};
    summary->captureId = captureId;
    summary->count = 1U;
    summary->items[0].serviceId = 1U;
    summary->items[0].decision = ready ? BTB_ADMIN_READY : BTB_ADMIN_BLOCKED;
    if (ready) summary->ready = 1U;
    else summary->blocked = 1U;
}

int BtbSecurityTrainingRemote(BtbRemoteReview *remote, int mode)
{
    BtbServiceSummary baseline, after, restored;
    BtbMaintenanceReview maintenance;
    BtbDeploymentReview deployment;
    BtbDeploymentPlan deploymentPlan = {0};
    BtbDeploymentEvidence stage = {0};
    BtbRemotePlan remotePlan = {0};
    BtbRemoteEvidence remoteEvidence = {0};
    if (remote == NULL || mode < 0 || mode > 2) return 0;
    Summary(&baseline, 100U, 1);
    if (BtbMaintenanceInit(&maintenance, "NotesRemote", Revision,
                           "MakerA", &baseline) != BTB_MAINTENANCE_OK) return 0;
    if (BtbMaintenanceApprove(&maintenance, "CheckerB", 1, 1) !=
        BTB_MAINTENANCE_OK) return 0;
    if (BtbMaintenanceStart(&maintenance) != BTB_MAINTENANCE_OK) return 0;
    Summary(&after, 200U, mode == 0);
    if (BtbMaintenanceObserveAfter(&maintenance, &after) !=
        BTB_MAINTENANCE_OK) return 0;
    if (mode == 0 && BtbMaintenanceComplete(&maintenance) !=
        BTB_MAINTENANCE_OK) return 0;
    if (mode == 2) {
        Summary(&restored, 220U, 1);
        if (BtbMaintenanceConfirmRestored(&maintenance, &restored) !=
            BTB_MAINTENANCE_OK) return 0;
    }
    (void)snprintf(deploymentPlan.releaseId, sizeof deploymentPlan.releaseId,
                   "%s", "NotesTraining");
    (void)snprintf(deploymentPlan.sourceRevision, sizeof deploymentPlan.sourceRevision,
                   "%s", Revision);
    (void)snprintf(deploymentPlan.packageSha256, sizeof deploymentPlan.packageSha256,
                   "%s", Package);
    (void)snprintf(deploymentPlan.configurationSha256,
                   sizeof deploymentPlan.configurationSha256, "%s", Config);
    (void)snprintf(deploymentPlan.privateStage, sizeof deploymentPlan.privateStage,
                   "%s", "practice-notes");
    if (BtbDeploymentInit(&deployment, &deploymentPlan, &maintenance) !=
        BTB_DEPLOYMENT_OK) return 0;
    stage.stageCaptureId = 150U;
    stage.verificationCaptureId = 240U;
    (void)snprintf(stage.observedSourceRevision,
                   sizeof stage.observedSourceRevision, "%s", Revision);
    (void)snprintf(stage.observedPackageSha256,
                   sizeof stage.observedPackageSha256, "%s", Package);
    stage.packageHashCompared = 1;
    stage.configurationReviewed = 1;
    stage.runtimeDependenciesChecked = 1;
    stage.privateStageInspected = 1;
    stage.entryPointProbed = 1;
    if (BtbDeploymentAttachStage(&deployment, &stage) != BTB_DEPLOYMENT_OK)
        return 0;
    (void)snprintf(remotePlan.serviceId, sizeof remotePlan.serviceId,
                   "%s", "notes-demo");
    (void)snprintf(remotePlan.hostLabel, sizeof remotePlan.hostLabel,
                   "%s", "notes.training.invalid");
    (void)snprintf(remotePlan.requestingOperator,
                   sizeof remotePlan.requestingOperator, "%s", "MakerA");
    (void)snprintf(remotePlan.independentReviewer,
                   sizeof remotePlan.independentReviewer, "%s", "CheckerB");
    (void)snprintf(remotePlan.sourceRevision, sizeof remotePlan.sourceRevision,
                   "%s", Revision);
    remotePlan.changeTicket = 500U;
    remotePlan.windowStartSeconds = 1000U;
    remotePlan.windowEndSeconds = 2000U;
    if (BtbRemoteInit(remote, &remotePlan, &deployment) != BTB_REMOTE_OK)
        return 0;
    remoteEvidence.captureId = 260U;
    remoteEvidence.observationSeconds = 1500U;
    (void)snprintf(remoteEvidence.observedSourceRevision,
                   sizeof remoteEvidence.observedSourceRevision, "%s", Revision);
    remoteEvidence.hostIdentityIndependentlyChecked = 1;
    remoteEvidence.authenticatedTransportReviewed = 1;
    remoteEvidence.destinationScopeReviewed = 1;
    remoteEvidence.leastPrivilegeReviewed = 1;
    remoteEvidence.credentialsExcludedFromLogs = 1;
    remoteEvidence.recoveryPlanAvailable = 1;
    remoteEvidence.separateReviewerRecorded = 1;
    remoteEvidence.readOnlyTrialObserved = 1;
    return BtbRemoteAttach(remote, &remoteEvidence) == BTB_REMOTE_OK;
}

int BtbSecurityTrainingPlan(BtbSecurityPlan *plan)
{
    if (plan == NULL) return 0;
    *plan = (BtbSecurityPlan){0};
    (void)snprintf(plan->serviceId, sizeof plan->serviceId, "%s", "notes-demo");
    (void)snprintf(plan->requestingOperator, sizeof plan->requestingOperator,
                   "%s", "MakerA");
    (void)snprintf(plan->independentReviewer, sizeof plan->independentReviewer,
                   "%s", "CheckerB");
    (void)snprintf(plan->sourceRevision, sizeof plan->sourceRevision,
                   "%s", Revision);
    (void)snprintf(plan->configurationSha256, sizeof plan->configurationSha256,
                   "%s", Config);
    (void)snprintf(plan->policyRevision, sizeof plan->policyRevision,
                   "%s", Policy);
    plan->changeTicket = 500U;
    plan->reviewWindowStartSeconds = 1000U;
    plan->reviewWindowEndSeconds = 2000U;
    return 1;
}

int BtbSecurityTrainingEvidence(BtbSecurityEvidence *evidence)
{
    if (evidence == NULL) return 0;
    *evidence = (BtbSecurityEvidence){0};
    evidence->captureId = 300U;
    evidence->observationSeconds = 1600U;
    (void)snprintf(evidence->observedSourceRevision,
                   sizeof evidence->observedSourceRevision, "%s", Revision);
    (void)snprintf(evidence->observedConfigurationSha256,
                   sizeof evidence->observedConfigurationSha256, "%s", Config);
    (void)snprintf(evidence->observedPolicyRevision,
                   sizeof evidence->observedPolicyRevision, "%s", Policy);
    evidence->accountsReviewed = 1;
    evidence->groupMembershipReviewed = 1;
    evidence->leastPrivilegeReviewed = 1;
    evidence->configurationCompared = 1;
    evidence->unexplainedDriftAbsent = 1;
    evidence->patchEvidenceReviewed = 1;
    evidence->independentRestoreTestRecorded = 1;
    evidence->auditRetentionReviewed = 1;
    evidence->credentialsExcludedFromEvidence = 1;
    evidence->credentialRotationPlanReviewed = 1;
    evidence->certificateExpiryReviewed = 1;
    evidence->independentApprovalRecorded = 1;
    evidence->monitoringResponsePathReviewed = 1;
    return 1;
}

int BtbSecurityTrainingReview(BtbSecurityReview *review, int mode)
{
    BtbRemoteReview remote;
    BtbSecurityPlan plan;
    if (review == NULL || !BtbSecurityTrainingRemote(&remote, mode) ||
        !BtbSecurityTrainingPlan(&plan)) return 0;
    return BtbSecurityInit(review, &plan, &remote) == BTB_SECURITY_OK;
}

int BtbSecurityTrainingComplete(BtbSecurityReview *review, int mode)
{
    BtbSecurityEvidence evidence;
    if (!BtbSecurityTrainingReview(review, mode) ||
        !BtbSecurityTrainingEvidence(&evidence)) return 0;
    return BtbSecurityAttach(review, &evidence) == BTB_SECURITY_OK;
}
