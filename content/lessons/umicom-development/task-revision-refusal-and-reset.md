<!--
Umicom Bits2Banking
File: content/lessons/umicom-development/task-revision-refusal-and-reset.md

PURPOSE:
Treat revisions as identities that cannot wrap

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->

# Treat revisions as identities that cannot wrap

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

## A revision is an observation token

Consumers can compare revisions to decide whether an observed task changed. An unsigned counter wraps mathematically, but reusing an earlier token can make stale state appear current. Run revision to place the descriptor at its representable limit. A new command must be refused and the saved state must remain identical.

## Choose a checked reset

Run reset to clear an ordinary registry through the status-returning API. The registry becomes empty and its identity advances once. The compatibility void clear remains available, but cannot report exhaustion to its caller. New code that needs to explain a refusal should use checked reset and handle its status explicitly.

## Reserve every affected identity

Replacing a task changes both its stored task identity and the registry identity. Checking only one counter is insufficient. The private regression suite reaches each exhausted boundary without adding public counter setters. Explain why these tests inspect complete state after refusal rather than merely checking that an error code was returned.

## Review and recover

If configuration or linking fails, identify the installed SDK and compiler before changing the source. Keep an assertion failure with its selected case and source revision. Do not weaken expected outputs to hide a mismatch.

[Read the C exercise](https://github.com/umicom-foundation/Bits2Banking/blob/main/labs/native/framework-tasks/main.c) · [Full setup and native commands](https://github.com/umicom-foundation/Bits2Banking/blob/main/labs/native/framework-tasks/README.md) · [Shared contract](https://github.com/umicom-foundation/umicom-framework/blob/main/docs/learning/task-admission.md)

[Course contents](index.md) · [Previous lesson](task-registry-owning-public-values.md) · [Next lesson](task-descriptors-and-dependency-graphs.md)
