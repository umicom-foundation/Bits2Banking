/*-----------------------------------------------------------------------------
 * Bits2Banking | Umicom Foundation
 * File: labs/native/git-history/graph.h
 * PURPOSE: Bounded, immutable-parent teaching model for Git ancestry.
 * AUTHOR: Sammy Hegab | LICENCE: MIT
 *
 * This is an educational graph, NOT a Git repository implementation, command
 * wrapper, authentication mechanism or replacement for Umicom Framework VCS.
 * The IDs below are classroom labels, not Git object IDs or verified hashes.
 *---------------------------------------------------------------------------*/
#ifndef BTB_GIT_GRAPH_H
#define BTB_GIT_GRAPH_H

#include <stddef.h>
#include <stdint.h>

#define BTB_GIT_GRAPH_CAPACITY 64U

typedef enum BtbGitResult {
    BTB_GIT_OK = 0,
    BTB_GIT_INVALID,
    BTB_GIT_FULL,
    BTB_GIT_DUPLICATE,
    BTB_GIT_UNKNOWN_COMMIT,
    BTB_GIT_INTEGRITY
} BtbGitResult;

typedef struct BtbGitCommit {
    uint32_t id;
    uint32_t firstParent;
    uint32_t secondParent;
} BtbGitCommit;

typedef struct BtbGitGraph {
    BtbGitCommit commits[BTB_GIT_GRAPH_CAPACITY];
    size_t count;
} BtbGitGraph;

typedef enum BtbGitRelation {
    BTB_GIT_EQUAL = 0,
    BTB_GIT_LOCAL_BEHIND,
    BTB_GIT_LOCAL_AHEAD,
    BTB_GIT_DIVERGED
} BtbGitRelation;

/* Snapshot observations are supplied by a human or a controlled test fixture.
 * They are NOT read from .git, nor inferred from a submodule's gitlink. */
typedef struct BtbGitSnapshot {
    uint32_t checkedOut;
    uint32_t localMain;
    uint32_t remoteMain;
    int detachedHead;
    int modifiedTracked;
    int untracked;
} BtbGitSnapshot;

typedef struct BtbGitAssessment {
    BtbGitRelation mainRelation;
    int localMainCanAdvanceByFastForward; /* ancestry-only candidate */
    int localMainPushIsFastForwardCandidate; /* not permissions/auth/checks */
    int needsWorkingTreeReview;           /* conservative; may not collide */
    int detachedCommitNotOnEitherMain;
    int requiresHumanReview;
} BtbGitAssessment;

/* Caller owns all storage. Root commits use firstParent=secondParent=0.
 * Additional commits must refer only to parents already in the graph.
 * A second parent requires a distinct, non-zero first parent.
 * Failed Add never changes graph. No API mutates an existing commit. */
BtbGitResult BtbGitGraphInit(BtbGitGraph *graph);
BtbGitResult BtbGitGraphAdd(BtbGitGraph *graph, BtbGitCommit commit);
int BtbGitGraphInvariants(const BtbGitGraph *graph);

/* Missing IDs or corrupt graph leave *outRelation unchanged. */
BtbGitResult BtbGitGraphClassify(const BtbGitGraph *graph,
                                  uint32_t localMain, uint32_t remoteMain,
                                  BtbGitRelation *outRelation);

/* A read-only advisory. No Git action is ever executed. No decision proves
 * that Git checkout, pull, or push will succeed on a real filesystem. */
BtbGitResult BtbGitGraphAssess(const BtbGitGraph *graph,
                                const BtbGitSnapshot *snapshot,
                                BtbGitAssessment *outAssessment);

#endif
