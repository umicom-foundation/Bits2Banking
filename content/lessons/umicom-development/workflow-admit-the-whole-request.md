<!--
Umicom Bits2Banking
File: content/lessons/umicom-development/workflow-admit-the-whole-request.md

PURPOSE:
Admit the whole request before work starts

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->

# Admit the whole request before work starts

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

## Find the late failure

A command can fail correctly and still fail too late. If complete first configures and builds a project, then discovers that its publication message is missing, the terminal reports an argument problem after real work has already changed the build directory. Admission means checking what the operation needs before it starts. It is a separate step from running each backend.

## Read the shared boundary

Open lifecycle_execution.c and follow lifecycle_admit. It checks the goal, option scope, positive job count, flags and required message. The executor does not inspect a CMake preset file or prove that the compiler exists. Those remain backend checks. Distinguish a complete syntactic request from a qualified environment.

## Exercise

Run missing-message in the lab. Predict zero callbacks before observing the output. Then run complete and compare the eight callback names. Add a whitespace-only message locally and explain why merely checking the pointer for NULL would not reject it. Retain both expected and observed results.

## Recover deliberately

When admission refuses an input, correct that input before retrying. When a backend fails later, retain earlier results because they may describe changes already made. Do not present these two failure classes as equivalent: their progress reports contain different evidence.

## Review and recover

A missing header or symbol requires checking the installed SDK identity. Preserve the command and output for a failed lab expectation. Controlled callbacks do not qualify real compilers, repository publication or a native GUI.

[Read the C exercise](https://github.com/umicom-foundation/Bits2Banking/blob/main/labs/native/lifecycle-execution/main.c) · [Shared contract](https://github.com/umicom-foundation/umicom-framework/blob/main/include/umicom/developer/lifecycle_execution.h)

[Course contents](index.md) · [Previous lesson](restart-qualify-each-layer.md) · [Next lesson](workflow-plan-stages-and-real-actions.md)
