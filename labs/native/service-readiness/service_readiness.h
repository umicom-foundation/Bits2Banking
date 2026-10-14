/*-----------------------------------------------------------------------------
 * Bits2Banking | Umicom Foundation | Sammy Hegab | MIT
 * File: labs/native/service-readiness/service_readiness.h
 * PURPOSE: Compose Update 39's C23 observation model into an offline service
 *          dependency/readiness lesson without duplicating its implementation.
 *
 * OWNERSHIP: Caller owns all values; observations are copied. No file, network,
 * process, service, Git, credential or administrative operation occurs here.
 *---------------------------------------------------------------------------*/
#ifndef BTB_SERVICE_READINESS_H
#define BTB_SERVICE_READINESS_H
#include "admin_evidence.h"
#include <stddef.h>
#include <stdint.h>

#define BTB_SERVICE_MAX 8U
#define BTB_SERVICE_ID_MAX 32U
#define BTB_SERVICE_NAME_BYTES 48U

typedef enum BtbServiceResult {
    BTB_SERVICE_OK = 0,
    BTB_SERVICE_INVALID,
    BTB_SERVICE_DUPLICATE,
    BTB_SERVICE_FULL,
    BTB_SERVICE_NOT_FOUND,
    BTB_SERVICE_DEPENDENCY_ERROR,
    BTB_SERVICE_CYCLE
} BtbServiceResult;

typedef struct BtbServiceSpec {
    /* serviceId 1..32 maps to dependency bit serviceId - 1. */
    uint32_t serviceId;
    /* Explicit prerequisites; unknown and cyclic dependencies refuse evaluation. */
    uint32_t dependencyMask;
    /* These checks MUST pass for the service to become READY. */
    uint32_t requiredChecks;
    char name[BTB_SERVICE_NAME_BYTES];
} BtbServiceSpec;

typedef struct BtbServiceNode {
    BtbServiceSpec spec;
    BtbAdminReview evidence;
    int hasEvidence;
} BtbServiceNode;

typedef struct BtbServiceGraph {
    BtbServiceNode nodes[BTB_SERVICE_MAX];
    size_t count;
    uint64_t captureId;
} BtbServiceGraph;

typedef struct BtbServiceOutcome {
    uint32_t serviceId;
    BtbAdminDecision decision;
    size_t staleChecks;
    size_t missingChecks;
    int blockedByDependency;
    int degradedByDependency;
} BtbServiceOutcome;

typedef struct BtbServiceSummary {
    BtbServiceOutcome items[BTB_SERVICE_MAX];
    size_t count;
    size_t ready;
    size_t review;
    size_t blocked;
    uint64_t captureId;
} BtbServiceSummary;

/* All invalid calls preserve existing graph/out parameters unless explicitly
 * documented. A valid init overwrites caller-owned graph storage. */
BtbServiceResult BtbServiceGraphInit(BtbServiceGraph *graph, uint64_t captureId);
BtbServiceResult BtbServiceGraphRegister(BtbServiceGraph *graph,
                                          const BtbServiceSpec *spec);
/* A valid older observation is retained with its original check capture IDs.
 * Evaluation compares those IDs with the new graph captureId and blocks stale
 * required checks. Attach replaces evidence only for the named service. */
BtbServiceResult BtbServiceGraphAttach(BtbServiceGraph *graph, uint32_t serviceId,
                                        const BtbAdminReview *review);
/* Calculates into a private candidate. Unknown prerequisites, cycles or
 * malformed evidence never produce a partial/optimistic output. */
BtbServiceResult BtbServiceGraphEvaluate(const BtbServiceGraph *graph,
                                          BtbServiceSummary *outSummary);
const char *BtbServiceResultText(BtbServiceResult result);
#endif
