/*-----------------------------------------------------------------------------
 * Bits2Banking | Umicom Foundation | Sammy Hegab | MIT
 * File: labs/native/operational-resilience/operations_review.c
 * PURPOSE: Checked, non-operational C23 composition of existing evidence.
 *---------------------------------------------------------------------------*/
#include "operations_review.h"
#include <stddef.h>
#include <stdint.h>
#include <string.h>

/* Do not inspect untrusted fixed arrays with strcmp before finding a NUL. */
static int ValidIdentifier(const char *bytes, size_t capacity)
{
    size_t i;
    if (bytes == NULL || capacity < 2U || bytes[0] == '\0') return 0;
    for (i = 0U; i < capacity; ++i) {
        const unsigned char c = (unsigned char)bytes[i];
        if (c == '\0') return i > 0U;
        if (!((c >= (unsigned char)'A' && c <= (unsigned char)'Z') ||
              (c >= (unsigned char)'a' && c <= (unsigned char)'z') ||
              (c >= (unsigned char)'0' && c <= (unsigned char)'9') ||
              c == (unsigned char)'_' || c == (unsigned char)'-' ||
              c == (unsigned char)'.')) return 0;
    }
    return 0;
}

static int ValidRevision(const char *bytes, size_t capacity)
{
    size_t i, length = 0U;
    if (bytes == NULL) return 0;
    while (length < capacity && bytes[length] != '\0') ++length;
    if (length != 40U && length != 64U) return 0;
    for (i = 0U; i < length; ++i) {
        const unsigned char c = (unsigned char)bytes[i];
        if (!((c >= (unsigned char)'0' && c <= (unsigned char)'9') ||
              (c >= (unsigned char)'a' && c <= (unsigned char)'f'))) return 0;
    }
    return 1;
}

static int ValidPolicy(const BtbOpsPolicy *policy)
{
    return policy != NULL &&
        ValidIdentifier(policy->serviceId, sizeof policy->serviceId) &&
        ValidRevision(policy->sourceRevision, sizeof policy->sourceRevision) &&
        policy->reviewStartSeconds != 0U &&
        policy->reviewEndSeconds > policy->reviewStartSeconds &&
        policy->maximumHeartbeatAgeSeconds != 0U &&
        policy->maximumBackupAgeSeconds != 0U &&
        policy->maximumRestoreDrillAgeSeconds != 0U &&
        policy->maximumDataLossSeconds != 0U &&
        policy->maximumRecoveryDurationSeconds != 0U &&
        policy->maximumQueuedJobs != 0U;
}

static int ValidFlag(int flag) { return flag == 0 || flag == 1; }

static int ValidEvidence(const BtbOpsEvidence *evidence)
{
    return evidence != NULL && evidence->captureId != 0U &&
        evidence->observedSeconds != 0U &&
        ValidRevision(evidence->observedSourceRevision,
                      sizeof evidence->observedSourceRevision) &&
        /* Zero means absent; a non-zero timestamp cannot claim to be future. */
        evidence->lastHealthySeconds <= evidence->observedSeconds &&
        evidence->lastVerifiedBackupSeconds <= evidence->observedSeconds &&
        evidence->lastSuccessfulRestoreDrillSeconds <= evidence->observedSeconds &&
        ValidFlag(evidence->alertRouteTested) &&
        ValidFlag(evidence->onCallOwnerAssigned) &&
        ValidFlag(evidence->independentRestoreVerified) &&
        ValidFlag(evidence->auditEvidenceRedacted);
}

/* No output is written until all public API calls succeed. */
BtbOpsResult BtbOpsInit(BtbOpsReview *review,
                        const BtbOpsPolicy *policy,
                        const BtbSecurityReview *security)
{
    BtbSecurityDecision upstream;
    BtbOpsReview candidate;
    if (review == NULL || !ValidPolicy(policy) || security == NULL) return BTB_OPS_INVALID;
    if (!ValidIdentifier(security->plan.serviceId,
                         sizeof security->plan.serviceId) ||
        !ValidRevision(security->plan.sourceRevision,
                       sizeof security->plan.sourceRevision)) return BTB_OPS_INVALID;
    if (strcmp(policy->serviceId, security->plan.serviceId) != 0 ||
        strcmp(policy->sourceRevision, security->plan.sourceRevision) != 0)
        return BTB_OPS_MISMATCH;
    if (BtbSecurityEvaluate(security, &upstream) != BTB_SECURITY_OK)
        return BTB_OPS_INVALID;
    candidate = (BtbOpsReview){0};
    candidate.policy = *policy;
    candidate.security = *security;
    *review = candidate;
    return BTB_OPS_OK;
}

BtbOpsResult BtbOpsAttach(BtbOpsReview *review,
                          const BtbOpsEvidence *evidence)
{
    if (review == NULL || !ValidPolicy(&review->policy) ||
        !ValidEvidence(evidence)) return BTB_OPS_INVALID;
    if (review->hasEvidence != 0) return BTB_OPS_STATE_ERROR;
    if (strcmp(review->policy.sourceRevision, evidence->observedSourceRevision) != 0)
        return BTB_OPS_MISMATCH;
    review->evidence = *evidence;
    review->hasEvidence = 1;
    return BTB_OPS_OK;
}

static void CheckAge(uint64_t now, uint64_t last, uint64_t limit,
                     uint32_t missing, uint32_t stale, uint32_t *bits)
{
    /* ValidEvidence already ensures last <= now for all nonzero timestamps. */
    if (last == 0U) *bits |= missing;
    else if (now - last > limit) *bits |= stale;
}

BtbOpsResult BtbOpsEvaluate(const BtbOpsReview *review,
                            BtbOpsDecision *outDecision)
{
    BtbSecurityDecision upstream;
    BtbOpsDecision candidate = {0};
    const BtbOpsEvidence *evidence;
    const BtbOpsPolicy *policy;
    if (review == NULL || outDecision == NULL ||
        !ValidPolicy(&review->policy) ||
        (review->hasEvidence != 0 && review->hasEvidence != 1))
        return BTB_OPS_INVALID;
    if (BtbSecurityEvaluate(&review->security, &upstream) != BTB_SECURITY_OK)
        return BTB_OPS_INVALID;
    if (!ValidIdentifier(review->security.plan.serviceId,
                         sizeof review->security.plan.serviceId) ||
        !ValidRevision(review->security.plan.sourceRevision,
                       sizeof review->security.plan.sourceRevision))
        return BTB_OPS_INVALID;
    if (strcmp(review->policy.serviceId, review->security.plan.serviceId) != 0 ||
        strcmp(review->policy.sourceRevision,
               review->security.plan.sourceRevision) != 0)
        return BTB_OPS_MISMATCH;
    candidate.securityStatus = upstream.status;
    candidate.securityCaptureId = upstream.securityObservationCapture;
    if (review->hasEvidence == 0) {
        candidate.missingEvidence = BTB_OPS_MISSING_EVIDENCE;
        candidate.status = BTB_OPS_PENDING;
        *outDecision = candidate;
        return BTB_OPS_OK;
    }
    evidence = &review->evidence;
    policy = &review->policy;
    if (!ValidEvidence(evidence)) return BTB_OPS_INVALID;
    if (strcmp(policy->sourceRevision, evidence->observedSourceRevision) != 0)
        return BTB_OPS_MISMATCH;
    candidate.operationsCaptureId = evidence->captureId;
    if (evidence->observedSeconds < policy->reviewStartSeconds ||
        evidence->observedSeconds > policy->reviewEndSeconds)
        candidate.missingEvidence |= BTB_OPS_OUTSIDE_REVIEW_WINDOW;
    CheckAge(evidence->observedSeconds, evidence->lastHealthySeconds,
             policy->maximumHeartbeatAgeSeconds, BTB_OPS_MISSING_HEARTBEAT,
             BTB_OPS_STALE_HEARTBEAT, &candidate.missingEvidence);
    CheckAge(evidence->observedSeconds, evidence->lastVerifiedBackupSeconds,
             policy->maximumBackupAgeSeconds, BTB_OPS_MISSING_BACKUP,
             BTB_OPS_STALE_BACKUP, &candidate.missingEvidence);
    CheckAge(evidence->observedSeconds,
             evidence->lastSuccessfulRestoreDrillSeconds,
             policy->maximumRestoreDrillAgeSeconds, BTB_OPS_MISSING_RESTORE_DRILL,
             BTB_OPS_STALE_RESTORE_DRILL, &candidate.missingEvidence);
    if (evidence->estimatedDataLossSeconds > policy->maximumDataLossSeconds)
        candidate.missingEvidence |= BTB_OPS_RPO_EXCEEDED;
    if (evidence->measuredRecoverySeconds > policy->maximumRecoveryDurationSeconds)
        candidate.missingEvidence |= BTB_OPS_RTO_EXCEEDED;
    if (evidence->queuedJobs > policy->maximumQueuedJobs)
        candidate.missingEvidence |= BTB_OPS_QUEUE_CAPACITY;
    if (!evidence->alertRouteTested)
        candidate.missingEvidence |= BTB_OPS_ALERT_ROUTE_UNVERIFIED;
    if (!evidence->onCallOwnerAssigned)
        candidate.missingEvidence |= BTB_OPS_ON_CALL_UNASSIGNED;
    if (!evidence->independentRestoreVerified)
        candidate.missingEvidence |= BTB_OPS_RESTORE_UNVERIFIED;
    if (!evidence->auditEvidenceRedacted)
        candidate.missingEvidence |= BTB_OPS_PRIVACY_UNVERIFIED;
    if (upstream.status != BTB_SECURITY_REVIEWABLE)
        candidate.missingEvidence |= BTB_OPS_UPSTREAM_NOT_READY;

    /* Never label restoration of the old generation as a successful upgrade. */
    if (upstream.status == BTB_SECURITY_RESTORED_ONLY)
        candidate.status = BTB_OPS_RESTORED_ONLY;
    else if (candidate.missingEvidence != 0U)
        candidate.status = BTB_OPS_BLOCKED;
    else candidate.status = BTB_OPS_REVIEWABLE;
    *outDecision = candidate;
    return BTB_OPS_OK;
}

BtbOpsResult BtbOpsNextDue(uint64_t lastCompletedSeconds,
                           uint64_t intervalSeconds,
                           uint64_t *outNextSeconds)
{
    if (outNextSeconds == NULL || intervalSeconds == 0U ||
        lastCompletedSeconds > UINT64_MAX - intervalSeconds)
        return BTB_OPS_INVALID;
    *outNextSeconds = lastCompletedSeconds + intervalSeconds;
    return BTB_OPS_OK;
}

const char *BtbOpsStatusText(BtbOpsStatus status)
{
    switch (status) {
        case BTB_OPS_PENDING: return "PENDING";
        case BTB_OPS_BLOCKED: return "BLOCKED";
        case BTB_OPS_REVIEWABLE: return "REVIEWABLE";
        case BTB_OPS_RESTORED_ONLY: return "RESTORED_ONLY";
        default: return "UNKNOWN";
    }
}
