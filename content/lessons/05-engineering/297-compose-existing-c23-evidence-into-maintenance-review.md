# Chapter 297 — Compose existing C23 evidence into maintenance review

**Bits to Banking · Engineering track · Umicom Foundation**  
**Author:** Sammy Hegab · ISO C23  
**Laboratory:** `labs/native/maintenance-review`.

## Why three libraries are better than one replacement

Update 39 introduced one owner for evidence records. Update 40 used those records to decide whether dependent services were ready. In Update 41, a small additional module models a *planned change*. Reimplementing the same evidence validation or copying previous C source into another folder would invite subtle inconsistencies. Instead, the CMake configuration links libraries in dependency order:

```text
btb-sysadmin-evidence-lib   (Update 39)
            ↑
btb-service-readiness-lib  (Update 40)
            ↑
btb-maintenance-review-lib (Update 41)
            ↑
     demo and tests
```

Notice that the arrow points toward the caller depending on an existing contract; it does not transfer authority for a production host to the teaching programme. This remains one process and one serial execution context. None of these three libraries requires Python, PowerShell automation, a network server or an external database.

## Understand the public state machine

Read `maintenance_review.h` before the implementation. `BtbMaintenanceState` distinguishes `PLANNED`, `APPROVED`, `STARTED`, `VERIFIED`, `ROLLBACK_REQUIRED`, `COMPLETE`, `RESTORED` and `CANCELLED`. The distinction between `COMPLETE` and `RESTORED` is intentionally strong. The first means the post-change checks passed; the second means the simulated recovery condition passed after a failed change. We must never mark a failed upgrade as successful simply because the earlier state was recovered.

```c
/* A review can finish successfully only after post-change checks pass. */
BtbMaintenanceResult BtbMaintenanceComplete(BtbMaintenanceReview *review)
{
    if (review == NULL || review->state != BTB_MAINTENANCE_VERIFIED)
        return BTB_MAINTENANCE_STATE_ERROR;
    review->state = BTB_MAINTENANCE_COMPLETE;
    return BTB_MAINTENANCE_OK;
}
```

This code is an actual excerpt from the new library. It cannot silently promote `ROLLBACK_REQUIRED` to `COMPLETE`. The caller can inspect the returned result and display a clear educational explanation.

## Memory ownership and failure atomicity

Every input summary is copied by value. A caller may safely destroy its temporary service graph after evaluation. Functions that may reject an operation construct and validate a candidate before assigning the new value. If a new capture reuses the baseline capture ID, if a service ID disappeared, or if a caller's counters contradict its entries, the function refuses the update and preserves the previous review.

A capture ID is *not* an authentication token or a timestamp. It is an identifier for one teaching observation session. A real Framework-owned evidence service would supply trustworthy identity, timestamps, provenance and access control. This example merely prevents accidental mixing of those already supplied values.

## Complete Windows build — interactive commands only

```powershell
Set-Location "C:\umicom\Umicom-Bits2Banking"
$env:Path = "C:\msys64\ucrt64\bin;$env:Path"
cmake -S ".\labs\native\maintenance-review" -B ".\output\learning-build\maintenance-review" -G Ninja -DCMAKE_C_COMPILER="C:\msys64\ucrt64\bin\gcc.exe" -DBUILD_TESTING=ON
cmake --build ".\output\learning-build\maintenance-review" --parallel 2
ctest --test-dir ".\output\learning-build\maintenance-review" --no-tests=error --output-on-failure
```

These commands must be typed into PowerShell; they are **not** saved as a `.ps1` script. The configure step requires the earlier Update 39 and 40 directories. If the prerequisite is absent, CMake fails with an explanation rather than inventing or copying dependencies.

## Read the demonstration output

```powershell
& ".\output\learning-build\maintenance-review\btb-maintenance-review-demo.exe"
```

The demonstration first records a fictional failure and reports `ROLLBACK_REQUIRED`. It then uses a different passing capture and reports `RESTORED`. It neither installs software nor restores actual files. A zero exit status means that the *educational state transitions* behaved as expected.

## Where students should put breakpoints

Open `maintenance_review.c` in an editor. Find `BtbMaintenanceObserveAfter`; inspect the `before.captureId`, `after.captureId`, `SameServices` result and `FullyReady` decision. Watch the value of `candidate.state` before the final copy to the caller. Then put a breakpoint in `BtbMaintenanceConfirmRestored` and observe why the restored capture must differ from both the baseline and failed post-change capture.

## Exercises and answers

1. **Design:** Can the review record borrow a pointer to a temporary `BtbServiceSummary`? **Answer:** No; the summary may go out of scope, so the public contract copies the value.
2. **Debugging:** Why does the module reject a fabricated service ID? **Answer:** It would claim post-change verification of a different service population.
3. **Security:** Is recording `ReviewerB` enough to satisfy production maker/checker? **Answer:** No; the labels are a simulation, not authenticated approval.
4. **Systems:** Could the same model be used for Windows and Linux teaching? **Answer:** Yes, because it consumes OS-neutral evidence and performs no host operations.

**Next:** [298 — Test failed changes and restoration](298-test-failed-changes-and-independent-restoration.md).
