/*-----------------------------------------------------------------------------
 * Bits2Banking | Umicom Foundation | Sammy Hegab | MIT
 * File: labs/native/fleet-readiness/fleet_readiness.c
 * PURPOSE: Aggregate reviewed host observations without performing live I/O.
 *---------------------------------------------------------------------------*/
#include "fleet_readiness.h"
#include <stddef.h>
#include <stdint.h>
#include <string.h>

static int ValidName(const char *text, size_t capacity)
{
    size_t position;
    if (text == NULL || capacity < 2U || text[0] == '\0') return 0;
    for (position = 0U; position < capacity; ++position) {
        unsigned char c = (unsigned char)text[position];
        if (c == (unsigned char)'\0') return position > 0U;
        if (!((c >= (unsigned char)'a' && c <= (unsigned char)'z') ||
              (c >= (unsigned char)'A' && c <= (unsigned char)'Z') ||
              (c >= (unsigned char)'0' && c <= (unsigned char)'9') ||
              c == (unsigned char)'.' || c == (unsigned char)'_' ||
              c == (unsigned char)'-')) return 0;
    }
    return 0;
}

static int ValidHex(const char *text, size_t capacity, int isPackage)
{
    size_t length = 0U, position;
    if (text == NULL) return 0;
    while (length < capacity && text[length] != '\0') ++length;
    if (isPackage ? (length != 64U) : (length != 40U && length != 64U)) return 0;
    for (position = 0U; position < length; ++position) {
        unsigned char c = (unsigned char)text[position];
        if (!((c >= (unsigned char)'0' && c <= (unsigned char)'9') ||
              (c >= (unsigned char)'a' && c <= (unsigned char)'f'))) return 0;
    }
    return 1;
}

static int ValidPolicy(const BtbFleetPolicy *policy)
{
    size_t left, right;
    if (policy == NULL || policy->hostCount == 0U ||
        policy->hostCount > BTB_FLEET_MAX_HOSTS ||
        policy->reviewTimeSeconds == 0U ||
        policy->maximumEvidenceAgeSeconds == 0U ||
        !ValidHex(policy->sourceRevision, sizeof policy->sourceRevision, 0) ||
        !ValidHex(policy->expectedPackageSha256,
                  sizeof policy->expectedPackageSha256, 1)) return 0;
    for (left = 0U; left < policy->hostCount; ++left) {
        if (!ValidName(policy->requiredHosts[left],
                       sizeof policy->requiredHosts[left])) return 0;
        for (right = 0U; right < left; ++right) {
            if (strcmp(policy->requiredHosts[left],
                       policy->requiredHosts[right]) == 0) return 0;
        }
    }
    return 1;
}

static int ValidFlag(int flag) { return flag == 0 || flag == 1; }

static int ValidHost(const BtbFleetHostEvidence *host)
{
    BtbOpsDecision decision = {0};
    return host != NULL &&
        ValidName(host->hostId, sizeof host->hostId) &&
        ValidHex(host->observedSourceRevision,
                 sizeof host->observedSourceRevision, 0) &&
        ValidHex(host->observedPackageSha256,
                 sizeof host->observedPackageSha256, 1) &&
        host->observationId != 0U && host->observedSeconds != 0U &&
        ValidFlag(host->filesystemReadable) &&
        ValidFlag(host->applicationOperationVerified) &&
        ValidFlag(host->clockSynchronised) &&
        ValidFlag(host->packageProvenanceReviewed) &&
        ValidFlag(host->independentReviewerAssigned) &&
        ValidFlag(host->evidenceRedacted) &&
        BtbOpsEvaluate(&host->operations, &decision) == BTB_OPS_OK;
}

static size_t FindHostIndex(const BtbFleetPolicy *policy, const char *name)
{
    size_t position;
    for (position = 0U; position < policy->hostCount; ++position)
        if (strcmp(policy->requiredHosts[position], name) == 0) return position;
    return policy->hostCount;
}

BtbFleetResult BtbFleetInit(BtbFleetReview *outReview,
                            const BtbFleetPolicy *policy)
{
    BtbFleetReview candidate = {0};
    if (outReview == NULL || !ValidPolicy(policy)) return BTB_FLEET_INVALID;
    candidate.policy = *policy;
    *outReview = candidate;
    return BTB_FLEET_OK;
}

BtbFleetResult BtbFleetAttach(BtbFleetReview *review,
                              const BtbFleetHostEvidence *evidence)
{
    size_t position;
    if (review == NULL || !ValidPolicy(&review->policy) ||
        review->observedCount > review->policy.hostCount ||
        !ValidHost(evidence)) return BTB_FLEET_INVALID;
    if (FindHostIndex(&review->policy, evidence->hostId) ==
        review->policy.hostCount) return BTB_FLEET_UNKNOWN_HOST;
    for (position = 0U; position < review->observedCount; ++position) {
        if (!ValidHost(&review->hosts[position])) return BTB_FLEET_INVALID;
        if (strcmp(review->hosts[position].hostId,
                   evidence->hostId) == 0) return BTB_FLEET_DUPLICATE_HOST;
    }
    if (review->observedCount == BTB_FLEET_MAX_HOSTS) return BTB_FLEET_FULL;
    review->hosts[review->observedCount] = *evidence;
    ++review->observedCount;
    return BTB_FLEET_OK;
}

BtbFleetResult BtbFleetEvaluate(const BtbFleetReview *review,
                                BtbFleetDecision *outDecision)
{
    BtbFleetDecision next = {0};
    size_t position, required;
    int restored = 0, blocked = 0;
    if (review == NULL || outDecision == NULL ||
        !ValidPolicy(&review->policy) ||
        review->observedCount > review->policy.hostCount) return BTB_FLEET_INVALID;
    /* All attached records must be valid, unique and match registered names.
     * This pass occurs BEFORE mutating the caller's output. */
    for (position = 0U; position < review->observedCount; ++position) {
        size_t previous;
        const BtbFleetHostEvidence *host = &review->hosts[position];
        if (!ValidHost(host) ||
            FindHostIndex(&review->policy, host->hostId) ==
                review->policy.hostCount) return BTB_FLEET_INVALID;
        for (previous = 0U; previous < position; ++previous)
            if (strcmp(host->hostId, review->hosts[previous].hostId) == 0)
                return BTB_FLEET_INVALID;
    }
    next.requiredCount = review->policy.hostCount;
    next.observedCount = review->observedCount;
    for (required = 0U; required < review->policy.hostCount; ++required) {
        const BtbFleetHostEvidence *host = NULL;
        BtbOpsDecision opsDecision = {0};
        size_t index;
        uint32_t flags = 0U;
        for (index = 0U; index < review->observedCount; ++index) {
            if (strcmp(review->hosts[index].hostId,
                       review->policy.requiredHosts[required]) == 0) {
                host = &review->hosts[index];
                break;
            }
        }
        if (host == NULL) {
            ++next.missingCount;
            next.issues |= BTB_FLEET_MISSING_HOST;
            continue;
        }
        /* Safe arithmetic: subtract only after proving observed <= review. */
        if (host->observedSeconds > review->policy.reviewTimeSeconds)
            flags |= BTB_FLEET_FUTURE_EVIDENCE;
        else if (review->policy.reviewTimeSeconds - host->observedSeconds >
                 review->policy.maximumEvidenceAgeSeconds)
            flags |= BTB_FLEET_STALE_EVIDENCE;
        if (strcmp(host->observedSourceRevision,
                   review->policy.sourceRevision) != 0)
            flags |= BTB_FLEET_REVISION_MISMATCH;
        if (strcmp(host->observedPackageSha256,
                   review->policy.expectedPackageSha256) != 0)
            flags |= BTB_FLEET_PACKAGE_MISMATCH;
        if (!host->filesystemReadable) flags |= BTB_FLEET_STORAGE_FAILURE;
        if (!host->applicationOperationVerified) flags |= BTB_FLEET_SERVICE_FAILURE;
        if (!host->clockSynchronised) flags |= BTB_FLEET_CLOCK_UNVERIFIED;
        if (!host->packageProvenanceReviewed) flags |= BTB_FLEET_PACKAGE_UNVERIFIED;
        if (!host->independentReviewerAssigned) flags |= BTB_FLEET_REVIEWER_MISSING;
        if (!host->evidenceRedacted) flags |= BTB_FLEET_PRIVACY_UNVERIFIED;
        /* The shared educational operations evaluator owns all lower-level
         * heartbeat, backup, audit, reviewer and recovery rules. */
        if (BtbOpsEvaluate(&host->operations, &opsDecision) != BTB_OPS_OK)
            return BTB_FLEET_INVALID;
        if (opsDecision.status == BTB_OPS_RESTORED_ONLY) {
            flags |= BTB_FLEET_RESTORED_PREVIOUS;
            restored = 1;
            ++next.restoredCount;
        } else if (opsDecision.status != BTB_OPS_REVIEWABLE) {
            flags |= BTB_FLEET_OPERATIONS_BLOCKED;
        }
        next.issues |= flags;
        if (flags == 0U) ++next.readyCount;
        else if (flags != BTB_FLEET_RESTORED_PREVIOUS) {
            ++next.blockedCount;
            blocked = 1;
        }
    }
    if (blocked) next.status = BTB_FLEET_BLOCKED;
    else if (restored) next.status = BTB_FLEET_RESTORED_ONLY;
    else if (next.missingCount > 0U) next.status = BTB_FLEET_PENDING;
    else next.status = BTB_FLEET_REVIEWABLE;
    *outDecision = next;
    return BTB_FLEET_OK;
}

const char *BtbFleetStatusText(BtbFleetStatus status)
{
    switch (status) {
        case BTB_FLEET_PENDING: return "PENDING";
        case BTB_FLEET_BLOCKED: return "BLOCKED";
        case BTB_FLEET_REVIEWABLE: return "REVIEWABLE";
        case BTB_FLEET_RESTORED_ONLY: return "RESTORED_ONLY";
        default: return "UNKNOWN";
    }
}
