/*-----------------------------------------------------------------------------
 * Bits2Banking | Umicom Foundation | Sammy Hegab | MIT
 * File: labs/native/deployment-rehearsal/deployment_review.c
 * PURPOSE: Fail-closed, copy-owned release-stage qualification exercise.
 *
 * No filesystem/process/network/service operation occurs. The existing
 * BtbMaintenanceReview remains the authority for the *teaching* maintenance
 * lifecycle. Only deployment-specific stage observations are considered here.
 *---------------------------------------------------------------------------*/
#include "deployment_review.h"
#include <string.h>

static int HasTerminator(const char *text, size_t capacity)
{
    return text != NULL && capacity != 0U && memchr(text, '\0', capacity) != NULL;
}

static int ValidHex(const char *text, size_t capacity, int allowSha1)
{
    if (!HasTerminator(text, capacity)) return 0;
    const size_t length = strlen(text);
    if (length != 64U && !(allowSha1 && length == 40U)) return 0;
    for (size_t i = 0U; i < length; ++i) {
        const unsigned char c = (unsigned char)text[i];
        if (!((c >= (unsigned char)'0' && c <= (unsigned char)'9') ||
              (c >= (unsigned char)'a' && c <= (unsigned char)'f') ||
              (c >= (unsigned char)'A' && c <= (unsigned char)'F'))) return 0;
    }
    return 1;
}

static int ValidLabel(const char *text, size_t capacity)
{
    if (!HasTerminator(text, capacity) || text[0] == '\0') return 0;
    const size_t length = strlen(text);
    for (size_t i = 0U; i < length; ++i) {
        const unsigned char c = (unsigned char)text[i];
        if (!((c >= (unsigned char)'0' && c <= (unsigned char)'9') ||
              (c >= (unsigned char)'A' && c <= (unsigned char)'Z') ||
              (c >= (unsigned char)'a' && c <= (unsigned char)'z') ||
              c == (unsigned char)'-' || c == (unsigned char)'_' ||
              c == (unsigned char)'.')) return 0;
    }
    return 1;
}

/* This is only a human-readable label, not a path permission policy. The
 * exercise uses an explicit 'practice-' prefix and prohibits path separators. */
static int ValidPrivateStage(const char *value, size_t capacity)
{
    if (!ValidLabel(value, capacity)) return 0;
    return strncmp(value, "practice-", 9U) == 0 && strlen(value) > 9U;
}

static int ValidPlan(const BtbDeploymentPlan *plan)
{
    return plan != NULL &&
        ValidLabel(plan->releaseId, sizeof plan->releaseId) &&
        ValidHex(plan->sourceRevision, sizeof plan->sourceRevision, 1) &&
        ValidHex(plan->packageSha256, sizeof plan->packageSha256, 0) &&
        ValidHex(plan->configurationSha256, sizeof plan->configurationSha256, 0) &&
        ValidPrivateStage(plan->privateStage, sizeof plan->privateStage);
}

/* A bounded explanation call verifies the *shape* of the existing maintenance
 * review; it does not establish human authority or prove a production test. */
static int ValidMaintenance(const BtbMaintenanceReview *maintenance)
{
    char explanation[BTB_MAINTENANCE_SUMMARY_BYTES];
    return maintenance != NULL &&
        BtbMaintenanceExplain(maintenance, explanation, sizeof explanation)
            == BTB_MAINTENANCE_OK;
}

static int SameBase(const BtbMaintenanceReview *old,
                    const BtbMaintenanceReview *next)
{
    return strcmp(old->changeId, next->changeId) == 0 &&
        strcmp(old->sourceRevision, next->sourceRevision) == 0 &&
        strcmp(old->operatorId, next->operatorId) == 0 &&
        memcmp(&old->before, &next->before, sizeof old->before) == 0 &&
        (old->approverId[0] == '\0' ||
            strcmp(old->approverId, next->approverId) == 0);
}

static int ValidReview(const BtbDeploymentReview *review)
{
    return review != NULL && ValidPlan(&review->plan) &&
        ValidMaintenance(&review->maintenance) &&
        strcmp(review->plan.sourceRevision, review->maintenance.sourceRevision) == 0 &&
        (review->hasStage == 0 || review->hasStage == 1);
}

BtbDeploymentResult BtbDeploymentInit(BtbDeploymentReview *review,
    const BtbDeploymentPlan *plan, const BtbMaintenanceReview *maintenance)
{
    if (review == NULL || !ValidPlan(plan) || !ValidMaintenance(maintenance))
        return BTB_DEPLOYMENT_INVALID;
    if (strcmp(plan->sourceRevision, maintenance->sourceRevision) != 0)
        return BTB_DEPLOYMENT_MISMATCH;
    BtbDeploymentReview candidate = {0};
    candidate.plan = *plan;
    candidate.maintenance = *maintenance;
    *review = candidate;
    return BTB_DEPLOYMENT_OK;
}

static int ValidEvidence(const BtbDeploymentEvidence *stage)
{
    if (stage == NULL || stage->stageCaptureId == 0U ||
        stage->verificationCaptureId == 0U ||
        !ValidHex(stage->observedSourceRevision,
                  sizeof stage->observedSourceRevision, 1) ||
        !ValidHex(stage->observedPackageSha256,
                  sizeof stage->observedPackageSha256, 0)) return 0;
    return (stage->packageHashCompared == 0 || stage->packageHashCompared == 1) &&
        (stage->configurationReviewed == 0 || stage->configurationReviewed == 1) &&
        (stage->runtimeDependenciesChecked == 0 || stage->runtimeDependenciesChecked == 1) &&
        (stage->privateStageInspected == 0 || stage->privateStageInspected == 1) &&
        (stage->entryPointProbed == 0 || stage->entryPointProbed == 1);
}

BtbDeploymentResult BtbDeploymentAttachStage(BtbDeploymentReview *review,
    const BtbDeploymentEvidence *stage)
{
    if (!ValidReview(review) || !ValidEvidence(stage)) return BTB_DEPLOYMENT_INVALID;
    if (strcmp(stage->observedSourceRevision, review->plan.sourceRevision) != 0 ||
        strcmp(stage->observedPackageSha256, review->plan.packageSha256) != 0)
        return BTB_DEPLOYMENT_MISMATCH;
    if (review->hasStage && stage->verificationCaptureId <= review->stage.verificationCaptureId)
        return BTB_DEPLOYMENT_STATE_ERROR;
    BtbDeploymentReview candidate = *review;
    candidate.stage = *stage;
    candidate.hasStage = 1;
    *review = candidate;
    return BTB_DEPLOYMENT_OK;
}

BtbDeploymentResult BtbDeploymentUpdateMaintenance(BtbDeploymentReview *review,
    const BtbMaintenanceReview *maintenance)
{
    if (!ValidReview(review) || !ValidMaintenance(maintenance)) return BTB_DEPLOYMENT_INVALID;
    if (!SameBase(&review->maintenance, maintenance)) return BTB_DEPLOYMENT_MISMATCH;
    /* The maintenance enum is progression-oriented. Do not accept a snapshot
     * that rewinds an already reviewed lifecycle. No 'git reset' analogues. */
    if (maintenance->state < review->maintenance.state)
        return BTB_DEPLOYMENT_STATE_ERROR;
    BtbDeploymentReview candidate = *review;
    candidate.maintenance = *maintenance;
    *review = candidate;
    return BTB_DEPLOYMENT_OK;
}

BtbDeploymentResult BtbDeploymentEvaluate(const BtbDeploymentReview *review,
    BtbDeploymentDecision *outDecision)
{
    if (!ValidReview(review) || outDecision == NULL ||
        (review->hasStage && !ValidEvidence(&review->stage)))
        return BTB_DEPLOYMENT_INVALID;
    BtbDeploymentDecision candidate = {0};
    candidate.baselineCaptureId = review->maintenance.before.captureId;
    candidate.status = BTB_DEPLOYMENT_BLOCKED;
    if (!review->hasStage) {
        candidate.missingEvidence |= BTB_DEPLOYMENT_MISSING_STAGE;
    } else {
        const BtbDeploymentEvidence *stage = &review->stage;
        if (strcmp(stage->observedSourceRevision, review->plan.sourceRevision) != 0 ||
            strcmp(stage->observedPackageSha256, review->plan.packageSha256) != 0)
            return BTB_DEPLOYMENT_MISMATCH;
        candidate.stageCaptureId = stage->stageCaptureId;
        candidate.verificationCaptureId = stage->verificationCaptureId;
        if (!stage->packageHashCompared) candidate.missingEvidence |= BTB_DEPLOYMENT_MISSING_PACKAGE_CHECK;
        if (!stage->configurationReviewed) candidate.missingEvidence |= BTB_DEPLOYMENT_MISSING_CONFIG_REVIEW;
        if (!stage->runtimeDependenciesChecked) candidate.missingEvidence |= BTB_DEPLOYMENT_MISSING_RUNTIME_CHECK;
        if (!stage->privateStageInspected) candidate.missingEvidence |= BTB_DEPLOYMENT_MISSING_PRIVATE_STAGE;
        if (!stage->entryPointProbed) candidate.missingEvidence |= BTB_DEPLOYMENT_MISSING_ENTRYPOINT;
        if (stage->stageCaptureId <= review->maintenance.before.captureId ||
            stage->verificationCaptureId <= stage->stageCaptureId ||
            (review->maintenance.hasAfter &&
             stage->verificationCaptureId <= review->maintenance.after.captureId))
            candidate.missingEvidence |= BTB_DEPLOYMENT_STALE_CAPTURE;
    }
    /* Rollback and restoration are distinct terminal outcomes; a restored
     * baseline must never be relabelled as successful new deployment. */
    if (review->maintenance.state == BTB_MAINTENANCE_ROLLBACK_REQUIRED)
        candidate.status = BTB_DEPLOYMENT_ROLLBACK_REQUIRED;
    else if (review->maintenance.state == BTB_MAINTENANCE_RESTORED)
        candidate.status = BTB_DEPLOYMENT_RESTORED_ONLY;
    else {
        if (review->maintenance.state != BTB_MAINTENANCE_COMPLETE)
            candidate.missingEvidence |= BTB_DEPLOYMENT_MISSING_MAINTENANCE;
        if (!review->maintenance.hasAfter)
            candidate.missingEvidence |= BTB_DEPLOYMENT_MISSING_MAINTENANCE;
        if (candidate.missingEvidence == 0U)
            candidate.status = BTB_DEPLOYMENT_QUALIFIED;
        else if (review->maintenance.state == BTB_MAINTENANCE_PLANNED ||
                 review->maintenance.state == BTB_MAINTENANCE_APPROVED ||
                 review->maintenance.state == BTB_MAINTENANCE_STARTED)
            candidate.status = BTB_DEPLOYMENT_PENDING;
    }
    *outDecision = candidate;
    return BTB_DEPLOYMENT_OK;
}

const char *BtbDeploymentStatusText(BtbDeploymentStatus status)
{
    switch (status) {
        case BTB_DEPLOYMENT_PENDING: return "PENDING";
        case BTB_DEPLOYMENT_BLOCKED: return "BLOCKED";
        case BTB_DEPLOYMENT_QUALIFIED: return "QUALIFIED";
        case BTB_DEPLOYMENT_ROLLBACK_REQUIRED: return "ROLLBACK_REQUIRED";
        case BTB_DEPLOYMENT_RESTORED_ONLY: return "RESTORED_ONLY";
        default: return "UNKNOWN";
    }
}
const char *BtbDeploymentResultText(BtbDeploymentResult result)
{
    switch (result) {
        case BTB_DEPLOYMENT_OK: return "OK";
        case BTB_DEPLOYMENT_INVALID: return "INVALID";
        case BTB_DEPLOYMENT_MISMATCH: return "MISMATCH";
        case BTB_DEPLOYMENT_STATE_ERROR: return "STATE_ERROR";
        default: return "UNKNOWN";
    }
}
