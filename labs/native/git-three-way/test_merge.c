/*-----------------------------------------------------------------------------
 * Bits2Banking | Umicom Foundation | Sammy Hegab | MIT
 * File: labs/native/git-three-way/test_merge.c
 * PURPOSE: Named CTest cases for bounded, failure-atomic reconciliation.
 *---------------------------------------------------------------------------*/
#include "merge.h"
#include <stdio.h>
#include <string.h>
#include <stdint.h>

#define CHECK(expression) do { if (!(expression)) { \
    (void)fprintf(stderr, "%s:%d: failed: %s\n", __FILE__, __LINE__, #expression); \
    return 0; } } while (0)

static int Add(BtbMergeSnapshot *snapshot, const char *name, const char *value)
{
    return BtbMergeSnapshotAdd(snapshot, name, value) == BTB_MERGE_OK;
}

static int Get(BtbMergeSnapshot *snapshot, const char *key, const char *value)
{
    for (size_t i = 0U; i < snapshot->count; ++i)
        if (strcmp(snapshot->records[i].key, key) == 0)
            return strcmp(snapshot->records[i].value, value) == 0;
    return 0;
}

static int Absent(BtbMergeSnapshot *snapshot, const char *key)
{
    for (size_t i = 0U; i < snapshot->count; ++i)
        if (strcmp(snapshot->records[i].key, key) == 0) return 0;
    return 1;
}

static int SingleVersion(const char *baseValue, const char *oursValue,
                         const char *theirsValue, BtbMergePlan *plan)
{
    BtbMergeSnapshot base = {0}, ours = {0}, theirs = {0};
    if (baseValue != NULL && !Add(&base, "bank/ledger.c", baseValue)) return 0;
    if (oursValue != NULL && !Add(&ours, "bank/ledger.c", oursValue)) return 0;
    if (theirsValue != NULL && !Add(&theirs, "bank/ledger.c", theirsValue)) return 0;
    return BtbMergePlanBuild(&base, &ours, &theirs, plan) == BTB_MERGE_OK;
}

static int TestEmpty(void)
{
    BtbMergeSnapshot base = {0}, ours = {0}, theirs = {0}, output = {0};
    BtbMergePlan plan = {0};
    CHECK(BtbMergePlanBuild(&base, &ours, &theirs, &plan) == BTB_MERGE_OK);
    CHECK(BtbMergePlanValid(&plan));
    CHECK(plan.count == 0U && plan.conflictCount == 0U);
    CHECK(BtbMergeMaterialise(&plan, &output) == BTB_MERGE_OK);
    CHECK(output.count == 0U);
    return 1;
}

static int TestUnchanged(void)
{
    BtbMergePlan plan = {0}; BtbMergeSnapshot result = {0};
    CHECK(SingleVersion("ledger-v1", "ledger-v1", "ledger-v1", &plan));
    CHECK(plan.decisions[0].kind == BTB_MERGE_UNCHANGED);
    CHECK(BtbMergeMaterialise(&plan, &result) == BTB_MERGE_OK);
    CHECK(Get(&result, "bank/ledger.c", "ledger-v1"));
    return 1;
}

static int TestOursOnly(void)
{
    BtbMergePlan plan = {0}; BtbMergeSnapshot result = {0};
    CHECK(SingleVersion("ledger-v1", "ledger-v2", "ledger-v1", &plan));
    CHECK(plan.decisions[0].kind == BTB_MERGE_OURS_ONLY);
    CHECK(BtbMergeMaterialise(&plan, &result) == BTB_MERGE_OK);
    CHECK(Get(&result, "bank/ledger.c", "ledger-v2"));
    return 1;
}

static int TestTheirsOnly(void)
{
    BtbMergePlan plan = {0}; BtbMergeSnapshot result = {0};
    CHECK(SingleVersion("ledger-v1", "ledger-v1", "ledger-v3", &plan));
    CHECK(plan.decisions[0].kind == BTB_MERGE_THEIRS_ONLY);
    CHECK(BtbMergeMaterialise(&plan, &result) == BTB_MERGE_OK);
    CHECK(Get(&result, "bank/ledger.c", "ledger-v3"));
    return 1;
}

static int TestIdenticalEdits(void)
{
    BtbMergePlan plan = {0}; BtbMergeSnapshot result = {0};
    CHECK(SingleVersion("ledger-v1", "ledger-v2", "ledger-v2", &plan));
    CHECK(plan.decisions[0].kind == BTB_MERGE_IDENTICAL_CHANGE);
    CHECK(plan.conflictCount == 0U);
    CHECK(BtbMergeMaterialise(&plan, &result) == BTB_MERGE_OK);
    CHECK(Get(&result, "bank/ledger.c", "ledger-v2"));
    return 1;
}

static int TestOursDelete(void)
{
    BtbMergePlan plan = {0}; BtbMergeSnapshot result = {0};
    CHECK(SingleVersion("ledger-v1", NULL, "ledger-v1", &plan));
    CHECK(plan.decisions[0].kind == BTB_MERGE_OURS_ONLY);
    CHECK(BtbMergeMaterialise(&plan, &result) == BTB_MERGE_OK);
    CHECK(Absent(&result, "bank/ledger.c"));
    return 1;
}

static int TestTheirsDelete(void)
{
    BtbMergePlan plan = {0}; BtbMergeSnapshot result = {0};
    CHECK(SingleVersion("ledger-v1", "ledger-v1", NULL, &plan));
    CHECK(plan.decisions[0].kind == BTB_MERGE_THEIRS_ONLY);
    CHECK(BtbMergeMaterialise(&plan, &result) == BTB_MERGE_OK);
    CHECK(Absent(&result, "bank/ledger.c"));
    return 1;
}

static int TestBothDelete(void)
{
    BtbMergePlan plan = {0}; BtbMergeSnapshot result = {0};
    CHECK(SingleVersion("ledger-v1", NULL, NULL, &plan));
    CHECK(plan.decisions[0].kind == BTB_MERGE_IDENTICAL_CHANGE);
    CHECK(BtbMergeMaterialise(&plan, &result) == BTB_MERGE_OK);
    CHECK(result.count == 0U);
    return 1;
}

static int TestOursAdd(void)
{
    BtbMergePlan plan = {0}; BtbMergeSnapshot result = {0};
    CHECK(SingleVersion(NULL, "ledger-v1", NULL, &plan));
    CHECK(plan.decisions[0].kind == BTB_MERGE_OURS_ONLY);
    CHECK(BtbMergeMaterialise(&plan, &result) == BTB_MERGE_OK);
    CHECK(Get(&result, "bank/ledger.c", "ledger-v1"));
    return 1;
}

static int TestTheirsAdd(void)
{
    BtbMergePlan plan = {0}; BtbMergeSnapshot result = {0};
    CHECK(SingleVersion(NULL, NULL, "ledger-v1", &plan));
    CHECK(plan.decisions[0].kind == BTB_MERGE_THEIRS_ONLY);
    CHECK(BtbMergeMaterialise(&plan, &result) == BTB_MERGE_OK);
    CHECK(Get(&result, "bank/ledger.c", "ledger-v1"));
    return 1;
}

static int TestSameAdd(void)
{
    BtbMergePlan plan = {0}; BtbMergeSnapshot result = {0};
    CHECK(SingleVersion(NULL, "ledger-v1", "ledger-v1", &plan));
    CHECK(plan.decisions[0].kind == BTB_MERGE_IDENTICAL_CHANGE);
    CHECK(BtbMergeMaterialise(&plan, &result) == BTB_MERGE_OK);
    CHECK(Get(&result, "bank/ledger.c", "ledger-v1"));
    return 1;
}

static int TestDifferentEdits(void)
{
    BtbMergePlan plan = {0}; BtbMergeSnapshot out = {0};
    CHECK(SingleVersion("base", "ours", "theirs", &plan));
    CHECK(plan.decisions[0].kind == BTB_MERGE_NEEDS_REVIEW);
    CHECK(plan.conflictCount == 1U && plan.unresolvedCount == 1U);
    CHECK(BtbMergeMaterialise(&plan, &out) == BTB_MERGE_CONFLICT_PENDING);
    return 1;
}

static int TestDifferentAdds(void)
{
    BtbMergePlan plan = {0};
    CHECK(SingleVersion(NULL, "ours", "theirs", &plan));
    CHECK(plan.decisions[0].kind == BTB_MERGE_NEEDS_REVIEW);
    CHECK(!plan.decisions[0].basePresent);
    return 1;
}

static int TestDeleteEdit(void)
{
    BtbMergePlan plan = {0};
    CHECK(SingleVersion("original", NULL, "replacement", &plan));
    CHECK(plan.decisions[0].kind == BTB_MERGE_NEEDS_REVIEW);
    CHECK(plan.decisions[0].basePresent && !plan.decisions[0].oursPresent);
    return 1;
}

static int TestEditDelete(void)
{
    BtbMergePlan plan = {0};
    CHECK(SingleVersion("original", "replacement", NULL, &plan));
    CHECK(plan.decisions[0].kind == BTB_MERGE_NEEDS_REVIEW);
    CHECK(plan.decisions[0].oursPresent && !plan.decisions[0].theirsPresent);
    return 1;
}

static int TestChoose(BtbMergeChoice choice, const char *expected)
{
    BtbMergePlan plan = {0}; BtbMergeSnapshot result = {0};
    CHECK(SingleVersion("base", "ours", "theirs", &plan));
    CHECK(BtbMergeResolve(&plan, "bank/ledger.c", choice) == BTB_MERGE_OK);
    CHECK(plan.conflictCount == 1U && plan.unresolvedCount == 0U);
    CHECK(BtbMergePlanValid(&plan));
    CHECK(BtbMergeMaterialise(&plan, &result) == BTB_MERGE_OK);
    if (expected == NULL) CHECK(Absent(&result, "bank/ledger.c"));
    else CHECK(Get(&result, "bank/ledger.c", expected));
    return 1;
}

static int TestChooseBase(void) { return TestChoose(BTB_CHOOSE_BASE, "base"); }
static int TestChooseOurs(void) { return TestChoose(BTB_CHOOSE_OURS, "ours"); }
static int TestChooseTheirs(void) { return TestChoose(BTB_CHOOSE_THEIRS, "theirs"); }
static int TestChooseDelete(void) { return TestChoose(BTB_CHOOSE_DELETE, NULL); }

static int TestExplicitAbsentChoice(void)
{
    BtbMergePlan plan = {0}; BtbMergeSnapshot result = {0};
    CHECK(SingleVersion("base", NULL, "theirs", &plan));
    CHECK(BtbMergeResolve(&plan, "bank/ledger.c", BTB_CHOOSE_OURS) == BTB_MERGE_OK);
    CHECK(BtbMergeMaterialise(&plan, &result) == BTB_MERGE_OK);
    CHECK(result.count == 0U);
    return 1;
}

static int TestResolveOnlyOnce(void)
{
    BtbMergePlan plan = {0}; BtbMergePlan original = {0};
    CHECK(SingleVersion("base", "ours", "theirs", &plan));
    CHECK(BtbMergeResolve(&plan, "bank/ledger.c", BTB_CHOOSE_OURS) == BTB_MERGE_OK);
    original = plan;
    CHECK(BtbMergeResolve(&plan, "bank/ledger.c", BTB_CHOOSE_THEIRS) == BTB_MERGE_ALREADY_RESOLVED);
    CHECK(memcmp(&plan, &original, sizeof(plan)) == 0);
    return 1;
}

static int TestNoResolveOnClean(void)
{
    BtbMergePlan plan = {0}; BtbMergePlan original = {0};
    CHECK(SingleVersion("base", "ours", "base", &plan));
    original = plan;
    CHECK(BtbMergeResolve(&plan, "bank/ledger.c", BTB_CHOOSE_THEIRS) == BTB_MERGE_NOT_CONFLICT);
    CHECK(memcmp(&plan, &original, sizeof(plan)) == 0);
    return 1;
}

static int TestResolveInputAtomic(void)
{
    BtbMergePlan plan = {0}; BtbMergePlan original = {0};
    CHECK(SingleVersion("base", "ours", "theirs", &plan));
    original = plan;
    CHECK(BtbMergeResolve(&plan, "bank/ledger.c", BTB_CHOOSE_NONE) == BTB_MERGE_INVALID);
    CHECK(memcmp(&plan, &original, sizeof(plan)) == 0);
    CHECK(BtbMergeResolve(&plan, "unknown", BTB_CHOOSE_OURS) == BTB_MERGE_NOT_FOUND);
    CHECK(memcmp(&plan, &original, sizeof(plan)) == 0);
    return 1;
}

static int TestPendingOutputAtomic(void)
{
    BtbMergePlan plan = {0}; BtbMergeSnapshot out = {0}, prior = {0};
    CHECK(SingleVersion("base", "ours", "theirs", &plan));
    CHECK(Add(&out, "important/recovery.c", "retain-me"));
    prior = out;
    CHECK(BtbMergeMaterialise(&plan, &out) == BTB_MERGE_CONFLICT_PENDING);
    CHECK(memcmp(&out, &prior, sizeof(out)) == 0);
    return 1;
}

static int TestRejectDuplicate(void)
{
    BtbMergeSnapshot s = {0}, before = {0};
    CHECK(Add(&s, "bank/ledger.c", "one"));
    before = s;
    CHECK(BtbMergeSnapshotAdd(&s, "bank/ledger.c", "two") == BTB_MERGE_DUPLICATE);
    CHECK(memcmp(&s, &before, sizeof(s)) == 0);
    return 1;
}

static int TestRejectInvalidKey(void)
{
    BtbMergeSnapshot s = {0}, before = {0};
    CHECK(Add(&s, "bank/ledger.c", "one")); before = s;
    CHECK(BtbMergeSnapshotAdd(&s, "space key", "two") == BTB_MERGE_INVALID);
    CHECK(BtbMergeSnapshotAdd(&s, "", "two") == BTB_MERGE_INVALID);
    CHECK(memcmp(&s, &before, sizeof(s)) == 0);
    return 1;
}

static int TestRejectUnterminated(void)
{
    BtbMergeSnapshot s = {0}, before = {0};
    char bad[BTB_MERGE_VALUE_CAPACITY];
    (void)memset(bad, 'z', sizeof(bad));
    CHECK(Add(&s, "bank/ledger.c", "one")); before = s;
    CHECK(BtbMergeSnapshotAdd(&s, "valid", bad) == BTB_MERGE_INVALID);
    CHECK(memcmp(&s, &before, sizeof(s)) == 0);
    return 1;
}

static int TestSnapshotFullAtomic(void)
{
    BtbMergeSnapshot s = {0}, before = {0};
    char key[BTB_MERGE_KEY_CAPACITY];
    for (unsigned i = 0U; i < BTB_MERGE_MAX_RECORDS; ++i) {
        (void)snprintf(key, sizeof(key), "module%u", i);
        CHECK(Add(&s, key, "record"));
    }
    before = s;
    CHECK(BtbMergeSnapshotAdd(&s, "overflow", "record") == BTB_MERGE_FULL);
    CHECK(memcmp(&s, &before, sizeof(s)) == 0);
    return 1;
}

static int TestPlanOverflowAtomic(void)
{
    BtbMergeSnapshot base = {0}, ours = {0}, theirs = {0};
    BtbMergePlan plan, before;
    char key[BTB_MERGE_KEY_CAPACITY];
    for (unsigned i = 0U; i < BTB_MERGE_MAX_RECORDS; ++i) {
        (void)snprintf(key, sizeof(key), "module%u", i);
        CHECK(Add(&base, key, "baseline"));
    }
    CHECK(Add(&ours, "another-module", "new"));
    (void)memset(&plan, 0x5a, sizeof(plan)); before = plan;
    CHECK(BtbMergePlanBuild(&base, &ours, &theirs, &plan) == BTB_MERGE_FULL);
    CHECK(memcmp(&plan, &before, sizeof(plan)) == 0);
    return 1;
}

static int TestPlanInvalidAtomic(void)
{
    BtbMergeSnapshot base = {0}, ours = {0}, theirs = {0};
    BtbMergePlan plan, before;
    CHECK(Add(&base, "account", "balance"));
    CHECK(Add(&base, "other", "balance"));
    (void)strcpy(base.records[1].key, "account"); /* corrupt caller source */
    (void)memset(&plan, 0x44, sizeof(plan)); before = plan;
    CHECK(BtbMergePlanBuild(&base, &ours, &theirs, &plan) == BTB_MERGE_INVALID);
    CHECK(memcmp(&plan, &before, sizeof(plan)) == 0);
    return 1;
}

static int TestOrdering(void)
{
    BtbMergeSnapshot base = {0}, ours = {0}, theirs = {0};
    BtbMergePlan plan = {0};
    CHECK(Add(&base, "b", "b")); CHECK(Add(&base, "a", "a"));
    CHECK(Add(&ours, "d", "d")); CHECK(Add(&ours, "a", "a"));
    CHECK(Add(&theirs, "c", "c")); CHECK(Add(&theirs, "b", "b"));
    CHECK(BtbMergePlanBuild(&base, &ours, &theirs, &plan) == BTB_MERGE_OK);
    CHECK(plan.count == 4U);
    CHECK(strcmp(plan.decisions[0].key, "b") == 0);
    CHECK(strcmp(plan.decisions[1].key, "a") == 0);
    CHECK(strcmp(plan.decisions[2].key, "d") == 0);
    CHECK(strcmp(plan.decisions[3].key, "c") == 0);
    return 1;
}

static int TestDeepCopy(void)
{
    BtbMergeSnapshot base = {0}, ours = {0}, theirs = {0}, out = {0};
    BtbMergePlan plan = {0};
    CHECK(Add(&base, "notes", "before"));
    CHECK(Add(&ours, "notes", "after"));
    CHECK(Add(&theirs, "notes", "before"));
    CHECK(BtbMergePlanBuild(&base, &ours, &theirs, &plan) == BTB_MERGE_OK);
    (void)strcpy(ours.records[0].value, "corrupted-later");
    CHECK(BtbMergeMaterialise(&plan, &out) == BTB_MERGE_OK);
    CHECK(Get(&out, "notes", "after"));
    return 1;
}

static int TestRejectTamper(void)
{
    BtbMergePlan plan = {0}; BtbMergeSnapshot out = {0};
    CHECK(SingleVersion("one", "two", "three", &plan));
    plan.decisions[0].kind = BTB_MERGE_IDENTICAL_CHANGE;
    CHECK(!BtbMergePlanValid(&plan));
    CHECK(BtbMergeMaterialise(&plan, &out) == BTB_MERGE_INVALID);
    return 1;
}

static int TestNoTruncation(void)
{
    BtbMergeSnapshot snap = {0}; char value[BTB_MERGE_VALUE_CAPACITY];
    (void)memset(value, 'x', sizeof(value));
    value[sizeof(value) - 1U] = '\0';
    CHECK(Add(&snap, "max-length-record", value));
    CHECK(strlen(snap.records[0].value) == BTB_MERGE_VALUE_CAPACITY - 1U);
    CHECK(BtbMergeSnapshotValid(&snap));
    return 1;
}

static uint32_t NextSeed(uint32_t *state)
{
    *state = (*state * UINT32_C(1664525)) + UINT32_C(1013904223);
    return *state;
}

static int TestMutation50000(void)
{
    uint32_t seed = UINT32_C(0x13572468);
    for (unsigned iteration = 0U; iteration < 50000U; ++iteration) {
        BtbMergeSnapshot base = {0}, ours = {0}, theirs = {0}, out = {0};
        BtbMergePlan plan = {0};
        char b[32], o[32], t[32];
        const uint32_t bits = NextSeed(&seed);
        const int bp = (bits & 1U) != 0U;
        const int op = (bits & 2U) != 0U;
        const int tp = (bits & 4U) != 0U;
        (void)snprintf(b, sizeof(b), "base-%u", (unsigned)(bits % 7U));
        (void)snprintf(o, sizeof(o), "ours-%u", (unsigned)((bits >> 3U) % 7U));
        (void)snprintf(t, sizeof(t), "theirs-%u", (unsigned)((bits >> 6U) % 7U));
        if ((bits & 32U) != 0U) (void)strcpy(o, b);
        if ((bits & 64U) != 0U) (void)strcpy(t, b);
        if ((bits & 128U) != 0U) (void)strcpy(t, o);
        if (bp) CHECK(Add(&base, "asset", b));
        if (op) CHECK(Add(&ours, "asset", o));
        if (tp) CHECK(Add(&theirs, "asset", t));
        CHECK(BtbMergePlanBuild(&base, &ours, &theirs, &plan) == BTB_MERGE_OK);
        CHECK(BtbMergePlanValid(&plan));
        if (plan.unresolvedCount != 0U) {
            CHECK(plan.unresolvedCount == 1U);
            CHECK(BtbMergeMaterialise(&plan, &out) == BTB_MERGE_CONFLICT_PENDING);
            CHECK(BtbMergeResolve(&plan, "asset", BTB_CHOOSE_OURS) == BTB_MERGE_OK);
        }
        CHECK(BtbMergeMaterialise(&plan, &out) == BTB_MERGE_OK);
        CHECK(BtbMergeSnapshotValid(&out));
        if (out.count != 0U) CHECK(strcmp(out.records[0].key, "asset") == 0);
    }
    return 1;
}

typedef int (*BtbTestFunction)(void);
typedef struct BtbTestEntry { const char *name; BtbTestFunction test; } BtbTestEntry;

static const BtbTestEntry tests[] = {
    {"empty", TestEmpty}, {"unchanged", TestUnchanged},
    {"ours_only", TestOursOnly}, {"theirs_only", TestTheirsOnly},
    {"identical_edits", TestIdenticalEdits}, {"ours_delete", TestOursDelete},
    {"theirs_delete", TestTheirsDelete}, {"both_delete", TestBothDelete},
    {"ours_add", TestOursAdd}, {"theirs_add", TestTheirsAdd},
    {"same_add", TestSameAdd}, {"different_edits", TestDifferentEdits},
    {"different_adds", TestDifferentAdds}, {"delete_edit", TestDeleteEdit},
    {"edit_delete", TestEditDelete}, {"choose_base", TestChooseBase},
    {"choose_ours", TestChooseOurs}, {"choose_theirs", TestChooseTheirs},
    {"choose_delete", TestChooseDelete},
    {"explicit_absent_choice", TestExplicitAbsentChoice},
    {"resolve_once", TestResolveOnlyOnce},
    {"no_resolve_on_clean", TestNoResolveOnClean},
    {"resolve_input_atomic", TestResolveInputAtomic},
    {"pending_output_atomic", TestPendingOutputAtomic},
    {"reject_duplicate", TestRejectDuplicate},
    {"reject_invalid_key", TestRejectInvalidKey},
    {"reject_unterminated", TestRejectUnterminated},
    {"snapshot_full_atomic", TestSnapshotFullAtomic},
    {"plan_overflow_atomic", TestPlanOverflowAtomic},
    {"plan_invalid_atomic", TestPlanInvalidAtomic},
    {"ordering", TestOrdering}, {"deep_copy", TestDeepCopy},
    {"reject_tamper", TestRejectTamper}, {"no_truncation", TestNoTruncation},
    {"mutation_50000", TestMutation50000}
};

int main(int argc, char **argv)
{
    if (argc != 2) {
        (void)fprintf(stderr, "usage: btb-git-three-way-test <named-case>\n");
        return 2;
    }
    for (size_t i = 0U; i < sizeof(tests) / sizeof(tests[0]); ++i) {
        if (strcmp(argv[1], tests[i].name) != 0) continue;
        if (!tests[i].test()) return 1;
        (void)printf("PASS %s\n", tests[i].name);
        return 0;
    }
    (void)fprintf(stderr, "unknown test case: %s\n", argv[1]);
    return 2;
}
