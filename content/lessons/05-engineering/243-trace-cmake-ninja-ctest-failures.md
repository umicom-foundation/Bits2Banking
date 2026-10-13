# Chapter 243 — Trace CMake, Ninja and CTest failures by stage

**Bits to Banking · Engineering track · Umicom Foundation**  
**Primary language:** C23 · **Tools:** CMake, Ninja, CTest  
**Prerequisites:** Chapter 242 and a configured Umicom build preset.

## Why this matters

“Build failed” is not a sufficient diagnosis. A CMake configure failure, a C compiler error, a linker error, a test assertion, and a missing packaged DLL require different remedies. Rebuilding thousands of targets without identifying the failing stage can consume hours while hiding the original defect. In Umicom, Framework also has shared dependencies consumed by Studio, Trader and OS, so the location of a failure determines who owns the fix.

## Five stages to distinguish

| Stage | What it establishes | Example failure | First evidence to inspect |
|---|---|---|---|
| Configure | Target graph and toolchain can be described | Missing package or wrong CMake option | First `CMake Error` and cache/profile |
| Compile | C source translates to object files | Missing declaration or incompatible type | First `FAILED:` compile command and C diagnostic |
| Link | Objects and libraries resolve into binaries | `undefined reference` or duplicate symbol | Failing target and full linker command |
| Test | Executables satisfy expected behaviour | Assertion failure, segfault, `Not Run` | Named CTest failure and executable existence |
| Package | Runtime artefacts are complete | Missing DLL or resource | Installed staging tree and dependency check |

The stages do not imply that all failures are in source code. A stale CMake cache can select the wrong compiler. A GTK4 executable can link but still fail to launch outside MSYS2 because runtime dependencies were not bundled. A test that is `Not Run` is different from a test that executed and failed.

## Use the current project preset

From the Umicom Applications root, inspect available presets before invoking them:

```powershell
Set-Location "C:\umicom\Umicom-Applications"
cmake --list-presets
cmake --preset windows-ucrt64-all-debug -DBUILD_TESTING=ON
cmake --build --preset windows-ucrt64-all-debug --parallel 2
ctest --preset windows-ucrt64-all-debug --output-on-failure
```

These are **interactive PowerShell commands**, not a PowerShell automation script. Use the preset that is actually present in your checkout. Do not assume a preset from an older document is still supported. The first failed configure/build/test command is the primary evidence; a long list of later skipped targets is secondary.

## Map observations into the C23 model

`BtbEvidenceStage` records `CONFIGURE`, `COMPILE`, `LINK`, `TEST` and `PACKAGE`. This is a human-supplied or runner-supplied classification, not a guessed parse of stdout. `BtbEvidenceProblem.severity` separately captures the original tool's note/warning/error/fatal status.

The lab computes `earliestErrorStage` as the lowest stage *among retained error records*. It does **not** claim causal proof that the earliest visible diagnostic caused every later problem. A linker error can be downstream of a configuration mistake; only a reproducible investigation establishes causality.

## Guided recovery exercise

Take a disposable or known failing C23 build. First run configure and record its exit status. If it fails, stop; do not report the later compile phase as tested. If configuration succeeds, run the build. Record the first `FAILED:` target, compiler/linker command and exit result. If that succeeds, run CTest and classify each failed, skipped or not-run test separately. Finally, confirm whether an installed application launches without relying on a shell's temporary PATH.

For a native test that failed, obtain more detail with:

```powershell
ctest --test-dir ".\build\windows-ucrt64-all-debug" --output-on-failure -V
```

Check the `--test-dir` against the real build tree before executing. A non-existent directory is a command-location error, not a failed unit test.

## Assessment

**What does an `undefined reference` normally indicate?** The linker lacks a definition or target dependency; a source-level type check alone will not fix it. **What does CTest `Not Run` tell you?** That the registered test did not execute, often because its executable was missing. **When are build results valid for a Git commit?** When the test evidence corresponds to the exact source revision and configuration being reviewed.

**Next:** Chapter 244 makes that revision identity explicit.
