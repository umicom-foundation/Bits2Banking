/*-----------------------------------------------------------------------------
 * Bits2Banking | Umicom Foundation | Sammy Hegab | MIT
 * File: labs/native/operational-resilience/operations_review.h
 * PURPOSE: Compose existing C23 security evidence with bounded operational
 *          observations for a fully offline, single-owner teaching model.
 *
 * ARCHITECTURE:
 *   Existing BtbSecurityReview remains the authoritative upstream educational
 *   review. No operating-system service, Git repository, secret, backup,
 *   scheduler or network connection is read or altered. This module implements
 *   only decision policy and checked time arithmetic. It is not a production
 *   monitoring engine, authorisation provider or Framework replacement.
 *
 * CONTRACT:
 *   All arguments are borrowed for each call. Init/Attach copy values.
 *   Invalid input and mismatched identities preserve outputs byte-for-byte.
 *   Records are caller-owned; do not share mutable records between threads.
 *---------------------------------------------------------------------------*/
#ifndef BTB_OPERATIONAL_RESILIENCE_REVIEW_H
#define BTB_OPERATIONAL_RESILIENCE_REVIEW_H

#include "security_operations_review.h"
#include <stdint.h>

#define BTB_OPS_SERVICE_CAPACITY 64U

typedef enum BtbOpsResult {
    BTB_OPS_OK = 0,
    BTB_OPS_INVALID,
    BTB_OPS_MISMATCH,
    BTB_OPS_STATE_ERROR
} BtbOpsResult;

typedef enum BtbOpsStatus {
    BTB_OPS_PENDING = 1,
    BTB_OPS_BLOCKED,
    BTB_OPS_REVIEWABLE,
    BTB_OPS_RESTORED_ONLY
} BtbOpsStatus;

typedef struct BtbOpsPolicy {
    char serviceId[BTB_OPS_SERVICE_CAPACITY];
    char sourceRevision[BTB_REMOTE_REVISION_BYTES];
    uint64_t reviewStartSeconds;
    uint64_t reviewEndSeconds;
    uint64_t maximumHeartbeatAgeSeconds;
    uint64_t maximumBackupAgeSeconds;
    uint64_t maximumRestoreDrillAgeSeconds;
    uint64_t maximumDataLossSeconds; /* RPO: tolerance, not backup frequency */
    uint64_t maximumRecoveryDurationSeconds; /* RTO: measured recovery limit */
    uint32_t maximumQueuedJobs;
} BtbOpsPolicy;

/* All values below are fictional, externally ASSERTED training observations.
 * They do not demonstrate that real backups restored or alerts arrived. */
typedef struct BtbOpsEvidence {
    uint64_t captureId;
    uint64_t observedSeconds;
    char observedSourceRevision[BTB_REMOTE_REVISION_BYTES];
    uint64_t lastHealthySeconds;
    uint64_t lastVerifiedBackupSeconds;
    uint64_t lastSuccessfulRestoreDrillSeconds;
    uint64_t estimatedDataLossSeconds;
    uint64_t measuredRecoverySeconds;
    uint32_t queuedJobs;
    int alertRouteTested;
    int onCallOwnerAssigned;
    int independentRestoreVerified;
    int auditEvidenceRedacted;
} BtbOpsEvidence;

typedef struct BtbOpsReview {
    BtbOpsPolicy policy;
    BtbSecurityReview security; /* copied, validated upstream classroom model */
    BtbOpsEvidence evidence;
    int hasEvidence;
} BtbOpsReview;

/* An independent bit identifies each missing or exceeded condition. */
enum {
    BTB_OPS_MISSING_EVIDENCE        = 1U << 0,
    BTB_OPS_OUTSIDE_REVIEW_WINDOW   = 1U << 1,
    BTB_OPS_MISSING_HEARTBEAT       = 1U << 2,
    BTB_OPS_STALE_HEARTBEAT         = 1U << 3,
    BTB_OPS_MISSING_BACKUP         = 1U << 4,
    BTB_OPS_STALE_BACKUP           = 1U << 5,
    BTB_OPS_MISSING_RESTORE_DRILL  = 1U << 6,
    BTB_OPS_STALE_RESTORE_DRILL    = 1U << 7,
    BTB_OPS_RPO_EXCEEDED           = 1U << 8,
    BTB_OPS_RTO_EXCEEDED           = 1U << 9,
    BTB_OPS_QUEUE_CAPACITY         = 1U << 10,
    BTB_OPS_ALERT_ROUTE_UNVERIFIED = 1U << 11,
    BTB_OPS_ON_CALL_UNASSIGNED     = 1U << 12,
    BTB_OPS_RESTORE_UNVERIFIED     = 1U << 13,
    BTB_OPS_PRIVACY_UNVERIFIED     = 1U << 14,
    BTB_OPS_UPSTREAM_NOT_READY     = 1U << 15
};

typedef struct BtbOpsDecision {
    BtbOpsStatus status;
    uint32_t missingEvidence;
    BtbSecurityStatus securityStatus;
    uint64_t securityCaptureId;
    uint64_t operationsCaptureId;
} BtbOpsDecision;

/* Start a new review, bound to the source identity and service ID from the
 * copied security review. Failure preserves the destination. */
BtbOpsResult BtbOpsInit(BtbOpsReview *review,
                        const BtbOpsPolicy *policy,
                        const BtbSecurityReview *security);

/* Attach one distinct, matched observation. Duplicate or invalid attaches
 * never overwrite previous evidence. To attach new evidence, make a new review. */
BtbOpsResult BtbOpsAttach(BtbOpsReview *review,
                          const BtbOpsEvidence *evidence);

/* Use existing BtbSecurityEvaluate. An upstream RESTORED_ONLY outcome can
 * never be promoted into successful deployment of the proposed generation. */
BtbOpsResult BtbOpsEvaluate(const BtbOpsReview *review,
                            BtbOpsDecision *outDecision);

/* Pure, checked scheduling arithmetic: there are no timers or background
 * processes. An overflow/zero cadence preserves outNextSeconds. */
BtbOpsResult BtbOpsNextDue(uint64_t lastCompletedSeconds,
                           uint64_t intervalSeconds,
                           uint64_t *outNextSeconds);

const char *BtbOpsStatusText(BtbOpsStatus status);

#endif
