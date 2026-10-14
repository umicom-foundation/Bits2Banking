# Chapter 298 — Test failed changes and independent restoration

**Bits to Banking · Engineering track · Umicom Foundation**  
**Author:** Sammy Hegab · ISO C23  
**Laboratory:** `labs/native/maintenance-review`.

## A negative test is not a failed test

In professional engineering, a test often sends invalid input on purpose. Suppose the maintenance model receives the same capture ID before and after a change. The expected behaviour is to **reject** the request. When the implementation rejects it without altering any stored state, the *test itself passes*. This distinction is important for learners interpreting CTest, compiler diagnostics and service alerts.

The new module registers independent CTest scenarios for invalid baselines, source-revision syntax, distinct reviewer identity, verified backups, explicit rollback plans, state transitions, fresh post-change captures, changed service populations, failed checks, restoration and bounded reporting. Earlier Update 39 and 40 tests remain registered through their existing CMake targets.

## Four properties we want to prove

**First, a complete baseline.** All service entries have unique bounded IDs, internally consistent counts and current READY outcomes. A failed or truncated baseline is rejected before an educational change record is established.

**Second, a controlled transition.** A change moves from PLANNED to APPROVED only when the claimed backup and rollback preconditions exist and the reviewer label differs from the operator label. The change cannot start directly from PLANNED.

**Third, new post-change evidence.** The same service identities must be checked again under a distinct capture ID. A WARNING, FAILURE or missing prerequisite prevents a clean COMPLETE result.

**Fourth, independent recovery.** The restoration record must contain a third capture ID, separate from the baseline and failed post-change observation. A passing restore can be recorded as RESTORED but never relabelled as a successful upgrade.

## Verify one case at a time

From the Bits2Banking root after building the laboratory:

```powershell
ctest --test-dir ".\output\learning-build\maintenance-review" -R "^bits2banking\.maintenance-review\.(ready-post|blocked-post|recovery-success|preserve)$" --output-on-failure
```

The regular expression selects four cases by name. `ready-post` accepts a healthy new capture. `blocked-post` turns failed prerequisite evidence into a required-recovery state. `recovery-success` accepts a separately verified recovered condition. `preserve` deliberately provides inconsistent counters and checks that the previous record remains unchanged.

Then run the full suite:

```powershell
ctest --test-dir ".\output\learning-build\maintenance-review" --no-tests=error --output-on-failure
```

The complete project includes **57 registered tests**: the 16 existing evidence cases, 16 readiness cases, and 25 new maintenance cases (24 named scenarios plus the demonstration). An absent test executable must be reported as Not Run, not counted as a pass. If your local result differs, compare the actual CMake configuration and CTest registration before accepting the batch.

## Why we test preserved output

Consider a caller that already has a valid record. A new observation arrives but contains a mismatched service ID. If the implementation overwrote half the record before discovering the problem, the user might see a misleading mix of the old and new run. The test copies the entire review record before the call, submits malformed evidence and compares the complete record afterward. This verifies **failure atomicity**: invalid requests have no externally visible partial effect.

The exact educational comparison uses memory for caller-owned structures initialised predictably within the tests. In production systems, padding bytes and serialisation need additional care; comparing structures byte-for-byte is not automatically a portable persistence format.

## Deterministic mutation exercise

The `mutation` scenario runs 30,000 repeated changes with an explicitly seeded generator. Each iteration creates a fresh educational baseline and supplies either passing or adverse post-change evidence. If every service is ready, the model must enter VERIFIED. Otherwise it must enter ROLLBACK_REQUIRED. The generator does not depend on wall-clock time, network traffic or thread scheduling, making failures reproducible.

Do not confuse this deterministic stress exercise with arbitrary-input fuzzing, a proof of thread safety or a claim that actual Windows services were tested. It is one layer of verification for the offline model.

## Troubleshooting a failure

If CMake reports that `service-readiness` is missing, merge Update 40 before compiling Update 41. If it reports missing `sysadmin-evidence`, merge Update 39 first. If the compiler cannot find `service_readiness.h`, inspect the existing target link and include paths; do not copy the header into this lab. If one CTest case fails, run it alone and inspect the first assertion. Do not delete an existing test simply to obtain a green report.

## Review questions

1. Why should an invalid post-change capture leave the previous record intact?
2. What does `ROLLBACK_REQUIRED` represent that `CANCELLED` does not?
3. Why is a new capture identifier necessary after recovery?
4. What does 57/57 passing prove, and what important claims does it **not** prove?

**Answers:** (1) It prevents mixed or misleading evidence. (2) A started simulated change failed verification; cancellation is allowed only before start. (3) Recovery is a separate observation. (4) It proves the registered teaching cases passed on the tested host; it does not prove a real service was upgraded or restored.

**Next:** [299 — Framework ownership and OS verification](299-framework-ownership-and-os-change-capstone.md).
