<!--
Umicom Bits2Banking
File: content/lessons/umicom-development/task-registry-owning-public-values.md

PURPOSE:
Publish task values into an owning registry

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->

# Publish task values into an owning registry

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

## Borrow briefly and copy deliberately

The caller owns its editable snapshot. Upsert borrows that object during the call, validates it and copies the accepted value into registry storage. Run owned: the example clears its caller snapshot after publication, then reads the task back by ID. The unchanged stored command demonstrates the intended lifetime boundary.

## Separate identity from position

A task ID selects an existing entry. Replacing that ID keeps its position but advances the stored task revision. Removing an entry shifts later entries, so array indices are not durable identities. When a Studio list stores a selection across refreshes, retain the task ID and resolve it again rather than assuming the old row number still names the same task.

## Plan cleanup at the owner

Registry creation allocates bounded owned storage and destruction releases it. Use one owning workspace service and serialize its mutations. This does not make the registry thread-safe by itself. Follow every error path in main.c and identify where the registry is destroyed before returning; distinguish a temporary descriptor from the larger long-lived registry.

## Review and recover

If configuration or linking fails, identify the installed SDK and compiler before changing the source. Keep an assertion failure with its selected case and source revision. Do not weaken expected outputs to hide a mismatch.

[Read the C exercise](https://github.com/umicom-foundation/Bits2Banking/blob/main/labs/native/framework-tasks/main.c) · [Full setup and native commands](https://github.com/umicom-foundation/Bits2Banking/blob/main/labs/native/framework-tasks/README.md) · [Shared contract](https://github.com/umicom-foundation/umicom-framework/blob/main/docs/learning/task-admission.md)

[Course contents](index.md) · [Previous lesson](task-command-and-directory-transaction.md) · [Next lesson](task-revision-refusal-and-reset.md)
