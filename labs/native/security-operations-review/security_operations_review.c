/*-----------------------------------------------------------------------------
 * Bits2Banking | Umicom Foundation | Sammy Hegab | MIT
 * File: labs/native/security-operations-review/security_operations_review.c
 * PURPOSE: Checked policy composition, never machine administration.
 *---------------------------------------------------------------------------*/
#include "security_operations_review.h"
#include <ctype.h>
#include <stddef.h>
#include <string.h>

/* Avoid scanning past a fixed-width caller-owned byte array. The label
 * alphabet deliberately excludes terminal control sequences and whitespace. */
static int ValidLabel(const char *value, size_t capacity)
{
    size_t i;
    if (value == NULL || capacity < 2U || value[0] == '\0') return 0;
    for (i = 0U; i < capacity; ++i) {
        const unsigned char c = (unsigned char)value[i];
        if (c == '\0') return i > 0U;
        if (!((c >= (unsigned char)'a' && c <= (unsigned char)'z') ||
              (c >= (unsigned char)'A' && c <= (unsigned char)'Z') ||
              (c >= (unsigned char)'0' && c <= (unsigned char)'9') ||
              c == (unsigned char)'_' || c == (unsigned char)'-' ||
              c == (unsigned char)'.')) return 0;
    }
    return 0;
}

static int ValidSha256(const char *value, size_t capacity)
{
    size_t i;
    if (value == NULL || capacity < 65U || value[64] != '\0') return 0;
    for (i = 0U; i < 64U; ++i) {
        const unsigned char c = (unsigned char)value[i];
        if (!((c >= (unsigned char)'0' && c <= (unsigned char)'9') ||
              (c >= (unsigned char)'a' && c <= (unsigned char)'f'))) return 0;
    }
    return 1;
}

static int ValidRevision(const char *value, size_t capacity)
{
    size_t i, len = 0U;
    if (value == NULL || capacity < 41U) return 0;
    while (len < capacity && value[len] != '\0') ++len;
    if (len != 40U && len != 64U) return 0;
    for (i = 0U; i < len; ++i) {
        const unsigned char c = (unsigned char)value[i];
        if (!((c >= (unsigned char)'0' && c <= (unsigned char)'9') ||
              (c >= (unsigned char)'a' && c <= (unsigned char)'f'))) return 0;
    }
    return 1;
}

static int ValidPlan(const BtbSecurityPlan *plan)
{
    return plan != NULL &&
        ValidLabel(plan->serviceId, sizeof plan->serviceId) &&
        ValidLabel(plan->requestingOperator, sizeof plan->requestingOperator) &&
        ValidLabel(plan->independentReviewer, sizeof plan->independentReviewer) &&
        strcmp(plan->requestingOperator, plan->independentReviewer) != 0 &&
        ValidRevision(plan->sourceRevision, sizeof plan->sourceRevision) &&
        ValidSha256(plan->configurationSha256, sizeof plan->configurationSha256) &&
        ValidLabel(plan->policyRevision, sizeof plan->policyRevision) &&
        plan->changeTicket != 0U &&
        plan->reviewWindowStartSeconds != 0U &&
        plan->reviewWindowEndSeconds > plan->reviewWindowStartSeconds;
}

static int ValidFlag(int value) { return value == 0 || value == 1; }

static int ValidEvidence(const BtbSecurityEvidence *evidence)
{
    if (evidence == NULL || evidence->captureId == 0U ||
        evidence->observationSeconds == 0U ||
        !ValidRevision(evidence->observedSourceRevision,
                       sizeof evidence->observedSourceRevision) ||
        !ValidSha256(evidence->observedConfigurationSha256,
                     sizeof evidence->observedConfigurationSha256) ||
        !ValidLabel(evidence->observedPolicyRevision,
                    sizeof evidence->observedPolicyRevision)) return 0;
    return ValidFlag(evidence->accountsReviewed) &&
           ValidFlag(evidence->groupMembershipReviewed) &&
           ValidFlag(evidence->leastPrivilegeReviewed) &&
           ValidFlag(evidence->configurationCompared) &&
           ValidFlag(evidence->unexplainedDriftAbsent) &&
           ValidFlag(evidence->patchEvidenceReviewed) &&
           ValidFlag(evidence->independentRestoreTestRecorded) &&
           ValidFlag(evidence->auditRetentionReviewed) &&
           ValidFlag(evidence->credentialsExcludedFromEvidence) &&
           ValidFlag(evidence->credentialRotationPlanReviewed) &&
           ValidFlag(evidence->certificateExpiryReviewed) &&
           ValidFlag(evidence->independentApprovalRecorded) &&
           ValidFlag(evidence->monitoringResponsePathReviewed);
}

/* Both source and scope must refer to the exact upstream object being used.
 * Re-evaluation of the upstream remote policy occurs in Evaluate. */
BtbSecurityResult BtbSecurityInit(BtbSecurityReview *review,
                                  const BtbSecurityPlan *plan,
                                  const BtbRemoteReview *remote)
{
    BtbSecurityReview candidate = {0};
    BtbRemoteDecision upstream;
    if (review == NULL || !ValidPlan(plan) || remote == NULL ||
        (remote->hasEvidence != 0 && remote->hasEvidence != 1) ||
        BtbRemoteEvaluate(remote, &upstream) != BTB_REMOTE_OK)
        return BTB_SECURITY_INVALID;
    if (strcmp(plan->serviceId, remote->plan.serviceId) != 0 ||
        strcmp(plan->requestingOperator, remote->plan.requestingOperator) != 0 ||
        strcmp(plan->independentReviewer, remote->plan.independentReviewer) != 0 ||
        strcmp(plan->sourceRevision, remote->plan.sourceRevision) != 0 ||
        plan->changeTicket != remote->plan.changeTicket ||
        plan->reviewWindowStartSeconds != remote->plan.windowStartSeconds ||
        plan->reviewWindowEndSeconds != remote->plan.windowEndSeconds)
        return BTB_SECURITY_MISMATCH;
    candidate.plan = *plan;
    candidate.remote = *remote;
    *review = candidate;
    return BTB_SECURITY_OK;
}

BtbSecurityResult BtbSecurityAttach(BtbSecurityReview *review,
                                    const BtbSecurityEvidence *evidence)
{
    if (review == NULL || !ValidPlan(&review->plan) ||
        !ValidEvidence(evidence) ||
        (review->hasEvidence != 0 && review->hasEvidence != 1))
        return BTB_SECURITY_INVALID;
    if (review->hasEvidence != 0) return BTB_SECURITY_STATE_ERROR;
    if (strcmp(evidence->observedSourceRevision,
               review->plan.sourceRevision) != 0 ||
        strcmp(evidence->observedConfigurationSha256,
               review->plan.configurationSha256) != 0 ||
        strcmp(evidence->observedPolicyRevision,
               review->plan.policyRevision) != 0) return BTB_SECURITY_MISMATCH;
    review->evidence = *evidence;
    review->hasEvidence = 1;
    return BTB_SECURITY_OK;
}

BtbSecurityResult BtbSecurityEvaluate(const BtbSecurityReview *review,
                                      BtbSecurityDecision *outDecision)
{
    BtbRemoteDecision upstream;
    BtbSecurityDecision candidate = {0};
    const BtbSecurityEvidence *e;
    if (review == NULL || outDecision == NULL ||
        !ValidPlan(&review->plan) ||
        (review->hasEvidence != 0 && review->hasEvidence != 1) ||
        BtbRemoteEvaluate(&review->remote, &upstream) != BTB_REMOTE_OK)
        return BTB_SECURITY_INVALID;
    if (strcmp(review->plan.serviceId, review->remote.plan.serviceId) != 0 ||
        strcmp(review->plan.sourceRevision, review->remote.plan.sourceRevision) != 0 ||
        strcmp(review->plan.requestingOperator,
               review->remote.plan.requestingOperator) != 0 ||
        strcmp(review->plan.independentReviewer,
               review->remote.plan.independentReviewer) != 0 ||
        review->plan.changeTicket != review->remote.plan.changeTicket ||
        review->plan.reviewWindowStartSeconds !=
            review->remote.plan.windowStartSeconds ||
        review->plan.reviewWindowEndSeconds !=
            review->remote.plan.windowEndSeconds)
        return BTB_SECURITY_MISMATCH;
    if (review->hasEvidence != 0 && !ValidEvidence(&review->evidence))
        return BTB_SECURITY_INVALID;
    if (review->hasEvidence != 0 &&
        (strcmp(review->evidence.observedSourceRevision,
                review->plan.sourceRevision) != 0 ||
         strcmp(review->evidence.observedConfigurationSha256,
                review->plan.configurationSha256) != 0 ||
         strcmp(review->evidence.observedPolicyRevision,
                review->plan.policyRevision) != 0))
        return BTB_SECURITY_MISMATCH;

    candidate.remoteStatus = upstream.status;
    candidate.remoteObservationCapture = upstream.accessObservationCapture;
    candidate.securityObservationCapture =
        review->hasEvidence != 0 ? review->evidence.captureId : 0U;
    if (upstream.status != BTB_REMOTE_REVIEWABLE)
        candidate.missingEvidence |= BTB_SECURITY_UPSTREAM_UNQUALIFIED;
    if (review->hasEvidence == 0) {
        candidate.missingEvidence |= BTB_SECURITY_MISSING_OBSERVATION;
        candidate.status = BTB_SECURITY_PENDING;
        *outDecision = candidate;
        return BTB_SECURITY_OK;
    }
    e = &review->evidence;
#define MISSING_IF_FALSE(field, bit) \
    do { if ((e->field) == 0) candidate.missingEvidence |= (bit); } while (0)
    MISSING_IF_FALSE(accountsReviewed, BTB_SECURITY_MISSING_ACCOUNT_REVIEW);
    MISSING_IF_FALSE(groupMembershipReviewed, BTB_SECURITY_MISSING_GROUP_REVIEW);
    MISSING_IF_FALSE(leastPrivilegeReviewed, BTB_SECURITY_MISSING_LEAST_PRIVILEGE);
    MISSING_IF_FALSE(configurationCompared, BTB_SECURITY_MISSING_CONFIG_CHECK);
    MISSING_IF_FALSE(unexplainedDriftAbsent, BTB_SECURITY_UNEXPLAINED_DRIFT);
    MISSING_IF_FALSE(patchEvidenceReviewed, BTB_SECURITY_MISSING_PATCH_EVIDENCE);
    MISSING_IF_FALSE(independentRestoreTestRecorded,
                     BTB_SECURITY_MISSING_RESTORE_TEST);
    MISSING_IF_FALSE(auditRetentionReviewed, BTB_SECURITY_MISSING_AUDIT_REVIEW);
    MISSING_IF_FALSE(credentialsExcludedFromEvidence,
                     BTB_SECURITY_CREDENTIAL_EXPOSURE_RISK);
    MISSING_IF_FALSE(credentialRotationPlanReviewed,
                     BTB_SECURITY_MISSING_ROTATION_REVIEW);
    MISSING_IF_FALSE(certificateExpiryReviewed,
                     BTB_SECURITY_MISSING_CERTIFICATE_REVIEW);
    MISSING_IF_FALSE(independentApprovalRecorded,
                     BTB_SECURITY_MISSING_APPROVAL);
    MISSING_IF_FALSE(monitoringResponsePathReviewed,
                     BTB_SECURITY_MISSING_RESPONSE_PATH);
#undef MISSING_IF_FALSE
    if (e->captureId <= upstream.accessObservationCapture)
        candidate.missingEvidence |= BTB_SECURITY_STALE_CAPTURE;
    if (e->observationSeconds < review->plan.reviewWindowStartSeconds ||
        e->observationSeconds >= review->plan.reviewWindowEndSeconds)
        candidate.missingEvidence |= BTB_SECURITY_OUTSIDE_REVIEW_WINDOW;
    if (upstream.status == BTB_REMOTE_RESTORED_ONLY)
        candidate.status = BTB_SECURITY_RESTORED_ONLY;
    else if (candidate.missingEvidence == 0U)
        candidate.status = BTB_SECURITY_REVIEWABLE;
    else
        candidate.status = BTB_SECURITY_BLOCKED;
    *outDecision = candidate;
    return BTB_SECURITY_OK;
}

const char *BtbSecurityStatusText(BtbSecurityStatus status)
{
    switch (status) {
        case BTB_SECURITY_PENDING: return "PENDING";
        case BTB_SECURITY_BLOCKED: return "BLOCKED";
        case BTB_SECURITY_REVIEWABLE: return "REVIEWABLE";
        case BTB_SECURITY_RESTORED_ONLY: return "RESTORED_ONLY";
        default: return "INVALID";
    }
}
