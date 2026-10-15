/*-----------------------------------------------------------------------------
 * Bits2Banking | Umicom Foundation | Sammy Hegab | MIT
 * File: labs/native/deployment-rehearsal/test_deployment.c
 * PURPOSE: Deterministic, named positive/negative C23 deployment review tests.
 *---------------------------------------------------------------------------*/
#include "deployment_review.h"
#include <stdio.h>
#include <string.h>
#include <stdint.h>
#define CHECK(condition) do { if (!(condition)) { \
    fprintf(stderr, "FAILED %s:%d: %s\n", __FILE__, __LINE__, #condition); \
    return 1; } } while (0)
static const char SourceRevision[] = "0123456789abcdef0123456789abcdef01234567";
static const char PackageDigest[] =
    "abcdef0123456789abcdef0123456789abcdef0123456789abcdef0123456789";
static const char ConfigurationDigest[] =
    "fedcba9876543210fedcba9876543210fedcba9876543210fedcba9876543210";

static void PrepareSummary(BtbServiceSummary *summary, uint64_t capture,
                           BtbAdminDecision decision)
{
    *summary = (BtbServiceSummary){0};
    summary->captureId = capture;
    summary->count = 1U;
    summary->items[0].serviceId = 1U;
    summary->items[0].decision = decision;
    if (decision == BTB_ADMIN_READY) summary->ready = 1U;
    else if (decision == BTB_ADMIN_REVIEW) summary->review = 1U;
    else summary->blocked = 1U;
}
static int CreateMaintenance(BtbMaintenanceReview *maintenance)
{
    BtbServiceSummary before;
    PrepareSummary(&before, 100U, BTB_ADMIN_READY);
    return BtbMaintenanceInit(maintenance, "NotesRelease", SourceRevision,
                              "OperatorA", &before) == BTB_MAINTENANCE_OK;
}
static void PreparePlan(BtbDeploymentPlan *plan)
{
    *plan = (BtbDeploymentPlan){0};
    (void)snprintf(plan->releaseId, sizeof plan->releaseId, "%s", "NotesTrainingRelease");
    (void)snprintf(plan->sourceRevision, sizeof plan->sourceRevision, "%s", SourceRevision);
    (void)snprintf(plan->packageSha256, sizeof plan->packageSha256, "%s", PackageDigest);
    (void)snprintf(plan->configurationSha256, sizeof plan->configurationSha256,
                   "%s", ConfigurationDigest);
    (void)snprintf(plan->privateStage, sizeof plan->privateStage,
                   "%s", "practice-notes-stage");
}
static void PrepareStage(BtbDeploymentEvidence *evidence)
{
    *evidence = (BtbDeploymentEvidence){0};
    evidence->stageCaptureId = 150U;
    evidence->verificationCaptureId = 201U;
    (void)snprintf(evidence->observedSourceRevision,
                   sizeof evidence->observedSourceRevision, "%s", SourceRevision);
    (void)snprintf(evidence->observedPackageSha256,
                   sizeof evidence->observedPackageSha256, "%s", PackageDigest);
    evidence->packageHashCompared = 1;
    evidence->configurationReviewed = 1;
    evidence->runtimeDependenciesChecked = 1;
    evidence->privateStageInspected = 1;
    evidence->entryPointProbed = 1;
}
static int AdvanceMaintenance(BtbMaintenanceReview *maintenance, int result)
{
    BtbServiceSummary after;
    if (BtbMaintenanceApprove(maintenance, "ReviewerB", 1, 1) != BTB_MAINTENANCE_OK ||
        BtbMaintenanceStart(maintenance) != BTB_MAINTENANCE_OK) return 0;
    PrepareSummary(&after, 200U, result ? BTB_ADMIN_READY : BTB_ADMIN_BLOCKED);
    if (BtbMaintenanceObserveAfter(maintenance, &after) != BTB_MAINTENANCE_OK) return 0;
    return result ? BtbMaintenanceComplete(maintenance) == BTB_MAINTENANCE_OK : 1;
}
static int PrepareReview(BtbDeploymentReview *review)
{
    BtbDeploymentPlan plan;
    BtbMaintenanceReview maintenance;
    if (!CreateMaintenance(&maintenance)) return 0;
    PreparePlan(&plan);
    return BtbDeploymentInit(review, &plan, &maintenance) == BTB_DEPLOYMENT_OK;
}
static int PrepareFull(BtbDeploymentReview *review, int success)
{
    BtbDeploymentPlan plan;
    BtbMaintenanceReview maintenance;
    BtbDeploymentEvidence evidence;
    if (!CreateMaintenance(&maintenance) || !AdvanceMaintenance(&maintenance, success)) return 0;
    PreparePlan(&plan);
    PrepareStage(&evidence);
    if (BtbDeploymentInit(review, &plan, &maintenance) != BTB_DEPLOYMENT_OK) return 0;
    return BtbDeploymentAttachStage(review, &evidence) == BTB_DEPLOYMENT_OK;
}

static int Scenario(const char *name)
{
    BtbDeploymentReview review;
    BtbDeploymentReview preserved;
    BtbDeploymentPlan plan;
    BtbMaintenanceReview maintenance;
    BtbDeploymentDecision decision;
    BtbDeploymentEvidence evidence;
    CHECK(PrepareReview(&review));
    preserved = review;
    PreparePlan(&plan);
    CHECK(CreateMaintenance(&maintenance));
    PrepareStage(&evidence);
    if (strcmp(name, "plan") == 0) {
        CHECK(strcmp(review.plan.privateStage, "practice-notes-stage") == 0);
        CHECK(review.hasStage == 0);
    } else if (strcmp(name, "invalid-plan") == 0) {
        (void)snprintf(plan.privateStage, sizeof plan.privateStage, "%s", "C:/production");
        CHECK(BtbDeploymentInit(&review, &plan, &maintenance) == BTB_DEPLOYMENT_INVALID);
        CHECK(memcmp(&review, &preserved, sizeof review) == 0);
    } else if (strcmp(name, "bad-hash") == 0) {
        plan.packageSha256[2] = 'G';
        CHECK(BtbDeploymentInit(&review, &plan, &maintenance) == BTB_DEPLOYMENT_INVALID);
        CHECK(memcmp(&review, &preserved, sizeof review) == 0);
    } else if (strcmp(name, "mismatch-revision") == 0) {
        plan.sourceRevision[3] = '0';
        CHECK(BtbDeploymentInit(&review, &plan, &maintenance) == BTB_DEPLOYMENT_MISMATCH);
        CHECK(memcmp(&review, &preserved, sizeof review) == 0);
    } else if (strcmp(name, "evidence-digest") == 0) {
        evidence.observedPackageSha256[3] = '0';
        CHECK(BtbDeploymentAttachStage(&review, &evidence) == BTB_DEPLOYMENT_MISMATCH);
        CHECK(memcmp(&review, &preserved, sizeof review) == 0);
    } else if (strcmp(name, "evidence-source") == 0) {
        evidence.observedSourceRevision[0] = 'e';
        CHECK(BtbDeploymentAttachStage(&review, &evidence) == BTB_DEPLOYMENT_MISMATCH);
        CHECK(memcmp(&review, &preserved, sizeof review) == 0);
    } else if (strcmp(name, "invalid-flags") == 0) {
        evidence.packageHashCompared = 2;
        CHECK(BtbDeploymentAttachStage(&review, &evidence) == BTB_DEPLOYMENT_INVALID);
        CHECK(memcmp(&review, &preserved, sizeof review) == 0);
    } else if (strcmp(name, "no-stage") == 0) {
        CHECK(BtbDeploymentEvaluate(&review, &decision) == BTB_DEPLOYMENT_OK);
        CHECK(decision.status == BTB_DEPLOYMENT_PENDING);
        CHECK((decision.missingEvidence & BTB_DEPLOYMENT_MISSING_STAGE) != 0U);
    } else if (strcmp(name, "stale-stage") == 0) {
        evidence.stageCaptureId = 100U;
        CHECK(BtbDeploymentAttachStage(&review, &evidence) == BTB_DEPLOYMENT_OK);
        CHECK(BtbDeploymentEvaluate(&review, &decision) == BTB_DEPLOYMENT_OK);
        CHECK((decision.missingEvidence & BTB_DEPLOYMENT_STALE_CAPTURE) != 0U);
    } else if (strcmp(name, "missing-runtime") == 0) {
        CHECK(PrepareFull(&review, 1));
        review.stage.runtimeDependenciesChecked = 0;
        CHECK(BtbDeploymentEvaluate(&review, &decision) == BTB_DEPLOYMENT_OK);
        CHECK(decision.status == BTB_DEPLOYMENT_BLOCKED);
        CHECK((decision.missingEvidence & BTB_DEPLOYMENT_MISSING_RUNTIME_CHECK) != 0U);
    } else if (strcmp(name, "missing-config") == 0) {
        CHECK(PrepareFull(&review, 1));
        review.stage.configurationReviewed = 0;
        CHECK(BtbDeploymentEvaluate(&review, &decision) == BTB_DEPLOYMENT_OK);
        CHECK((decision.missingEvidence & BTB_DEPLOYMENT_MISSING_CONFIG_REVIEW) != 0U);
    } else if (strcmp(name, "stale-verification") == 0) {
        CHECK(PrepareFull(&review, 1));
        review.stage.verificationCaptureId = 200U;
        CHECK(BtbDeploymentEvaluate(&review, &decision) == BTB_DEPLOYMENT_OK);
        CHECK((decision.missingEvidence & BTB_DEPLOYMENT_STALE_CAPTURE) != 0U);
    } else if (strcmp(name, "fully-qualified") == 0) {
        CHECK(PrepareFull(&review, 1));
        CHECK(BtbDeploymentEvaluate(&review, &decision) == BTB_DEPLOYMENT_OK);
        CHECK(decision.status == BTB_DEPLOYMENT_QUALIFIED);
        CHECK(decision.missingEvidence == 0U);
    } else if (strcmp(name, "rollback") == 0) {
        CHECK(PrepareFull(&review, 0));
        CHECK(BtbDeploymentEvaluate(&review, &decision) == BTB_DEPLOYMENT_OK);
        CHECK(decision.status == BTB_DEPLOYMENT_ROLLBACK_REQUIRED);
    } else if (strcmp(name, "restored") == 0) {
        BtbServiceSummary restored;
        CHECK(PrepareFull(&review, 0));
        maintenance = review.maintenance;
        PrepareSummary(&restored, 300U, BTB_ADMIN_READY);
        CHECK(BtbMaintenanceConfirmRestored(&maintenance, &restored) == BTB_MAINTENANCE_OK);
        CHECK(BtbDeploymentUpdateMaintenance(&review, &maintenance) == BTB_DEPLOYMENT_OK);
        CHECK(BtbDeploymentEvaluate(&review, &decision) == BTB_DEPLOYMENT_OK);
        CHECK(decision.status == BTB_DEPLOYMENT_RESTORED_ONLY);
    } else if (strcmp(name, "copy-ownership") == 0) {
        CHECK(BtbDeploymentAttachStage(&review, &evidence) == BTB_DEPLOYMENT_OK);
        evidence.packageHashCompared = 0;
        CHECK(review.stage.packageHashCompared == 1);
    } else if (strcmp(name, "replayed-evidence") == 0) {
        CHECK(BtbDeploymentAttachStage(&review, &evidence) == BTB_DEPLOYMENT_OK);
        preserved = review;
        CHECK(BtbDeploymentAttachStage(&review, &evidence) == BTB_DEPLOYMENT_STATE_ERROR);
        CHECK(memcmp(&review, &preserved, sizeof review) == 0);
    } else if (strcmp(name, "maintenance-changed") == 0) {
        maintenance.before.captureId += 1U;
        CHECK(BtbDeploymentUpdateMaintenance(&review, &maintenance) == BTB_DEPLOYMENT_MISMATCH);
        CHECK(memcmp(&review, &preserved, sizeof review) == 0);
    } else if (strcmp(name, "maintenance-regress") == 0) {
        CHECK(PrepareFull(&review, 1));
        preserved = review;
        /* A prior, otherwise matching VERIFIED revision may not rewind COMPLETE. */
        maintenance = review.maintenance;
        maintenance.state = BTB_MAINTENANCE_VERIFIED;
        CHECK(BtbDeploymentUpdateMaintenance(&review, &maintenance) == BTB_DEPLOYMENT_STATE_ERROR);
        CHECK(memcmp(&review, &preserved, sizeof review) == 0);
    } else if (strcmp(name, "preserve-output") == 0) {
        (void)memset(&decision, 0x5AU, sizeof decision);
        BtbDeploymentDecision saved = decision;
        review.plan.sourceRevision[0] = 'x';
        CHECK(BtbDeploymentEvaluate(&review, &decision) == BTB_DEPLOYMENT_INVALID);
        CHECK(memcmp(&decision, &saved, sizeof decision) == 0);
    } else if (strcmp(name, "mutation") == 0) {
        uint32_t seed = UINT32_C(0x98273451);
        for (size_t i = 0U; i < 30000U; ++i) {
            BtbDeploymentEvidence sample;
            BtbDeploymentDecision result;
            CHECK(PrepareFull(&review, 1));
            sample = review.stage;
            seed = seed * UINT32_C(1664525) + UINT32_C(1013904223);
            const unsigned selector = (unsigned)(seed % 6U);
            if (selector == 0U) sample.runtimeDependenciesChecked = 0;
            if (selector == 1U) sample.privateStageInspected = 0;
            if (selector == 2U) sample.entryPointProbed = 0;
            if (selector == 3U) sample.packageHashCompared = 0;
            if (selector == 4U) sample.configurationReviewed = 0;
            if (selector == 5U) sample.verificationCaptureId = 200U;
            review.stage = sample;
            CHECK(BtbDeploymentEvaluate(&review, &result) == BTB_DEPLOYMENT_OK);
            CHECK(result.status == BTB_DEPLOYMENT_BLOCKED);
            CHECK(result.missingEvidence != 0U);
        }
    } else {
        fprintf(stderr, "Unknown scenario: %s\n", name);
        return 1;
    }
    return 0;
}
int main(int argc, char **argv)
{
    if (argc != 2) {
        fprintf(stderr, "Usage: btb-deployment-review-test SCENARIO\n");
        return 2;
    }
    return Scenario(argv[1]);
}
