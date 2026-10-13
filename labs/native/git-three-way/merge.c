/*-----------------------------------------------------------------------------
 * Bits2Banking | Umicom Foundation | Sammy Hegab | MIT
 * File: labs/native/git-three-way/merge.c
 * PURPOSE: Failure-atomic, bounded, three-way record reconciliation in C23.
 *
 * DESIGN: Keep the three independent versions. A conflict is evidence to
 * review, never permission to discard an implementation automatically.
 *---------------------------------------------------------------------------*/
#include "merge.h"
#include <string.h>

static int BoundedString(const char *text, size_t capacity, size_t *length)
{
    const char *ending;
    if (text == NULL) return 0;
    ending = memchr(text, '\0', capacity);
    if (ending == NULL) return 0;
    if (length != NULL) *length = (size_t)(ending - text);
    return 1;
}

static int ValidKey(const char *key)
{
    size_t length = 0U;
    if (!BoundedString(key, BTB_MERGE_KEY_CAPACITY, &length) || length == 0U)
        return 0;
    for (size_t i = 0U; i < length; ++i) {
        const unsigned char ch = (unsigned char)key[i];
        const int letter = (ch >= (unsigned char)'a' && ch <= (unsigned char)'z') ||
                           (ch >= (unsigned char)'A' && ch <= (unsigned char)'Z');
        const int digit = ch >= (unsigned char)'0' && ch <= (unsigned char)'9';
        if (!letter && !digit && ch != (unsigned char)'_' &&
            ch != (unsigned char)'.' && ch != (unsigned char)'/' &&
            ch != (unsigned char)'-') return 0;
    }
    return 1;
}

static int ValidValue(const char *value)
{
    return BoundedString(value, BTB_MERGE_VALUE_CAPACITY, NULL);
}

static size_t FindRecord(const BtbMergeSnapshot *snapshot, const char *key)
{
    for (size_t i = 0U; i < snapshot->count; ++i)
        if (strcmp(snapshot->records[i].key, key) == 0) return i;
    return snapshot->count;
}

int BtbMergeSnapshotValid(const BtbMergeSnapshot *snapshot)
{
    if (snapshot == NULL || snapshot->count > BTB_MERGE_MAX_RECORDS) return 0;
    for (size_t i = 0U; i < snapshot->count; ++i) {
        const BtbMergeRecord *record = &snapshot->records[i];
        if (!ValidKey(record->key) || !ValidValue(record->value)) return 0;
        for (size_t j = 0U; j < i; ++j)
            if (strcmp(record->key, snapshot->records[j].key) == 0) return 0;
    }
    return 1;
}

BtbMergeStatus BtbMergeSnapshotInit(BtbMergeSnapshot *snapshot)
{
    if (snapshot == NULL) return BTB_MERGE_INVALID;
    *snapshot = (BtbMergeSnapshot){0};
    return BTB_MERGE_OK;
}

BtbMergeStatus BtbMergeSnapshotAdd(BtbMergeSnapshot *snapshot,
                                   const char *key, const char *value)
{
    BtbMergeRecord next = {0};
    if (!BtbMergeSnapshotValid(snapshot) || !ValidKey(key) || !ValidValue(value))
        return BTB_MERGE_INVALID;
    if (FindRecord(snapshot, key) < snapshot->count) return BTB_MERGE_DUPLICATE;
    if (snapshot->count == BTB_MERGE_MAX_RECORDS) return BTB_MERGE_FULL;
    (void)strcpy(next.key, key);
    (void)strcpy(next.value, value);
    snapshot->records[snapshot->count] = next;
    ++snapshot->count;
    return BTB_MERGE_OK;
}

static int SameVersion(int leftPresent, const char *left,
                       int rightPresent, const char *right)
{
    return leftPresent == rightPresent &&
           (!leftPresent || strcmp(left, right) == 0);
}

/* Classify by comparing the complete record presence AND value. Deletion is
 * not an empty string; it is a separate, explicit absence state. */
static void Classify(BtbMergeDecision *decision)
{
    const int sameAsBaseOurs = SameVersion(decision->basePresent, decision->base,
                                           decision->oursPresent, decision->ours);
    const int sameAsBaseTheirs = SameVersion(decision->basePresent, decision->base,
                                             decision->theirsPresent, decision->theirs);
    const int sameBranches = SameVersion(decision->oursPresent, decision->ours,
                                         decision->theirsPresent, decision->theirs);
    decision->resolved = 1;
    if (sameAsBaseOurs && sameAsBaseTheirs) {
        decision->kind = BTB_MERGE_UNCHANGED;
        decision->choice = BTB_CHOOSE_BASE;
    } else if (sameBranches) {
        decision->kind = BTB_MERGE_IDENTICAL_CHANGE;
        decision->choice = BTB_CHOOSE_OURS;
    } else if (sameAsBaseOurs) {
        decision->kind = BTB_MERGE_THEIRS_ONLY;
        decision->choice = BTB_CHOOSE_THEIRS;
    } else if (sameAsBaseTheirs) {
        decision->kind = BTB_MERGE_OURS_ONLY;
        decision->choice = BTB_CHOOSE_OURS;
    } else {
        decision->kind = BTB_MERGE_NEEDS_REVIEW;
        decision->choice = BTB_CHOOSE_NONE;
        decision->resolved = 0;
    }
}

static size_t FindDecision(const BtbMergePlan *plan, const char *key)
{
    for (size_t i = 0U; i < plan->count; ++i)
        if (strcmp(plan->decisions[i].key, key) == 0) return i;
    return plan->count;
}

static BtbMergeStatus AppendNames(BtbMergePlan *plan,
                                  const BtbMergeSnapshot *snapshot)
{
    for (size_t i = 0U; i < snapshot->count; ++i) {
        const char *key = snapshot->records[i].key;
        if (FindDecision(plan, key) < plan->count) continue;
        if (plan->count == BTB_MERGE_MAX_RECORDS) return BTB_MERGE_FULL;
        (void)strcpy(plan->decisions[plan->count].key, key);
        ++plan->count;
    }
    return BTB_MERGE_OK;
}

static void CopyVersion(BtbMergeDecision *decision,
                        const BtbMergeSnapshot *snapshot,
                        int which)
{
    const size_t index = FindRecord(snapshot, decision->key);
    if (index == snapshot->count) return;
    if (which == 0) {
        decision->basePresent = 1;
        (void)strcpy(decision->base, snapshot->records[index].value);
    } else if (which == 1) {
        decision->oursPresent = 1;
        (void)strcpy(decision->ours, snapshot->records[index].value);
    } else {
        decision->theirsPresent = 1;
        (void)strcpy(decision->theirs, snapshot->records[index].value);
    }
}

BtbMergeStatus BtbMergePlanBuild(const BtbMergeSnapshot *base,
                                 const BtbMergeSnapshot *ours,
                                 const BtbMergeSnapshot *theirs,
                                 BtbMergePlan *outPlan)
{
    BtbMergePlan candidate = {0};
    BtbMergeStatus status;
    if (outPlan == NULL || !BtbMergeSnapshotValid(base) ||
        !BtbMergeSnapshotValid(ours) || !BtbMergeSnapshotValid(theirs))
        return BTB_MERGE_INVALID;
    status = AppendNames(&candidate, base);
    if (status != BTB_MERGE_OK) return status;
    status = AppendNames(&candidate, ours);
    if (status != BTB_MERGE_OK) return status;
    status = AppendNames(&candidate, theirs);
    if (status != BTB_MERGE_OK) return status;
    for (size_t i = 0U; i < candidate.count; ++i) {
        BtbMergeDecision *decision = &candidate.decisions[i];
        CopyVersion(decision, base, 0);
        CopyVersion(decision, ours, 1);
        CopyVersion(decision, theirs, 2);
        Classify(decision);
        if (decision->kind == BTB_MERGE_NEEDS_REVIEW) {
            ++candidate.conflictCount;
            ++candidate.unresolvedCount;
        }
    }
    *outPlan = candidate;
    return BTB_MERGE_OK;
}

const BtbMergeDecision *BtbMergeDecisionAt(const BtbMergePlan *plan,
                                            size_t index)
{
    return BtbMergePlanValid(plan) && index < plan->count ?
           &plan->decisions[index] : NULL;
}

int BtbMergePlanValid(const BtbMergePlan *plan)
{
    size_t conflicts = 0U, unresolved = 0U;
    if (plan == NULL || plan->count > BTB_MERGE_MAX_RECORDS ||
        plan->conflictCount > plan->count ||
        plan->unresolvedCount > plan->conflictCount) return 0;
    for (size_t i = 0U; i < plan->count; ++i) {
        const BtbMergeDecision *d = &plan->decisions[i];
        BtbMergeDecision expected = *d;
        if (!ValidKey(d->key) || !ValidValue(d->base) ||
            !ValidValue(d->ours) || !ValidValue(d->theirs) ||
            (d->basePresent != 0 && d->basePresent != 1) ||
            (d->oursPresent != 0 && d->oursPresent != 1) ||
            (d->theirsPresent != 0 && d->theirsPresent != 1) ||
            (!d->basePresent && !d->oursPresent && !d->theirsPresent)) return 0;
        for (size_t j = 0U; j < i; ++j)
            if (strcmp(d->key, plan->decisions[j].key) == 0) return 0;
        Classify(&expected);
        if (expected.kind != d->kind) return 0;
        if (d->kind == BTB_MERGE_NEEDS_REVIEW) {
            ++conflicts;
            if (!d->resolved) {
                ++unresolved;
                if (d->choice != BTB_CHOOSE_NONE) return 0;
            } else if (d->choice < BTB_CHOOSE_BASE ||
                       d->choice > BTB_CHOOSE_DELETE) return 0;
        } else if (!d->resolved || d->choice != expected.choice) return 0;
    }
    return conflicts == plan->conflictCount && unresolved == plan->unresolvedCount;
}

BtbMergeStatus BtbMergeResolve(BtbMergePlan *plan, const char *key,
                               BtbMergeChoice choice)
{
    size_t index;
    if (!BtbMergePlanValid(plan) || !ValidKey(key) ||
        choice < BTB_CHOOSE_BASE || choice > BTB_CHOOSE_DELETE)
        return BTB_MERGE_INVALID;
    index = FindDecision(plan, key);
    if (index == plan->count) return BTB_MERGE_NOT_FOUND;
    BtbMergeDecision *decision = &plan->decisions[index];
    if (decision->kind != BTB_MERGE_NEEDS_REVIEW) return BTB_MERGE_NOT_CONFLICT;
    if (decision->resolved) return BTB_MERGE_ALREADY_RESOLVED;
    decision->choice = choice;
    decision->resolved = 1;
    --plan->unresolvedCount;
    return BTB_MERGE_OK;
}

BtbMergeStatus BtbMergeMaterialise(const BtbMergePlan *plan,
                                   BtbMergeSnapshot *outSnapshot)
{
    BtbMergeSnapshot result = {0};
    if (outSnapshot == NULL || !BtbMergePlanValid(plan)) return BTB_MERGE_INVALID;
    if (plan->unresolvedCount != 0U) return BTB_MERGE_CONFLICT_PENDING;
    for (size_t i = 0U; i < plan->count; ++i) {
        const BtbMergeDecision *d = &plan->decisions[i];
        const char *value = NULL;
        switch (d->choice) {
            case BTB_CHOOSE_BASE: if (d->basePresent) value = d->base; break;
            case BTB_CHOOSE_OURS: if (d->oursPresent) value = d->ours; break;
            case BTB_CHOOSE_THEIRS: if (d->theirsPresent) value = d->theirs; break;
            case BTB_CHOOSE_DELETE: break;
            default: return BTB_MERGE_INVALID;
        }
        if (value != NULL) {
            const BtbMergeStatus status = BtbMergeSnapshotAdd(&result, d->key, value);
            if (status != BTB_MERGE_OK) return status;
        }
    }
    *outSnapshot = result;
    return BTB_MERGE_OK;
}
