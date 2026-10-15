# C23 operational resilience review — teaching laboratory

**Owner:** Bits2Banking learning project, Umicom Foundation · Sammy Hegab · MIT

This laboratory composes the existing C23 libraries from Updates 39–44. It **does not** implement a real operating-system scheduler, monitoring collector, backup tool or access-control engine. It evaluates strictly fictional, caller-provided observations to teach how a source revision, security evidence, recovery objectives, response owner, timeliness and queue capacity affect review decisions. The new model calls `BtbSecurityEvaluate` rather than copying the previous security-operations implementation. Any production version should reuse the corresponding Umicom Framework capabilities after a separate design review and test campaign.

## Native contracts

- `BtbOpsInit` copies a reviewed policy and upstream security review, with matching service and source identity. Invalid input leaves the caller's review untouched.
- `BtbOpsAttach` copies one complete fictional observation and refuses mismatched revisions, future timestamp claims, bad flags and duplicate records.
- `BtbOpsEvaluate` derives a **bitmask** of missing or exceeded checks; it never administers a service. An upstream `RESTORED_ONLY` result cannot become a successful upgrade.
- `BtbOpsNextDue` demonstrates arithmetic for a periodic schedule, but does not start a timer or create a background task. An overflow is rejected without changing the destination.
- Logical times are unitless simulated **seconds in one clock domain**. Do not compare host wall clocks with monotonic elapsed-time counters in a real service.

## Configure, build, test

From PowerShell 7 after merging Updates 39–44:

```powershell
Set-Location 'C:\umicom\Umicom-Bits2Banking'
$env:Path = "C:\msys64\ucrt64\bin;$env:Path"
cmake -S '.\labs\native\operational-resilience' -B '.\output\learning-build\operational-resilience' -G Ninja -DCMAKE_C_COMPILER='C:\msys64\ucrt64\bin\gcc.exe' -DBUILD_TESTING=ON
cmake --build '.\output\learning-build\operational-resilience' --parallel 2
ctest --test-dir '.\output\learning-build\operational-resilience' --no-tests=error --output-on-failure
& '.\output\learning-build\operational-resilience\btb-operations-demo.exe'
```

On Linux, omit the Windows compiler path and use a supported local GCC or Clang. Build output stays under `output/learning-build`, not under repository source. Preserve the prior labs; do not replace them with abbreviated copies.

## Acceptance interpretation

Test success means that the **offline policy model** handles its declared scenarios. It is **not evidence** that a real backup restored, a certificate is valid, a service responds, or an administrator has approved a change. A `REVIEWABLE` result is not deployment permission. The CMake project imports all previous CTest registrations for regression visibility.
