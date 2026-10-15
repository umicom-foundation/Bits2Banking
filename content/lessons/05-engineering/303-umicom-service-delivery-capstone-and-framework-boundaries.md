# Chapter 303 — Capstone: an Umicom service-delivery rehearsal with Framework ownership

**Bits to Banking · Native engineering · Umicom Foundation**  
**Scope:** A harmless local C23 demonstration and carefully recorded evidence. No production changes.

## The objective

A contributor is asked to deliver a fictional Umicom Notes training build. They should be able to explain the complete route from Git revision through build and tests to a private staged executable, identify which checks were **not performed**, and know where each reusable capability belongs in the Umicom architecture. The goal is a professional, reproducible workflow rather than a complicated installer.

![Delivery and evidence sequence](../../assets/diagrams/sysadmin-source-to-stage-update42.svg)

## 1. Establish source and repository state

Before editing anything, check the repository you are in and the branch you are using:

```powershell
Set-Location "C:\umicom\Umicom-Bits2Banking"
git status
git branch --show-current
git rev-parse HEAD
```

A repository can be clean and still be at the wrong revision. `git status` does not prove that Windows builds succeed, nor that submodules are at their intended commits. For any Framework change, consult the Framework-owned read-only VCS and submodule verification facilities first. **This batch does not modify Framework, Applications or OS.**

## 2. Configure and run the existing native tests

```powershell
$env:Path = "C:\msys64\ucrt64\bin;$env:Path"
cmake -S ".\labs\native\deployment-rehearsal" -B ".\output\learning-build\deployment-rehearsal" -G Ninja -DCMAKE_C_COMPILER="C:\msys64\ucrt64\bin\gcc.exe" -DBUILD_TESTING=ON
cmake --build ".\output\learning-build\deployment-rehearsal" --parallel 2
ctest --test-dir ".\output\learning-build\deployment-rehearsal" --no-tests=error --output-on-failure
```

The new CMake project links previous C23 owners from Updates 39–41 rather than copying or rewriting them. Check the full CTest summary and record *your* actual test count, failures and ignored/skipped cases. A failed test is not the same thing as a test not run.

## 3. Stage the output inside a private directory

```powershell
Test-Path "C:\umicom\learning-stage-update42"
cmake --install ".\output\learning-build\deployment-rehearsal" --prefix "C:\umicom\learning-stage-update42"
& "C:\umicom\learning-stage-update42\bin\btb-deployment-review-demo.exe"
```

**Before executing** the install command, confirm that the target directory is appropriate and does not contain important files. A private prefix avoids system-level writes and is not an operating-system installer.

Record the output. The demonstration prints a fictional `PENDING` decision and then a fictional `QUALIFIED` result based on supplied training values. Those strings do not mean a cryptographic hash was computed, a service was deployed or that Umicom OS booted.

## 4. Document the safety evidence

Create a short engineering note in your preferred text editor with these fields (no new PowerShell or Python script is required):

| Field | Example of what to record |
|---|---|
| Source revision | Actual `git rev-parse HEAD` from your learning checkout |
| Build profile | Selected compiler and CMake build directory |
| Tests | Exact number passed, failed, skipped or not run |
| Stage destination | Approved private `learning-stage-update42` directory |
| Staged execution | Exit code and key demonstration output |
| Host impact | No service, user, disk partition or system setting changed |
| Unverified | Real package signature, production installer, OS boot and service availability |

This difference between **observed results** and **unverified claims** is part of the assessment.

## 5. Map each production responsibility to its Framework owner

Do not lift the teaching library into Umicom Framework without source inspection and an approved design. The production system already has reusable contracts that must be reused or extended when needed: VCS working-tree observations, submodule locks, automated build planning, compiler diagnostics, platform processes, application manifests and release packaging. Umicom Studio should consume those services; Umicom OS should use them in normal user space. The Kernel and recovery environment have independent privileged responsibilities.

`BtbDeploymentReview` is not a native installer, checksum utility, scheduler, service manager or Git integration. It is an **offline evidence model** that shows which facts would have to be supplied by their real owners.

## 6. Commit the Bits2Banking learning update

Only after reviewing the merge and confirming that the current branch is `main`:

```powershell
git status
git branch --show-current
git add -A
git diff --cached --check
git diff --cached --stat
git diff --cached
git commit -m "feat(learning): add virtual machines and C23 deployment rehearsal"
git push origin main
git status
```

`git add -A` stages every modification and deletion in this repository. Review the diff before committing; the exercise does not give permission to publish unrelated changes or secrets. If a push is rejected, inspect the local and remote history rather than using a force push.

## Capstone questions

1. Why is a private CMake installation safer for beginners than a system-wide package installation?
2. What does `BTB_DEPLOYMENT_STALE_CAPTURE` protect the teaching review from?
3. Why does a restored baseline not count as a successful upgrade?
4. Why must a real Framework VCS service be reused instead of creating a new app-local Git parser?
5. What evidence would be needed to say that an Umicom OS image actually booted in QEMU?

### Suggested answers

1. It confines the changed files to a known owned directory without elevated permissions.
2. It prevents older stage or verification observations from qualifying a newer change.
3. The new release failed; independent restoration merely re-established an earlier safe state.
4. Reusing a canonical owner prevents divergent behaviour, duplicated parsing and uncontrolled security boundaries.
5. A known source/image revision, reproducible build, actual QEMU invocation, serial boot output, guest checks and explicit success criteria.

**Next:** Update 43 will extend the course into further infrastructure administration, secure remote access and production-observation concepts while retaining the native Framework-first policy.
