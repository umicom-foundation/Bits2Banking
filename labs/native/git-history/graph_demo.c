/*-----------------------------------------------------------------------------
 * Bits2Banking | Umicom Foundation | Sammy Hegab | MIT
 * File: labs/native/git-history/graph_demo.c
 * PURPOSE: Explain a detached HEAD and stale local main without calling Git.
 *---------------------------------------------------------------------------*/
#include "graph.h"
#include <stdio.h>

int main(void)
{
    BtbGitGraph graph;
    if (BtbGitGraphInit(&graph) != BTB_GIT_OK) return 1;
    if (BtbGitGraphAdd(&graph, (BtbGitCommit){1U, 0U, 0U}) != BTB_GIT_OK ||
        BtbGitGraphAdd(&graph, (BtbGitCommit){2U, 1U, 0U}) != BTB_GIT_OK ||
        BtbGitGraphAdd(&graph, (BtbGitCommit){3U, 2U, 0U}) != BTB_GIT_OK ||
        BtbGitGraphAdd(&graph, (BtbGitCommit){4U, 3U, 0U}) != BTB_GIT_OK)
        return 2;

    /* Child framework HEAD is at commit 4, but local main still names 2.
     * git push origin main therefore pushes 2, NOT detached HEAD 4. */
    const BtbGitSnapshot snapshot = {
        .checkedOut = 4U,
        .localMain = 2U,
        .remoteMain = 4U,
        .detachedHead = 1,
        .modifiedTracked = 0,
        .untracked = 0
    };
    BtbGitAssessment assessment = {0};
    if (BtbGitGraphAssess(&graph, &snapshot, &assessment) != BTB_GIT_OK)
        return 3;
    if (assessment.mainRelation != BTB_GIT_LOCAL_BEHIND ||
        assessment.localMainPushIsFastForwardCandidate != 0 ||
        assessment.localMainCanAdvanceByFastForward != 1)
        return 4;
    puts("Umicom OS / Framework educational graph");
    puts("checked-out HEAD: 4 (detached); local main: 2; origin/main: 4");
    puts("The local main is BEHIND; 'git push origin main' does not push HEAD 4.");
    puts("Inspect real state with Git before synchronising. No Git command executed.");
    return 0;
}
