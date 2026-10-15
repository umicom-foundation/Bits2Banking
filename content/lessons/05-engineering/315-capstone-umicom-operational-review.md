# Chapter 315 — Capstone: a Framework-first Umicom operational review

**Bits to Banking · Native Engineering · Umicom Foundation**  
**Laboratory:** `labs/native/operational-resilience`  
**Prerequisites:** [System Administration Chapter 108](../08-system-administration/108-capstone-seven-day-operations-plan.md) and engineering Chapters 312–314.

## Assignment

You are supporting a fictional Notes deployment for an educational team. The revision and security-review record have been supplied, and a daily operations check is due. The owner wants a clear recommendation that does not obscure missing evidence or a failed upgrade. Do not connect to a real Umicom service: the objective is to apply C23 contracts and operational reasoning.

## Step 1 — Build the complete dependency chain

Use a merged Bits2Banking checkout containing Updates 39–45. From PowerShell 7, type each command separately:

```powershell
Set-Location 'C:\umicom\Umicom-Bits2Banking'
$env:Path = "C:\msys64\ucrt64\bin;$env:Path"
cmake -S '.\labs\native\operational-resilience' -B '.\output\learning-build\operational-resilience' -G Ninja -DCMAKE_C_COMPILER='C:\msys64\ucrt64\bin\gcc.exe' -DBUILD_TESTING=ON
cmake --build '.\output\learning-build\operational-resilience' --parallel 2
ctest --test-dir '.\output\learning-build\operational-resilience' --no-tests=error --output-on-failure
```

The complete test registration should contain **161 named cases** (131 previous + 30 new) when every earlier C23 lab is present. Your actual host results take precedence over this expectation. Record the compiler version, CMake configure result, build warnings, count and names of failures; do not call a not-run test a pass.

## Step 2 — Observe the non-operational demo

```powershell
& '.\output\learning-build\operational-resilience\btb-operations-demo.exe'
```

You should see a fictional reviewable baseline, a blocked case with an unassigned owner, a calculated logical due time and a `RESTORED_ONLY` case. The demo is not a system administration tool. It does not start a process, touch Git or inspect backup files.

## Step 3 — Explain the boundary chain

Read these original headers in order:

1. `labs/native/sysadmin-evidence/admin_evidence.h` — observation vocabulary.
2. `labs/native/service-readiness/service_readiness.h` — readiness model.
3. `labs/native/maintenance-review/maintenance_review.h` — maintenance outcomes.
4. `labs/native/deployment-rehearsal/deployment_review.h` — deployment evidence.
5. `labs/native/remote-access-review/remote_access_review.h` — access review.
6. `labs/native/security-operations-review/security_operations_review.h` — security review.
7. `labs/native/operational-resilience/operations_review.h` — this batch's additional gates.

Explain how each layer adds one review responsibility while preserving previous source. If a type name or signature differs from the documentation, prefer the header in your checked-out repository and report the discrepancy; do not invent a replacement type.

## Step 4 — Apply a change to a fictional observation

Use a debugger to set `review.evidence.onCallOwnerAssigned = 0` after fixture setup. Re-evaluate and confirm the decision includes `BTB_OPS_ON_CALL_UNASSIGNED`. Then examine the `upstream-restored` test and identify why the status cannot become REVIEWABLE. Do not change source only to make an unsafe condition pass.

## Step 5 — Create a review record

Write one page with service name, fictional source revision, observation capture, source of upstream security evidence, proposed change, unmet gates, response owner, next approved action and the difference between a failed update and restoration. If a gate was not actually tested, mark it *Not verified*. No real credentials or live host addresses belong in the submission.

## Assessment

**What was tested?** Only the C23 classroom logic on the observed compiler/test host. **What was not tested?** Real systemd/Windows service management, host credentials, SSH, backups, live Framework deployment and operating-system recovery. **Who may approve a real action?** Only the authorised administrator or change authority. **Where should reusable implementation eventually live?** In existing Umicom Framework contracts, extended natively and reviewed rather than copied into teaching apps.

**Next milestone:** more advanced system-administration coursework on multi-host operations, backup evidence and integration with authorised Framework service observations.
