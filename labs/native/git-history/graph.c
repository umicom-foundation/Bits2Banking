/*-----------------------------------------------------------------------------
 * Bits2Banking | Umicom Foundation
 * File: labs/native/git-history/graph.c
 * PURPOSE: Failure-atomic graph construction and bounded ancestry checks.
 * AUTHOR: Sammy Hegab | LICENCE: MIT
 *
 * A directed edge goes from a commit to its parent(s), as in a real Git DAG.
 * All nodes are in caller-owned fixed storage and allocate no heap memory.
 *---------------------------------------------------------------------------*/
#include "graph.h"
#include <string.h>

static size_t FindIndex(const BtbGitGraph *graph, uint32_t commitId)
{
    for (size_t i = 0U; i < graph->count; ++i) {
        if (graph->commits[i].id == commitId) return i;
    }
    return graph->count;
}

int BtbGitGraphInvariants(const BtbGitGraph *graph)
{
    if (graph == NULL || graph->count > BTB_GIT_GRAPH_CAPACITY) return 0;
    for (size_t i = 0U; i < graph->count; ++i) {
        const BtbGitCommit node = graph->commits[i];
        if (node.id == 0U ||
            (node.secondParent != 0U &&
             (node.firstParent == 0U || node.firstParent == node.secondParent)))
            return 0;
        for (size_t j = 0U; j < i; ++j) {
            if (graph->commits[j].id == node.id) return 0;
        }
        if (node.firstParent != 0U) {
            size_t parentIndex = i;
            for (size_t j = 0U; j < i; ++j) {
                if (graph->commits[j].id == node.firstParent) parentIndex = j;
            }
            if (parentIndex == i) return 0;
        }
        if (node.secondParent != 0U) {
            size_t parentIndex = i;
            for (size_t j = 0U; j < i; ++j) {
                if (graph->commits[j].id == node.secondParent) parentIndex = j;
            }
            if (parentIndex == i) return 0;
        }
    }
    return 1;
}

BtbGitResult BtbGitGraphInit(BtbGitGraph *graph)
{
    if (graph == NULL) return BTB_GIT_INVALID;
    *graph = (BtbGitGraph){0};
    return BTB_GIT_OK;
}

BtbGitResult BtbGitGraphAdd(BtbGitGraph *graph, BtbGitCommit commit)
{
    if (graph == NULL || commit.id == 0U ||
        (commit.secondParent != 0U &&
         (commit.firstParent == 0U || commit.firstParent == commit.secondParent)))
        return BTB_GIT_INVALID;
    if (!BtbGitGraphInvariants(graph)) return BTB_GIT_INTEGRITY;
    if (FindIndex(graph, commit.id) != graph->count) return BTB_GIT_DUPLICATE;
    if (commit.firstParent != 0U &&
        FindIndex(graph, commit.firstParent) == graph->count)
        return BTB_GIT_UNKNOWN_COMMIT;
    if (commit.secondParent != 0U &&
        FindIndex(graph, commit.secondParent) == graph->count)
        return BTB_GIT_UNKNOWN_COMMIT;
    if (graph->count == BTB_GIT_GRAPH_CAPACITY) return BTB_GIT_FULL;
    graph->commits[graph->count] = commit;
    ++graph->count;
    return BTB_GIT_OK;
}

/* Every path points to older nodes. This bounded walk cannot loop and does
 * not recurse on the C stack. Seen flags avoid repeated traversal at merges. */
static int IsAncestor(const BtbGitGraph *graph, uint32_t ancestor,
                      uint32_t descendant)
{
    const size_t start = FindIndex(graph, descendant);
    if (start == graph->count) return 0;
    size_t todo[BTB_GIT_GRAPH_CAPACITY];
    int seen[BTB_GIT_GRAPH_CAPACITY] = {0};
    size_t pending = 0U;
    todo[pending++] = start;
    seen[start] = 1;
    while (pending > 0U) {
        const size_t current = todo[--pending];
        const BtbGitCommit node = graph->commits[current];
        if (node.id == ancestor) return 1;
        const uint32_t parents[2] = {node.firstParent, node.secondParent};
        for (size_t i = 0U; i < 2U; ++i) {
            if (parents[i] == 0U) continue;
            const size_t parentIndex = FindIndex(graph, parents[i]);
            /* Invariants checked by the public caller, so parent exists. */
            if (parentIndex < graph->count && !seen[parentIndex]) {
                seen[parentIndex] = 1;
                todo[pending++] = parentIndex;
            }
        }
    }
    return 0;
}

BtbGitResult BtbGitGraphClassify(const BtbGitGraph *graph,
                                  uint32_t localMain, uint32_t remoteMain,
                                  BtbGitRelation *outRelation)
{
    if (graph == NULL || outRelation == NULL ||
        localMain == 0U || remoteMain == 0U)
        return BTB_GIT_INVALID;
    if (!BtbGitGraphInvariants(graph)) return BTB_GIT_INTEGRITY;
    if (FindIndex(graph, localMain) == graph->count ||
        FindIndex(graph, remoteMain) == graph->count)
        return BTB_GIT_UNKNOWN_COMMIT;
    BtbGitRelation relation = BTB_GIT_DIVERGED;
    if (localMain == remoteMain) relation = BTB_GIT_EQUAL;
    else if (IsAncestor(graph, localMain, remoteMain))
        relation = BTB_GIT_LOCAL_BEHIND;
    else if (IsAncestor(graph, remoteMain, localMain))
        relation = BTB_GIT_LOCAL_AHEAD;
    *outRelation = relation;
    return BTB_GIT_OK;
}

BtbGitResult BtbGitGraphAssess(const BtbGitGraph *graph,
                                const BtbGitSnapshot *snapshot,
                                BtbGitAssessment *outAssessment)
{
    if (graph == NULL || snapshot == NULL || outAssessment == NULL ||
        snapshot->checkedOut == 0U ||
        (snapshot->detachedHead != 0 && snapshot->detachedHead != 1) ||
        (snapshot->modifiedTracked != 0 && snapshot->modifiedTracked != 1) ||
        (snapshot->untracked != 0 && snapshot->untracked != 1))
        return BTB_GIT_INVALID;
    BtbGitRelation relation = BTB_GIT_DIVERGED;
    const BtbGitResult result = BtbGitGraphClassify(graph, snapshot->localMain,
                                                    snapshot->remoteMain, &relation);
    if (result != BTB_GIT_OK) return result;
    if (FindIndex(graph, snapshot->checkedOut) == graph->count)
        return BTB_GIT_UNKNOWN_COMMIT;
    if (!snapshot->detachedHead && snapshot->checkedOut != snapshot->localMain)
        return BTB_GIT_INVALID;

    BtbGitAssessment assessment = {0};
    assessment.mainRelation = relation;
    assessment.localMainCanAdvanceByFastForward =
        (relation == BTB_GIT_EQUAL || relation == BTB_GIT_LOCAL_BEHIND);
    assessment.localMainPushIsFastForwardCandidate =
        (relation == BTB_GIT_EQUAL || relation == BTB_GIT_LOCAL_AHEAD);
    assessment.needsWorkingTreeReview =
        snapshot->modifiedTracked || snapshot->untracked;
    assessment.detachedCommitNotOnEitherMain = snapshot->detachedHead &&
        !IsAncestor(graph, snapshot->checkedOut, snapshot->localMain) &&
        !IsAncestor(graph, snapshot->checkedOut, snapshot->remoteMain);
    assessment.requiresHumanReview = assessment.needsWorkingTreeReview ||
        assessment.detachedCommitNotOnEitherMain ||
        relation == BTB_GIT_DIVERGED;
    *outAssessment = assessment;
    return BTB_GIT_OK;
}
