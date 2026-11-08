<!--
Umicom Bits2Banking
File: content/lessons/umicom-development/task-graph-readiness-and-diamonds.md

PURPOSE:
Compute readiness across chains and diamonds

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->

# Compute readiness across chains and diamonds

## Prepare the exercise

Install the matching Framework SDK, then run these commands separately. Select the scenario named by the lesson and stop on an unexpected error.

```powershell
Set-Location "C:\umicom\Umicom-Bits2Banking"
$env:Path = "C:\msys64\ucrt64\bin;$env:Path"
cmake -S .\labs\native\framework-task-graph -B .\build\framework-task-graph -G Ninja -DCMAKE_C_COMPILER=C:/msys64/ucrt64/bin/gcc.exe -DCMAKE_PREFIX_PATH=C:/umicom/installed/framework -DBUILD_TESTING=ON
cmake --build .\build\framework-task-graph --parallel 2
ctest --test-dir .\build\framework-task-graph --output-on-failure --no-tests=error
& .\build\framework-task-graph\btb-framework-task-graph.exe complete
```

Complete and retry model three successes; fail models one failure and two blocked tasks; cancel leaves two waiting tasks canceled; reject preserves the running graph. These are task-state observations, not actual build results.

## Follow prerequisite edges

Configure must finish before build is ready, and build must finish before test. A dependency graph represents these relationships independently of how commands will later execute. Run complete and trace each ready task before recording its fictional success. The ordering is a property of dependencies and deterministic registry order, not the spelling of task IDs.

## Add a second branch

Extend the lab with compile-a and compile-b after configure, then make link depend on both. Complete the two compilations in opposite orders. Link must remain pending after only one succeeds. Record its satisfied dependency count and explain why that count changes before the scheduling state changes.

## Observe changes without losing them

A node revision identifies its observable runtime record. Updating a satisfied-dependency count while keeping the same revision can leave a UI showing stale detail. The shared graph advances that identity even when the node remains Pending. Consumers should compare revision identities rather than infer changes solely from the state label.

## Review and recover

Confirm the installed archive and headers when behavior differs. Preserve the selected scenario and assertion output. Do not change scheduling policies or expected counts merely to obtain a passing result.

[Read the C exercise](https://github.com/umicom-foundation/Bits2Banking/blob/main/labs/native/framework-task-graph/main.c) · [Full setup and native commands](https://github.com/umicom-foundation/Bits2Banking/blob/main/labs/native/framework-task-graph/README.md) · [Shared contract](https://github.com/umicom-foundation/umicom-framework/blob/main/docs/learning/task-graph-transactions.md)

[Course contents](index.md) · [Previous lesson](task-graph-rejected-replacement.md) · [Next lesson](task-graph-failure-and-skip-policy.md)
