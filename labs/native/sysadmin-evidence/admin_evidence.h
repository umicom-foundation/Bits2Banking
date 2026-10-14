/*-----------------------------------------------------------------------------
 * Bits2Banking | Umicom Foundation | Sammy Hegab | MIT
 * File: labs/native/sysadmin-evidence/admin_evidence.h
 * PURPOSE: Offline, deterministic system-administration evidence review model.
 *
 * ARCHITECTURE:
 *   Training only. This module consumes supplied observations. It does not
 *   discover services, read private logs, change permissions, execute Git,
 *   manage backups or replace Umicom Framework's production services.
 *   The caller owns every object. Invalid operations preserve their outputs.
 *---------------------------------------------------------------------------*/
#ifndef BTB_SYSADMIN_EVIDENCE_H
#define BTB_SYSADMIN_EVIDENCE_H

#include <stddef.h>
#include <stdint.h>

#define BTB_ADMIN_MAX_CHECKS 16U
#define BTB_ADMIN_MAX_CHECK_ID 32U
#define BTB_ADMIN_LABEL_CAPACITY 64U

typedef enum BtbAdminResult {
    BTB_ADMIN_OK = 0,
    BTB_ADMIN_INVALID,
    BTB_ADMIN_DUPLICATE,
    BTB_ADMIN_FULL
} BtbAdminResult;

typedef enum BtbAdminState {
    BTB_ADMIN_PASS = 1,
    BTB_ADMIN_WARNING = 2,
    BTB_ADMIN_FAILURE = 3,
    BTB_ADMIN_NOT_RUN = 4
} BtbAdminState;

typedef enum BtbAdminDecision {
    BTB_ADMIN_READY = 1,
    BTB_ADMIN_REVIEW = 2,
    BTB_ADMIN_BLOCKED = 3
} BtbAdminDecision;

typedef struct BtbAdminObservation {
    /* ID 1..32 selects one named check in the caller's declared runbook. */
    uint32_t checkId;
    /* The capture ID binds the evidence to one observed support session. */
    uint64_t captureId;
    BtbAdminState state;
    /* Human-readable name only: never place secrets or private log lines here. */
    char label[BTB_ADMIN_LABEL_CAPACITY];
} BtbAdminObservation;

typedef struct BtbAdminReview {
    BtbAdminObservation observations[BTB_ADMIN_MAX_CHECKS];
    size_t count;
    uint64_t captureId;
} BtbAdminReview;

typedef struct BtbAdminReport {
    BtbAdminDecision decision;
    size_t passed;
    size_t warnings;
    size_t failed;
    size_t notRun;
    size_t stale;
    size_t missingRequired;
    uint32_t presentMask;
    uint32_t requiredMask;
} BtbAdminReport;

/* Initialise caller-owned storage; captureId must identify a real teaching run. */
BtbAdminResult BtbAdminReviewInit(BtbAdminReview *review, uint64_t captureId);

/* The observation is copied. Duplicate IDs, invalid labels and full storage
 * are refused without modifying review (failure atomicity). */
BtbAdminResult BtbAdminReviewAdd(BtbAdminReview *review,
                                 const BtbAdminObservation *observation);

/* requiredMask bit N-1 means that check N must be present, current and PASS.
 * Missing/stale/unrun required checks block readiness. Optional warnings or
 * failures result in REVIEW, never READY. Invalid inputs preserve outReport.
 * No function here changes a machine, a repository or a real service. */
BtbAdminResult BtbAdminReviewEvaluate(const BtbAdminReview *review,
                                      uint32_t requiredMask,
                                      BtbAdminReport *outReport);

const char *BtbAdminDecisionText(BtbAdminDecision decision);

#endif
