/*-----------------------------------------------------------------------------
 * Bits to Banking | Umicom Foundation | Sammy Hegab | MIT
 * File: labs/native/change-impact/test_impact.c
 * PURPOSE: Named native C23, deterministic and negative verification cases.
 *---------------------------------------------------------------------------*/
#include "impact.h"
#include <inttypes.h>
#include <stdio.h>
#include <string.h>

#define SHA_A "0123456789abcdef0123456789abcdef01234567"
#define SHA_B "abcdef0123456789abcdef0123456789abcdef01"
#define SHA_256 "0123456789abcdef0123456789abcdef0123456789abcdef0123456789abcdef"
#define CHECK(expr) do { if (!(expr)) { \
    fprintf(stderr, "%s:%d: check failed: %s\n", __FILE__, __LINE__, #expr); \
    return 0; } } while (0)
#define OK(expr) CHECK((expr) == BTB_IMPACT_OK)

/* Fixed teaching graph. An edge points from consumer towards its dependency:
 * base -> vcs,build -> ui -> studio,trader; base -> os, build -> bank.
 * Check the source for the actual directions, rather than interpreting arrows
 * as permission to update another repository. */
static int Fixture(BtbImpactGraph *graph)
{
    size_t index;
    static const char *const names[] = {
        "framework.base", "framework.vcs", "framework.build", "framework.ui",
        "applications.studio", "applications.trader", "os.desktop", "applications.bank"
    };
    static const uint32_t gates[] = {
        BTB_GATE_BUILD | BTB_GATE_UNIT,
        BTB_GATE_BUILD | BTB_GATE_INTEGRATION,
        BTB_GATE_BUILD | BTB_GATE_UNIT,
        BTB_GATE_BUILD | BTB_GATE_UI,
        BTB_GATE_INTEGRATION | BTB_GATE_SMOKE,
        BTB_GATE_SMOKE,
        BTB_GATE_BOOT | BTB_GATE_SECURITY,
        BTB_GATE_INTEGRATION | BTB_GATE_SECURITY
    };
    const size_t count = sizeof names / sizeof names[0];
    OK(BtbImpactGraphInit(graph));
    for (index = 0U; index < count; ++index) {
        size_t observedIndex = BTB_IMPACT_MAX_MODULES;
        OK(BtbImpactAddModule(graph, names[index], gates[index], &observedIndex));
        CHECK(observedIndex == index);
    }
    OK(BtbImpactAddDependency(graph, 1U, 0U));
    OK(BtbImpactAddDependency(graph, 2U, 0U));
    OK(BtbImpactAddDependency(graph, 3U, 2U));
    OK(BtbImpactAddDependency(graph, 4U, 1U));
    OK(BtbImpactAddDependency(graph, 4U, 3U));
    OK(BtbImpactAddDependency(graph, 5U, 3U));
    OK(BtbImpactAddDependency(graph, 6U, 0U));
    OK(BtbImpactAddDependency(graph, 6U, 3U));
    OK(BtbImpactAddDependency(graph, 7U, 2U));
    CHECK(BtbImpactGraphValid(graph));
    return 1;
}

static int Ready(BtbImpactPlan *plan, BtbImpactEvidence *evidence)
{
    BtbImpactGraph graph;
    CHECK(Fixture(&graph));
    OK(BtbImpactPlanBuild(&graph, SHA_A, UINT64_C(1) << 1U, plan));
    *evidence = (BtbImpactEvidence){0};
    memcpy(evidence->sourceRevision, SHA_A, sizeof SHA_A);
    evidence->passedGates = plan->requiredGates;
    evidence->logComplete = 1;
    evidence->sourceReviewed = 1;
    return 1;
}

static int RunCase(const char *name)
{
    BtbImpactGraph graph = {0};
    BtbImpactPlan plan = {0};
    BtbImpactEvidence evidence = {0};
    BtbImpactAssessment assessment = {0};
    size_t index = 777U;
    BtbImpactStatus status;
    if (strcmp(name, "graph_empty") == 0) {
        OK(BtbImpactGraphInit(&graph));
        CHECK(BtbImpactGraphValid(&graph) && graph.count == 0U);
    } else if (strcmp(name, "graph_null") == 0) {
        CHECK(BtbImpactGraphInit(NULL) == BTB_IMPACT_INVALID_ARGUMENT);
        CHECK(!BtbImpactGraphValid(NULL));
    } else if (strcmp(name, "duplicate_modules") == 0) {
        OK(BtbImpactGraphInit(&graph));
        OK(BtbImpactAddModule(&graph, "framework.vcs", BTB_GATE_BUILD, &index));
        CHECK(BtbImpactAddModule(&graph, "framework.vcs", BTB_GATE_UNIT, &index) == BTB_IMPACT_DUPLICATE);
        CHECK(graph.count == 1U && index == 0U);
    } else if (strcmp(name, "name_empty") == 0) {
        OK(BtbImpactGraphInit(&graph));
        CHECK(BtbImpactAddModule(&graph, "", BTB_GATE_BUILD, &index) == BTB_IMPACT_INVALID_ARGUMENT);
        CHECK(index == 777U && graph.count == 0U);
    } else if (strcmp(name, "name_space") == 0) {
        OK(BtbImpactGraphInit(&graph));
        CHECK(BtbImpactAddModule(&graph, "bad path", BTB_GATE_BUILD, &index) == BTB_IMPACT_INVALID_ARGUMENT);
        CHECK(index == 777U && graph.count == 0U);
    } else if (strcmp(name, "name_overflow") == 0) {
        const char longName[] = "012345678901234567890123456789012345678901234567890";
        OK(BtbImpactGraphInit(&graph));
        CHECK(BtbImpactAddModule(&graph, longName, BTB_GATE_BUILD, &index) == BTB_IMPACT_INVALID_ARGUMENT);
        CHECK(index == 777U);
    } else if (strcmp(name, "invalid_gates") == 0) {
        OK(BtbImpactGraphInit(&graph));
        CHECK(BtbImpactAddModule(&graph, "x", UINT32_C(0), &index) == BTB_IMPACT_INVALID_ARGUMENT);
        CHECK(BtbImpactAddModule(&graph, "x", UINT32_C(0x100), &index) == BTB_IMPACT_INVALID_ARGUMENT);
        CHECK(index == 777U);
    } else if (strcmp(name, "capacity") == 0) {
        static const char *const identifiers[] = {
            "n0", "n1", "n2", "n3", "n4", "n5", "n6", "n7", "n8", "n9", "n10", "n11"
        };
        OK(BtbImpactGraphInit(&graph));
        for (size_t i = 0U; i < BTB_IMPACT_MAX_MODULES; ++i)
            OK(BtbImpactAddModule(&graph, identifiers[i], BTB_GATE_BUILD, &index));
        CHECK(BtbImpactAddModule(&graph, "n12", BTB_GATE_BUILD, &index) == BTB_IMPACT_CAPACITY);
        CHECK(graph.count == BTB_IMPACT_MAX_MODULES);
    } else if (strcmp(name, "module_atomic") == 0) {
        BtbImpactGraph before;
        CHECK(Fixture(&graph));
        before = graph;
        CHECK(BtbImpactAddModule(&graph, "bad:name", BTB_GATE_UNIT, &index) == BTB_IMPACT_INVALID_ARGUMENT);
        CHECK(memcmp(&before, &graph, sizeof graph) == 0 && index == 777U);
    } else if (strcmp(name, "edge_added") == 0) {
        CHECK(Fixture(&graph));
        CHECK((graph.modules[4].dependencies & (UINT64_C(1) << 1U)) != 0U);
    } else if (strcmp(name, "edge_duplicate") == 0) {
        BtbImpactGraph before;
        CHECK(Fixture(&graph));
        before = graph;
        CHECK(BtbImpactAddDependency(&graph, 4U, 1U) == BTB_IMPACT_DUPLICATE);
        CHECK(memcmp(&before, &graph, sizeof graph) == 0);
    } else if (strcmp(name, "cycle_self") == 0) {
        CHECK(Fixture(&graph));
        CHECK(BtbImpactAddDependency(&graph, 0U, 0U) == BTB_IMPACT_CYCLE);
    } else if (strcmp(name, "cycle_indirect") == 0) {
        BtbImpactGraph before;
        CHECK(Fixture(&graph));
        before = graph;
        CHECK(BtbImpactAddDependency(&graph, 0U, 4U) == BTB_IMPACT_CYCLE);
        CHECK(memcmp(&before, &graph, sizeof graph) == 0);
    } else if (strcmp(name, "edge_atomic") == 0) {
        BtbImpactGraph before;
        CHECK(Fixture(&graph));
        before = graph;
        CHECK(BtbImpactAddDependency(&graph, 4U, 99U) == BTB_IMPACT_INVALID_ARGUMENT);
        CHECK(memcmp(&before, &graph, sizeof graph) == 0);
    } else if (strcmp(name, "corrupted_graph") == 0) {
        CHECK(Fixture(&graph));
        graph.modules[0].dependencies = UINT64_C(1) << 5U;
        CHECK(!BtbImpactGraphValid(&graph));
        CHECK(BtbImpactAddDependency(&graph, 1U, 2U) == BTB_IMPACT_INVALID_ARGUMENT);
    } else if (strcmp(name, "sha1_valid") == 0) {
        CHECK(BtbImpactRevisionValid(SHA_A));
        CHECK(BtbImpactRevisionValid(SHA_B));
    } else if (strcmp(name, "sha256_valid") == 0) {
        CHECK(BtbImpactRevisionValid(SHA_256));
    } else if (strcmp(name, "revision_short") == 0) {
        CHECK(!BtbImpactRevisionValid("abc123") && !BtbImpactRevisionValid(""));
    } else if (strcmp(name, "revision_bad_hex") == 0) {
        CHECK(!BtbImpactRevisionValid("0123456789abcdef0123456789abcdef0123456g"));
    } else if (strcmp(name, "revision_too_long") == 0) {
        CHECK(!BtbImpactRevisionValid("0123456789abcdef0123456789abcdef0123456789abcdef0123456789abcdef0"));
    } else if (strcmp(name, "plan_empty_changes") == 0) {
        CHECK(Fixture(&graph));
        CHECK(BtbImpactPlanBuild(&graph, SHA_A, 0U, &plan) == BTB_IMPACT_INVALID_ARGUMENT);
    } else if (strcmp(name, "plan_unknown_index") == 0) {
        CHECK(Fixture(&graph));
        CHECK(BtbImpactPlanBuild(&graph, SHA_A, UINT64_C(1) << 10U, &plan) == BTB_IMPACT_INVALID_ARGUMENT);
    } else if (strcmp(name, "plan_transitive") == 0) {
        CHECK(Fixture(&graph));
        OK(BtbImpactPlanBuild(&graph, SHA_A, UINT64_C(1), &plan));
        CHECK(plan.affected == UINT64_C(0xff));
        CHECK((plan.requiredGates & BTB_GATE_BOOT) != 0U);
    } else if (strcmp(name, "plan_targeted") == 0) {
        CHECK(Fixture(&graph));
        OK(BtbImpactPlanBuild(&graph, SHA_A, UINT64_C(1) << 1U, &plan));
        CHECK(plan.affected == ((UINT64_C(1) << 1U) | (UINT64_C(1) << 4U)));
        CHECK((plan.requiredGates & BTB_GATE_BOOT) == 0U);
    } else if (strcmp(name, "plan_ui_change") == 0) {
        CHECK(Fixture(&graph));
        OK(BtbImpactPlanBuild(&graph, SHA_A, UINT64_C(1) << 3U, &plan));
        CHECK(plan.affected == (UINT64_C(1) << 3U | UINT64_C(1) << 4U |
                                UINT64_C(1) << 5U | UINT64_C(1) << 6U));
    } else if (strcmp(name, "plan_atomic") == 0) {
        BtbImpactPlan before;
        CHECK(Fixture(&graph));
        memset(&plan, 0x37, sizeof plan);
        before = plan;
        CHECK(BtbImpactPlanBuild(&graph, "badsha", UINT64_C(1), &plan) == BTB_IMPACT_INVALID_ARGUMENT);
        CHECK(memcmp(&plan, &before, sizeof plan) == 0);
    } else if (strcmp(name, "assess_ready") == 0) {
        CHECK(Ready(&plan, &evidence));
        OK(BtbImpactAssess(&plan, &evidence, &assessment));
        CHECK(assessment.reasons == 0U && assessment.suitableForHumanReview);
    } else if (strcmp(name, "assess_stale") == 0) {
        CHECK(Ready(&plan, &evidence));
        memcpy(evidence.sourceRevision, SHA_B, sizeof SHA_B);
        OK(BtbImpactAssess(&plan, &evidence, &assessment));
        CHECK((assessment.reasons & BTB_REASON_STALE_REVISION) != 0U);
    } else if (strcmp(name, "assess_missing") == 0) {
        CHECK(Ready(&plan, &evidence));
        evidence.passedGates = 0U;
        OK(BtbImpactAssess(&plan, &evidence, &assessment));
        CHECK(assessment.missingGates == plan.requiredGates);
    } else if (strcmp(name, "assess_failed") == 0) {
        CHECK(Ready(&plan, &evidence));
        evidence.passedGates &= ~BTB_GATE_BUILD;
        evidence.failedGates = BTB_GATE_BUILD;
        OK(BtbImpactAssess(&plan, &evidence, &assessment));
        CHECK((assessment.reasons & BTB_REASON_FAILED_GATE) != 0U);
    } else if (strcmp(name, "assess_not_run") == 0) {
        CHECK(Ready(&plan, &evidence));
        evidence.passedGates &= ~BTB_GATE_INTEGRATION;
        evidence.notRunGates = BTB_GATE_INTEGRATION;
        OK(BtbImpactAssess(&plan, &evidence, &assessment));
        CHECK((assessment.reasons & BTB_REASON_NOT_RUN_GATE) != 0U);
    } else if (strcmp(name, "assess_dropped") == 0) {
        CHECK(Ready(&plan, &evidence));
        evidence.droppedDiagnostics = 1U;
        OK(BtbImpactAssess(&plan, &evidence, &assessment));
        CHECK((assessment.reasons & BTB_REASON_DROPPED_DIAGNOSTIC) != 0U);
    } else if (strcmp(name, "assess_incomplete_log") == 0) {
        CHECK(Ready(&plan, &evidence));
        evidence.logComplete = 0;
        OK(BtbImpactAssess(&plan, &evidence, &assessment));
        CHECK((assessment.reasons & BTB_REASON_INCOMPLETE_LOG) != 0U);
    } else if (strcmp(name, "assess_unreviewed") == 0) {
        CHECK(Ready(&plan, &evidence));
        evidence.sourceReviewed = 0;
        OK(BtbImpactAssess(&plan, &evidence, &assessment));
        CHECK((assessment.reasons & BTB_REASON_UNREVIEWED_SOURCE) != 0U);
    } else if (strcmp(name, "assess_overlap") == 0) {
        CHECK(Ready(&plan, &evidence));
        evidence.failedGates = BTB_GATE_BUILD;
        CHECK(BtbImpactAssess(&plan, &evidence, &assessment) == BTB_IMPACT_INVALID_ARGUMENT);
    } else if (strcmp(name, "assess_badmask") == 0) {
        CHECK(Ready(&plan, &evidence));
        evidence.passedGates |= UINT32_C(0x100);
        CHECK(BtbImpactAssess(&plan, &evidence, &assessment) == BTB_IMPACT_INVALID_ARGUMENT);
    } else if (strcmp(name, "assess_badboolean") == 0) {
        CHECK(Ready(&plan, &evidence));
        evidence.sourceReviewed = 2;
        CHECK(BtbImpactAssess(&plan, &evidence, &assessment) == BTB_IMPACT_INVALID_ARGUMENT);
    } else if (strcmp(name, "assess_atomic") == 0) {
        BtbImpactAssessment before;
        CHECK(Ready(&plan, &evidence));
        memset(&assessment, 0x5a, sizeof assessment);
        before = assessment;
        evidence.logComplete = -1;
        status = BtbImpactAssess(&plan, &evidence, &assessment);
        CHECK(status == BTB_IMPACT_INVALID_ARGUMENT);
        CHECK(memcmp(&assessment, &before, sizeof assessment) == 0);
    } else if (strcmp(name, "assess_extra_pass") == 0) {
        CHECK(Ready(&plan, &evidence));
        evidence.passedGates |= BTB_GATE_SECURITY;
        OK(BtbImpactAssess(&plan, &evidence, &assessment));
        CHECK(assessment.reasons == 0U);
    } else if (strcmp(name, "assess_multiple") == 0) {
        CHECK(Ready(&plan, &evidence));
        memcpy(evidence.sourceRevision, SHA_B, sizeof SHA_B);
        evidence.passedGates = 0U;
        evidence.droppedDiagnostics = 4U;
        evidence.logComplete = 0;
        evidence.sourceReviewed = 0;
        OK(BtbImpactAssess(&plan, &evidence, &assessment));
        CHECK((assessment.reasons & (BTB_REASON_STALE_REVISION |
              BTB_REASON_MISSING_GATE | BTB_REASON_DROPPED_DIAGNOSTIC |
              BTB_REASON_INCOMPLETE_LOG | BTB_REASON_UNREVIEWED_SOURCE)) ==
              (BTB_REASON_STALE_REVISION | BTB_REASON_MISSING_GATE |
              BTB_REASON_DROPPED_DIAGNOSTIC | BTB_REASON_INCOMPLETE_LOG |
              BTB_REASON_UNREVIEWED_SOURCE));
    } else if (strcmp(name, "assess_sha256") == 0) {
        CHECK(Fixture(&graph));
        OK(BtbImpactPlanBuild(&graph, SHA_256, UINT64_C(1), &plan));
        memcpy(evidence.sourceRevision, SHA_256, sizeof SHA_256);
        evidence.passedGates = plan.requiredGates;
        evidence.sourceReviewed = 1;
        evidence.logComplete = 1;
        OK(BtbImpactAssess(&plan, &evidence, &assessment));
        CHECK(assessment.suitableForHumanReview);
    } else if (strcmp(name, "deterministic_mutations") == 0) {
        uint32_t state = UINT32_C(0x70c3ef51);
        CHECK(Fixture(&graph));
        for (size_t step = 0U; step < 50000U; ++step) {
            uint64_t changed;
            state ^= state << 13;
            state ^= state >> 17;
            state ^= state << 5;
            changed = (uint64_t)(state & UINT32_C(0xff));
            if (changed == 0U) changed = 1U;
            OK(BtbImpactPlanBuild(&graph, SHA_A, changed, &plan));
            CHECK((plan.changed & plan.affected) == plan.changed);
            CHECK((plan.requiredGates & BTB_GATE_ALL) == plan.requiredGates);
            memcpy(evidence.sourceRevision, SHA_A, sizeof SHA_A);
            evidence.passedGates = plan.requiredGates;
            evidence.failedGates = 0U;
            evidence.notRunGates = 0U;
            evidence.droppedDiagnostics = 0U;
            evidence.logComplete = 1;
            evidence.sourceReviewed = 1;
            OK(BtbImpactAssess(&plan, &evidence, &assessment));
            CHECK(assessment.suitableForHumanReview);
            /* Every fiftieth sample must reject a stale observation. */
            if ((step % 50U) == 0U) {
                memcpy(evidence.sourceRevision, SHA_B, sizeof SHA_B);
                OK(BtbImpactAssess(&plan, &evidence, &assessment));
                CHECK(assessment.reasons == BTB_REASON_STALE_REVISION);
            }
        }
    } else {
        fprintf(stderr, "Unknown test: %s\n", name);
        return 0;
    }
    return 1;
}

int main(int argc, char **argv)
{
    if (argc != 2) {
        fprintf(stderr, "Usage: btb-change-impact-test CASE_NAME\n");
        return 2;
    }
    if (!RunCase(argv[1])) return 1;
    printf("PASS %s\n", argv[1]);
    return 0;
}
