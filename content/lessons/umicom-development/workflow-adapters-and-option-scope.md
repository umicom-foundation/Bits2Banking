<!--
Umicom Bits2Banking
File: content/lessons/umicom-development/workflow-adapters-and-option-scope.md

PURPOSE:
Forward only options with defined meaning

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->

# Forward only options with defined meaning

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

## Follow the native adapter

The CLI converts a typed action into arguments for an existing command. Configure, build and test receive the source and optional preset. Only compilation receives jobs. Repository publication receives message, remote and branch. Update has its own no-submodules flag. The executor does not implement Git or CMake itself.

## Reject ambiguous input

The parser accepts each named option once. Supplying source twice is an error rather than first-value-wins behavior. Goal belongs to plan, not complete. Options with no meaning for a selected goal are refused before any adapter runs. This makes an accepted command correspond to the user’s stated intent.

## Exercise

Read test_workflow_cli.c and find the full-options adapter assertions. Predict the exact argument vector for the build action, including a source path with a space. Compare it with the test action. Then inspect duplicate-source and goal-on-complete cases and explain why both must record zero backend calls.

## Use the correct command surface

The workflow command deliberately has a bounded option set. For definitions, explicit build folders, logs, JUnit output, installation or packages, use the individual native commands documented in the development guide. An unrecognized flag should not be silently forwarded to an unrelated tool.

## Review and recover

A missing header or symbol requires checking the installed SDK identity. Preserve the command and output for a failed lab expectation. Controlled callbacks do not qualify real compilers, repository publication or a native GUI.

[Read the C exercise](https://github.com/umicom-foundation/Bits2Banking/blob/main/labs/native/lifecycle-execution/main.c) · [Shared contract](https://github.com/umicom-foundation/umicom-framework/blob/main/include/umicom/developer/lifecycle_execution.h)

[Course contents](index.md) · [Previous lesson](workflow-preview-and-optional-audits.md) · [Next lesson](workflow-qualify-the-integration-layers.md)
