<!--
Umicom Bits2Banking
File: content/lessons/umicom-development/workflow-qualify-the-integration-layers.md

PURPOSE:
Qualify a workflow through distinct layers

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->

# Qualify a workflow through distinct layers

## Prepare the exercise

Install a C23 compiler, CMake 3.25 or later, Ninja and a matching Framework SDK with the developer lifecycle service. A terminal runs commands; CMake prepares build instructions and Ninja compiles the program. Use your actual SDK prefix and stop on a configure or build error before running an existing executable.

```powershell
Set-Location "C:\umicom\Umicom-Bits2Banking\labs\native\lifecycle-execution"
$env:Path = "C:\msys64\ucrt64\bin;$env:Path"
cmake -S . -B build -G Ninja -DCMAKE_PREFIX_PATH="C:/umicom/installed/framework"
cmake --build build
.\build\lifecycle-execution.exe fail-build
ctest --test-dir build --output-on-failure --no-tests=error
```

For fail-build, expect five attempted callbacks, four completed callbacks and zero external commands. The deliberate backend result is 23. This is an expected observation to verify, not a claimed pass on your machine.

## Name the evidence layers

The lab links an installed Framework SDK and uses controlled callbacks. Framework regression cases exercise admission and ordering. CLI cases include the real parser and assert native argument vectors against controlled backends. Actual compiler execution, repository state changes and GUI responsiveness require further integration evidence.

## Build a useful record

For each layer, record the source revision, installed SDK identity, exact command, environment, observed result and remaining limits. A stale executable can produce a reassuring pass for older source. Build the intended target successfully before relying on its test result, and retain skipped cases separately from passed ones.

## Exercise

Run the five lab scenarios after a successful build. In a separate Framework test tree, run the lifecycle execution and workflow CLI cases. Compare the two reports: the first proves installed-consumer linking; the second covers more boundaries. Neither proves a real push. Leave an unexecuted row for any integration check you have not performed.

## Diagnose by boundary

A missing lifecycle header points to SDK selection. A missing symbol points to library or installation identity. A wrong callback count points to plan/executor behavior. A real backend failure belongs to that backend’s evidence. Start with the earliest demonstrated failure instead of treating every symptom as a build-system defect.

## Review and recover

A missing header or symbol requires checking the installed SDK identity. Preserve the command and output for a failed lab expectation. Controlled callbacks do not qualify real compilers, repository publication or a native GUI.

[Read the C exercise](https://github.com/umicom-foundation/Bits2Banking/blob/main/labs/native/lifecycle-execution/main.c) · [Shared contract](https://github.com/umicom-foundation/umicom-framework/blob/main/include/umicom/developer/lifecycle_execution.h)

[Course contents](index.md) · [Previous lesson](workflow-adapters-and-option-scope.md) · [Next lesson](deployment-models-and-real-providers.md)
