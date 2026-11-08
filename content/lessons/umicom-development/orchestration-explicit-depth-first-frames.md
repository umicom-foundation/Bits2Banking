<!--
Umicom Bits2Banking
File: content/lessons/umicom-development/orchestration-explicit-depth-first-frames.md

PURPOSE:
Bound dependency traversal without recursive task copies

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->

# Bound dependency traversal without recursive task copies

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

## Recognize the hidden stack cost

A task snapshot contains command text, paths and several bounded arrays. Recursively declaring one snapshot per dependency depth can consume a large thread stack even when the registry count itself is bounded. A 128-task chain is a valid input shape, so the implementation must handle its memory cost deliberately rather than assuming real projects will always be shallow.

## Represent the traversal directly

Framework keeps small arrays of task indices and the next dependency position for each active frame. One reusable task snapshot is loaded for the current frame. Descending pushes an index; completing a node publishes it into the candidate registry and pops the frame. This preserves depth-first, dependency-first ordering without accumulating large C call frames.

## Verify depth and cycles separately

The closure suite declares both a maximum-depth chain and a cycle at that depth. The first must plan all tasks and expose the first prerequisite as ready. The second must refuse and preserve the idle owner. Read the iterative helper and trace a three-node example on paper before inspecting the full-depth fixture; do not substitute a shallow test for the capacity boundary.

## Review and recover

Verify installed headers, archive and compiler when a contract differs. Keep the selected scenario and failure line. Preserve real process evidence separately from any refused graph observation.

[Read the C exercise](https://github.com/umicom-foundation/Bits2Banking/blob/main/labs/native/framework-task-orchestration/main.c) · [Full setup and native commands](https://github.com/umicom-foundation/Bits2Banking/blob/main/labs/native/framework-task-orchestration/README.md) · [Shared contract](https://github.com/umicom-foundation/umicom-framework/blob/main/docs/learning/task-orchestration.md)

[Course contents](index.md) · [Previous lesson](orchestration-select-a-dependency-closure.md) · [Next lesson](orchestration-owned-plans-and-source-edits.md)
