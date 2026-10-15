/*-----------------------------------------------------------------------------
 * Bits2Banking | Umicom Foundation | Sammy Hegab | MIT
 * File: labs/native/security-operations-review/security_operations_review.h
 * PURPOSE: Offline C23 evidence policy for a supervised security-operations
 *          review; composes the existing Update 43 remote-access review.
 *
 * ARCHITECTURE:
 *   No accounts, secrets, services, files, network endpoints or Git history
 *   are read or changed. Flags represent externally asserted evidence, never
 *   independently authenticated facts or permission to perform an operation.
 *   Every record is caller-owned and copied. Successful review means ONLY
 *   'reviewable training evidence', never authority to deploy or connect.
 *   Invalid calls preserve the caller's state and output byte for byte.
 *---------------------------------------------------------------------------*/
#ifndef BTB_SECURITY_OPERATIONS_REVIEW_H
#define BTB_SECURITY_OPERATIONS_REVIEW_H

#include "remote_access_review.h"
#include <stdint.h>

#define BTB_SECURITY_LABEL_CAPACITY 64U
#define BTB_SECURITY_POLICY_CAPACITY 48U
#define BTB_SECURITY_DIGEST_CAPACITY 65U

typedef enum BtbSecurityResult {
    BTB_SECURITY_OK = 0,
    BTB_SECURITY_INVALID,
    BTB_SECURITY_MISMATCH,
    BTB_SECURITY_STATE_ERROR
} BtbSecurityResult;

typedef enum BtbSecurityStatus {
    BTB_SECURITY_PENDING = 1,
    BTB_SECURITY_BLOCKED,
    BTB_SECURITY_REVIEWABLE,
    BTB_SECURITY_RESTORED_ONLY
} BtbSecurityStatus;

/* Identifiers are labels, never real principals or secrets. The revision
 * copies the exact source identity recorded by the upstream remote review. */
typedef struct BtbSecurityPlan {
    char serviceId[BTB_SECURITY_LABEL_CAPACITY];
    char requestingOperator[BTB_SECURITY_LABEL_CAPACITY];
    char independentReviewer[BTB_SECURITY_LABEL_CAPACITY];
    char sourceRevision[BTB_REMOTE_REVISION_BYTES];
    char configurationSha256[BTB_SECURITY_DIGEST_CAPACITY];
    char policyRevision[BTB_SECURITY_POLICY_CAPACITY];
    uint64_t changeTicket;
    uint64_t reviewWindowStartSeconds;
    uint64_t reviewWindowEndSeconds;
} BtbSecurityPlan;

/* External asserted observations: the C23 model cannot itself prove that a
 * password has been rotated, an ACL is correct or a backup can restore. */
typedef struct BtbSecurityEvidence {
    uint64_t captureId;
    uint64_t observationSeconds;
    char observedSourceRevision[BTB_REMOTE_REVISION_BYTES];
    char observedConfigurationSha256[BTB_SECURITY_DIGEST_CAPACITY];
    char observedPolicyRevision[BTB_SECURITY_POLICY_CAPACITY];
    int accountsReviewed;
    int groupMembershipReviewed;
    int leastPrivilegeReviewed;
    int configurationCompared;
    int unexplainedDriftAbsent;
    int patchEvidenceReviewed;
    int independentRestoreTestRecorded;
    int auditRetentionReviewed;
    int credentialsExcludedFromEvidence;
    int credentialRotationPlanReviewed;
    int certificateExpiryReviewed;
    int independentApprovalRecorded;
    int monitoringResponsePathReviewed;
} BtbSecurityEvidence;

typedef struct BtbSecurityReview {
    BtbSecurityPlan plan;
    BtbRemoteReview remote; /* copied immutable upstream observation */
    BtbSecurityEvidence evidence;
    int hasEvidence;
} BtbSecurityReview;

/* Bitmask permits a reviewer to identify EVERY missing gate, not merely the
 * first. Retain the original evidence externally; the mask is not an audit log. */
enum {
    BTB_SECURITY_MISSING_OBSERVATION        = 1U << 0,
    BTB_SECURITY_MISSING_ACCOUNT_REVIEW     = 1U << 1,
    BTB_SECURITY_MISSING_GROUP_REVIEW       = 1U << 2,
    BTB_SECURITY_MISSING_LEAST_PRIVILEGE    = 1U << 3,
    BTB_SECURITY_MISSING_CONFIG_CHECK       = 1U << 4,
    BTB_SECURITY_UNEXPLAINED_DRIFT          = 1U << 5,
    BTB_SECURITY_MISSING_PATCH_EVIDENCE     = 1U << 6,
    BTB_SECURITY_MISSING_RESTORE_TEST       = 1U << 7,
    BTB_SECURITY_MISSING_AUDIT_REVIEW       = 1U << 8,
    BTB_SECURITY_CREDENTIAL_EXPOSURE_RISK   = 1U << 9,
    BTB_SECURITY_MISSING_ROTATION_REVIEW    = 1U << 10,
    BTB_SECURITY_MISSING_CERTIFICATE_REVIEW = 1U << 11,
    BTB_SECURITY_MISSING_APPROVAL           = 1U << 12,
    BTB_SECURITY_MISSING_RESPONSE_PATH      = 1U << 13,
    BTB_SECURITY_STALE_CAPTURE              = 1U << 14,
    BTB_SECURITY_OUTSIDE_REVIEW_WINDOW      = 1U << 15,
    BTB_SECURITY_UPSTREAM_UNQUALIFIED       = 1U << 16
};

typedef struct BtbSecurityDecision {
    BtbSecurityStatus status;
    uint32_t missingEvidence;
    BtbRemoteStatus remoteStatus;
    uint64_t remoteObservationCapture;
    uint64_t securityObservationCapture;
} BtbSecurityDecision;

/* Initialise with a copied upstream review. Invalid plan or source mismatch
 * returns a status without changing destination (even if previously filled). */
BtbSecurityResult BtbSecurityInit(BtbSecurityReview *review,
                                  const BtbSecurityPlan *plan,
                                  const BtbRemoteReview *remote);
/* Evidence is appended exactly once. Changed source/configuration/policy IDs
 * are rejected rather than attached. A later revision needs a NEW review. */
BtbSecurityResult BtbSecurityAttach(BtbSecurityReview *review,
                                    const BtbSecurityEvidence *evidence);
/* Reuse BtbRemoteEvaluate for upstream qualification. Invalid structure or
 * upstream evaluation preserves caller-owned outDecision. */
BtbSecurityResult BtbSecurityEvaluate(const BtbSecurityReview *review,
                                      BtbSecurityDecision *outDecision);
const char *BtbSecurityStatusText(BtbSecurityStatus status);
#endif
