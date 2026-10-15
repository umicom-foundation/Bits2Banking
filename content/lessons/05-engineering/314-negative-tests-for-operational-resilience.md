# Chapter 314 — Negative tests for operational resilience and honest recovery

**Bits to Banking · Native Engineering · C23 tests and evidence quality**

## Why test refusal as carefully as success?

A service-readiness model can be dangerous if missing evidence is interpreted as success. For example, a backup may have been verified last month, but a learner may enter “yes” because a copy exists today. Our model records independent fields: latest backup verification, independent restore drill, source-revision identity, observation age, queue capacity, on-call assignment, alert route, estimated data loss and measured recovery duration. A missing or stale field produces an explicit review blocker.

The laboratory registers **29 new named policy tests plus one demo**. The previous 131 Update 39–44 tests remain registered because the existing CMake subprojects are imported. You should treat the number as an acceptance expectation, not as a claim about Windows until you have run CTest on your machine.

## Tests are contracts, not decorative green numbers

| Test name suffix | Input deliberately changed | What must happen |
|---|---|---|
| `missing-heartbeat` | No last healthy observation | Missing heartbeat bit set |
| `stale-backup` | Backup time outside the allowed age | Stale backup bit set |
| `stale-restore` | Restore drill too old | Stale restore bit set |
| `rpo` / `rto` | Measured values above policy limits | Separate objective-miss bits set |
| `queue` | More jobs waiting than allowed | Capacity bit set |
| `alert-owner` | Nobody assigned to respond | Owner-missing bit set |
| `source-mismatch` | Observation uses a different revision | Attach refused; prior review untouched |
| `invalid-flag` | Boolean field contains 7 | Evaluation refused; output untouched |
| `future-timestamp` | Evidence claims an event after observation | Attach refused |
| `cadence-overflow` | Due time exceeds `UINT64_MAX` | Calculation refused; destination unchanged |
| `upstream-restored` | Previous security review reports restored old version | `RESTORED_ONLY`, never new release success |
| `mutations` | 30,000 reproducible one-gate failures | None may become REVIEWABLE |

This mix matters: ordinary inputs test the happy path; malformed inputs test safety; missing evidence tests honesty; mutation tests repeatedly exercise refusal. A deterministic seed permits the same unexpected result to be reproduced under GCC and Clang.

## Run selected tests first

```powershell
Set-Location 'C:\umicom\Umicom-Bits2Banking'
ctest --test-dir '.\output\learning-build\operational-resilience' -R '^bits2banking\.operations\.(rpo|rto|source-mismatch|upstream-restored)$' --no-tests=error --output-on-failure
```

Use `ctest --test-dir ... -N` to list registered tests without executing them. `ctest` is a compiled native test driver controlled by CMake; we are not introducing a new PowerShell script.

## Failure-atomic review

The API commits a new record only after validation. In `test_operations.c`, compare a snapshot of `BtbOpsReview` before and after a rejected attach. In the `atomic-evaluate` test, prefill `BtbOpsDecision` with recognisable bytes; the invalid evaluation must leave it unchanged. A rejected result must not be mistaken for a blank or successful decision.

## One essential production distinction

The training model's time values are fictional logical seconds in one controlled domain. A production scheduler must distinguish wall-clock time and monotonic elapsed intervals, handle clock changes, and persist relevant results through the Framework's own services. This batch does not run a background process or perform a backup. It only teaches checked reasoning over supplied evidence.

**Assessment:** Explain why a successful `BtbOpsNextDue` call is not proof that a scheduled operation ran. Explain why restoring a previous service generation is a different result from the proposed release passing acceptance.

**Next:** [Chapter 315 — Complete operational review capstone](315-capstone-umicom-operational-review.md).
