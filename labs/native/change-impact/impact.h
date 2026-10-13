/*-----------------------------------------------------------------------------
 * Bits to Banking | Umicom Foundation | Sammy Hegab | MIT
 * File: labs/native/change-impact/impact.h
 * PURPOSE: Bounded C23 teaching model of change impact and verification gates.
 *
 * OWNERSHIP:
 *   Umicom Framework owns live Git inspection, dependency/build graphs, tool
 *   execution, compiler diagnostics, tests and repository actions. This lab
 *   consumes a caller-verified set of MODULE-LEVEL facts. It never reads or
 *   changes a repository, invokes Git, parses build logs or publishes code.
 *   All records are caller-owned; there are no retained input pointers.
 *---------------------------------------------------------------------------*/
#ifndef BTB_CHANGE_IMPACT_H
#define BTB_CHANGE_IMPACT_H

#include <stddef.h>
#include <stdint.h>

#define BTB_IMPACT_MAX_MODULES 12U
#define BTB_IMPACT_NAME_CAPACITY 48U
#define BTB_IMPACT_REVISION_CAPACITY 65U

/* A gate is a named class of verification, not a claim that a test ran. */
#define BTB_GATE_BUILD        UINT32_C(0x0001)
#define BTB_GATE_UNIT         UINT32_C(0x0002)
#define BTB_GATE_INTEGRATION  UINT32_C(0x0004)
#define BTB_GATE_UI           UINT32_C(0x0008)
#define BTB_GATE_BOOT         UINT32_C(0x0010)
#define BTB_GATE_SECURITY     UINT32_C(0x0020)
#define BTB_GATE_PACKAGE      UINT32_C(0x0040)
#define BTB_GATE_SMOKE        UINT32_C(0x0080)
#define BTB_GATE_ALL          UINT32_C(0x00ff)

/* A nonzero reason means the facts are insufficient for even human review.
 * A zero reason does NOT authorise a Git push, release or deployment. */
#define BTB_REASON_STALE_REVISION      UINT32_C(0x0001)
#define BTB_REASON_FAILED_GATE         UINT32_C(0x0002)
#define BTB_REASON_NOT_RUN_GATE        UINT32_C(0x0004)
#define BTB_REASON_MISSING_GATE        UINT32_C(0x0008)
#define BTB_REASON_DROPPED_DIAGNOSTIC  UINT32_C(0x0010)
#define BTB_REASON_INCOMPLETE_LOG      UINT32_C(0x0020)
#define BTB_REASON_UNREVIEWED_SOURCE   UINT32_C(0x0040)

/* An edge means: module 'dependent' uses/depends on module 'dependency'.
 * Changes propagate in the opposite direction to the edge. */
typedef struct BtbImpactModule {
    char name[BTB_IMPACT_NAME_CAPACITY];
    uint64_t dependencies; /* indices into graph.modules; only lower count bits */
    uint32_t requiredGates;
} BtbImpactModule;

typedef struct BtbImpactGraph {
    BtbImpactModule modules[BTB_IMPACT_MAX_MODULES];
    size_t count;
} BtbImpactGraph;

typedef struct BtbImpactPlan {
    char sourceRevision[BTB_IMPACT_REVISION_CAPACITY]; /* full SHA-1 or SHA-256 */
    uint64_t changed;
    uint64_t affected;
    uint32_t requiredGates;
    size_t moduleCount;
} BtbImpactPlan;

typedef struct BtbImpactEvidence {
    char sourceRevision[BTB_IMPACT_REVISION_CAPACITY];
    uint32_t passedGates;
    uint32_t failedGates;
    uint32_t notRunGates;
    size_t droppedDiagnostics;
    int logComplete;       /* strictly zero or one */
    int sourceReviewed;    /* strictly zero or one */
} BtbImpactEvidence;

typedef struct BtbImpactAssessment {
    uint32_t reasons;
    uint32_t missingGates;
    uint32_t failedGates;
    uint32_t notRunGates;
    int suitableForHumanReview;
} BtbImpactAssessment;

typedef enum BtbImpactStatus {
    BTB_IMPACT_OK = 0,
    BTB_IMPACT_INVALID_ARGUMENT,
    BTB_IMPACT_CAPACITY,
    BTB_IMPACT_DUPLICATE,
    BTB_IMPACT_CYCLE
} BtbImpactStatus;

/* Initialise caller-owned storage; null input is rejected. */
BtbImpactStatus BtbImpactGraphInit(BtbImpactGraph *graph);

/* Add a unique ASCII identifier ([A-Za-z0-9._-]+) and nonempty gate mask.
 * On rejection, neither graph nor outIndex is modified. */
BtbImpactStatus BtbImpactAddModule(BtbImpactGraph *graph, const char *name,
                                    uint32_t gates, size_t *outIndex);

/* Refuse unregistered indices, duplicate edges, self-edges and cycles.
 * Rejected operations leave graph unchanged. */
BtbImpactStatus BtbImpactAddDependency(BtbImpactGraph *graph,
                                       size_t dependent, size_t dependency);

/* Check representation, edges and graph acyclicity without side effects. */
int BtbImpactGraphValid(const BtbImpactGraph *graph);

/* Validate full hex revision and changed set, then calculate transitive
 * reverse dependencies. A rejected call leaves outPlan unchanged. */
BtbImpactStatus BtbImpactPlanBuild(const BtbImpactGraph *graph,
                                    const char *fullRevision,
                                    uint64_t changedModules,
                                    BtbImpactPlan *outPlan);

/* Validates evidence masks and evaluates all mandatory gates. A stale SHA is
 * an ordinary blocking outcome, NOT malformed input. Rejected calls preserve
 * outAssessment. Human-review suitability is NOT publication permission. */
BtbImpactStatus BtbImpactAssess(const BtbImpactPlan *plan,
                                 const BtbImpactEvidence *evidence,
                                 BtbImpactAssessment *outAssessment);

int BtbImpactRevisionValid(const char *fullRevision);
const char *BtbImpactStatusText(BtbImpactStatus status);

#endif
