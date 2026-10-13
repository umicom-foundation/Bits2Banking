/*-----------------------------------------------------------------------------
 * Bits2Banking | Umicom Foundation | Sammy Hegab | MIT
 * File: labs/native/git-three-way/merge.h
 * PURPOSE: Bounded, read-only three-way reconciliation of named C23 records.
 *
 * This is an EDUCATIONAL MODEL, not Git's text or tree merge algorithm.
 * Real repository operations belong to the Umicom Framework VCS subsystem.
 * No filesystem, Git process, network or repository mutation occurs here.
 *---------------------------------------------------------------------------*/
#ifndef BTB_GIT_THREE_WAY_MERGE_H
#define BTB_GIT_THREE_WAY_MERGE_H

#include <stddef.h>

#define BTB_MERGE_MAX_RECORDS 16U
#define BTB_MERGE_KEY_CAPACITY 48U
#define BTB_MERGE_VALUE_CAPACITY 128U

typedef enum BtbMergeStatus {
    BTB_MERGE_OK = 0,
    BTB_MERGE_INVALID,
    BTB_MERGE_DUPLICATE,
    BTB_MERGE_FULL,
    BTB_MERGE_CONFLICT_PENDING,
    BTB_MERGE_NOT_CONFLICT,
    BTB_MERGE_ALREADY_RESOLVED,
    BTB_MERGE_NOT_FOUND
} BtbMergeStatus;

typedef struct BtbMergeRecord {
    char key[BTB_MERGE_KEY_CAPACITY];
    char value[BTB_MERGE_VALUE_CAPACITY];
} BtbMergeRecord;

typedef struct BtbMergeSnapshot {
    BtbMergeRecord records[BTB_MERGE_MAX_RECORDS];
    size_t count;
} BtbMergeSnapshot;

typedef enum BtbMergeKind {
    BTB_MERGE_UNCHANGED = 0,
    BTB_MERGE_IDENTICAL_CHANGE,
    BTB_MERGE_OURS_ONLY,
    BTB_MERGE_THEIRS_ONLY,
    BTB_MERGE_NEEDS_REVIEW
} BtbMergeKind;

typedef enum BtbMergeChoice {
    BTB_CHOOSE_NONE = 0,
    BTB_CHOOSE_BASE,
    BTB_CHOOSE_OURS,
    BTB_CHOOSE_THEIRS,
    BTB_CHOOSE_DELETE
} BtbMergeChoice;

typedef struct BtbMergeDecision {
    char key[BTB_MERGE_KEY_CAPACITY];
    char base[BTB_MERGE_VALUE_CAPACITY];
    char ours[BTB_MERGE_VALUE_CAPACITY];
    char theirs[BTB_MERGE_VALUE_CAPACITY];
    int basePresent;
    int oursPresent;
    int theirsPresent;
    BtbMergeKind kind;
    BtbMergeChoice choice;
    int resolved;
} BtbMergeDecision;

typedef struct BtbMergePlan {
    BtbMergeDecision decisions[BTB_MERGE_MAX_RECORDS];
    size_t count;
    size_t conflictCount;
    size_t unresolvedCount;
} BtbMergePlan;

/* Caller-owned zero-initialised storage. All outputs are replaced on success. */
BtbMergeStatus BtbMergeSnapshotInit(BtbMergeSnapshot *snapshot);

/* Strings MUST be NUL-terminated within capacity. Invalid input, duplicate
 * names and overflow leave the existing snapshot completely unchanged.
 * Record keys are symbolic identifiers, not trusted filesystem paths. */
BtbMergeStatus BtbMergeSnapshotAdd(BtbMergeSnapshot *snapshot,
                                   const char *key, const char *value);

/* Validates unique, bounded records, including snapshots made by callers. */
int BtbMergeSnapshotValid(const BtbMergeSnapshot *snapshot);

/* BASE is the common ancestor; OURS and THEIRS are independent snapshots.
 * Input snapshot arrays remain caller-owned and are NEVER modified.
 * Decisions store complete copies and are ordered by BASE, then new OURS,
 * then new THEIRS identifiers. Invalid input leaves outPlan unchanged. */
BtbMergeStatus BtbMergePlanBuild(const BtbMergeSnapshot *base,
                                 const BtbMergeSnapshot *ours,
                                 const BtbMergeSnapshot *theirs,
                                 BtbMergePlan *outPlan);

/* Borrowed until the plan changes or goes out of scope; never free. */
const BtbMergeDecision *BtbMergeDecisionAt(const BtbMergePlan *plan,
                                            size_t index);

/* Resolve ONLY a genuine conflict, exactly once. No silent 'ours wins' rule.
 * DELETE is an explicit human decision; BASE/OURS/THEIRS retain the chosen
 * presence/absence and value from that snapshot. Failure is non-mutating. */
BtbMergeStatus BtbMergeResolve(BtbMergePlan *plan, const char *key,
                               BtbMergeChoice choice);

/* Produces an owned, fully materialised snapshot only when every conflict
 * is resolved. BLOCKED/invalid inputs preserve the caller's output. */
BtbMergeStatus BtbMergeMaterialise(const BtbMergePlan *plan,
                                   BtbMergeSnapshot *outSnapshot);

/* Internal-consistency checks for teaching and tests; this does NOT verify
 * the authenticity of Git data or provenance. */
int BtbMergePlanValid(const BtbMergePlan *plan);

#endif
