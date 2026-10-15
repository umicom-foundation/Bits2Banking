/*-----------------------------------------------------------------------------
 * Bits2Banking | Umicom Foundation | Sammy Hegab | MIT
 * File: labs/native/deployment-rehearsal/deployment_review.h
 * PURPOSE: Review a fictional, staged C23 release without changing a host.
 *
 * ARCHITECTURE:
 *   This educational boundary consumes the existing Update 41 maintenance
 *   review, which itself consumes Updates 39 and 40. No second service,
 *   backup, Git, installation or recovery engine is implemented here.
 *
 * OWNERSHIP AND SAFETY:
 *   Caller owns every record. All inputs are copied and no pointers retained.
 *   Rejected calls preserve the entire previous record, including outputs.
 *   This model never reads disks, executes programs or grants real approval.
 *---------------------------------------------------------------------------*/
#ifndef BTB_DEPLOYMENT_REVIEW_H
#define BTB_DEPLOYMENT_REVIEW_H
#include "maintenance_review.h"
#include <stddef.h>
#include <stdint.h>

#define BTB_DEPLOYMENT_NAME_BYTES 48U
#define BTB_DEPLOYMENT_REVISION_BYTES 65U
#define BTB_DEPLOYMENT_STAGE_BYTES 96U

/* Every digest is a textual *claim*: this module does not hash real files. */
typedef struct BtbDeploymentPlan {
    char releaseId[BTB_DEPLOYMENT_NAME_BYTES];
    char sourceRevision[BTB_DEPLOYMENT_REVISION_BYTES];
    char packageSha256[BTB_DEPLOYMENT_REVISION_BYTES];
    char configurationSha256[BTB_DEPLOYMENT_REVISION_BYTES];
    char privateStage[BTB_DEPLOYMENT_STAGE_BYTES];
} BtbDeploymentPlan;

typedef struct BtbDeploymentEvidence {
    uint64_t stageCaptureId;
    uint64_t verificationCaptureId;
    char observedSourceRevision[BTB_DEPLOYMENT_REVISION_BYTES];
    char observedPackageSha256[BTB_DEPLOYMENT_REVISION_BYTES];
    /* One means independently observed; zero means not proven. */
    int packageHashCompared;
    int configurationReviewed;
    int runtimeDependenciesChecked;
    int privateStageInspected;
    int entryPointProbed;
} BtbDeploymentEvidence;

typedef struct BtbDeploymentReview {
    BtbDeploymentPlan plan;
    BtbMaintenanceReview maintenance;
    BtbDeploymentEvidence stage;
    int hasStage;
} BtbDeploymentReview;

typedef enum BtbDeploymentStatus {
    BTB_DEPLOYMENT_PENDING = 1,
    BTB_DEPLOYMENT_BLOCKED,
    BTB_DEPLOYMENT_QUALIFIED,
    BTB_DEPLOYMENT_ROLLBACK_REQUIRED,
    BTB_DEPLOYMENT_RESTORED_ONLY
} BtbDeploymentStatus;

typedef enum BtbDeploymentResult {
    BTB_DEPLOYMENT_OK = 0,
    BTB_DEPLOYMENT_INVALID,
    BTB_DEPLOYMENT_MISMATCH,
    BTB_DEPLOYMENT_STATE_ERROR
} BtbDeploymentResult;

enum {
    BTB_DEPLOYMENT_MISSING_STAGE = 1U << 0,
    BTB_DEPLOYMENT_MISSING_PACKAGE_CHECK = 1U << 1,
    BTB_DEPLOYMENT_MISSING_CONFIG_REVIEW = 1U << 2,
    BTB_DEPLOYMENT_MISSING_RUNTIME_CHECK = 1U << 3,
    BTB_DEPLOYMENT_MISSING_PRIVATE_STAGE = 1U << 4,
    BTB_DEPLOYMENT_MISSING_ENTRYPOINT = 1U << 5,
    BTB_DEPLOYMENT_MISSING_MAINTENANCE = 1U << 6,
    BTB_DEPLOYMENT_STALE_CAPTURE = 1U << 7
};

typedef struct BtbDeploymentDecision {
    BtbDeploymentStatus status;
    uint32_t missingEvidence;
    uint64_t baselineCaptureId;
    uint64_t stageCaptureId;
    uint64_t verificationCaptureId;
} BtbDeploymentDecision;

/* A valid release is immutable while a review exists. Stage names are labels,
 * not paths used by the library. The caller must ensure real staging isolation. */
BtbDeploymentResult BtbDeploymentInit(BtbDeploymentReview *review,
    const BtbDeploymentPlan *plan, const BtbMaintenanceReview *maintenance);

/* Accept external, *claimed* stage observations without I/O. The package
 * identity and commit revision must agree with the plan; otherwise refuse. */
BtbDeploymentResult BtbDeploymentAttachStage(BtbDeploymentReview *review,
    const BtbDeploymentEvidence *evidence);

/* Consume a newer snapshot from the existing C23 maintenance model. A
 * different change, baseline, approval identity or source revision is refused. */
BtbDeploymentResult BtbDeploymentUpdateMaintenance(BtbDeploymentReview *review,
    const BtbMaintenanceReview *maintenance);

/* Evaluate conservatively. Invalid review/output leaves output byte-for-byte
 * unchanged. A recovered release is NEVER qualified as a successful change. */
BtbDeploymentResult BtbDeploymentEvaluate(const BtbDeploymentReview *review,
    BtbDeploymentDecision *outDecision);

const char *BtbDeploymentStatusText(BtbDeploymentStatus status);
const char *BtbDeploymentResultText(BtbDeploymentResult result);
#endif
