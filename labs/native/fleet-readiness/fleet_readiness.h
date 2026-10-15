/*-----------------------------------------------------------------------------
 * Bits2Banking | Umicom Foundation | Sammy Hegab | MIT
 * File: labs/native/fleet-readiness/fleet_readiness.h
 * PURPOSE: Teaching-only C23 multi-host readiness evidence composition.
 *
 * DESIGN:
 *   A reviewed host retains its existing BtbOpsReview from Update 45. This
 *   module DOES NOT reimplement service readiness, security, repository
 *   discovery, operating-system administration or deployment. It composes
 *   previously verified educational results across a bounded set of hosts.
 *   It does not open files, make network requests or change any service.
 *
 * OWNERSHIP:
 *   All caller pointers are borrowed only for the call. Init and Attach copy
 *   complete values into caller-owned FleetReview storage. No heap allocation.
 *   Invalid operations preserve the destination byte-for-byte. No thread safety;
 *   callers must serialise shared access. Struct fields are teaching records,
 *   not a long-term binary ABI; production consumers use Umicom Framework.
 *---------------------------------------------------------------------------*/
#ifndef BTB_FLEET_READINESS_H
#define BTB_FLEET_READINESS_H
#include "operations_review.h"
#include <stddef.h>
#include <stdint.h>

#define BTB_FLEET_MAX_HOSTS 4U
#define BTB_FLEET_HOST_NAME_CAPACITY 48U
#define BTB_FLEET_DIGEST_CAPACITY 65U

typedef enum BtbFleetResult {
    BTB_FLEET_OK = 0,
    BTB_FLEET_INVALID,
    BTB_FLEET_UNKNOWN_HOST,
    BTB_FLEET_DUPLICATE_HOST,
    BTB_FLEET_FULL
} BtbFleetResult;

typedef enum BtbFleetStatus {
    BTB_FLEET_PENDING = 1,
    BTB_FLEET_BLOCKED,
    BTB_FLEET_REVIEWABLE,
    BTB_FLEET_RESTORED_ONLY
} BtbFleetStatus;

typedef struct BtbFleetPolicy {
    char sourceRevision[BTB_REMOTE_REVISION_BYTES];
    char expectedPackageSha256[BTB_FLEET_DIGEST_CAPACITY];
    char requiredHosts[BTB_FLEET_MAX_HOSTS][BTB_FLEET_HOST_NAME_CAPACITY];
    size_t hostCount;
    uint64_t reviewTimeSeconds;
    uint64_t maximumEvidenceAgeSeconds;
} BtbFleetPolicy;

typedef struct BtbFleetHostEvidence {
    char hostId[BTB_FLEET_HOST_NAME_CAPACITY];
    char observedSourceRevision[BTB_REMOTE_REVISION_BYTES];
    char observedPackageSha256[BTB_FLEET_DIGEST_CAPACITY];
    uint64_t observationId;
    uint64_t observedSeconds;
    /* A true flag records a fictional, externally asserted check, not a live
     * permission grant, valid certificate or verified real backup. */
    int filesystemReadable;
    int applicationOperationVerified;
    int clockSynchronised;
    int packageProvenanceReviewed;
    int independentReviewerAssigned;
    int evidenceRedacted;
    BtbOpsReview operations;
} BtbFleetHostEvidence;

typedef struct BtbFleetReview {
    BtbFleetPolicy policy;
    BtbFleetHostEvidence hosts[BTB_FLEET_MAX_HOSTS];
    size_t observedCount;
} BtbFleetReview;

enum {
    BTB_FLEET_MISSING_HOST       = 1U << 0,
    BTB_FLEET_STALE_EVIDENCE    = 1U << 1,
    BTB_FLEET_FUTURE_EVIDENCE   = 1U << 2,
    BTB_FLEET_PACKAGE_MISMATCH  = 1U << 3,
    BTB_FLEET_REVISION_MISMATCH = 1U << 4,
    BTB_FLEET_STORAGE_FAILURE   = 1U << 5,
    BTB_FLEET_SERVICE_FAILURE   = 1U << 6,
    BTB_FLEET_CLOCK_UNVERIFIED  = 1U << 7,
    BTB_FLEET_PACKAGE_UNVERIFIED= 1U << 8,
    BTB_FLEET_REVIEWER_MISSING  = 1U << 9,
    BTB_FLEET_PRIVACY_UNVERIFIED= 1U << 10,
    BTB_FLEET_OPERATIONS_BLOCKED= 1U << 11,
    BTB_FLEET_RESTORED_PREVIOUS = 1U << 12
};

typedef struct BtbFleetDecision {
    BtbFleetStatus status;
    uint32_t issues;
    size_t requiredCount;
    size_t observedCount;
    size_t readyCount;
    size_t restoredCount;
    size_t missingCount;
    size_t blockedCount;
} BtbFleetDecision;

/* Refuse invalid configuration and duplicate host identity without changing
 * outReview. Expected revision: exactly 40 or 64 lowercase hex characters;
 * package checksum: exactly 64 lowercase hex characters. */
BtbFleetResult BtbFleetInit(BtbFleetReview *outReview,
                            const BtbFleetPolicy *policy);

/* Attach one matching host record exactly once, without modifying either
 * record on failure. A pending/blocked operations review is VALID EVIDENCE:
 * it simply cannot authorise a release. */
BtbFleetResult BtbFleetAttach(BtbFleetReview *review,
                              const BtbFleetHostEvidence *evidence);

/* Evaluate each host using the existing BtbOpsEvaluate implementation.
 * A restored old revision NEVER means that the attempted new release passed.
 * Invalid internal records preserve outDecision byte-for-byte. */
BtbFleetResult BtbFleetEvaluate(const BtbFleetReview *review,
                                BtbFleetDecision *outDecision);

const char *BtbFleetStatusText(BtbFleetStatus status);
#endif
