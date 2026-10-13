# Chapter 247 — Reject truncated, stale and incomplete build evidence

**Bits to Banking · Engineering track · Umicom Foundation**  
**Primary language:** C23 · **Source:** `BtbEvidenceAssess`  
**Prerequisites:** Chapters 242, 244–246.

## Why this matters

A build log can be incomplete for perfectly ordinary reasons: output capture reached its limit, a parser rejected an oversized path, a process was killed, CTest skipped an executable that was not built, or a contributor tested an earlier commit. Counting zero errors in a partial transcript is not proof of success. A professional engineering system must distinguish **no error observed** from **sufficient evidence to conclude no error occurred**.

The Umicom Framework compiler/build parser already maintains a `dropped` count. Our teaching model carries that count into the finished snapshot, rather than hiding it. It also records the build-process exit code and independent test counts.

## Review flags, not a magic green light

`BtbEvidenceAssess` returns a `BtbEvidenceAssessment` with a bitmask of review flags. The flags include stale revision, wrong profile, nonzero build exit, observed errors, dropped diagnostics, missing test evidence, failed tests, not-run tests and warnings above the selected teaching budget.

The function returns `BTB_EVIDENCE_OK` when it has **successfully evaluated** structurally valid evidence. A nonzero `reviewFlags` then means the evidence is **blocked for manual review**. The return code is not a success claim about the build itself.

```c
BtbEvidenceAssessment assessment = {0};
BtbEvidenceResult status = BtbEvidenceAssess(
    &run, expectedCommit, expectedProfile, 0U, &assessment);
if (status == BTB_EVIDENCE_OK && assessment.reviewFlags != 0U) {
    /* Explain each condition; do not publish a green status. */
}
```

`run`, `expectedCommit` and `expectedProfile` must be supplied by the caller. The warning budget of zero is deliberately conservative for the exercise. Real products can have carefully justified warning policies, documented exceptions and independent release controls.

## The false-negative case

Imagine Ninja exits with code 1 because a linker process crashes before printing a recognised compiler diagnostic. The snapshot may contain zero `ERROR` records. `BtbEvidenceAssess` still sets `BTB_REVIEW_BUILD_FAILURE`. The failure cannot disappear merely because the parser had nothing to classify.

Now imagine Ninja exits zero but a bounded Framework diagnostics list drops two oversized messages. The review reports `BTB_REVIEW_DROPPED_DIAGNOSTICS`. The caller should preserve the raw transcript and diagnose the capture limit, not reduce the dropped count to zero in order to proceed.

Finally, imagine all 20 tests were registered but three are `Not Run`. The review distinguishes these from three tests that ran and returned a failure. Both conditions block a completeness claim; they require different fixes.

## Formal invariants

A structurally valid snapshot cannot be sealed before a build result has been recorded. Test counts may be recorded only after the build result, and their sum must not overflow `size_t`. A record cannot be added after the build process outcome is fixed. Invalid inputs must not mutate the source snapshot or the caller's previous assessment.

The lab tests these invariants with `assessment_missing_tests`, `assessment_zero_tests`, `assessment_dropped`, `assessment_build_failed`, `assessment_not_run_tests`, `tests_sum_overflow` and `assessment_invalid_output_atomic`. Each represents a failure seen in real build/release work, not a contrived “hello world” example.

## Guided operational runbook

In PowerShell, record the current revision before you build:

```powershell
git status
git rev-parse HEAD
cmake --build --preset windows-ucrt64-all-debug --parallel 2
ctest --preset windows-ucrt64-all-debug --output-on-failure
```

Do not run the last command if configuration or compilation did not produce the required test executables; otherwise mark the test gate as not executed. If you rebuild, record which source revision and configuration were used **after** the change. A fresh build cannot retroactively certify a different revision.

## Review questions

**Can a run with zero parsed errors and nonzero exit code pass?** No. **Can a skipped test count as a verified pass?** No. **Should a stale revision be classified as malformed evidence?** No: the evidence is valid but applies to a different revision. **Does a zero review flag authorise a Git push?** Absolutely not; the result is a teaching pre-review signal, not production release authorisation.

**Next:** Chapter 248 applies these boundaries to a real Umicom build investigation.
