/*-----------------------------------------------------------------------------
 * Bits to Banking | Umicom Foundation | Sammy Hegab | MIT
 * File: labs/native/change-impact/impact.c
 * PURPOSE: Validate a module dependency graph and produce fail-closed C23
 *          learning evidence without implementing Git or a build system.
 *---------------------------------------------------------------------------*/
#include "impact.h"

#include <string.h>

static uint64_t KnownMask(size_t count)
{
    return count == 0U ? UINT64_C(0) : ((UINT64_C(1) << count) - UINT64_C(1));
}

/* At most 64 bytes are examined; callers must provide a terminated string.
 * Only ASCII characters used by the public identifier grammar are accepted. */
static int ValidName(const char *name)
{
    size_t index = 0U;
    if (name == NULL) return 0;
    while (index < BTB_IMPACT_NAME_CAPACITY) {
        const unsigned char character = (unsigned char)name[index];
        if (character == 0U) return index > 0U;
        if (!((character >= (unsigned char)'a' && character <= (unsigned char)'z') ||
              (character >= (unsigned char)'A' && character <= (unsigned char)'Z') ||
              (character >= (unsigned char)'0' && character <= (unsigned char)'9') ||
              character == (unsigned char)'_' || character == (unsigned char)'.' ||
              character == (unsigned char)'-')) return 0;
        ++index;
    }
    return 0;
}

/* No libc extension (strnlen) is necessary; 40 or 64 hex characters only. */
int BtbImpactRevisionValid(const char *fullRevision)
{
    size_t index = 0U;
    if (fullRevision == NULL) return 0;
    while (index < BTB_IMPACT_REVISION_CAPACITY) {
        const unsigned char character = (unsigned char)fullRevision[index];
        if (character == 0U) return index == 40U || index == 64U;
        if (!((character >= (unsigned char)'0' && character <= (unsigned char)'9') ||
              (character >= (unsigned char)'a' && character <= (unsigned char)'f') ||
              (character >= (unsigned char)'A' && character <= (unsigned char)'F'))) return 0;
        ++index;
    }
    return 0;
}

static int Reachable(const BtbImpactGraph *graph, size_t start, size_t goal)
{
    uint64_t reached = UINT64_C(1) << start;
    uint64_t pending = reached;
    while (pending != UINT64_C(0)) {
        size_t index;
        for (index = 0U; index < graph->count; ++index) {
            uint64_t bit = UINT64_C(1) << index;
            if ((pending & bit) == UINT64_C(0)) continue;
            pending &= ~bit;
            if (index == goal) return 1;
            {
                const uint64_t added = graph->modules[index].dependencies & ~reached;
                pending |= added;
                reached |= added;
            }
        }
    }
    return 0;
}

int BtbImpactGraphValid(const BtbImpactGraph *graph)
{
    size_t index;
    if (graph == NULL || graph->count > BTB_IMPACT_MAX_MODULES) return 0;
    for (index = 0U; index < graph->count; ++index) {
        const BtbImpactModule *node = &graph->modules[index];
        size_t earlier;
        if (!ValidName(node->name) || node->requiredGates == UINT32_C(0) ||
            (node->requiredGates & ~BTB_GATE_ALL) != UINT32_C(0) ||
            (node->dependencies & ~KnownMask(graph->count)) != UINT64_C(0) ||
            (node->dependencies & (UINT64_C(1) << index)) != UINT64_C(0)) return 0;
        for (earlier = 0U; earlier < index; ++earlier) {
            if (strcmp(node->name, graph->modules[earlier].name) == 0) return 0;
        }
        /* A directed cycle exists if an edge from this node can reach itself. */
        {
            size_t dependency;
            for (dependency = 0U; dependency < graph->count; ++dependency) {
                if ((node->dependencies & (UINT64_C(1) << dependency)) != UINT64_C(0) &&
                    Reachable(graph, dependency, index)) return 0;
            }
        }
    }
    return 1;
}

BtbImpactStatus BtbImpactGraphInit(BtbImpactGraph *graph)
{
    if (graph == NULL) return BTB_IMPACT_INVALID_ARGUMENT;
    *graph = (BtbImpactGraph){0};
    return BTB_IMPACT_OK;
}

BtbImpactStatus BtbImpactAddModule(BtbImpactGraph *graph, const char *name,
                                    uint32_t gates, size_t *outIndex)
{
    size_t index;
    BtbImpactModule candidate = {0};
    if (!BtbImpactGraphValid(graph) || !ValidName(name) || outIndex == NULL ||
        gates == UINT32_C(0) || (gates & ~BTB_GATE_ALL) != UINT32_C(0))
        return BTB_IMPACT_INVALID_ARGUMENT;
    for (index = 0U; index < graph->count; ++index) {
        if (strcmp(graph->modules[index].name, name) == 0) return BTB_IMPACT_DUPLICATE;
    }
    if (graph->count == BTB_IMPACT_MAX_MODULES) return BTB_IMPACT_CAPACITY;
    memcpy(candidate.name, name, strlen(name) + 1U);
    candidate.requiredGates = gates;
    graph->modules[graph->count] = candidate;
    *outIndex = graph->count;
    ++graph->count;
    return BTB_IMPACT_OK;
}

BtbImpactStatus BtbImpactAddDependency(BtbImpactGraph *graph,
                                       size_t dependent, size_t dependency)
{
    uint64_t dependencyBit;
    if (!BtbImpactGraphValid(graph) || dependent >= graph->count ||
        dependency >= graph->count) return BTB_IMPACT_INVALID_ARGUMENT;
    if (dependent == dependency) return BTB_IMPACT_CYCLE;
    dependencyBit = UINT64_C(1) << dependency;
    if ((graph->modules[dependent].dependencies & dependencyBit) != UINT64_C(0))
        return BTB_IMPACT_DUPLICATE;
    if (Reachable(graph, dependency, dependent)) return BTB_IMPACT_CYCLE;
    graph->modules[dependent].dependencies |= dependencyBit;
    return BTB_IMPACT_OK;
}

BtbImpactStatus BtbImpactPlanBuild(const BtbImpactGraph *graph,
                                    const char *fullRevision,
                                    uint64_t changedModules,
                                    BtbImpactPlan *outPlan)
{
    BtbImpactPlan candidate = {0};
    uint64_t affected;
    size_t index;
    int changed;
    if (outPlan == NULL || !BtbImpactGraphValid(graph) ||
        !BtbImpactRevisionValid(fullRevision) || changedModules == UINT64_C(0) ||
        (changedModules & ~KnownMask(graph->count)) != UINT64_C(0))
        return BTB_IMPACT_INVALID_ARGUMENT;
    affected = changedModules;
    /* A topological graph of <=12 nodes stabilises in at most 12 rounds. */
    do {
        changed = 0;
        for (index = 0U; index < graph->count; ++index) {
            const uint64_t bit = UINT64_C(1) << index;
            if ((affected & bit) == UINT64_C(0) &&
                (graph->modules[index].dependencies & affected) != UINT64_C(0)) {
                affected |= bit;
                changed = 1;
            }
        }
    } while (changed);
    for (index = 0U; index < graph->count; ++index) {
        if ((affected & (UINT64_C(1) << index)) != UINT64_C(0))
            candidate.requiredGates |= graph->modules[index].requiredGates;
    }
    memcpy(candidate.sourceRevision, fullRevision, strlen(fullRevision) + 1U);
    candidate.changed = changedModules;
    candidate.affected = affected;
    candidate.moduleCount = graph->count;
    *outPlan = candidate;
    return BTB_IMPACT_OK;
}

static int PlanValid(const BtbImpactPlan *plan)
{
    const uint64_t known = plan != NULL && plan->moduleCount <= BTB_IMPACT_MAX_MODULES
        ? KnownMask(plan->moduleCount) : UINT64_C(0);
    return plan != NULL && plan->moduleCount <= BTB_IMPACT_MAX_MODULES &&
        BtbImpactRevisionValid(plan->sourceRevision) &&
        plan->changed != UINT64_C(0) && (plan->changed & ~known) == UINT64_C(0) &&
        (plan->affected & plan->changed) == plan->changed &&
        (plan->affected & ~known) == UINT64_C(0) &&
        plan->requiredGates != UINT32_C(0) &&
        (plan->requiredGates & ~BTB_GATE_ALL) == UINT32_C(0);
}

BtbImpactStatus BtbImpactAssess(const BtbImpactPlan *plan,
                                 const BtbImpactEvidence *evidence,
                                 BtbImpactAssessment *outAssessment)
{
    BtbImpactAssessment candidate = {0};
    uint32_t observed;
    if (!PlanValid(plan) || evidence == NULL || outAssessment == NULL ||
        !BtbImpactRevisionValid(evidence->sourceRevision) ||
        (evidence->passedGates & ~BTB_GATE_ALL) != UINT32_C(0) ||
        (evidence->failedGates & ~BTB_GATE_ALL) != UINT32_C(0) ||
        (evidence->notRunGates & ~BTB_GATE_ALL) != UINT32_C(0) ||
        (evidence->passedGates & evidence->failedGates) != UINT32_C(0) ||
        (evidence->passedGates & evidence->notRunGates) != UINT32_C(0) ||
        (evidence->failedGates & evidence->notRunGates) != UINT32_C(0) ||
        (evidence->logComplete != 0 && evidence->logComplete != 1) ||
        (evidence->sourceReviewed != 0 && evidence->sourceReviewed != 1))
        return BTB_IMPACT_INVALID_ARGUMENT;
    observed = evidence->passedGates | evidence->failedGates | evidence->notRunGates;
    candidate.missingGates = plan->requiredGates & ~observed;
    candidate.failedGates = plan->requiredGates & evidence->failedGates;
    candidate.notRunGates = plan->requiredGates & evidence->notRunGates;
    if (strcmp(plan->sourceRevision, evidence->sourceRevision) != 0)
        candidate.reasons |= BTB_REASON_STALE_REVISION;
    if (candidate.failedGates != UINT32_C(0)) candidate.reasons |= BTB_REASON_FAILED_GATE;
    if (candidate.notRunGates != UINT32_C(0)) candidate.reasons |= BTB_REASON_NOT_RUN_GATE;
    if (candidate.missingGates != UINT32_C(0)) candidate.reasons |= BTB_REASON_MISSING_GATE;
    if (evidence->droppedDiagnostics != 0U) candidate.reasons |= BTB_REASON_DROPPED_DIAGNOSTIC;
    if (!evidence->logComplete) candidate.reasons |= BTB_REASON_INCOMPLETE_LOG;
    if (!evidence->sourceReviewed) candidate.reasons |= BTB_REASON_UNREVIEWED_SOURCE;
    candidate.suitableForHumanReview = candidate.reasons == UINT32_C(0);
    *outAssessment = candidate;
    return BTB_IMPACT_OK;
}

const char *BtbImpactStatusText(BtbImpactStatus status)
{
    switch (status) {
        case BTB_IMPACT_OK: return "ok";
        case BTB_IMPACT_INVALID_ARGUMENT: return "invalid argument";
        case BTB_IMPACT_CAPACITY: return "capacity exceeded";
        case BTB_IMPACT_DUPLICATE: return "duplicate";
        case BTB_IMPACT_CYCLE: return "dependency cycle";
        default: return "unknown status";
    }
}
