<!--
Umicom Bits2Banking
File: content/lessons/umicom-development/orchestration-layered-regression-evidence.md

PURPOSE:
Qualify orchestration across owner and child boundaries

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->

# Qualify orchestration across owner and child boundaries

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

## Test the whole rejected transition

The transaction suite declares 25 cases that compare both the owner and its graph after refusal. A test checking only the owner's return code could miss a child that already changed state. The private fixture reaches revision and allocation limits without exposing test-only setters in the public SDK. Review the stop-graph and complete-graph cases as examples of nested refusal.

## Retain public workflow coverage

The 12 public closure cases cover maximum depth, cycles, shared prerequisites, selected roots, source edits, parallel admission, retries and stopping. These scenarios preserve practical behavior while internal storage changes. The five installed lab scenarios then check that matching headers and archives expose the same contracts to a consumer.

## Separate authored checks from qualified work

CMake registration makes tests discoverable; it does not execute them. Static comparison of case lists can catch incorrect wiring but cannot prove compiler or runtime behavior. After owner execution, record selected counts, failures and source identity. Even a fully passing modeled workflow leaves actual configure, build, deployment and application launch evidence to the process-owning integration layer.

## Review and recover

Verify installed headers, archive and compiler when a contract differs. Keep the selected scenario and failure line. Preserve real process evidence separately from any refused graph observation.

[Read the C exercise](https://github.com/umicom-foundation/Bits2Banking/blob/main/labs/native/framework-task-orchestration/main.c) · [Full setup and native commands](https://github.com/umicom-foundation/Bits2Banking/blob/main/labs/native/framework-task-orchestration/README.md) · [Shared contract](https://github.com/umicom-foundation/umicom-framework/blob/main/docs/learning/task-orchestration.md)

[Course contents](index.md) · [Previous lesson](orchestration-stop-retry-and-finish.md)
