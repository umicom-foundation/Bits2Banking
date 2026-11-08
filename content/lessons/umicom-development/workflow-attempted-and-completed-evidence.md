<!--
Umicom Bits2Banking
File: content/lessons/umicom-development/workflow-attempted-and-completed-evidence.md

PURPOSE:
Report attempted and completed actions separately

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->

# Report attempted and completed actions separately

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

## Observe a deliberate failure

Run fail-build. The controlled build callback returns 23. Five actions were attempted, four completed and the remaining actions were never invoked. A nonzero backend result stays in the report unchanged, while the Framework status identifies execution failure. These two values answer different questions.

## Read the failure boundary

The executor marks attempted immediately before calling the adapter and completed only after a zero result. It stops at the first failure. Publication is one grouped callback, so its failure cannot tell the executor whether a commit was already created before a rejected push. Read the publisher’s own action evidence for that detail.

## Exercise

Change the controlled failure to TEST. Predict six attempts and five completions, update the expectation and run the lab. Then inspect the regression case for a negative backend result and explain why normalizing every failure to one generic integer would discard information useful to a caller.

## Plan recovery from evidence

A failed workflow is not a transaction rollback. Review which actions actually completed and what the failed backend reports before retrying. Do not automatically repeat a publication because an earlier summary lacks detail, and do not label unattempted tests as passes or skips.

## Review and recover

A missing header or symbol requires checking the installed SDK identity. Preserve the command and output for a failed lab expectation. Controlled callbacks do not qualify real compilers, repository publication or a native GUI.

[Read the C exercise](https://github.com/umicom-foundation/Bits2Banking/blob/main/labs/native/lifecycle-execution/main.c) · [Shared contract](https://github.com/umicom-foundation/umicom-framework/blob/main/include/umicom/developer/lifecycle_execution.h)

[Course contents](index.md) · [Previous lesson](workflow-borrowed-inputs-and-lifetime.md) · [Next lesson](workflow-preview-and-optional-audits.md)
