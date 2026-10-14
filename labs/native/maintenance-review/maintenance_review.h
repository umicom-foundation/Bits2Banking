/*-----------------------------------------------------------------------------
 * Bits2Banking | Umicom Foundation | Sammy Hegab | MIT
 * File: labs/native/maintenance-review/maintenance_review.h
 * PURPOSE: Educational change-window review over existing C23 readiness evidence.
 *
 * Architecture: This module owns only an offline, caller-owned review record.
 * It consumes BtbServiceSummary produced by Update 40; Update 40 consumes
 * Update 39's evidence model. It never controls an OS service, invokes Git,
 * installs software, writes files, or grants an actual security approval.
 *
 * Ownership: Input summaries are copied. No input pointer is retained.
 * Invalid operations leave the entire caller-owned review unchanged. All
 * public operations are single-threaded; synchronisation is the caller's job.
 *---------------------------------------------------------------------------*/
#ifndef BTB_MAINTENANCE_REVIEW_H
#define BTB_MAINTENANCE_REVIEW_H
#include "service_readiness.h"
#include <stddef.h>
#include <stdint.h>
#define BTB_MAINTENANCE_ID_BYTES 48U
#define BTB_MAINTENANCE_REVISION_BYTES 65U
#define BTB_MAINTENANCE_PERSON_BYTES 48U
#define BTB_MAINTENANCE_SUMMARY_BYTES 384U

typedef enum BtbMaintenanceState {
    BTB_MAINTENANCE_PLANNED = 1,
    BTB_MAINTENANCE_APPROVED,
    BTB_MAINTENANCE_STARTED,
    BTB_MAINTENANCE_VERIFIED,
    BTB_MAINTENANCE_ROLLBACK_REQUIRED,
    BTB_MAINTENANCE_COMPLETE,
    BTB_MAINTENANCE_RESTORED,
    BTB_MAINTENANCE_CANCELLED
} BtbMaintenanceState;
typedef enum BtbMaintenanceResult {
    BTB_MAINTENANCE_OK = 0,
    BTB_MAINTENANCE_INVALID,
    BTB_MAINTENANCE_STATE_ERROR,
    BTB_MAINTENANCE_PRECONDITION,
    BTB_MAINTENANCE_EVIDENCE_MISMATCH,
    BTB_MAINTENANCE_CAPACITY
} BtbMaintenanceResult;
typedef struct BtbMaintenanceReview {
    char changeId[BTB_MAINTENANCE_ID_BYTES];
    char sourceRevision[BTB_MAINTENANCE_REVISION_BYTES];
    char operatorId[BTB_MAINTENANCE_PERSON_BYTES];
    char approverId[BTB_MAINTENANCE_PERSON_BYTES];
    BtbServiceSummary before;
    BtbServiceSummary after;
    uint64_t restorationCaptureId;
    BtbMaintenanceState state;
    int hasAfter;
    int backupVerified;
    int rollbackDocumented;
} BtbMaintenanceReview;
/* Initialise from a READY baseline with unique service identities. A revision
 * is exactly 40 or 64 hexadecimal digits; no repository is queried. */
BtbMaintenanceResult BtbMaintenanceInit(BtbMaintenanceReview *review,
                                         const char *changeId,
                                         const char *sourceRevision,
                                         const char *operatorId,
                                         const BtbServiceSummary *before);
/* Records a *training* approval only. Caller must establish real authority.
 * Distinct, nonempty operator and approver labels model maker/checker. */
BtbMaintenanceResult BtbMaintenanceApprove(BtbMaintenanceReview *review,
                                            const char *approverId,
                                            int backupVerified,
                                            int rollbackDocumented);
BtbMaintenanceResult BtbMaintenanceStart(BtbMaintenanceReview *review);
/* A new observation must cover the same service identities, be a distinct
 * capture and report complete current evidence. A failed readiness result
 * enters ROLLBACK_REQUIRED rather than producing a false success. */
BtbMaintenanceResult BtbMaintenanceObserveAfter(BtbMaintenanceReview *review,
                                                 const BtbServiceSummary *after);
BtbMaintenanceResult BtbMaintenanceComplete(BtbMaintenanceReview *review);
/* After a failed change, record an independent passing restore verification.
 * Recording RESTORED does not itself perform a restore. */
BtbMaintenanceResult BtbMaintenanceConfirmRestored(BtbMaintenanceReview *review,
                                                   const BtbServiceSummary *restored);
BtbMaintenanceResult BtbMaintenanceCancel(BtbMaintenanceReview *review);
/* Human-readable, bounded, failure-atomic educational status. Never use this
 * output as a machine authorisation, credential or production audit record. */
BtbMaintenanceResult BtbMaintenanceExplain(const BtbMaintenanceReview *review,
                                            char *output, size_t capacity);
const char *BtbMaintenanceStateText(BtbMaintenanceState state);
const char *BtbMaintenanceResultText(BtbMaintenanceResult result);
#endif
