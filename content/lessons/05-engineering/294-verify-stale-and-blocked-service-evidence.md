# Chapter 294 — Verify stale, blocked and incomplete service evidence in C23

**Bits to Banking · Engineering track · ISO C23**

## Reliable software rejects false success

A program that reports READY for every input is not useful, even if it compiles with no warnings. A service-readiness evaluator is especially sensitive to false positives: an operator might act on the result and send work to a service that cannot complete it. Before adding threading, databases or a graphical status panel, we therefore test the fundamental invariants deterministically.

The new `test_readiness.c` registers named CTest cases. Test selection uses a command-line argument such as `stale` or `inherited-block`. Assertions are explicit check statements that fail with an error and line number; the suite does not depend on sleeps, a real Windows service, systemd, sockets or network timing.

## Tests we require

| Case | Initial facts | Required decision |
|---|---|---|
| `ready` | Store and app required checks pass in same capture | Both READY |
| `missing` | Required check has no observation | BLOCKED with missing count |
| `optional-warning` | Required passes; optional warning | REVIEW |
| `required-failure` | Required check fails | BLOCKED |
| `required-notrun` | Required check not executed | BLOCKED |
| `stale` | An earlier capture had passed | BLOCKED, stale count preserved |
| `inherited-block` | App passes but store fails | Both BLOCKED |
| `inherited-review` | Store is REVIEW and app passes | Both REVIEW |
| `missing-dependency` | Required predecessor is absent | Evaluation rejects graph |
| `cycle` | A depends on B, B on A | Evaluation rejects cycle |
| `duplicate` | Repeated service ID | Registration rejects and retains original |
| `capacity` | Attempt to register ninth service | FULL without overwriting |
| `invalid` | Invalid ID, name, self-dependency or capture | INVALID |
| `preserve` | Graph invalid when output contains sentinel bytes | Output bytes unchanged |
| `mutation` | 50,000 varied, reproducible evidence states | Invariants hold |
| `demo` | Fictional valid two-service graph | Output reports 2 READY |

The previous Update 39 laboratory contributes 16 further tests for evidence validation. Thus an integrated configuration should register **32** tests: 16 new and 16 regression tests. The test count is a qualification expectation for this specific CMake project, not a universal number of tests across Umicom.

## Why stale evidence is blocked

A requirement can pass for one observation session but become invalid for another. For example, storage was writable before a software upgrade, but we have not checked it since. Reusing the old PASS would misrepresent the current state. The graph stores the original observation's `captureId`, then compares it against the graph's expected `captureId`. A mismatch on a required check yields BLOCKED; a mismatch on an optional check yields REVIEW when mandatory checks pass.

```c
/* captureId 499 was observed yesterday; graph expects 500 today. */
BtbAdminObservation oldCheck = {
    1U, UINT64_C(499), BTB_ADMIN_PASS, "Earlier practice check"
};
```

Only the classroom evidence interpretation changes. No process is restarted and no filesystem is read. In a real system, capture identity must itself come from an appropriate trustworthy telemetry source and be bound to service identity and time.

## Failure atomicity

When the caller passes a malformed graph or a dependency cycle, the evaluator does **not** write a partially completed `BtbServiceSummary`. Internally it calculates into a local candidate, and assigns it to the caller's output only after all nodes have been checked. Tests put a known byte pattern in the output and compare its contents after a rejected call.

This matters because callers may keep showing the last known valid result while reporting that new evaluation failed. Whether they may act on that old result is a separate freshness-policy question. The UI must never silently label old data as the new result.

## Run a focused case

From PowerShell, after configuring and building the lab:

```powershell
ctest --test-dir ".\output\learning-build\service-readiness" -R "service-readiness.stale" --no-tests=error --output-on-failure
```

Run every registered test before completion:

```powershell
ctest --test-dir ".\output\learning-build\service-readiness" --no-tests=error --output-on-failure
```

When using a compiler with AddressSanitizer/UndefinedBehaviorSanitizer support, configure a separate build directory with supported instrumentation flags. Do not assume those flags or runtimes exist on every Windows compiler. The supplied validation report distinguishes verified Linux results from Windows acceptance that still must be run.

## Practical questions

1. If the graph evaluates successfully but a service is BLOCKED, should the command exit with a parsing error? **No.** The evaluation succeeded; the business/health decision is blocked.
2. If a cycle is detected, is it safe to accept a partial summary? **No.** Consumers could incorrectly appear ready before the cycle is discovered.
3. If a previous test passed on another commit, is this commit qualified? **No.** Test evidence must be bound to the correct revision and environment.
4. Does a seed-based mutation test prove all possible inputs? **No.** It covers a deterministic set of transitions; independent review and boundary tests remain required.

**Next:** [Chapter 295 — Complete system-administration capstone](295-capstone-support-incident-to-framework-readiness.md).
