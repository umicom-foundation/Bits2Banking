/*-----------------------------------------------------------------------------
 * Bits2Banking | Umicom Foundation | Sammy Hegab | MIT
 * File: labs/native/service-readiness/service_readiness.c
 * PURPOSE: Read-only service dependency evaluation using Update 39 evidence.
 *---------------------------------------------------------------------------*/
#include "service_readiness.h"
#include <string.h>

static int ValidName(const char *name)
{
    return name != NULL && name[0] > ' ' &&
           memchr(name, '\0', BTB_SERVICE_NAME_BYTES) != NULL;
}

static size_t FindNode(const BtbServiceGraph *graph, uint32_t serviceId)
{
    size_t i;
    for (i = 0U; i < graph->count; ++i) {
        if (graph->nodes[i].spec.serviceId == serviceId) return i;
    }
    return graph->count;
}

static int ValidSpec(const BtbServiceSpec *spec)
{
    if (spec == NULL || spec->serviceId == 0U ||
        spec->serviceId > BTB_SERVICE_ID_MAX || spec->requiredChecks == 0U ||
        !ValidName(spec->name)) return 0;
    if ((spec->dependencyMask & (UINT32_C(1) << (spec->serviceId - 1U))) != 0U)
        return 0;
    return 1;
}

static int ValidGraphHeader(const BtbServiceGraph *graph)
{
    return graph != NULL && graph->captureId != 0U &&
           graph->count <= BTB_SERVICE_MAX;
}

BtbServiceResult BtbServiceGraphInit(BtbServiceGraph *graph, uint64_t captureId)
{
    if (graph == NULL || captureId == 0U) return BTB_SERVICE_INVALID;
    *graph = (BtbServiceGraph){.captureId = captureId};
    return BTB_SERVICE_OK;
}

BtbServiceResult BtbServiceGraphRegister(BtbServiceGraph *graph,
                                          const BtbServiceSpec *spec)
{
    if (!ValidGraphHeader(graph) || !ValidSpec(spec)) return BTB_SERVICE_INVALID;
    if (FindNode(graph, spec->serviceId) != graph->count) return BTB_SERVICE_DUPLICATE;
    if (graph->count == BTB_SERVICE_MAX) return BTB_SERVICE_FULL;
    graph->nodes[graph->count] = (BtbServiceNode){.spec = *spec};
    ++graph->count;
    return BTB_SERVICE_OK;
}

BtbServiceResult BtbServiceGraphAttach(BtbServiceGraph *graph, uint32_t serviceId,
                                        const BtbAdminReview *review)
{
    BtbAdminReport validation;
    size_t index;
    if (!ValidGraphHeader(graph) || review == NULL) return BTB_SERVICE_INVALID;
    index = FindNode(graph, serviceId);
    if (index == graph->count) return BTB_SERVICE_NOT_FOUND;
    /* Delegated validation is owned by the existing Update 39 contract. */
    if (BtbAdminReviewEvaluate(review, graph->nodes[index].spec.requiredChecks,
                               &validation) != BTB_ADMIN_OK)
        return BTB_SERVICE_INVALID;
    graph->nodes[index].evidence = *review;
    graph->nodes[index].hasEvidence = 1;
    return BTB_SERVICE_OK;
}

/* Recursively visit a bounded, acyclic graph. marks 1=visiting, 2=completed.
 * This is deterministic, not a thread scheduler or a service manager. */
static BtbServiceResult EvaluateNode(const BtbServiceGraph *graph,
                                     size_t index, unsigned char marks[BTB_SERVICE_MAX],
                                     BtbServiceOutcome items[BTB_SERVICE_MAX])
{
    BtbAdminReview observation;
    BtbAdminReport evidence;
    BtbServiceOutcome candidate = {0};
    const BtbServiceNode *node = &graph->nodes[index];
    BtbServiceResult status;
    if (marks[index] == 1U) return BTB_SERVICE_CYCLE;
    if (marks[index] == 2U) return BTB_SERVICE_OK;
    marks[index] = 1U;
    for (uint32_t dependencyId = 1U; dependencyId <= BTB_SERVICE_ID_MAX; ++dependencyId) {
        if ((node->spec.dependencyMask & (UINT32_C(1) << (dependencyId - 1U))) == 0U)
            continue;
        const size_t dependencyIndex = FindNode(graph, dependencyId);
        if (dependencyIndex == graph->count) return BTB_SERVICE_DEPENDENCY_ERROR;
        status = EvaluateNode(graph, dependencyIndex, marks, items);
        if (status != BTB_SERVICE_OK) return status;
        if (items[dependencyIndex].decision == BTB_ADMIN_BLOCKED)
            candidate.blockedByDependency = 1;
        if (items[dependencyIndex].decision == BTB_ADMIN_REVIEW)
            candidate.degradedByDependency = 1;
    }
    /* Missing evidence uses an empty properly initialised review. Provided
     * evidence retains its per-check capture IDs; a new run cannot reuse a
     * previous run's passing checks. */
    if (node->hasEvidence) observation = node->evidence;
    else if (BtbAdminReviewInit(&observation, graph->captureId) != BTB_ADMIN_OK)
        return BTB_SERVICE_INVALID;
    observation.captureId = graph->captureId;
    if (BtbAdminReviewEvaluate(&observation, node->spec.requiredChecks, &evidence)
        != BTB_ADMIN_OK) return BTB_SERVICE_INVALID;
    candidate.serviceId = node->spec.serviceId;
    candidate.staleChecks = evidence.stale;
    candidate.missingChecks = evidence.missingRequired;
    candidate.decision = evidence.decision;
    if (candidate.blockedByDependency) candidate.decision = BTB_ADMIN_BLOCKED;
    else if (candidate.degradedByDependency && candidate.decision == BTB_ADMIN_READY)
        candidate.decision = BTB_ADMIN_REVIEW;
    items[index] = candidate;
    marks[index] = 2U;
    return BTB_SERVICE_OK;
}

BtbServiceResult BtbServiceGraphEvaluate(const BtbServiceGraph *graph,
                                          BtbServiceSummary *outSummary)
{
    unsigned char marks[BTB_SERVICE_MAX] = {0};
    BtbServiceSummary candidate = {0};
    uint32_t usedIds = 0U;
    if (!ValidGraphHeader(graph) || outSummary == NULL || graph->count == 0U)
        return BTB_SERVICE_INVALID;
    for (size_t i = 0U; i < graph->count; ++i) {
        const BtbServiceNode *node = &graph->nodes[i];
        if (!ValidSpec(&node->spec)) return BTB_SERVICE_INVALID;
        const uint32_t bit = UINT32_C(1) << (node->spec.serviceId - 1U);
        if ((usedIds & bit) != 0U) return BTB_SERVICE_INVALID;
        usedIds |= bit;
    }
    candidate.count = graph->count;
    candidate.captureId = graph->captureId;
    for (size_t i = 0U; i < graph->count; ++i) {
        BtbServiceResult status = EvaluateNode(graph, i, marks, candidate.items);
        if (status != BTB_SERVICE_OK) return status;
    }
    for (size_t i = 0U; i < candidate.count; ++i) {
        switch (candidate.items[i].decision) {
            case BTB_ADMIN_READY: ++candidate.ready; break;
            case BTB_ADMIN_REVIEW: ++candidate.review; break;
            case BTB_ADMIN_BLOCKED: ++candidate.blocked; break;
            default: return BTB_SERVICE_INVALID;
        }
    }
    *outSummary = candidate;
    return BTB_SERVICE_OK;
}

const char *BtbServiceResultText(BtbServiceResult result)
{
    switch (result) {
        case BTB_SERVICE_OK: return "OK";
        case BTB_SERVICE_INVALID: return "INVALID";
        case BTB_SERVICE_DUPLICATE: return "DUPLICATE";
        case BTB_SERVICE_FULL: return "FULL";
        case BTB_SERVICE_NOT_FOUND: return "NOT_FOUND";
        case BTB_SERVICE_DEPENDENCY_ERROR: return "MISSING_DEPENDENCY";
        case BTB_SERVICE_CYCLE: return "CYCLE";
        default: return "UNKNOWN";
    }
}
