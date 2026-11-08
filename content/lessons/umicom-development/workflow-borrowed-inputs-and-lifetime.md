<!--
Umicom Bits2Banking
File: content/lessons/umicom-development/workflow-borrowed-inputs-and-lifetime.md

PURPOSE:
Keep borrowed request data alive

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->

# Keep borrowed request data alive

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

## Read the ownership contract

The execution request contains pointers to source, preset, jobs, message, remote and branch strings. Framework borrows them for a synchronous call. It copies the structure and callback table, but a structure copy copies pointer values rather than the pointed-to text. The caller owns that storage throughout execution.

## Trace one option

Follow source from the CLI parser to UmiDeveloperLifecycleExecutionRequest, then to workflow_execute_action. The adapter passes a separate argv element to the existing command service. Spaces belong to that one value; the executor does not concatenate a shell command. C strings still require a terminator and valid storage.

## Exercise

In the controlled lab, replace the source literal with a character array in main and print it from Explain. Keep the array alive until umi_developer_lifecycle_execute returns. Sketch why a pointer returned from a helper to its local array would be invalid. Do not run deliberately invalid pointer code as a learning shortcut.

## Choose an asynchronous boundary

A future worker-based client must own copies of request text until its worker finishes. It cannot retain pointers into a temporary dialog buffer and assume the synchronous service will extend their lifetime. Document who copies, who frees and which thread may mutate each value.

## Review and recover

A missing header or symbol requires checking the installed SDK identity. Preserve the command and output for a failed lab expectation. Controlled callbacks do not qualify real compilers, repository publication or a native GUI.

[Read the C exercise](https://github.com/umicom-foundation/Bits2Banking/blob/main/labs/native/lifecycle-execution/main.c) · [Shared contract](https://github.com/umicom-foundation/umicom-framework/blob/main/include/umicom/developer/lifecycle_execution.h)

[Course contents](index.md) · [Previous lesson](workflow-check-every-host-capability.md) · [Next lesson](workflow-attempted-and-completed-evidence.md)
