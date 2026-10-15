/*-----------------------------------------------------------------------------
 * Bits2Banking | Umicom Foundation | Sammy Hegab | MIT
 * File: labs/native/remote-access-review/remote_access_review.c
 * PURPOSE: Offline, fail-closed remote-access preflight over the existing C23
 *          deployment-review contract. No OS or network side effects.
 *---------------------------------------------------------------------------*/
#include "remote_access_review.h"
#include <ctype.h>
#include <stddef.h>
#include <string.h>

/* Fixed-array strings may come from malformed external records. Never call
 * strlen or strcmp until a terminator is found within the declared capacity. */
static int Terminated(const char *value, size_t capacity)
{
    return value != NULL && capacity > 0U &&
           memchr(value, '\0', capacity) != NULL;
}

static int SafeLabel(const char *value, size_t capacity)
{
    if (!Terminated(value, capacity) || value[0] == '\0') return 0;
    for (size_t i = 0U; value[i] != '\0'; ++i) {
        const unsigned char character = (unsigned char)value[i];
        if (!((character >= (unsigned char)'a' && character <= (unsigned char)'z') ||
              (character >= (unsigned char)'A' && character <= (unsigned char)'Z') ||
              (character >= (unsigned char)'0' && character <= (unsigned char)'9') ||
              character == (unsigned char)'-' || character == (unsigned char)'_' ||
              character == (unsigned char)'.')) return 0;
    }
    return 1;
}

static int ValidSha(const char *value, size_t capacity)
{
    if (!Terminated(value, capacity)) return 0;
    const size_t n = strlen(value);
    if (n != 40U && n != 64U) return 0;
    for (size_t i = 0U; i < n; ++i) {
        if (!isxdigit((unsigned char)value[i])) return 0;
    }
    return 1;
}

static int ValidPlan(const BtbRemotePlan *plan)
{
    return plan != NULL &&
           SafeLabel(plan->serviceId, sizeof plan->serviceId) &&
           SafeLabel(plan->hostLabel, sizeof plan->hostLabel) &&
           SafeLabel(plan->requestingOperator, sizeof plan->requestingOperator) &&
           SafeLabel(plan->independentReviewer, sizeof plan->independentReviewer) &&
           strcmp(plan->requestingOperator, plan->independentReviewer) != 0 &&
           ValidSha(plan->sourceRevision, sizeof plan->sourceRevision) &&
           plan->changeTicket != 0U &&
           plan->windowStartSeconds != 0U &&
           plan->windowEndSeconds > plan->windowStartSeconds;
}

static int BooleanFlag(int value) { return value == 0 || value == 1; }
static int ValidEvidence(const BtbRemoteEvidence *e)
{
    return e != NULL && e->captureId > 0U &&
           e->observationSeconds > 0U &&
           ValidSha(e->observedSourceRevision, sizeof e->observedSourceRevision) &&
           BooleanFlag(e->hostIdentityIndependentlyChecked) &&
           BooleanFlag(e->authenticatedTransportReviewed) &&
           BooleanFlag(e->destinationScopeReviewed) &&
           BooleanFlag(e->leastPrivilegeReviewed) &&
           BooleanFlag(e->credentialsExcludedFromLogs) &&
           BooleanFlag(e->recoveryPlanAvailable) &&
           BooleanFlag(e->separateReviewerRecorded) &&
           BooleanFlag(e->readOnlyTrialObserved);
}

BtbRemoteResult BtbRemoteInit(BtbRemoteReview *review,
                              const BtbRemotePlan *plan,
                              const BtbDeploymentReview *deployment)
{
    BtbDeploymentDecision decision;
    if (review == NULL || !ValidPlan(plan) || deployment == NULL)
        return BTB_REMOTE_INVALID;
    /* Do not assume the upstream record is valid merely because its pointers
     * exist. Reuse the authoritative educational deployment evaluator. */
    if (BtbDeploymentEvaluate(deployment, &decision) != BTB_DEPLOYMENT_OK)
        return BTB_REMOTE_INVALID;
    if (strcmp(plan->sourceRevision, deployment->plan.sourceRevision) != 0)
        return BTB_REMOTE_MISMATCH;
    const BtbRemoteReview next = {.plan = *plan, .deployment = *deployment};
    *review = next;
    return BTB_REMOTE_OK;
}

BtbRemoteResult BtbRemoteAttach(BtbRemoteReview *review,
                                const BtbRemoteEvidence *evidence)
{
    BtbDeploymentDecision decision;
    if (review == NULL || evidence == NULL || !ValidEvidence(evidence))
        return BTB_REMOTE_INVALID;
    if (!ValidPlan(&review->plan) ||
        BtbDeploymentEvaluate(&review->deployment, &decision) != BTB_DEPLOYMENT_OK)
        return BTB_REMOTE_INVALID;
    if (review->hasEvidence != 0) return BTB_REMOTE_STATE_ERROR;
    if (strcmp(evidence->observedSourceRevision, review->plan.sourceRevision) != 0)
        return BTB_REMOTE_MISMATCH;
    BtbRemoteReview next = *review;
    next.evidence = *evidence;
    next.hasEvidence = 1;
    *review = next;
    return BTB_REMOTE_OK;
}

BtbRemoteResult BtbRemoteEvaluate(const BtbRemoteReview *review,
                                  BtbRemoteDecision *outDecision)
{
    BtbDeploymentDecision deployment;
    if (review == NULL || outDecision == NULL || !ValidPlan(&review->plan) ||
        (review->hasEvidence != 0 && review->hasEvidence != 1) ||
        (review->hasEvidence && !ValidEvidence(&review->evidence)) ||
        BtbDeploymentEvaluate(&review->deployment, &deployment) != BTB_DEPLOYMENT_OK)
        return BTB_REMOTE_INVALID;
    if (strcmp(review->plan.sourceRevision, review->deployment.plan.sourceRevision) != 0)
        return BTB_REMOTE_MISMATCH;
    BtbRemoteDecision next = {0};
    next.status = BTB_REMOTE_BLOCKED;
    next.deploymentStatus = deployment.status;
    next.deploymentVerificationCapture = deployment.verificationCaptureId;
    if (deployment.status == BTB_DEPLOYMENT_RESTORED_ONLY) {
        next.status = BTB_REMOTE_RESTORED_ONLY;
    } else if (deployment.status != BTB_DEPLOYMENT_QUALIFIED) {
        next.missingEvidence |= BTB_REMOTE_DEPLOYMENT_UNQUALIFIED;
    }
    if (!review->hasEvidence) {
        next.missingEvidence |= BTB_REMOTE_MISSING_OBSERVATION;
        if (deployment.status == BTB_DEPLOYMENT_PENDING) next.status = BTB_REMOTE_PENDING;
    } else {
        const BtbRemoteEvidence *e = &review->evidence;
        if (strcmp(e->observedSourceRevision, review->plan.sourceRevision) != 0)
            return BTB_REMOTE_MISMATCH;
        next.accessObservationCapture = e->captureId;
        if (!e->hostIdentityIndependentlyChecked)
            next.missingEvidence |= BTB_REMOTE_MISSING_HOST_IDENTITY;
        if (!e->authenticatedTransportReviewed)
            next.missingEvidence |= BTB_REMOTE_MISSING_TRANSPORT;
        if (!e->destinationScopeReviewed)
            next.missingEvidence |= BTB_REMOTE_MISSING_SCOPE;
        if (!e->leastPrivilegeReviewed)
            next.missingEvidence |= BTB_REMOTE_MISSING_LEAST_PRIVILEGE;
        if (!e->credentialsExcludedFromLogs)
            next.missingEvidence |= BTB_REMOTE_MISSING_CREDENTIAL_SAFETY;
        if (!e->recoveryPlanAvailable)
            next.missingEvidence |= BTB_REMOTE_MISSING_RECOVERY_PLAN;
        if (!e->separateReviewerRecorded)
            next.missingEvidence |= BTB_REMOTE_MISSING_REVIEWER;
        if (!e->readOnlyTrialObserved)
            next.missingEvidence |= BTB_REMOTE_MISSING_READ_ONLY_TRIAL;
        if (e->captureId <= deployment.verificationCaptureId)
            next.missingEvidence |= BTB_REMOTE_STALE_CAPTURE;
        if (e->observationSeconds < review->plan.windowStartSeconds ||
            e->observationSeconds >= review->plan.windowEndSeconds)
            next.missingEvidence |= BTB_REMOTE_OUTSIDE_WINDOW;
        if (next.missingEvidence == 0U &&
            deployment.status == BTB_DEPLOYMENT_QUALIFIED)
            next.status = BTB_REMOTE_REVIEWABLE;
    }
    *outDecision = next;
    return BTB_REMOTE_OK;
}

const char *BtbRemoteStatusText(BtbRemoteStatus status)
{
    switch (status) {
        case BTB_REMOTE_PENDING: return "PENDING";
        case BTB_REMOTE_BLOCKED: return "BLOCKED";
        case BTB_REMOTE_REVIEWABLE: return "REVIEWABLE";
        case BTB_REMOTE_RESTORED_ONLY: return "RESTORED_ONLY";
        default: return "UNKNOWN";
    }
}
