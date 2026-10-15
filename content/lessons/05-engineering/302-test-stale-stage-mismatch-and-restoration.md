# Chapter 302 — Test stage mismatches, stale observations and verified restoration

**Bits to Banking · Native engineering · Umicom Foundation**  
**Implementation:** ISO C23 test executable and CTest metadata; no new scripts.

## Why negative tests matter

A successful code path is only one part of the contract. In financial systems, a wrong source revision, stale approval, missing account permission or incomplete settlement must produce an explicit refusal. Deployment tooling has the same requirement: a partial result must never be presented as a complete release.

The Update 42 C23 laboratory registers named test cases that exercise **accepted evidence**, **rejected evidence** and **state that must remain unchanged after a refusal**. Earlier laboratories are linked as existing targets, so their tests continue to execute as regressions.

![Review gates](../../assets/diagrams/sysadmin-rollback-gates-update42.svg)

## Test category 1 — invalid and mismatched identity

A plan contains textual SHA-1 or SHA-256 revision identity and 64-digit package/configuration digests. The format validator rejects invalid characters, missing NUL terminators and illegal stage labels. A candidate source revision or package digest that disagrees with the plan is rejected as a mismatch, not silently accepted.

Run a focused test in PowerShell:

```powershell
ctest --test-dir ".\output\learning-build\deployment-rehearsal" `
  -R "deployment-review\.(bad-hash|mismatch-revision|evidence-digest|evidence-source)" `
  --no-tests=error --output-on-failure
```

Note that this **does not hash a real executable**. The test checks the syntax and consistency of fictional evidence structures only. If production release code needs hashing, use the native cryptography and package-integrity services already owned by Umicom Framework.

## Test category 2 — incomplete and stale stage verification

Run:

```powershell
ctest --test-dir ".\output\learning-build\deployment-rehearsal" `
  -R "deployment-review\.(no-stage|missing-runtime|missing-config|stale-stage|stale-verification)" `
  --no-tests=error --output-on-failure
```

The `no-stage` path reports `PENDING` because the review has no stage evidence. `missing-runtime` and `missing-config` report `BLOCKED` even after a fictional maintenance review completes. `stale-verification` reports the `BTB_DEPLOYMENT_STALE_CAPTURE` flag because the verification capture is not newer than the post-change service observation. A timestamp or capture number is a teaching proxy for evidence ordering; it is not a secure time source or a signed proof.

## Test category 3 — invalid calls must not mutate the caller

The `test_deployment.c` fixture initialises a valid review, stores a copy, attempts an invalid operation and checks that the original bytes remain unchanged. This is done for plan validation, stage attachment, replayed evidence and maintenance identity. The `preserve-output` scenario similarly checks that a rejected `BtbDeploymentEvaluate` call leaves the caller’s decision untouched.

A typical assertion follows this principle:

```c
BtbDeploymentReview saved = review;
BtbDeploymentResult result = BtbDeploymentAttachStage(&review, &badEvidence);
if (result == BTB_DEPLOYMENT_OK) {
    /* Test fails: invalid evidence should not have been accepted. */
}
if (memcmp(&saved, &review, sizeof review) != 0) {
    /* Test fails: refusal changed the prior review. */
}
```

These variables belong to the test fixture; read the complete source to see how valid starting values are constructed. The example is not intended as a replacement for all production assertions.

## Test category 4 — failed change and independent recovery

A simulated change may reach `ROLLBACK_REQUIRED`. That is an actual review result, not an invitation for the laboratory to execute a rollback. The existing maintenance model accepts a later independent restoration observation and reports `RESTORED`. Update 42 deliberately maps it to `RESTORED_ONLY`, preserving the distinction from a successful new deployment.

```powershell
ctest --test-dir ".\output\learning-build\deployment-rehearsal" `
  -R "deployment-review\.(rollback|restored|fully-qualified)" `
  --no-tests=error --output-on-failure
```

Never describe restoration as successful merely because a previous binary was copied into place. A real rollback needs data, configuration, service readiness and audit review by the appropriate system authority.

## Test category 5 — deterministic mutation exercises

The `mutation` test repeats 30,000 bounded trials with a deterministic integer sequence. In each trial exactly one required stage condition is deliberately removed or invalidated. **Every trial must refuse qualification.** There is no random network I/O, wall-clock waiting, parallel worker or mutable global service state; the test is reproducible under a debugger.

```powershell
ctest --test-dir ".\output\learning-build\deployment-rehearsal" `
  -R "deployment-review\.mutation" `
  --no-tests=error --output-on-failure
```

To validate with sanitizers on Linux, configure a separate Clang build directory and enable `-fsanitize=address,undefined` for both compile and link steps; do not modify the original source tree to turn on diagnostics.

## Practical assessment

Produce a table with four columns: input condition, expected result, reason code, evidence owner. Include at least eight scenarios. Distinguish `INVALID` (malformed record) from `MISMATCH` (different identity) and from a valid but `BLOCKED` review. Explain why these categories allow an operator to repair the correct problem without overriding controls.

**Next:** Chapter 303, complete the private-stage release rehearsal and review the Framework boundary.
