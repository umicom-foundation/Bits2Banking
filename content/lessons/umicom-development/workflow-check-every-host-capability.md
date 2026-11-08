<!--
Umicom Bits2Banking
File: content/lessons/umicom-development/workflow-check-every-host-capability.md

PURPOSE:
Check every host capability before execution

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->

# Check every host capability before execution

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

## Understand a callback table

A C function pointer lets a library request behavior supplied by its caller. Framework owns the lifecycle sequence while the host supplies native commands, a GUI adapter or the controlled lab. Each needed action has a callback slot. An empty slot means the host cannot carry out that action.

## Inspect the admission loop

The executor checks all slots required by the plan before calling the first one. This matters when the last publisher is unavailable: checking slots only when reached would leave earlier configuration and build work behind. Preview needs no host because it only describes actions. Unused slots may remain empty.

## Exercise

Run missing-backend and confirm that it describes planned work but records no attempts. In main.c, move the missing slot from publication to configuration and predict the same zero-call boundary. Then select a verification-only goal with the publisher slot empty; explain why that unused capability should not prevent verification.

## Extend a client carefully

Implement a new adapter by returning a truthful result from the existing service. Do not return success just because a slot exists. Capability admission proves that a function is supplied, not that its external tools, filesystem permissions or network connection will work when invoked.

## Review and recover

A missing header or symbol requires checking the installed SDK identity. Preserve the command and output for a failed lab expectation. Controlled callbacks do not qualify real compilers, repository publication or a native GUI.

[Read the C exercise](https://github.com/umicom-foundation/Bits2Banking/blob/main/labs/native/lifecycle-execution/main.c) · [Shared contract](https://github.com/umicom-foundation/umicom-framework/blob/main/include/umicom/developer/lifecycle_execution.h)

[Course contents](index.md) · [Previous lesson](workflow-plan-stages-and-real-actions.md) · [Next lesson](workflow-borrowed-inputs-and-lifetime.md)
