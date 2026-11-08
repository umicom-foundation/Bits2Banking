<!--
Umicom Bits2Banking
File: content/lessons/umicom-development/orchestration-parallel-slots-and-outcomes.md

PURPOSE:
Admit parallel work through one owning orchestrator

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->

# Admit parallel work through one owning orchestrator

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

## Count admitted operations

Run parallel. Configure completes before left and right start together. With maximum parallelism two, another next-ready request returns Busy while both slots are occupied. The count represents tasks admitted as running, not CPU cores measured by the service. Choosing a useful limit still requires the host to understand process and resource costs.

## Report completion through the owner

The host records each task completion through the orchestrator, which updates the graph, releases an active slot and recomputes terminal operation state. Updating the graph directly would leave those owner counters stale. Trace the sequence in main.c and identify the point at which link becomes ready after both branch outcomes are accepted.

## Keep process evidence outside the model

The lab supplies immediate fictional outcomes and starts no child process. A production runner would retain process handles, output and exit status in the supervisor, then report accepted observations. If recording an outcome is refused, preserve the real outcome for diagnosis; an unchanged graph does not roll back a process or its filesystem effects.

## Review and recover

Verify installed headers, archive and compiler when a contract differs. Keep the selected scenario and failure line. Preserve real process evidence separately from any refused graph observation.

[Read the C exercise](https://github.com/umicom-foundation/Bits2Banking/blob/main/labs/native/framework-task-orchestration/main.c) · [Full setup and native commands](https://github.com/umicom-foundation/Bits2Banking/blob/main/labs/native/framework-task-orchestration/README.md) · [Shared contract](https://github.com/umicom-foundation/umicom-framework/blob/main/docs/learning/task-orchestration.md)

[Course contents](index.md) · [Previous lesson](orchestration-owned-plans-and-source-edits.md) · [Next lesson](orchestration-stop-retry-and-finish.md)
