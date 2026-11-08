<!--
Umicom Bits2Banking
File: content/lessons/umicom-development/task-graph-cancellation-and-process-ownership.md

PURPOSE:
Cancel waiting work while preserving running-process ownership

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->

# Cancel waiting work while preserving running-process ownership

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

## Cancel what the graph owns

Run cancel. Configure is already running in the model, so cancel-waiting changes only build and test. The example then records configure success. The final counts are one succeeded and two canceled tasks. This behavior lets a supervising host stop scheduling new work while it handles the process already in flight.

## Do not confuse state with interruption

The task graph does not own an operating-system process handle. Marking a node Cancelled does not kill a compiler or roll back a file write. The process supervisor must request cancellation, collect its terminal outcome and then report evidence to the graph. Explain the difference between a stop request and a confirmed process exit.

## Handle a refused observation

A completion can affect several dependent records. If one needed revision cannot advance, the entire graph transition is refused and prior state remains visible. Preserve the real process result in the host even though the graph could not record it. Never reinterpret that refusal as proof that the external process is still executing or that its effects were undone.

## Review and recover

Confirm the installed archive and headers when behavior differs. Preserve the selected scenario and assertion output. Do not change scheduling policies or expected counts merely to obtain a passing result.

[Read the C exercise](https://github.com/umicom-foundation/Bits2Banking/blob/main/labs/native/framework-task-graph/main.c) · [Full setup and native commands](https://github.com/umicom-foundation/Bits2Banking/blob/main/labs/native/framework-task-graph/README.md) · [Shared contract](https://github.com/umicom-foundation/umicom-framework/blob/main/docs/learning/task-graph-transactions.md)

[Course contents](index.md) · [Previous lesson](task-graph-retry-and-attempts.md) · [Next lesson](task-graph-transactions-and-regression-evidence.md)
