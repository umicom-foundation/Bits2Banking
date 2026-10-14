/*-----------------------------------------------------------------------------
 * Bits2Banking | Umicom Foundation | Sammy Hegab | MIT
 * PURPOSE: Negative, stale, dependency and deterministic-mutation tests.
 *---------------------------------------------------------------------------*/
#include "service_readiness.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define REQUIRE(expr) do { if (!(expr)) { \
    (void)fprintf(stderr, "%s:%d: failed: %s\n", __FILE__, __LINE__, #expr); \
    return 1; } } while (0)

static BtbServiceSpec Spec(uint32_t id, uint32_t dependencies)
{
    BtbServiceSpec spec = {0};
    spec.serviceId = id;
    spec.dependencyMask = dependencies;
    spec.requiredChecks = UINT32_C(1);
    (void)snprintf(spec.name, sizeof(spec.name), "Teaching service %u", id);
    return spec;
}

static int Attach(BtbServiceGraph *graph, uint32_t serviceId, BtbAdminState state,
                  int optionalWarning, int oldCapture)
{
    BtbAdminReview review;
    BtbAdminObservation check = {0};
    const uint64_t origin = oldCapture ? graph->captureId - 1U : graph->captureId;
    if (BtbAdminReviewInit(&review, origin) != BTB_ADMIN_OK) return 0;
    check = (BtbAdminObservation){1U, origin, state, "Teaching service check"};
    if (BtbAdminReviewAdd(&review, &check) != BTB_ADMIN_OK) return 0;
    if (optionalWarning) {
        check = (BtbAdminObservation){2U, origin, BTB_ADMIN_WARNING, "Optional diagnostic"};
        if (BtbAdminReviewAdd(&review, &check) != BTB_ADMIN_OK) return 0;
    }
    return BtbServiceGraphAttach(graph, serviceId, &review) == BTB_SERVICE_OK;
}

static int BasicGraph(BtbServiceGraph *graph, int twoNodes)
{
    BtbServiceSpec node;
    if (BtbServiceGraphInit(graph, UINT64_C(500)) != BTB_SERVICE_OK) return 0;
    node = Spec(1U, 0U);
    if (BtbServiceGraphRegister(graph, &node) != BTB_SERVICE_OK) return 0;
    if (twoNodes) {
        node = Spec(2U, UINT32_C(1));
        if (BtbServiceGraphRegister(graph, &node) != BTB_SERVICE_OK) return 0;
    }
    return 1;
}

static int TestReady(void)
{
    BtbServiceGraph g; BtbServiceSummary s;
    REQUIRE(BasicGraph(&g, 1));
    REQUIRE(Attach(&g, 1U, BTB_ADMIN_PASS, 0, 0));
    REQUIRE(Attach(&g, 2U, BTB_ADMIN_PASS, 0, 0));
    REQUIRE(BtbServiceGraphEvaluate(&g, &s) == BTB_SERVICE_OK);
    REQUIRE(s.ready == 2U && s.review == 0U && s.blocked == 0U);
    REQUIRE(s.items[0].serviceId == 1U && s.items[1].serviceId == 2U);
    return 0;
}
static int TestMissing(void)
{
    BtbServiceGraph g; BtbServiceSummary s;
    REQUIRE(BasicGraph(&g, 0));
    REQUIRE(BtbServiceGraphEvaluate(&g, &s) == BTB_SERVICE_OK);
    REQUIRE(s.blocked == 1U && s.items[0].missingChecks == 1U);
    return 0;
}
static int TestOptionalWarning(void)
{
    BtbServiceGraph g; BtbServiceSummary s;
    REQUIRE(BasicGraph(&g, 0));
    REQUIRE(Attach(&g, 1U, BTB_ADMIN_PASS, 1, 0));
    REQUIRE(BtbServiceGraphEvaluate(&g, &s) == BTB_SERVICE_OK);
    REQUIRE(s.review == 1U && s.blocked == 0U);
    return 0;
}
static int TestRequiredFailure(void)
{
    BtbServiceGraph g; BtbServiceSummary s;
    REQUIRE(BasicGraph(&g, 0));
    REQUIRE(Attach(&g, 1U, BTB_ADMIN_FAILURE, 0, 0));
    REQUIRE(BtbServiceGraphEvaluate(&g, &s) == BTB_SERVICE_OK);
    REQUIRE(s.blocked == 1U);
    return 0;
}
static int TestRequiredNotRun(void)
{
    BtbServiceGraph g; BtbServiceSummary s;
    REQUIRE(BasicGraph(&g, 0));
    REQUIRE(Attach(&g, 1U, BTB_ADMIN_NOT_RUN, 0, 0));
    REQUIRE(BtbServiceGraphEvaluate(&g, &s) == BTB_SERVICE_OK);
    REQUIRE(s.blocked == 1U);
    return 0;
}
static int TestStale(void)
{
    BtbServiceGraph g; BtbServiceSummary s;
    REQUIRE(BasicGraph(&g, 0));
    REQUIRE(Attach(&g, 1U, BTB_ADMIN_PASS, 0, 1));
    REQUIRE(BtbServiceGraphEvaluate(&g, &s) == BTB_SERVICE_OK);
    REQUIRE(s.blocked == 1U && s.items[0].staleChecks == 1U);
    return 0;
}
static int TestInheritedBlock(void)
{
    BtbServiceGraph g; BtbServiceSummary s;
    REQUIRE(BasicGraph(&g, 1));
    REQUIRE(Attach(&g, 1U, BTB_ADMIN_FAILURE, 0, 0));
    REQUIRE(Attach(&g, 2U, BTB_ADMIN_PASS, 0, 0));
    REQUIRE(BtbServiceGraphEvaluate(&g, &s) == BTB_SERVICE_OK);
    REQUIRE(s.blocked == 2U && s.items[1].blockedByDependency == 1);
    return 0;
}
static int TestInheritedReview(void)
{
    BtbServiceGraph g; BtbServiceSummary s;
    REQUIRE(BasicGraph(&g, 1));
    REQUIRE(Attach(&g, 1U, BTB_ADMIN_PASS, 1, 0));
    REQUIRE(Attach(&g, 2U, BTB_ADMIN_PASS, 0, 0));
    REQUIRE(BtbServiceGraphEvaluate(&g, &s) == BTB_SERVICE_OK);
    REQUIRE(s.review == 2U && s.items[1].degradedByDependency == 1);
    return 0;
}
static int TestMissingDependency(void)
{
    BtbServiceGraph g; BtbServiceSummary s;
    BtbServiceSpec node = Spec(2U, UINT32_C(1));
    REQUIRE(BtbServiceGraphInit(&g, 500U) == BTB_SERVICE_OK);
    REQUIRE(BtbServiceGraphRegister(&g, &node) == BTB_SERVICE_OK);
    REQUIRE(BtbServiceGraphEvaluate(&g, &s) == BTB_SERVICE_DEPENDENCY_ERROR);
    return 0;
}
static int TestCycle(void)
{
    BtbServiceGraph g; BtbServiceSummary s;
    BtbServiceSpec one = Spec(1U, UINT32_C(2));
    BtbServiceSpec two = Spec(2U, UINT32_C(1));
    REQUIRE(BtbServiceGraphInit(&g, 500U) == BTB_SERVICE_OK);
    REQUIRE(BtbServiceGraphRegister(&g, &one) == BTB_SERVICE_OK);
    REQUIRE(BtbServiceGraphRegister(&g, &two) == BTB_SERVICE_OK);
    REQUIRE(BtbServiceGraphEvaluate(&g, &s) == BTB_SERVICE_CYCLE);
    return 0;
}
static int TestDuplicate(void)
{
    BtbServiceGraph g, saved;
    BtbServiceSpec node = Spec(1U, 0U);
    REQUIRE(BasicGraph(&g, 0));
    saved = g;
    REQUIRE(BtbServiceGraphRegister(&g, &node) == BTB_SERVICE_DUPLICATE);
    REQUIRE(memcmp(&saved, &g, sizeof(g)) == 0);
    return 0;
}
static int TestCapacity(void)
{
    BtbServiceGraph g; BtbServiceSpec node;
    REQUIRE(BtbServiceGraphInit(&g, 500U) == BTB_SERVICE_OK);
    for (uint32_t id = 1U; id <= BTB_SERVICE_MAX; ++id) {
        node = Spec(id, 0U);
        REQUIRE(BtbServiceGraphRegister(&g, &node) == BTB_SERVICE_OK);
    }
    node = Spec(9U, 0U);
    REQUIRE(BtbServiceGraphRegister(&g, &node) == BTB_SERVICE_FULL);
    REQUIRE(g.count == BTB_SERVICE_MAX);
    return 0;
}
static int TestInvalid(void)
{
    BtbServiceGraph g;
    BtbServiceSpec bad = Spec(1U, 1U);
    REQUIRE(BtbServiceGraphInit(&g, 500U) == BTB_SERVICE_OK);
    REQUIRE(BtbServiceGraphRegister(&g, &bad) == BTB_SERVICE_INVALID);
    bad = Spec(1U, 0U); bad.name[0] = '\0';
    REQUIRE(BtbServiceGraphRegister(&g, &bad) == BTB_SERVICE_INVALID);
    bad = Spec(33U, 0U);
    REQUIRE(BtbServiceGraphRegister(&g, &bad) == BTB_SERVICE_INVALID);
    REQUIRE(BtbServiceGraphInit(&g, 0U) == BTB_SERVICE_INVALID);
    REQUIRE(g.captureId == 500U);
    return 0;
}
static int TestPreserve(void)
{
    BtbServiceGraph g; BtbServiceSummary summary, saved;
    BtbAdminReview badReview = {0};
    BtbServiceSpec node = Spec(2U, UINT32_C(1));
    REQUIRE(BtbServiceGraphInit(&g, 500U) == BTB_SERVICE_OK);
    REQUIRE(BtbServiceGraphRegister(&g, &node) == BTB_SERVICE_OK);
    (void)memset(&summary, 0xA6, sizeof(summary)); saved = summary;
    REQUIRE(BtbServiceGraphEvaluate(&g, &summary) == BTB_SERVICE_DEPENDENCY_ERROR);
    REQUIRE(memcmp(&summary, &saved, sizeof(summary)) == 0);
    REQUIRE(BtbServiceGraphAttach(&g, 2U, &badReview) == BTB_SERVICE_INVALID);
    REQUIRE(g.nodes[0].hasEvidence == 0);
    return 0;
}
static int TestMutation(void)
{
    BtbServiceGraph g; BtbServiceSummary s;
    REQUIRE(BasicGraph(&g, 1));
    for (uint32_t iteration = 0U; iteration < 50000U; ++iteration) {
        const BtbAdminState state = (iteration % 4U == 0U) ? BTB_ADMIN_PASS :
             (iteration % 4U == 1U) ? BTB_ADMIN_WARNING :
             (iteration % 4U == 2U) ? BTB_ADMIN_FAILURE : BTB_ADMIN_NOT_RUN;
        const int stale = iteration % 11U == 0U;
        REQUIRE(Attach(&g, 1U, state, 0, stale));
        REQUIRE(Attach(&g, 2U, BTB_ADMIN_PASS, 0, 0));
        REQUIRE(BtbServiceGraphEvaluate(&g, &s) == BTB_SERVICE_OK);
        REQUIRE(s.count == 2U);
        REQUIRE(s.ready + s.review + s.blocked == 2U);
        if (state == BTB_ADMIN_PASS && !stale) {
            REQUIRE(s.ready == 2U);
        } else {
            REQUIRE(s.blocked == 2U);
        }
    }
    return 0;
}

typedef int (*CaseFunction)(void);
typedef struct CaseRow { const char *name; CaseFunction run; } CaseRow;
int main(int argc, char **argv)
{
    const CaseRow cases[] = {
        {"ready", TestReady}, {"missing", TestMissing},
        {"optional-warning", TestOptionalWarning},
        {"required-failure", TestRequiredFailure},
        {"required-notrun", TestRequiredNotRun}, {"stale", TestStale},
        {"inherited-block", TestInheritedBlock},
        {"inherited-review", TestInheritedReview},
        {"missing-dependency", TestMissingDependency}, {"cycle", TestCycle},
        {"duplicate", TestDuplicate}, {"capacity", TestCapacity},
        {"invalid", TestInvalid}, {"preserve", TestPreserve},
        {"mutation", TestMutation}
    };
    if (argc != 2) { (void)fprintf(stderr, "Usage: btb-service-readiness-test CASE\n"); return 2; }
    for (size_t i = 0U; i < sizeof(cases) / sizeof(cases[0]); ++i) {
        if (strcmp(cases[i].name, argv[1]) == 0) return cases[i].run();
    }
    (void)fprintf(stderr, "Unknown case: %s\n", argv[1]);
    return 2;
}
