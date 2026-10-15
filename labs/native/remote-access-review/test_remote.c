/*-----------------------------------------------------------------------------
 * Bits2Banking | Umicom Foundation | Sammy Hegab | MIT
 * File: labs/native/remote-access-review/test_remote.c
 * PURPOSE: Named deterministic C23 tests, including failure-atomic checks.
 *---------------------------------------------------------------------------*/
#include "remote_access_review.h"
#include <stdio.h>
#include <string.h>
#include <stdint.h>

#define CHECK(test) do { if (!(test)) { \
    fprintf(stderr,"FAILED %s:%d: %s\n",__FILE__,__LINE__,#test); \
    return 1; } } while (0)

static const char Revision[] = "0123456789abcdef0123456789abcdef01234567";
static const char Digest[] = "abcdef0123456789abcdef0123456789abcdef0123456789abcdef0123456789";
static const char Config[] = "fedcba9876543210fedcba9876543210fedcba9876543210fedcba9876543210";

static void Summary(BtbServiceSummary *summary, uint64_t capture, int ready)
{
    *summary = (BtbServiceSummary){0};
    summary->captureId = capture;
    summary->count = 1U;
    summary->items[0].serviceId = 1U;
    summary->items[0].decision = ready ? BTB_ADMIN_READY : BTB_ADMIN_BLOCKED;
    if (ready) summary->ready = 1U;
    else summary->blocked = 1U;
}

/* The fixture calls the real, already delivered Update 39–42 APIs, thereby
 * testing composition. It does not replicate any of their state machines. */
static int DeploymentFixture(BtbDeploymentReview *deployment, int mode)
{
    BtbServiceSummary before, after, restored;
    BtbMaintenanceReview maintenance;
    BtbDeploymentPlan plan = {0};
    BtbDeploymentEvidence stage = {0};
    Summary(&before, 100U, 1);
    if (BtbMaintenanceInit(&maintenance, "NotesRemote", Revision, "MakerA", &before)
        != BTB_MAINTENANCE_OK) return 0;
    if (BtbMaintenanceApprove(&maintenance, "CheckerB", 1, 1)
        != BTB_MAINTENANCE_OK) return 0;
    if (BtbMaintenanceStart(&maintenance) != BTB_MAINTENANCE_OK) return 0;
    Summary(&after, 200U, mode == 0);
    if (BtbMaintenanceObserveAfter(&maintenance, &after) != BTB_MAINTENANCE_OK) return 0;
    if (mode == 0 && BtbMaintenanceComplete(&maintenance) != BTB_MAINTENANCE_OK) return 0;
    if (mode == 2) {
        Summary(&restored, 220U, 1);
        if (BtbMaintenanceConfirmRestored(&maintenance, &restored) != BTB_MAINTENANCE_OK) return 0;
    }
    (void)snprintf(plan.releaseId, sizeof plan.releaseId, "%s", "NotesTraining");
    (void)snprintf(plan.sourceRevision, sizeof plan.sourceRevision, "%s", Revision);
    (void)snprintf(plan.packageSha256, sizeof plan.packageSha256, "%s", Digest);
    (void)snprintf(plan.configurationSha256, sizeof plan.configurationSha256, "%s", Config);
    (void)snprintf(plan.privateStage, sizeof plan.privateStage, "%s", "practice-notes");
    if (BtbDeploymentInit(deployment, &plan, &maintenance) != BTB_DEPLOYMENT_OK) return 0;
    stage.stageCaptureId = 150U;
    stage.verificationCaptureId = 240U;
    (void)snprintf(stage.observedSourceRevision, sizeof stage.observedSourceRevision,
                   "%s", Revision);
    (void)snprintf(stage.observedPackageSha256, sizeof stage.observedPackageSha256,
                   "%s", Digest);
    stage.packageHashCompared = 1;
    stage.configurationReviewed = 1;
    stage.runtimeDependenciesChecked = 1;
    stage.privateStageInspected = 1;
    stage.entryPointProbed = 1;
    return BtbDeploymentAttachStage(deployment, &stage) == BTB_DEPLOYMENT_OK;
}

static void Plan(BtbRemotePlan *plan)
{
    *plan = (BtbRemotePlan){0};
    (void)snprintf(plan->serviceId, sizeof plan->serviceId, "%s", "notes-demo");
    (void)snprintf(plan->hostLabel, sizeof plan->hostLabel, "%s", "notes.training.invalid");
    (void)snprintf(plan->requestingOperator, sizeof plan->requestingOperator,
                   "%s", "MakerA");
    (void)snprintf(plan->independentReviewer, sizeof plan->independentReviewer,
                   "%s", "CheckerB");
    (void)snprintf(plan->sourceRevision, sizeof plan->sourceRevision, "%s", Revision);
    plan->changeTicket = 500U;
    plan->windowStartSeconds = 1000U;
    plan->windowEndSeconds = 2000U;
}
static void Evidence(BtbRemoteEvidence *e)
{
    *e = (BtbRemoteEvidence){0};
    e->captureId = 260U;
    e->observationSeconds = 1500U;
    (void)snprintf(e->observedSourceRevision,
                   sizeof e->observedSourceRevision, "%s", Revision);
    e->hostIdentityIndependentlyChecked = 1;
    e->authenticatedTransportReviewed = 1;
    e->destinationScopeReviewed = 1;
    e->leastPrivilegeReviewed = 1;
    e->credentialsExcludedFromLogs = 1;
    e->recoveryPlanAvailable = 1;
    e->separateReviewerRecorded = 1;
    e->readOnlyTrialObserved = 1;
}
static int ReviewFixture(BtbRemoteReview *review, int mode)
{
    BtbDeploymentReview deployment;
    BtbRemotePlan plan;
    if (!DeploymentFixture(&deployment, mode)) return 0;
    Plan(&plan);
    return BtbRemoteInit(review, &plan, &deployment) == BTB_REMOTE_OK;
}
static int FullReview(BtbRemoteReview *review, int mode)
{
    BtbRemoteEvidence e;
    if (!ReviewFixture(review, mode)) return 0;
    Evidence(&e);
    return BtbRemoteAttach(review, &e) == BTB_REMOTE_OK;
}

static int Scenario(const char *name)
{
    BtbRemoteReview review;
    BtbRemoteReview before;
    BtbRemotePlan plan;
    BtbRemoteEvidence evidence;
    BtbRemoteDecision decision;
    BtbDeploymentReview deployment;
    CHECK(ReviewFixture(&review, 0));
    Plan(&plan);
    Evidence(&evidence);
    if (strcmp(name, "pending") == 0) {
        CHECK(BtbRemoteEvaluate(&review, &decision) == BTB_REMOTE_OK);
        CHECK(decision.status == BTB_REMOTE_BLOCKED);
        CHECK((decision.missingEvidence & BTB_REMOTE_MISSING_OBSERVATION) != 0U);
    } else if (strcmp(name, "approved-evidence") == 0) {
        CHECK(BtbRemoteAttach(&review, &evidence) == BTB_REMOTE_OK);
        CHECK(BtbRemoteEvaluate(&review, &decision) == BTB_REMOTE_OK);
        CHECK(decision.status == BTB_REMOTE_REVIEWABLE);
        CHECK(decision.missingEvidence == 0U);
    } else if (strcmp(name, "host-key") == 0) {
        evidence.hostIdentityIndependentlyChecked = 0;
        CHECK(BtbRemoteAttach(&review, &evidence) == BTB_REMOTE_OK);
        CHECK(BtbRemoteEvaluate(&review, &decision) == BTB_REMOTE_OK);
        CHECK((decision.missingEvidence & BTB_REMOTE_MISSING_HOST_IDENTITY) != 0U);
    } else if (strcmp(name, "transport") == 0) {
        evidence.authenticatedTransportReviewed = 0;
        CHECK(BtbRemoteAttach(&review, &evidence) == BTB_REMOTE_OK);
        CHECK(BtbRemoteEvaluate(&review, &decision) == BTB_REMOTE_OK);
        CHECK((decision.missingEvidence & BTB_REMOTE_MISSING_TRANSPORT) != 0U);
    } else if (strcmp(name, "scope") == 0) {
        evidence.destinationScopeReviewed = 0;
        CHECK(BtbRemoteAttach(&review, &evidence) == BTB_REMOTE_OK);
        CHECK(BtbRemoteEvaluate(&review, &decision) == BTB_REMOTE_OK);
        CHECK((decision.missingEvidence & BTB_REMOTE_MISSING_SCOPE) != 0U);
    } else if (strcmp(name, "privilege") == 0) {
        evidence.leastPrivilegeReviewed = 0;
        CHECK(BtbRemoteAttach(&review, &evidence) == BTB_REMOTE_OK);
        CHECK(BtbRemoteEvaluate(&review, &decision) == BTB_REMOTE_OK);
        CHECK((decision.missingEvidence & BTB_REMOTE_MISSING_LEAST_PRIVILEGE) != 0U);
    } else if (strcmp(name, "credentials") == 0) {
        evidence.credentialsExcludedFromLogs = 0;
        CHECK(BtbRemoteAttach(&review, &evidence) == BTB_REMOTE_OK);
        CHECK(BtbRemoteEvaluate(&review, &decision) == BTB_REMOTE_OK);
        CHECK((decision.missingEvidence & BTB_REMOTE_MISSING_CREDENTIAL_SAFETY) != 0U);
    } else if (strcmp(name, "recovery") == 0) {
        evidence.recoveryPlanAvailable = 0;
        CHECK(BtbRemoteAttach(&review, &evidence) == BTB_REMOTE_OK);
        CHECK(BtbRemoteEvaluate(&review, &decision) == BTB_REMOTE_OK);
        CHECK((decision.missingEvidence & BTB_REMOTE_MISSING_RECOVERY_PLAN) != 0U);
    } else if (strcmp(name, "reviewer") == 0) {
        evidence.separateReviewerRecorded = 0;
        CHECK(BtbRemoteAttach(&review, &evidence) == BTB_REMOTE_OK);
        CHECK(BtbRemoteEvaluate(&review, &decision) == BTB_REMOTE_OK);
        CHECK((decision.missingEvidence & BTB_REMOTE_MISSING_REVIEWER) != 0U);
    } else if (strcmp(name, "read-only") == 0) {
        evidence.readOnlyTrialObserved = 0;
        CHECK(BtbRemoteAttach(&review, &evidence) == BTB_REMOTE_OK);
        CHECK(BtbRemoteEvaluate(&review, &decision) == BTB_REMOTE_OK);
        CHECK((decision.missingEvidence & BTB_REMOTE_MISSING_READ_ONLY_TRIAL) != 0U);
    } else if (strcmp(name, "stale") == 0) {
        evidence.captureId = 240U;
        CHECK(BtbRemoteAttach(&review, &evidence) == BTB_REMOTE_OK);
        CHECK(BtbRemoteEvaluate(&review, &decision) == BTB_REMOTE_OK);
        CHECK((decision.missingEvidence & BTB_REMOTE_STALE_CAPTURE) != 0U);
    } else if (strcmp(name, "outside-window") == 0) {
        evidence.observationSeconds = 2000U;
        CHECK(BtbRemoteAttach(&review, &evidence) == BTB_REMOTE_OK);
        CHECK(BtbRemoteEvaluate(&review, &decision) == BTB_REMOTE_OK);
        CHECK((decision.missingEvidence & BTB_REMOTE_OUTSIDE_WINDOW) != 0U);
    } else if (strcmp(name, "revision") == 0) {
        evidence.observedSourceRevision[1] = 'f';
        before = review;
        CHECK(BtbRemoteAttach(&review, &evidence) == BTB_REMOTE_MISMATCH);
        CHECK(memcmp(&before, &review, sizeof review) == 0);
    } else if (strcmp(name, "mismatched-plan") == 0) {
        CHECK(DeploymentFixture(&deployment, 0));
        plan.sourceRevision[0] = 'f';
        before = review;
        CHECK(BtbRemoteInit(&review, &plan, &deployment) == BTB_REMOTE_MISMATCH);
        CHECK(memcmp(&before, &review, sizeof review) == 0);
    } else if (strcmp(name, "same-person") == 0) {
        CHECK(DeploymentFixture(&deployment, 0));
        (void)snprintf(plan.independentReviewer, sizeof plan.independentReviewer,
                       "%s", "MakerA");
        before = review;
        CHECK(BtbRemoteInit(&review, &plan, &deployment) == BTB_REMOTE_INVALID);
        CHECK(memcmp(&before, &review, sizeof review) == 0);
    } else if (strcmp(name, "bad-flag") == 0) {
        evidence.leastPrivilegeReviewed = 3;
        before = review;
        CHECK(BtbRemoteAttach(&review, &evidence) == BTB_REMOTE_INVALID);
        CHECK(memcmp(&before, &review, sizeof review) == 0);
    } else if (strcmp(name, "repeat") == 0) {
        CHECK(BtbRemoteAttach(&review, &evidence) == BTB_REMOTE_OK);
        before = review;
        CHECK(BtbRemoteAttach(&review, &evidence) == BTB_REMOTE_STATE_ERROR);
        CHECK(memcmp(&before, &review, sizeof review) == 0);
    } else if (strcmp(name, "atomic-output") == 0) {
        CHECK(FullReview(&review, 0));
        (void)memset(&decision, 0xA5, sizeof decision);
        BtbRemoteDecision preserved = decision;
        review.plan.hostLabel[0] = '\n';
        CHECK(BtbRemoteEvaluate(&review, &decision) == BTB_REMOTE_INVALID);
        CHECK(memcmp(&decision, &preserved, sizeof decision) == 0);
    } else if (strcmp(name, "rollback") == 0) {
        CHECK(FullReview(&review, 1));
        CHECK(BtbRemoteEvaluate(&review, &decision) == BTB_REMOTE_OK);
        CHECK(decision.deploymentStatus == BTB_DEPLOYMENT_ROLLBACK_REQUIRED);
        CHECK(decision.status == BTB_REMOTE_BLOCKED);
    } else if (strcmp(name, "restored") == 0) {
        CHECK(FullReview(&review, 2));
        CHECK(BtbRemoteEvaluate(&review, &decision) == BTB_REMOTE_OK);
        CHECK(decision.status == BTB_REMOTE_RESTORED_ONLY);
    } else if (strcmp(name, "mutations") == 0) {
        CHECK(FullReview(&review, 0));
        for (unsigned i = 0U; i < 25000U; ++i) {
            BtbRemoteReview candidate = review;
            const unsigned selected = i % 8U;
            if (selected == 0U) candidate.evidence.hostIdentityIndependentlyChecked = 0;
            if (selected == 1U) candidate.evidence.authenticatedTransportReviewed = 0;
            if (selected == 2U) candidate.evidence.destinationScopeReviewed = 0;
            if (selected == 3U) candidate.evidence.leastPrivilegeReviewed = 0;
            if (selected == 4U) candidate.evidence.credentialsExcludedFromLogs = 0;
            if (selected == 5U) candidate.evidence.recoveryPlanAvailable = 0;
            if (selected == 6U) candidate.evidence.separateReviewerRecorded = 0;
            if (selected == 7U) candidate.evidence.readOnlyTrialObserved = 0;
            CHECK(BtbRemoteEvaluate(&candidate, &decision) == BTB_REMOTE_OK);
            CHECK(decision.status == BTB_REMOTE_BLOCKED);
            CHECK(decision.missingEvidence != 0U);
        }
    } else return 2;
    return 0;
}
int main(int argc, char **argv)
{
    if (argc != 2) {
        fprintf(stderr, "Usage: btb-remote-review-test <named-case>\n");
        return 2;
    }
    const int result = Scenario(argv[1]);
    if (result == 0) printf("PASS: %s\n", argv[1]);
    return result;
}
