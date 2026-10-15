# Chapter 306 — Prove remote review fails closed under malformed evidence

**Bits to Banking · Engineering track · C23 · Umicom Foundation**  
**Laboratory:** `labs/native/remote-access-review`  
**Required understanding:** `BtbRemoteResult`, `BtbRemoteStatus` and `BtbRemoteDecision`.

## Why happy-path tests are insufficient

An access review that accepts every valid example may still be dangerous if a missing host-key check, stale source revision or failed deployment is treated as success. Professional tests must make the refusal behaviour observable. In Umicom, an engineer should preserve rejected input and failure evidence rather than weakening validation to produce a green build.

This laboratory has **named tests** and composes the earlier regression suite. There is no remote server, timing-dependent thread or platform command hidden in the tests. Each case constructs a deterministic fictional review, changes exactly one field and checks the resulting status or missing-evidence bits.

## Three kinds of outcome

| Outcome | Meaning in this lab | Production implication |
|---|---|---|
| `BTB_REMOTE_REVIEWABLE` | All *claimed* teaching evidence present and upstream deployment model qualified. | Human approval still required. |
| `BTB_REMOTE_BLOCKED` | A required check is missing, stale or upstream deployment has not qualified. | Do not grant access or proceed to change. |
| `BTB_REMOTE_RESTORED_ONLY` | Upstream model reports a failed deployment whose prior state was restored. | Do not relabel a recovery as deployment success. |

Invalid structural input produces a **result-code error**, not a valid decision. Repeating an attachment produces `BTB_REMOTE_STATE_ERROR`. These errors protect the caller's existing data.

![Negative cases stop at the appropriate review gate](../../assets/diagrams/sysadmin-admin-change-gates-update43.svg)

## Read the tests and follow their evidence

Open `test_remote.c`. The fixture deliberately calls real previously delivered `BtbMaintenanceInit`, `BtbMaintenanceApprove`, `BtbMaintenanceObserveAfter`, `BtbDeploymentInit` and `BtbDeploymentAttachStage`. This is why Updates 39–42 must be merged before Update 43.

Follow the `host-key` case. It sets `hostIdentityIndependentlyChecked` to zero. `Attach` can accept the *structurally valid but incomplete* evidence; `Evaluate` reports `BTB_REMOTE_MISSING_HOST_IDENTITY`. This distinction lets a support dashboard explain **what is missing** without pretending the review succeeded.

Follow the `stale` case. Its access capture ID equals the deployment verification capture ID. Because there is no independent later observation, `BTB_REMOTE_STALE_CAPTURE` is reported. New observations must be demonstrably later than the state they claim to review. Real systems should also bind observation time and content to a trustworthy authority; the lab deliberately stops short of that.

Follow `atomic-output`. The test initialises a decision with a distinctive byte pattern, damages the input plan and invokes `BtbRemoteEvaluate`. It asserts `BTB_REMOTE_INVALID` and checks that the caller's decision bytes did not change. This makes failure atomicity testable rather than merely documented.

## Run selected tests on Windows

```powershell
Set-Location "C:\umicom\Umicom-Bits2Banking"
ctest --test-dir ".\output\learning-build\remote-access-review" -R "bits2banking\.remote-review\.(host-key|transport|stale|rollback|restored|atomic-output)$" --no-tests=error --output-on-failure
```

If the build directory does not exist, configure and build the lab first as shown in Chapter 304. If the requested tests are not registered, verify that the CMake project was actually configured with `BUILD_TESTING=ON`; do not report a zero-test invocation as a pass.

## Mutation exercise

The named `mutations` test repeats 25,000 deterministic incomplete-evidence scenarios. Each scenario removes one different claimed check and must produce a blocked decision with at least one missing-evidence bit. It does **not** constitute fuzzing of an SSH implementation, cryptographic proof or penetration testing; it exercises only a small, bounded in-memory policy model.

## Failure modes to consider

1. **Time jump:** The lab accepts externally supplied observation times. A real operating system can have a clock problem; production evidence must not rely on unchecked local timestamps alone.
2. **Compromised reporter:** An attacker can falsely set every flag to one. Real verification must happen in trusted Framework/OS systems and produce auditable provenance.
3. **Untrusted string:** A host label that fits a buffer is not an approved network destination.
4. **Restoration:** A failed change followed by restoration is not the same as a successful new deployment.

## Questions

- **Why keep the distinction between invalid and blocked?** Invalid evidence cannot be interpreted reliably; blocked means well-formed evidence that fails a review requirement.
- **Why run inherited tests?** Upstream library behaviour is part of this composition's contract.
- **What does a passing lab prove?** Only the modelled C23 behaviour under the specified deterministic inputs.

**Next:** Chapter 307 — build, review and report the complete educational capstone.
