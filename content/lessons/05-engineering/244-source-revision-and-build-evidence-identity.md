# Chapter 244 — Bind build evidence to one source revision

**Bits to Banking · Engineering track · Umicom Foundation**  
**Primary language:** C23 · **Laboratory:** `labs/native/build-evidence`  
**Prerequisites:** Chapters 240–243.

## Why this matters

A clean test result can be genuine and still be irrelevant. Suppose a developer builds Framework commit `A`, sees green tests, edits `decimal_arithmetic.c`, and then publishes commit `B` without rebuilding. The successful test result was about `A`; it does not certify `B`. The same mistake occurs if a Framework gitlink is updated inside Umicom OS after the OS build has finished. The apparent good result is stale with respect to the source that would actually be published.

This chapter introduces an **evidence identity**: the complete source commit, the build profile, the toolchain label and a caller-supplied observation sequence. None of these individually proves a release. Together they help a reviewer identify what the run did and did not cover.

## Identity versus freshness

`git rev-parse HEAD` identifies the current repository commit. If uncommitted modifications exist, however, the build input includes more than that commit. The example's source identity therefore assumes a **reviewed clean checkout or separately captured worktree provenance**. Never claim that a commit SHA represents an arbitrary modified working tree.

The educational model accepts a 40-hex SHA-1 or 64-hex SHA-256 commit identifier. It rejects short display hashes because a seven-character abbreviation is unsuitable for durable evidence. It does not calculate Git object hashes; Git and Umicom Framework already own that responsibility.

## Read the C23 identity

Open `labs/native/build-evidence/evidence.h`:

```c
typedef struct BtbEvidenceIdentity {
    char commit[BTB_EVIDENCE_SHA_CAPACITY];
    char profile[BTB_EVIDENCE_NAME_CAPACITY];
    char toolchain[BTB_EVIDENCE_NAME_CAPACITY];
    uint64_t observationSequence;
} BtbEvidenceIdentity;
```

The fixed arrays are bounded; `BtbEvidenceRunInit` validates all NUL terminators and refuses controls or malformed revisions. A zero observation sequence is invalid. The sequence is an identity from the observation owner; it is not a fabricated wall-clock timestamp.

## Real Umicom example

Suppose Framework was built in `windows-ucrt64-all-debug` using GCC UCRT64, and Umicom OS later updates its Framework gitlink. Record these facts as distinct evidence:

1. Framework `HEAD` at the time of Framework compilation and tests.
2. Umicom OS `HEAD` plus its recorded Framework gitlink at the time of OS compilation and tests.
3. Build profile/toolchain for each process.
4. Test pass/fail/not-run counts, process exit results and whether diagnostics were truncated.

The OS build's identity is a **source tuple** in the engineering process: parent commit plus child SHA. The teaching `BtbEvidenceIdentity` is deliberately a one-revision record, so production multi-repository provenance needs a Framework-owned dependency manifest or gitlink observation. The lab does not pretend one SHA authenticates an entire nested dependency tree.

## Exercise: detect stale evidence

Read the `assessment_stale_sha` test case. It completes a clean fictional run for `SHA_A`, then asks whether that run proves `SHA_B`. `BtbEvidenceAssess` returns a valid assessment with `BTB_REVIEW_STALE_REVISION`. That is a **blocked review** rather than a malformed-data error: the evidence was valid, but it was collected for a different revision.

Try the same test with a different profile name. Observe `BTB_REVIEW_PROFILE_MISMATCH`. A debug build cannot be presented as evidence that an untested release build passed. Toolchain changes likewise make diagnostic comparisons formally incomparable until a new baseline is established.

## Assessment

**Can a short hash be sufficient for an educational screenshot?** Usually, provided it is clearly labelled as display-only. **Can it be used as a durable evidence identity here?** No. **Can the model prove that a dirty working tree equals the commit value?** No; the caller must preserve and review worktree provenance. **Should an Umicom OS integration update a Framework pointer without rerunning OS tests?** No.

**Next:** Chapter 245 implements the bounded snapshot that holds those observations.
