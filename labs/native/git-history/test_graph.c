/*-----------------------------------------------------------------------------
 * Bits2Banking | Umicom Foundation | Sammy Hegab | MIT
 * File: labs/native/git-history/test_graph.c
 * PURPOSE: Deterministic acceptance tests for safe commit-graph reasoning.
 *---------------------------------------------------------------------------*/
#include "graph.h"
#include <stdio.h>
#include <string.h>

#define CHECK(condition) do { \
    if (!(condition)) { \
        fprintf(stderr, "check failed (%s:%d): %s\n", \
                __FILE__, __LINE__, #condition); \
        return 1; \
    } \
} while (0)

static int Add(BtbGitGraph *graph, uint32_t id, uint32_t p1, uint32_t p2)
{
    return BtbGitGraphAdd(graph, (BtbGitCommit){id, p1, p2}) == BTB_GIT_OK;
}

static int Fixture(BtbGitGraph *graph)
{
    if (BtbGitGraphInit(graph) != BTB_GIT_OK) return 0;
    /* 1--2--4, 1--3--5, 6 merges 4 and 5. */
    return Add(graph, 1U, 0U, 0U) &&
           Add(graph, 2U, 1U, 0U) &&
           Add(graph, 3U, 1U, 0U) &&
           Add(graph, 4U, 2U, 0U) &&
           Add(graph, 5U, 3U, 0U) &&
           Add(graph, 6U, 4U, 5U);
}

static int ExpectRelation(const BtbGitGraph *graph, uint32_t local,
                          uint32_t remote, BtbGitRelation expected)
{
    BtbGitRelation observed = BTB_GIT_DIVERGED;
    return BtbGitGraphClassify(graph, local, remote, &observed) == BTB_GIT_OK &&
           observed == expected;
}

static int TestEqual(void)
{
    BtbGitGraph graph;
    CHECK(Fixture(&graph));
    CHECK(ExpectRelation(&graph, 4U, 4U, BTB_GIT_EQUAL));
    CHECK(ExpectRelation(&graph, 6U, 6U, BTB_GIT_EQUAL));
    return 0;
}

static int TestBehind(void)
{
    BtbGitGraph graph;
    CHECK(Fixture(&graph));
    CHECK(ExpectRelation(&graph, 2U, 4U, BTB_GIT_LOCAL_BEHIND));
    CHECK(ExpectRelation(&graph, 1U, 6U, BTB_GIT_LOCAL_BEHIND));
    return 0;
}

static int TestAhead(void)
{
    BtbGitGraph graph;
    CHECK(Fixture(&graph));
    CHECK(ExpectRelation(&graph, 4U, 2U, BTB_GIT_LOCAL_AHEAD));
    CHECK(ExpectRelation(&graph, 6U, 1U, BTB_GIT_LOCAL_AHEAD));
    return 0;
}

static int TestDiverged(void)
{
    BtbGitGraph graph;
    CHECK(Fixture(&graph));
    CHECK(ExpectRelation(&graph, 4U, 5U, BTB_GIT_DIVERGED));
    CHECK(ExpectRelation(&graph, 2U, 3U, BTB_GIT_DIVERGED));
    return 0;
}

static int TestMerge(void)
{
    BtbGitGraph graph;
    CHECK(Fixture(&graph));
    CHECK(ExpectRelation(&graph, 4U, 6U, BTB_GIT_LOCAL_BEHIND));
    CHECK(ExpectRelation(&graph, 5U, 6U, BTB_GIT_LOCAL_BEHIND));
    CHECK(ExpectRelation(&graph, 6U, 5U, BTB_GIT_LOCAL_AHEAD));
    CHECK(Add(&graph, 7U, 6U, 0U));
    CHECK(ExpectRelation(&graph, 2U, 7U, BTB_GIT_LOCAL_BEHIND));
    return 0;
}

static int TestDirty(void)
{
    BtbGitGraph graph;
    CHECK(Fixture(&graph));
    BtbGitSnapshot snapshot = {
        .checkedOut = 4U, .localMain = 4U, .remoteMain = 6U,
        .detachedHead = 0, .modifiedTracked = 1, .untracked = 1
    };
    BtbGitAssessment result = {0};
    CHECK(BtbGitGraphAssess(&graph, &snapshot, &result) == BTB_GIT_OK);
    CHECK(result.mainRelation == BTB_GIT_LOCAL_BEHIND);
    CHECK(result.localMainCanAdvanceByFastForward == 1);
    CHECK(result.needsWorkingTreeReview == 1);
    CHECK(result.requiresHumanReview == 1);
    /* The advisory does not create a stash or alter the graph. */
    CHECK(graph.count == 6U);
    CHECK(BtbGitGraphInvariants(&graph));
    return 0;
}

static int TestDetached(void)
{
    BtbGitGraph graph;
    CHECK(Fixture(&graph));
    BtbGitSnapshot snapshot = {
        .checkedOut = 6U, .localMain = 4U, .remoteMain = 6U,
        .detachedHead = 1, .modifiedTracked = 0, .untracked = 0
    };
    BtbGitAssessment result = {0};
    CHECK(BtbGitGraphAssess(&graph, &snapshot, &result) == BTB_GIT_OK);
    CHECK(result.mainRelation == BTB_GIT_LOCAL_BEHIND);
    CHECK(result.localMainPushIsFastForwardCandidate == 0);
    CHECK(result.localMainCanAdvanceByFastForward == 1);
    CHECK(result.detachedCommitNotOnEitherMain == 0);

    /* A commit reachable from neither main may be unpublished. Review first. */
    CHECK(Add(&graph, 7U, 5U, 0U));
    snapshot.checkedOut = 7U;
    CHECK(BtbGitGraphAssess(&graph, &snapshot, &result) == BTB_GIT_OK);
    CHECK(result.detachedCommitNotOnEitherMain == 1);
    CHECK(result.requiresHumanReview == 1);
    return 0;
}

static int TestInvalid(void)
{
    BtbGitGraph graph;
    CHECK(BtbGitGraphInit(&graph) == BTB_GIT_OK);
    CHECK(Add(&graph, 1U, 0U, 0U));
    const size_t originalCount = graph.count;
    CHECK(BtbGitGraphAdd(&graph, (BtbGitCommit){1U, 0U, 0U}) == BTB_GIT_DUPLICATE);
    CHECK(BtbGitGraphAdd(&graph, (BtbGitCommit){2U, 99U, 0U}) == BTB_GIT_UNKNOWN_COMMIT);
    CHECK(BtbGitGraphAdd(&graph, (BtbGitCommit){2U, 0U, 1U}) == BTB_GIT_INVALID);
    CHECK(BtbGitGraphAdd(&graph, (BtbGitCommit){2U, 1U, 1U}) == BTB_GIT_INVALID);
    CHECK(graph.count == originalCount);
    CHECK(BtbGitGraphInvariants(&graph));

    BtbGitRelation unchanged = BTB_GIT_LOCAL_AHEAD;
    CHECK(BtbGitGraphClassify(&graph, 1U, 99U, &unchanged) == BTB_GIT_UNKNOWN_COMMIT);
    CHECK(unchanged == BTB_GIT_LOCAL_AHEAD);
    CHECK(BtbGitGraphClassify(&graph, 1U, 1U, NULL) == BTB_GIT_INVALID);
    BtbGitAssessment untouched = {.needsWorkingTreeReview = 7};
    BtbGitSnapshot bad = {
        .checkedOut = 1U, .localMain = 1U, .remoteMain = 1U,
        .detachedHead = 2
    };
    CHECK(BtbGitGraphAssess(&graph, &bad, &untouched) == BTB_GIT_INVALID);
    CHECK(untouched.needsWorkingTreeReview == 7);
    bad.detachedHead = 0;
    bad.checkedOut = 99U;
    CHECK(BtbGitGraphAssess(&graph, &bad, &untouched) == BTB_GIT_UNKNOWN_COMMIT);
    CHECK(untouched.needsWorkingTreeReview == 7);

    /* Corrupt a parent directly to simulate a damaged graph; no repair. */
    graph.commits[0].firstParent = 1U;
    CHECK(!BtbGitGraphInvariants(&graph));
    CHECK(BtbGitGraphClassify(&graph, 1U, 1U, &unchanged) == BTB_GIT_INTEGRITY);
    CHECK(unchanged == BTB_GIT_LOCAL_AHEAD);
    return 0;
}

static int TestCapacity(void)
{
    BtbGitGraph graph;
    CHECK(BtbGitGraphInit(&graph) == BTB_GIT_OK);
    for (uint32_t id = 1U; id <= BTB_GIT_GRAPH_CAPACITY; ++id)
        CHECK(Add(&graph, id, id == 1U ? 0U : id - 1U, 0U));
    CHECK(graph.count == BTB_GIT_GRAPH_CAPACITY);
    CHECK(BtbGitGraphAdd(&graph, (BtbGitCommit){65U, 64U, 0U}) == BTB_GIT_FULL);
    CHECK(graph.count == BTB_GIT_GRAPH_CAPACITY);
    CHECK(BtbGitGraphInvariants(&graph));
    CHECK(ExpectRelation(&graph, 1U, 64U, BTB_GIT_LOCAL_BEHIND));
    return 0;
}

static int TestStress(void)
{
    BtbGitGraph graph;
    CHECK(BtbGitGraphInit(&graph) == BTB_GIT_OK);
    for (uint32_t id = 1U; id <= BTB_GIT_GRAPH_CAPACITY; ++id)
        CHECK(Add(&graph, id, id == 1U ? 0U : id - 1U, 0U));
    uint32_t seed = UINT32_C(0x23A52026);
    for (uint32_t i = 0U; i < 20000U; ++i) {
        seed = seed * UINT32_C(1664525) + UINT32_C(1013904223);
        const uint32_t local = 1U + (seed % BTB_GIT_GRAPH_CAPACITY);
        seed = seed * UINT32_C(1664525) + UINT32_C(1013904223);
        const uint32_t remote = 1U + (seed % BTB_GIT_GRAPH_CAPACITY);
        const BtbGitRelation expected = local == remote ? BTB_GIT_EQUAL :
            (local < remote ? BTB_GIT_LOCAL_BEHIND : BTB_GIT_LOCAL_AHEAD);
        CHECK(ExpectRelation(&graph, local, remote, expected));
    }
    CHECK(BtbGitGraphInvariants(&graph));
    return 0;
}

typedef struct NamedTest {
    const char *name;
    int (*run)(void);
} NamedTest;

int main(int argc, char **argv)
{
    const NamedTest tests[] = {
        {"equal", TestEqual}, {"behind", TestBehind},
        {"ahead", TestAhead}, {"diverged", TestDiverged},
        {"merge", TestMerge}, {"dirty", TestDirty},
        {"detached", TestDetached}, {"invalid", TestInvalid},
        {"capacity", TestCapacity}, {"stress", TestStress}
    };
    if (argc != 2 || argv == NULL || argv[1] == NULL) {
        fputs("usage: btb-git-history-test TEST-NAME\n", stderr);
        return 2;
    }
    for (size_t i = 0U; i < sizeof(tests) / sizeof(tests[0]); ++i) {
        if (strcmp(argv[1], tests[i].name) != 0) continue;
        const int result = tests[i].run();
        if (result == 0) printf("PASS %s\n", tests[i].name);
        return result;
    }
    fprintf(stderr, "unknown case: %s\n", argv[1]);
    return 2;
}
