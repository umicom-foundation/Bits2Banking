<!--
Umicom Bits2Banking
File: content/lessons/umicom-development/task-descriptors-and-dependency-graphs.md

PURPOSE:
Separate local task validity from dependency validity

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->

# Separate local task validity from dependency validity

## Prepare the exercise

Install a matching Framework SDK, then run these PowerShell commands separately. Use the lab scenario named in each lesson and stop on an unexpected error.

```powershell
Set-Location "C:\umicom\Umicom-Bits2Banking"
$env:Path = "C:\msys64\ucrt64\bin;$env:Path"
cmake -S .\labs\native\framework-tasks -B .\build\framework-tasks -G Ninja -DCMAKE_C_COMPILER=C:/msys64/ucrt64/bin/gcc.exe -DCMAKE_PREFIX_PATH=C:/umicom/installed/framework -DBUILD_TESTING=ON
cmake --build .\build\framework-tasks --parallel 2
ctest --test-dir .\build\framework-tasks --output-on-failure --no-tests=error
& .\build\framework-tasks\btb-framework-tasks.exe atomic
```

The lab has five scenarios: atomic, shape, owned, reset and revision. A zero exit means the selected assertion matched its expected metadata behavior; no stored task command runs.

## Local validity has a boundary

A descriptor can name configure as a dependency without proving a configure task exists. This is not a reason to duplicate dependency lookup in every UI. First publish individually valid descriptors into a registry, then use the shared task graph to inspect relationships. The lab extension asks you to add configure and explain which layer establishes its presence.

## Detect the relationship you actually mean

A task depending on itself is invalid locally. A cycle across configure, generate and build requires a graph view of several tasks. Missing IDs and cycles are different explanations and should be shown separately. Disabling a task is also policy, not evidence that its output exists. Inspect the graph API before choosing how a workflow should interpret disabled prerequisites.

## Keep planning distinct from execution

A successful graph review still does not locate a compiler, compare input digests or create output files. Those responsibilities belong to toolchain, file-observation and supervised-process services. Write down the evidence each stage adds. A CLI preview or Studio panel should report only the facts supplied by the stage it actually performed.

## Review and recover

If configuration or linking fails, identify the installed SDK and compiler before changing the source. Keep an assertion failure with its selected case and source revision. Do not weaken expected outputs to hide a mismatch.

[Read the C exercise](https://github.com/umicom-foundation/Bits2Banking/blob/main/labs/native/framework-tasks/main.c) · [Full setup and native commands](https://github.com/umicom-foundation/Bits2Banking/blob/main/labs/native/framework-tasks/README.md) · [Shared contract](https://github.com/umicom-foundation/umicom-framework/blob/main/docs/learning/task-admission.md)

[Course contents](index.md) · [Previous lesson](task-revision-refusal-and-reset.md) · [Next lesson](task-source-sdk-and-runtime-evidence.md)
