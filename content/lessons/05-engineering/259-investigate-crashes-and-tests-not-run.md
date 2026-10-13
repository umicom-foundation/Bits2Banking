# Chapter 259 — Investigate native crashes, timeouts and CTest “Not Run”

**Bits to Banking · Engineering track · Umicom Foundation**  
**Primary language:** C23 · **Prerequisites:** diagnostics, process exit codes and memory ownership.

## A crash is not a compilation failure

A completed C23 compile can still produce a program that dereferences an invalid pointer, uses storage after its lifetime, corrupts a stack buffer or deadlocks during shutdown. A failing GUI process, a CTest timeout and a test marked *Not Run* require different investigations. Recording them all as “one failed test” hides essential information.

On Windows, `0xC0000409` commonly indicates a fail-fast termination but is not a proof of which source line is faulty. A `SegFault` label from CTest indicates a fault while executing a test, not the cause. On Linux, SIGSEGV and SIGABRT likewise need stack traces and source-level evidence before correction. Do not infer that every memory crash is a simple null-pointer bug.

## Case study: an Umicom Studio test does not start

Suppose the `studio.workspace` test executable is absent because an earlier Framework library failed to link. CTest may report the test as *Not Run*. This is not a test that passed and not necessarily a failing assertion inside Studio. Inspect the build error and target generation before changing test source. If another test **does** start and crashes, preserve its command line, exact arguments, environment, executable SHA and debugger backtrace.

Use these read-only and test commands after choosing the correct configured preset:

```powershell
Set-Location "C:\umicom\Umicom-Applications"
cmake --list-presets
ctest --preset windows-ucrt64-all-debug --show-only
ctest --preset windows-ucrt64-all-debug --output-on-failure
```

If that preset does not exist, consult the current repository rather than copying the name blindly. `--show-only` enumerates tests; it does not run them. The full CTest output is evidence and should be retained even when it is large.

## Native sanitizers versus debugger traces

AddressSanitizer can identify many out-of-bounds accesses, use-after-free and double-free bugs under a supported Clang/GCC build. UndefinedBehaviorSanitizer can detect selected undefined operations such as invalid signed arithmetic or shifts. They do not cover every race, lifetime or GUI correctness problem. A sanitizer-passing educational library does not prove the entire Windows application works. Build sanitizer configurations in separate directories; do not mix instrumented and ordinary objects without a deliberate plan.

Example Linux configuration for this C23 lab:

```sh
cmake -S labs/native/change-impact -B output/learning-build/change-impact-asan -G Ninja \
  -DCMAKE_C_COMPILER=clang \
  -DCMAKE_C_FLAGS='-fsanitize=address,undefined -fno-omit-frame-pointer -g' \
  -DCMAKE_EXE_LINKER_FLAGS='-fsanitize=address,undefined' -DBUILD_TESTING=ON
cmake --build output/learning-build/change-impact-asan --parallel 2
ctest --test-dir output/learning-build/change-impact-asan --output-on-failure
```

These commands require an available compatible Clang sanitizer runtime. They do not use Python, PowerShell scripting or shell implementation logic in the source project.

## Preserve before fixing

When a test crashes, record the exact reproduction and which revision was built. Capture the original backtrace and trace the first invalid state change rather than immediately rewriting the largest affected `.c` file. The Umicom source-preservation rule is to retain existing public contracts, functions, comments and features; preserve superseded implementation in an explicitly disabled block when a replacement makes it uncallable and obtain approval before physical deletion.

A minimal corrective change is easier to review than a broad “cleanup” during a regression investigation. Recompile the affected target, rerun its focused test, run adjacent regressions and then the complete required suite. Mark unexecuted platform gates as not run. Only after evidence is complete should the repository owner consider merging/publishing.

## Practical negative tests

```powershell
Set-Location "C:\umicom\Umicom-Bits2Banking"
& ".\output\learning-build\change-impact\btb-change-impact-test.exe" assess_not_run
& ".\output\learning-build\change-impact\btb-change-impact-test.exe" assess_failed
& ".\output\learning-build\change-impact\btb-change-impact-test.exe" assess_incomplete_log
```

Each test passes if the evaluator refuses an incomplete release conclusion. This is not an intentionally crashing program; it is a safe simulation of evidence states.

**Exercises:** For a Windows fail-fast exit and a CTest *Not Run* result, write separate five-step triage procedures. Explain why a missing executable calls for checking build targets before inspecting application assertion code. Identify what a real stack trace contributes that a generic exit code cannot.

**Next:** combine these diagnostic practices with safe Git submodule recovery and the required direct-to-main workflow.
