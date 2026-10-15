/*-----------------------------------------------------------------------------
 * Bits2Banking | Umicom Foundation | Sammy Hegab | MIT
 * File: labs/native/remote-access-review/remote_access_review.h
 * PURPOSE: Educational C23 remote-access preflight policy over existing
 *          deployment, maintenance, service and evidence review contracts.
 *
 * ARCHITECTURE AND SAFETY:
 * - Pure in-memory educational analysis; no sockets, files, Git, service
 *   managers, SSH, TLS or platform configuration are accessed or modified.
 * - Reuses Update 42's BtbDeploymentEvaluate; does not duplicate its rules.
 * - A REVIEWABLE result is NOT authorisation to connect or change a system.
 * - All records are caller owned and copied. No borrowed input is retained.
 * - Invalid calls preserve caller-owned outputs byte-for-byte.
 * - Not thread-safe. The calling thread owns the whole review lifetime.
 *---------------------------------------------------------------------------*/
#ifndef BTB_REMOTE_ACCESS_REVIEW_H
#define BTB_REMOTE_ACCESS_REVIEW_H

#include "deployment_review.h"
#include <stdint.h>

#define BTB_REMOTE_LABEL_BYTES 64U
#define BTB_REMOTE_HOST_BYTES 96U
#define BTB_REMOTE_REVISION_BYTES BTB_DEPLOYMENT_REVISION_BYTES

typedef enum BtbRemoteResult {
    BTB_REMOTE_OK = 0,
    BTB_REMOTE_INVALID,
    BTB_REMOTE_MISMATCH,
    BTB_REMOTE_STATE_ERROR
} BtbRemoteResult;

typedef enum BtbRemoteStatus {
    BTB_REMOTE_PENDING = 1,
    BTB_REMOTE_BLOCKED,
    BTB_REMOTE_REVIEWABLE,
    BTB_REMOTE_RESTORED_ONLY
} BtbRemoteStatus;

/* Identifiers are teaching labels, not proven credentials or authorisation. */
typedef struct BtbRemotePlan {
    char serviceId[BTB_REMOTE_LABEL_BYTES];
    char hostLabel[BTB_REMOTE_HOST_BYTES];
    char requestingOperator[BTB_REMOTE_LABEL_BYTES];
    char independentReviewer[BTB_REMOTE_LABEL_BYTES];
    char sourceRevision[BTB_REMOTE_REVISION_BYTES];
    uint64_t changeTicket;
    uint64_t windowStartSeconds;
    uint64_t windowEndSeconds;
} BtbRemotePlan;

/* Every boolean represents claimed human or external-tool evidence. This
 * exercise does not verify a real host key, route, certificate or identity. */
typedef struct BtbRemoteEvidence {
    uint64_t captureId;
    uint64_t observationSeconds;
    char observedSourceRevision[BTB_REMOTE_REVISION_BYTES];
    int hostIdentityIndependentlyChecked;
    int authenticatedTransportReviewed;
    int destinationScopeReviewed;
    int leastPrivilegeReviewed;
    int credentialsExcludedFromLogs;
    int recoveryPlanAvailable;
    int separateReviewerRecorded;
    int readOnlyTrialObserved;
} BtbRemoteEvidence;

typedef struct BtbRemoteReview {
    BtbRemotePlan plan;
    BtbDeploymentReview deployment; /* copied from the existing Update 42 module */
    BtbRemoteEvidence evidence;
    int hasEvidence;
} BtbRemoteReview;

enum {
    BTB_REMOTE_MISSING_OBSERVATION = 1U << 0,
    BTB_REMOTE_MISSING_HOST_IDENTITY = 1U << 1,
    BTB_REMOTE_MISSING_TRANSPORT = 1U << 2,
    BTB_REMOTE_MISSING_SCOPE = 1U << 3,
    BTB_REMOTE_MISSING_LEAST_PRIVILEGE = 1U << 4,
    BTB_REMOTE_MISSING_CREDENTIAL_SAFETY = 1U << 5,
    BTB_REMOTE_MISSING_RECOVERY_PLAN = 1U << 6,
    BTB_REMOTE_MISSING_REVIEWER = 1U << 7,
    BTB_REMOTE_MISSING_READ_ONLY_TRIAL = 1U << 8,
    BTB_REMOTE_STALE_CAPTURE = 1U << 9,
    BTB_REMOTE_OUTSIDE_WINDOW = 1U << 10,
    BTB_REMOTE_DEPLOYMENT_UNQUALIFIED = 1U << 11
};

typedef struct BtbRemoteDecision {
    BtbRemoteStatus status;
    uint32_t missingEvidence;
    BtbDeploymentStatus deploymentStatus;
    uint64_t deploymentVerificationCapture;
    uint64_t accessObservationCapture;
} BtbRemoteDecision;

/* Validate a named training scope and copy the existing deployment record.
 * A mismatching source SHA is refused; the destination remains unchanged. */
BtbRemoteResult BtbRemoteInit(BtbRemoteReview *review,
                              const BtbRemotePlan *plan,
                              const BtbDeploymentReview *deployment);
/* Attach evidence once. Repeated attachment is refused, including after a
 * fully completed review; immutable evidence must not be silently overwritten. */
BtbRemoteResult BtbRemoteAttach(BtbRemoteReview *review,
                                const BtbRemoteEvidence *evidence);
/* Reuse BtbDeploymentEvaluate to calculate upstream readiness; never present
 * restored-only or rollback-required deployments as successful. */
BtbRemoteResult BtbRemoteEvaluate(const BtbRemoteReview *review,
                                  BtbRemoteDecision *outDecision);
const char *BtbRemoteStatusText(BtbRemoteStatus status);
#endif
