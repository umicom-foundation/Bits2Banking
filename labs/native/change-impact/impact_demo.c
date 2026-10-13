/*-----------------------------------------------------------------------------
 * Bits to Banking | Umicom Foundation | Sammy Hegab | MIT
 * File: labs/native/change-impact/impact_demo.c
 * PURPOSE: Illustrate a fictional Framework change and a required OS rebuild.
 *---------------------------------------------------------------------------*/
#include "impact.h"
#include <inttypes.h>
#include <stdio.h>
#include <string.h>

#define FICTIONAL_REVISION "0123456789abcdef0123456789abcdef01234567"

static int Add(BtbImpactGraph *graph, const char *name, uint32_t gates,
               size_t *index)
{
    BtbImpactStatus result = BtbImpactAddModule(graph, name, gates, index);
    if (result != BTB_IMPACT_OK) {
        fprintf(stderr, "Cannot add %s: %s\n", name, BtbImpactStatusText(result));
        return 0;
    }
    return 1;
}

int main(void)
{
    BtbImpactGraph graph;
    BtbImpactPlan plan;
    BtbImpactAssessment assessment;
    BtbImpactEvidence evidence = {0};
    size_t frameworkBase = 0U, vcs = 0U, studio = 0U, os = 0U;
    BtbImpactStatus result;
    if (BtbImpactGraphInit(&graph) != BTB_IMPACT_OK ||
        !Add(&graph, "framework.base", BTB_GATE_BUILD | BTB_GATE_UNIT, &frameworkBase) ||
        !Add(&graph, "framework.vcs", BTB_GATE_BUILD | BTB_GATE_INTEGRATION, &vcs) ||
        !Add(&graph, "applications.studio", BTB_GATE_SMOKE | BTB_GATE_UI, &studio) ||
        !Add(&graph, "os.desktop", BTB_GATE_BOOT | BTB_GATE_SECURITY, &os)) return 1;
    if (BtbImpactAddDependency(&graph, vcs, frameworkBase) != BTB_IMPACT_OK ||
        BtbImpactAddDependency(&graph, studio, vcs) != BTB_IMPACT_OK ||
        BtbImpactAddDependency(&graph, os, frameworkBase) != BTB_IMPACT_OK)
        return 1;

    result = BtbImpactPlanBuild(&graph, FICTIONAL_REVISION,
                                UINT64_C(1) << frameworkBase, &plan);
    if (result != BTB_IMPACT_OK) return 1;
    printf("Educational change impact — fictional Umicom checkout\n");
    printf("Changed module bit: 0x%04" PRIx64 "\n", plan.changed);
    printf("Affected modules bitmask: 0x%04" PRIx64 "\n", plan.affected);
    printf("Mandatory evidence gate mask: 0x%04" PRIx32 "\n", plan.requiredGates);
    printf("Affected modules:\n");
    for (size_t index = 0U; index < graph.count; ++index) {
        if ((plan.affected & (UINT64_C(1) << index)) != 0U)
            printf(" - %s\n", graph.modules[index].name);
    }
    /* The first review has not performed an OS boot check. */
    memcpy(evidence.sourceRevision, FICTIONAL_REVISION, sizeof FICTIONAL_REVISION);
    evidence.passedGates = plan.requiredGates & ~BTB_GATE_BOOT;
    evidence.notRunGates = BTB_GATE_BOOT;
    evidence.logComplete = 1;
    evidence.sourceReviewed = 1;
    if (BtbImpactAssess(&plan, &evidence, &assessment) != BTB_IMPACT_OK) return 1;
    printf("First review: reasons=0x%04" PRIx32 " (not ready, OS boot not run)\n",
           assessment.reasons);
    if ((assessment.reasons & BTB_REASON_NOT_RUN_GATE) == UINT32_C(0)) return 1;
    /* A fictional second review supplies all required observations. */
    evidence.passedGates |= BTB_GATE_BOOT;
    evidence.notRunGates = 0U;
    if (BtbImpactAssess(&plan, &evidence, &assessment) != BTB_IMPACT_OK) return 1;
    printf("Second review: reasons=0x%04" PRIx32 " (eligible for HUMAN review only)\n",
           assessment.reasons);
    return assessment.suitableForHumanReview ? 0 : 1;
}
