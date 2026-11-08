<!--
Umicom Bits2Banking
File: content/lessons/umicom-development/task-command-and-directory-transaction.md

PURPOSE:
Change a command and directory together

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->

# Change a command and directory together

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

## Observe the partial-update problem

A command and its working directory describe one intended operation. Copying a new command before discovering that the new directory is too long leaves an accidental combination. Returning an error does not undo the first write. If the revision also stays unchanged, another component may incorrectly reuse a cached view of the old command.

## Stage before publication

Framework first copies both proposed strings into temporary bounded storage. Only after both copies succeed does it publish them and advance the revision. Run atomic and inspect the byte-for-byte preservation assertion. Change the command text in the example and predict why it must still remain unchanged when the directory is rejected.

## Preserve intentional input forms

A null directory means retain the previous directory; an empty string explicitly replaces it with an empty value. The arguments may also refer to the existing command and directory fields. Staging both values before either write makes a field swap well-defined. Describe these behaviors as part of the API contract instead of relying on the order of individual copy calls.

## Review and recover

If configuration or linking fails, identify the installed SDK and compiler before changing the source. Keep an assertion failure with its selected case and source revision. Do not weaken expected outputs to hide a mismatch.

[Read the C exercise](https://github.com/umicom-foundation/Bits2Banking/blob/main/labs/native/framework-tasks/main.c) · [Full setup and native commands](https://github.com/umicom-foundation/Bits2Banking/blob/main/labs/native/framework-tasks/README.md) · [Shared contract](https://github.com/umicom-foundation/umicom-framework/blob/main/docs/learning/task-admission.md)

[Course contents](index.md) · [Previous lesson](task-descriptor-storage-before-meaning.md) · [Next lesson](task-registry-owning-public-values.md)
