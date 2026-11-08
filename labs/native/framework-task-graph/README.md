<!--
Umicom Bits2Banking
File: labs/native/framework-task-graph/README.md

PURPOSE:
Use the installed Framework dependency graph to distinguish readiness, failures, retries and canceled work.

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->

# Rehearse a dependency-aware build workflow

This C23 consumer registers configure, build and test tasks, then reports fictional provider outcomes to the actual Framework graph. It does not invoke CMake, a compiler or any stored task command.

## Prepare and run

1. Install the matching Framework development SDK with the compiler and architecture used by this consumer.
2. Run each command below separately and stop on an unexpected error.
3. Repeat the final command with `fail`, `retry`, `cancel` and `reject`.

```powershell
Set-Location "C:\umicom\Umicom-Bits2Banking"
$env:Path = "C:\msys64\ucrt64\bin;$env:Path"
cmake -S .\labs\native\framework-task-graph -B .\build\framework-task-graph -G Ninja -DCMAKE_C_COMPILER=C:/msys64/ucrt64/bin/gcc.exe -DCMAKE_PREFIX_PATH=C:/umicom/installed/framework -DBUILD_TESTING=ON
cmake --build .\build\framework-task-graph --parallel 2
ctest --test-dir .\build\framework-task-graph --output-on-failure --no-tests=error
& .\build\framework-task-graph\btb-framework-task-graph.exe complete
```

Complete and retry end with three succeeded tasks. Fail records one failure and two blocked dependants. Cancel allows the already-running configure task to finish while the two waiting tasks remain canceled. Reject attempts a replacement with a missing dependency and checks that the running graph remains unchanged. The executable returns zero when its selected teaching scenario matches its expected state, even for the intentionally failed scenario.

## Read the shared implementation

`main.c` calls `task.h` and `task_graph.h` from the installed SDK. The registry owns task descriptions. The graph copies them and owns runtime state; it does not retain a live view of later registry edits. A successful rebuild replaces that snapshot. A refused rebuild leaves the previous source revision, tasks and state intact.

Runtime mutations stage compact state records before publishing, rather than copying the large task descriptions for every progress update. Revision exhaustion in a dependent node can refuse the whole proposed completion; the running task must then remain running in the model. The host should retain its real process outcome for diagnosis instead of reporting a contradictory graph success.

## Understand the policies

A skipped dependency counts as satisfied. A disabled task begins skipped. A failed dependency blocks later tasks unless that dependency has the continue-on-error flag. These are scheduling policies, not evidence that output files exist. Missing dependencies and cycles are checked among enabled tasks; disabled-only relationships are not executed and retain the existing permissive behavior. Recipe importers that require every declared relationship resolved must apply their own stronger admission policy before graph construction.

## Recover and extend

An undefined symbol or differing refusal behavior may indicate a stale installed SDK. Record the headers, archive, compiler and selected scenario before changing expected values. Read the failure line and review the immediate operation. A zero-test selection must be treated as missing coverage.

Add two independent compilation tasks and a link task that depends on both. Complete them in opposite orders and verify that link becomes ready only after both succeed. Then change one dependency to continue-on-error and explain why readiness still does not prove the linker will find valid inputs. Real build, test and cancellation evidence requires a supervised process provider and source-specific output verification.
