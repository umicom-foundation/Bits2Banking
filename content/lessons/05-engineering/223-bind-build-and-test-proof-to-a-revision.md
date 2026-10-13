# Chapter 223 — Bind build and test proof to an observed revision

**Bits to Banking · Native quality engineering · Umicom Foundation**  
**Author:** Sammy Hegab · **Laboratory:** `labs/native/git-review-timeline`.

## The problem

A status dashboard displays a green build icon and a green test icon, while a contributor has just changed a public C23 header. If the icons represent an older checkout, they no longer prove that the new interface is compatible. A professional system labels the result with the input revision and refuses stale evidence rather than silently inheriting success.

The Update 33 laboratory uses `BtbReviewEvidence` to express **kind** (`BUILD` or `TEST`), **result** (`PASSED` or `FAILED`), observation ID and full commit ID. `NOT_RUN` is the default state inside the timeline; it is not a positive submitted result. The caller creates and owns evidence objects. The timeline stores small copied values, not pointers to mutable output files or IDE widgets.

## Follow the C23 implementation

Open `review.c` and find `BtbReviewRecordEvidence`. It validates the kind and proof enumerations before checking identity. If the supplied ID or SHA differs from the current observation, it returns `BTB_REVIEW_STALE` without modifying the timeline. When a new build result is recorded, the previous test result becomes `NOT_RUN`. The reason is deliberate: rebuilding may change binaries, generated sources or dependencies even when the Git HEAD is unchanged.

A compact example of the intended call sequence is:

```c
BtbReviewEvidence build = {
    .kind = BTB_REVIEW_EVIDENCE_BUILD,
    .proof = BTB_REVIEW_PROOF_PASSED,
    .observationId = currentObservation.observationId
};
/* Copy a validated full SHA from the observed checkout to build.commit
 * before passing this structure to BtbReviewRecordEvidence. */
```

The example intentionally omits a fabricated SHA lookup. In a real caller, obtain the revision through the existing Framework VCS provider. Do not use the current date or a random number as a substitute for the tested source identity.

## Run the dedicated regression tests

```powershell
Set-Location "C:\umicom\Umicom-Bits2Banking"
ctest --test-dir ".\output\learning-build\git-review-timeline" --output-on-failure
```

The named test cases include `stale-evidence`, `wrong-commit-evidence`, `observation-invalidates`, `rebuild-invalidates`, `failed-build`, `failed-test` and `invalid-atomic`. Open `test_review.c` to inspect their exact assertions. An important test expects the previous report or proof to remain unchanged after an invalid request.

## Negative scenario

Suppose build B returned success for observation 21, followed by a CTest pass for observation 21. The team then updates the Framework submodule to observation 22. Sending the old build receipt for 21 must fail. Even if both observations display the same abbreviated commit in a terminal, it is not sufficient to treat the proofs as interchangeable. Source-tree changes, untracked files and configuration differences may still exist.

## What the lab cannot prove

There is no cryptographic attestation of a compiler invocation and no trusted CI signature. A caller could lie about a passed build or incorrectly label a SHA. The native model checks **internal consistency of supplied facts**, not their real-world authenticity. To obtain defensible release evidence, a pipeline must record executed commands, toolchain identity, source revision, tests, exit codes and artefact checksums from an appropriately controlled environment.

## Exercises

1. Make one negative test present an invalid enumeration value and confirm it is rejected.
2. Explain why the output structure is changed only after validation.
3. Describe the difference between a compiler return code and a complete executable test pass.
4. Explain how an OS QEMU boot gate differs from a native CTest gate.
5. Identify which new evidence would be necessary after changing a Framework public header.

**Next:** [Chapter 224 — Compile against the Framework VCS contract](224-compile-an-optional-framework-vcs-adapter.md).
