<!--
Umicom Bits2Banking
File: content/lessons/umicom-development/orchestration-owned-plans-and-source-edits.md

PURPOSE:
Keep accepted plans separate from editable source tasks

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->

# Keep accepted plans separate from editable source tasks

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

## Borrow the registry and own the plan

The source registry must outlive the orchestrator, but the accepted plan owns copied task definitions. Editing source tasks does not change the operation already under review. Run reject: the example replaces a source dependency with a missing ID, refuses a new plan and then completes the previous valid operation through its retained definitions.

## Publish a candidate only when complete

Planning creates a new candidate registry, resolves the dependency closure and validates the replacement graph. It destroys the previous planned registry only after the new graph has been accepted. Failed lookup, cycles, allocation refusal and identity limits therefore leave the previous operation usable. This ordering is the ownership counterpart of staging a command and directory together.

## Retain observer identity deliberately

The graph object address stays stable across replanning for compatible borrowed observers. Its contents and revisions can change on successful publication. Treat the exposed pointer as an observation surface while using orchestration; changing graph state directly bypasses the owner's active counts. Explain which object owns each pointer in the lab's cleanup sequence.

## Review and recover

Verify installed headers, archive and compiler when a contract differs. Keep the selected scenario and failure line. Preserve real process evidence separately from any refused graph observation.

[Read the C exercise](https://github.com/umicom-foundation/Bits2Banking/blob/main/labs/native/framework-task-orchestration/main.c) · [Full setup and native commands](https://github.com/umicom-foundation/Bits2Banking/blob/main/labs/native/framework-task-orchestration/README.md) · [Shared contract](https://github.com/umicom-foundation/umicom-framework/blob/main/docs/learning/task-orchestration.md)

[Course contents](index.md) · [Previous lesson](orchestration-explicit-depth-first-frames.md) · [Next lesson](orchestration-parallel-slots-and-outcomes.md)
