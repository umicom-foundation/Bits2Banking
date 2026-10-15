# Major Update 42 — native C23 deployment review

**Author:** Sammy Hegab · Umicom Foundation · MIT

This *educational* laboratory extends Updates 39, 40 and 41 **without copying their implementations**. The new source `deployment_review.c` evaluates release-stage metadata alongside the existing `BtbMaintenanceReview`. It does **not** inspect the actual host, hash a file, install software, register services, create accounts, change Git state, run QEMU or claim that a production release is safe.

Every digest is an externally supplied **claim**. A flag saying a hash was compared represents fictional lesson evidence; students must not confuse it with a computation performed by this model. In real software, Umicom Framework should own package integrity, process supervision, VCS state, build automation, security and release verification.

## Windows PowerShell 7: configure, build, test

```powershell
Set-Location "C:\umicom\Umicom-Bits2Banking"
$env:Path = "C:\msys64\ucrt64\bin;$env:Path"
cmake -S ".\labs\native\deployment-rehearsal" -B ".\output\learning-build\deployment-rehearsal" -G Ninja -DCMAKE_C_COMPILER="C:\msys64\ucrt64\bin\gcc.exe" -DBUILD_TESTING=ON
cmake --build ".\output\learning-build\deployment-rehearsal" --parallel 2
ctest --test-dir ".\output\learning-build\deployment-rehearsal" --no-tests=error --output-on-failure
& ".\output\learning-build\deployment-rehearsal\btb-deployment-review-demo.exe"
```

### Optional private installation rehearsal

```powershell
cmake --install ".\output\learning-build\deployment-rehearsal" --prefix "C:\umicom\learning-stage-update42"
Test-Path "C:\umicom\learning-stage-update42\bin\btb-deployment-review-demo.exe"
& "C:\umicom\learning-stage-update42\bin\btb-deployment-review-demo.exe"
```

This `cmake --install` action writes only the named private prefix. Check the path first; do not run as administrator. If you already use that directory for important data, choose another empty practice location.

## Linux

```bash
cmake -S labs/native/deployment-rehearsal -B output/learning-build/deployment-rehearsal -G Ninja -DCMAKE_BUILD_TYPE=Debug -DBUILD_TESTING=ON
cmake --build output/learning-build/deployment-rehearsal --parallel 2
ctest --test-dir output/learning-build/deployment-rehearsal --no-tests=error --output-on-failure
./output/learning-build/deployment-rehearsal/btb-deployment-review-demo
cmake --install output/learning-build/deployment-rehearsal --prefix "$HOME/umicom-learning-stage"
```

## Source ownership

- Update 39 `BtbAdminReview`: required/optional check observations.
- Update 40 `BtbServiceGraph`: dependency-aware service readiness.
- Update 41 `BtbMaintenanceReview`: approval, changed-service observations and restoration state.
- Update 42 `BtbDeploymentReview`: package/build/staging evidence **only**.

`BTB_DEPLOYMENT_RESTORED_ONLY` means the previous state has been reported restored; it must never be misrepresented as a successful newly deployed release. An invalid operation preserves the entire previous review or output. Values are copied and owned by the caller. Thread safety is not provided.

## Exercises

1. Run `btb-deployment-review-test missing-runtime` and explain why a completed fictional maintenance change is still blocked from release qualification.
2. Run `rollback` and `restored`. Explain why the two decisions are distinct from `QUALIFIED`.
3. Identify exactly where `stageCaptureId` and `verificationCaptureId` are checked for freshness.
4. Demonstrate that the source tree contains no `.py` or `.ps1` implementations in this update.
5. Explain why calculating a real SHA-256 digest and verifying a signed package would be separate **Framework-owned** production responsibilities.
