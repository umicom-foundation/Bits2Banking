# Chapter 234 — Prove failure-atomic merge decisions with C23 tests

**Bits to Banking · Native C23 testing · Umicom Foundation**  
**Prerequisite:** Chapters 232–233 · **Test source:** `labs/native/git-three-way/test_merge.c`.

## Why the failure path is the main feature

An educational record-merge model is useful only if it never publishes a result while a disagreement is unresolved. The key guarantee is **failure atomicity**: if an operation rejects input or cannot complete, the caller's existing output remains unchanged. This is a C23 memory and API design lesson relevant to Umicom Bank account postings, TMS transitions and Framework configuration.

For example, an incompatible Framework change must not partly update the OS integration's release-evidence report. A rejected operation should return a result code and leave the previous observation intact.

## Read the public contracts before the implementation

```c
BtbMergeStatus BtbMergePlanBuild(
    const BtbMergeSnapshot *base,
    const BtbMergeSnapshot *ours,
    const BtbMergeSnapshot *theirs,
    BtbMergePlan *outPlan);

BtbMergeStatus BtbMergeMaterialise(
    const BtbMergePlan *plan,
    BtbMergeSnapshot *outSnapshot);
```

In `merge.c`, `BtbMergePlanBuild` constructs a **local candidate** first. It assigns `*outPlan` only after all names, presence flags and decisions are valid. Similarly, `BtbMergeMaterialise` assembles a local output and publishes it only after every conflict has been resolved.

## Test boundaries, not only the happy path

| Input or state | Expected behaviour | Why it matters |
|---|---|---|
| Duplicate record name | `BTB_MERGE_DUPLICATE` | Prevents ambiguous identity. |
| Unterminated value within 128 bytes | `BTB_MERGE_INVALID` | Prevents out-of-bounds C string reads. |
| Seventeenth union name | `BTB_MERGE_FULL` | Prevents buffer overflow and partial output. |
| An unresolved conflict | `BTB_MERGE_CONFLICT_PENDING` | Prevents a silent side choice. |
| Attempt to change a resolved choice | `BTB_MERGE_ALREADY_RESOLVED` | Prevents accidental revision without a new review. |
| Tampered plan classification | `BTB_MERGE_INVALID` | Avoids trusting inconsistent stored state. |

The plan is a teaching data structure, not an authenticated source of truth; its consistency check cannot prove a Git commit was signed or remotely published. That requires separate provenance evidence.

## Run the reproducible tests

```powershell
Set-Location "C:\umicom\Umicom-Bits2Banking"
ctest --test-dir ".\output\learning-build\git-three-way" --output-on-failure
ctest --test-dir ".\output\learning-build\git-three-way" -R "(atomic|reject|mutation_50000)" --output-on-failure
```

The suite registers **36 tests**: 35 named logical cases and one executable demonstration. The `mutation_50000` case uses a fixed-seed C23 pseudorandom sequence. It does not depend on sleeps, sockets, network access, Python, PowerShell scripts or background threads.

## Trace one rejected operation in a debugger

1. In `TestPendingOutputAtomic`, observe the existing `out` snapshot holding the fictional recovery record.
2. Step into `BtbMergeMaterialise` with `plan.unresolvedCount > 0`.
3. Confirm the function returns `BTB_MERGE_CONFLICT_PENDING` **before** writing `*outSnapshot`.
4. Step back into the test and inspect `memcmp(&out, &prior, sizeof(out)) == 0`.
5. Repeat with `TestPlanOverflowAtomic`, inspecting the unmodified caller-provided `BtbMergePlan`.

Do not compare structs byte-by-byte in arbitrary production code without controlling padding and initialisation. These tests use fully initialised fixed-size teaching structures so the explicit byte comparison is meaningful. When designing a public ABI, prefer comparing named fields and validating structure size/version.

## Questions and answers

**Why not allocate unlimited memory for every result?** Bounded storage allows us to define failure behaviour and inspect memory. **What happens on a seventeenth distinct key?** The build fails with `BTB_MERGE_FULL`; no plan is published. **Does passing the mutation test prove the model correct for every input?** No; it provides deterministic regression evidence. Formal reasoning, boundary tests and integration acceptance remain necessary.

**Next:** locate the genuine Umicom Framework VCS ownership boundary before connecting any model to live repositories.
