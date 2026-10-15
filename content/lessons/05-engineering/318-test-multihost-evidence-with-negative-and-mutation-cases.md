# Chapter 318 — Verify C23 multi-host evidence with negative and mutation tests

**Bits to Banking · Engineering track · Umicom Foundation**  
**Code:** `fleet_readiness.c`, `fleet_fixture.c`, `test_fleet.c`, `CMakeLists.txt`.

## Test what must not happen

A security-conscious or operational review is often easier to validate by looking at the cases that must be refused. The Update 46 tests exercise invalid host names, duplicate host identities, unknown hosts, truncated or invalid revision values, wrong package digests, future-dated observations, stale observations and unauthorised or unverified status flags. The C23 API bounds the host collection at four. This is a teaching capacity, not a production sizing recommendation.

The code also checks **failure-atomicity**. For example, if a caller supplies a malformed new host, `BtbFleetAttach` must leave the existing review unchanged. One test copies the complete structure before the attempted operation, calls the function and compares the bytes afterwards. Such byte comparisons are appropriate here because both values were copied from the same initial object representation; the operation did not create separate objects with uninitialised padding to compare as independent semantic values.

`BtbFleetEvaluate` likewise builds a temporary decision and copies it only on success. An invalid boolean encoded as 3 must not overwrite the caller's previous decision. This matters in a GUI that displays the last valid review alongside a separate error message. A failed parsing or inspection operation must not silently change the recorded pass/fail status.

## Structured tests and deterministic mutations

The CMake file registers one CTest test per scenario. This enables a learner to run only `bits2banking.fleet.stale` or only `bits2banking.fleet.atomic-evaluate`, then inspect the failure without reading all tests at once. The mutation case runs **30,000 deterministic transitions** under one known integer generator; it deliberately changes flags and timestamps without sleeping, creating threads or connecting to network services.

```powershell
Set-Location "C:\umicom\Umicom-Bits2Banking"
ctest --test-dir ".\output\learning-build\fleet-readiness" -R "^bits2banking\.fleet\." --no-tests=error --output-on-failure
ctest --test-dir ".\output\learning-build\fleet-readiness" -R "atomic|stale|revision|package" --no-tests=error --output-on-failure
```

CTest by itself is a runner, not evidence that the test is meaningful. Look at the code to see the assertion and compare it with the documented contract. A previously passing Linux test is not proof that Windows UCRT64 now passes. Report Windows as a separate acceptance gate.

## Inspect the boundary in the debugger

Set a breakpoint at `BtbFleetEvaluate` and inspect `review->observedCount`, `next.issues`, `next.missingCount`, the host `operations` status and the final decision. Verify that `ValidHost` is run before the output changes. With a deliberately malformed `hostId`, the function should refuse evaluation rather than create a plausible `REVIEWABLE` result.

## Assessment

1. Why must `observedSeconds > reviewTimeSeconds` be checked before subtracting unsigned integers? **To avoid wraparound, which could turn future timestamps into plausible ages.**
2. Why does failure-atomicity matter? **An invalid new observation must not corrupt the last valid review.**
3. Can this test prove the Umicom OS boots? **No. It is a hosted C23 offline model, not a boot test.**
4. Is a test run valid if one registered test is Not Run? **No. Inspect configuration and registration; do not quietly exclude it.**

**Next:** Chapter 319 relates the educational demonstration to the actual Framework and OS engineering boundaries.
