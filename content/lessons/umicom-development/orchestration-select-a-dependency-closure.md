<!--
Umicom Bits2Banking
File: content/lessons/umicom-development/orchestration-select-a-dependency-closure.md

PURPOSE:
Select a task and its complete dependency closure

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->

# Select a task and its complete dependency closure

## Prepare the exercise

Install the matching Framework SDK and run these PowerShell commands separately. Use the scenario named in the lesson and stop on unexpected errors.

```powershell
Set-Location "C:\umicom\Umicom-Bits2Banking"
$env:Path = "C:\msys64\ucrt64\bin;$env:Path"
cmake -S .\labs\native\framework-task-orchestration -B .\build\framework-task-orchestration -G Ninja -DCMAKE_C_COMPILER=C:/msys64/ucrt64/bin/gcc.exe -DCMAKE_PREFIX_PATH=C:/umicom/installed/framework -DBUILD_TESTING=ON
cmake --build .\build\framework-task-orchestration --parallel 2
ctest --test-dir .\build\framework-task-orchestration --output-on-failure --no-tests=error
& .\build\framework-task-orchestration\btb-framework-task-orchestration.exe selected
```

Selected plans two tasks; parallel, retry and reject complete four; stop leaves three waiting tasks canceled after the active task finishes. These are modeled outcomes, not actual process results.

## Start from the requested result

A developer choosing link expects its prerequisites to be included without running every unrelated task. The orchestrator walks from the requested task through all transitive dependencies. Run selected in the lab: choosing left plans configure and left, while right and link remain outside the operation. Compare the planned count with the four descriptors in the source registry.

## Include shared prerequisites once

The full link plan forms a diamond: left and right both depend on configure, and link depends on both. Configure belongs in the plan once. An included marker records a completed traversal, while a visiting marker tracks the current unfinished path. Explain why using one marker for both facts would confuse a shared prerequisite with a cycle.

## Choose roots explicitly

A null or empty requested target selects every enabled root. A disabled task can still be included as a required prerequisite and begin skipped under the existing graph policy. The closure walk resolves dependencies it traverses, including those reached through a disabled prerequisite. Document this distinction when presenting an all-tasks command in a CLI or Studio panel.

## Review and recover

Verify installed headers, archive and compiler when a contract differs. Keep the selected scenario and failure line. Preserve real process evidence separately from any refused graph observation.

[Read the C exercise](https://github.com/umicom-foundation/Bits2Banking/blob/main/labs/native/framework-task-orchestration/main.c) · [Full setup and native commands](https://github.com/umicom-foundation/Bits2Banking/blob/main/labs/native/framework-task-orchestration/README.md) · [Shared contract](https://github.com/umicom-foundation/umicom-framework/blob/main/docs/learning/task-orchestration.md)

[Course contents](index.md) · [Previous lesson](task-graph-transactions-and-regression-evidence.md) · [Next lesson](orchestration-explicit-depth-first-frames.md)
