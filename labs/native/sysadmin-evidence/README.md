# System-administration evidence — native C23 learning laboratory

This is a **teaching model**, not a host administrator, monitoring daemon, permission manager or automated deployment policy. It consumes caller-supplied, **fictional** observations and evaluates a declared set of required checks. It does not run shell commands, inspect accounts, read system logs, write files, open sockets, stop services or contact GitHub.

## Why this exercise exists

A learner may see a green `git status` but have an untested build; a service may be running while its database is unavailable; a backup may exist without having been restored. The model teaches why a support report must distinguish **PASS**, **WARNING**, **FAILURE**, **NOT RUN** and **STALE** evidence, and why missing required checks block readiness.

The caller owns the `BtbAdminReview`, its copied `BtbAdminObservation` records and `BtbAdminReport`. An observation carries a check ID, capture ID, state and short human-readable label. All inputs have fixed capacities. Invalid insertions or invalid evaluation preserve previous state and outputs. Required checks must be present, current and pass. Optional adverse evidence produces REVIEW. There is no auto-fix or authority to change a machine.

## Configure / build / test (Windows PowerShell 7)

```powershell
Set-Location "C:\umicom\Umicom-Bits2Banking"
$env:Path = "C:\msys64\ucrt64\bin;$env:Path"
cmake -S ".\labs\native\sysadmin-evidence" -B ".\output\learning-build\sysadmin-evidence" -G Ninja -DCMAKE_C_COMPILER="C:\msys64\ucrt64\bin\gcc.exe" -DBUILD_TESTING=ON
cmake --build ".\output\learning-build\sysadmin-evidence" --parallel 2
ctest --test-dir ".\output\learning-build\sysadmin-evidence" --no-tests=error --output-on-failure
& ".\output\learning-build\sysadmin-evidence\btb-sysadmin-evidence-demo.exe"
```

Expected: **16 CTest cases** and a demo decision of `REVIEW`. Run this in a personal learning checkout, not as an administrator. If a check is unavailable or skipped, say so; never substitute a previous build's results.

## Relation to Umicom Framework

For a real application, investigate Framework-owned `UmiVcsWorkingTreeRead`, `umi_build_automation_evaluate`, the existing diagnostic parser, audit, service-health and observability services first. A product should consume those contracts instead of promoting this classroom state machine into a competing production component. Moving this lesson's ideas into production requires an approved Framework contract and integration tests.

## Exercises

1. Identify the two **required** checks in `main.c` and explain why a warning on an optional check produces REVIEW rather than READY.
2. Edit the **fictional** backup observation in the demo from PASS to NOT_RUN. Predict BLOCKED and verify it.
3. Run the `stale` and `missing` tests. Explain how these differ from FAILURE.
4. Confirm that no source file contains calls to `system()`, service managers, Git commands or file-writing functions.
5. Answer: Why is this model insufficient to certify an actual Umicom OS release?
