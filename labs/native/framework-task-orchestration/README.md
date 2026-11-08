<!--
Umicom Bits2Banking
File: labs/native/framework-task-orchestration/README.md

PURPOSE:
Teach selected dependency closure and bounded task orchestration through an installed Framework SDK.

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->

# Rehearse a complete task operation

This C23 client uses the installed Framework orchestrator to select task dependencies, admit parallel work and record fictional outcomes. Framework owns planning and state; the client does not copy graph algorithms or launch a compiler.

## Prepare and run

1. Install the matching Framework development SDK using the compiler and architecture selected below.
2. Run each PowerShell command separately and stop on an unexpected error.
3. Repeat the final command with `parallel`, `stop`, `retry` and `reject`.

```powershell
Set-Location "C:\umicom\Umicom-Bits2Banking"
$env:Path = "C:\msys64\ucrt64\bin;$env:Path"
cmake -S .\labs\native\framework-task-orchestration -B .\build\framework-task-orchestration -G Ninja -DCMAKE_C_COMPILER=C:/msys64/ucrt64/bin/gcc.exe -DCMAKE_PREFIX_PATH=C:/umicom/installed/framework -DBUILD_TESTING=ON
cmake --build .\build\framework-task-orchestration --parallel 2
ctest --test-dir .\build\framework-task-orchestration --output-on-failure --no-tests=error
& .\build\framework-task-orchestration\btb-framework-task-orchestration.exe selected
```

Selected plans only configure and left, then records two successes. Parallel admits left and right together after configure, refuses a third ready request while both slots are occupied, and finishes with four successes. Stop records one running success and three canceled waiting tasks. Retry records one failed configure attempt, then one retry and four successes. Reject proves that an invalid replacement leaves the prior operation usable. Each scenario returns zero only when its modeled contract is satisfied.

## Follow ownership and lifetime

The source registry is borrowed: it must outlive the orchestrator. Planning copies the selected task and all transitive dependencies into owned storage. Later edits to the source registry do not change that plan. The graph address remains stable across successful replanning, but clients should route runtime mutations through the orchestrator so its active counters and terminal state stay synchronized.

The dependency walk uses explicit bounded index frames and one reusable task snapshot. A maximum-depth plan therefore does not accumulate a large snapshot on every recursive call. Shared prerequisites are included once and published before their consumers.

## Recovery and limitations

A plan ID must fit in full; an oversized value is refused instead of silently truncated. Rejected planning preserves the previous operation, generation and graph. Owner revision limits are checked before calling a child service, and a stop flag is published only after waiting-task cancellation succeeds. Finish cannot manufacture success for an idle or merely planned operation.

If configuration fails, verify the installed development package and prefix. If behavior differs, record the SDK revision, compiler, scenario and assertion output before changing the example. The tests model scheduling: actual processes require a supervised provider, cancellation evidence and output verification. A real host should retain a process outcome if recording it is refused, because a graph transaction cannot undo external effects.

## Extend the exercise

Add an optional documentation task independent of link. Compare planning link alone with planning every enabled task. Then set maximum parallelism to one and predict the busy responses before running. Finally introduce a missing prerequisite and show that the previous valid operation can still execute through its copied definitions.
