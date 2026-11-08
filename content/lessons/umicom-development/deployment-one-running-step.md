<!--
Umicom Bits2Banking
File: content/lessons/umicom-development/deployment-one-running-step.md

PURPOSE:
Give one deployment step the execution slot

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->

# Give one deployment step the execution slot

## Prepare the exercise

Use a matching installed Framework development SDK and the provider-free C23 consumer. Run commands separately and stop on unexpected errors.

```powershell
Set-Location "C:\umicom\Umicom-Bits2Banking"
$env:Path = "C:\msys64\ucrt64\bin;$env:Path"
cmake -S .\labs\native\framework-deployment -B .\build\framework-deployment -G Ninja -DCMAKE_C_COMPILER=C:/msys64/ucrt64/bin/gcc.exe -DCMAKE_PREFIX_PATH=C:/umicom/installed/framework -DBUILD_TESTING=ON
cmake --build .\build\framework-deployment --parallel 2
ctest --test-dir .\build\framework-deployment --output-on-failure --no-tests=error
& .\build\framework-deployment\btb-framework-deployment.exe complete
& .\build\framework-deployment\btb-framework-deployment.exe fail
& .\build\framework-deployment\btb-framework-deployment.exe rollback
& .\build\framework-deployment\btb-framework-deployment.exe cancel
& .\build\framework-deployment\btb-framework-deployment.exe revise
```

The five scenarios report modeled outcomes. None installs a package, launches an application or contacts a target.

## Trace ownership through a step

The controller owns its copied plan and stores the index of the running step. next_step offers a pending action only when that slot is empty. start_step claims it; completion or failure releases it. A provider must keep its operation alive until it can report a definite outcome. The controller does not manage the provider’s thread or process for it.

## Understand a busy result

If a caller asks for another step while one is running, next_step now returns BUSY and preserves its output. This prevents a host from interpreting a later pending action as permission for parallel work. The ordered required steps remain checked when start_step is called, so a stale or manually selected step cannot bypass those dependencies.

## Use snapshots for display

A UI can read a snapshot to display current_step_id and progress while work is running. It should not use repeated start calls as a status query. Separate read operations from state transitions. All access must still be serialized through the owner; an opaque pointer does not make simultaneous reads and writes safe in C.

## Extend the controlled scenario

Read next-busy in the lifecycle regression. Predict what happens if completion names a different step: the current slot does not match, so the operation is refused. Write a host-side timeline showing a start, a status refresh, one completion and the next request. Include a late duplicate completion and explain why it must not advance the plan twice.

## Review and recover

Inspect the selected SDK, compiler identity and failing output before changing expectations. Keep actual provider qualification separate from this state-model exercise.

[Read the C exercise](https://github.com/umicom-foundation/Bits2Banking/blob/main/labs/native/framework-deployment/main.c) · [Full setup and native commands](https://github.com/umicom-foundation/Bits2Banking/blob/main/labs/native/framework-deployment/README.md) · [Shared contract](https://github.com/umicom-foundation/umicom-framework/blob/main/include/umicom/build/deployment_controller.h)

[Course contents](index.md) · [Previous lesson](deployment-approval-follows-content.md) · [Next lesson](deployment-stop-and-completion-evidence.md)
