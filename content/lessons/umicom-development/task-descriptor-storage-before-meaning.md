<!--
Umicom Bits2Banking
File: content/lessons/umicom-development/task-descriptor-storage-before-meaning.md

PURPOSE:
Validate task storage before task meaning

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->

# Validate task storage before task meaning

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

## A descriptor is a complete object

A fixed array has a physical bound, while its count records how many entries are active. If a public descriptor claims more entries than that bound, a loop can leave the object before it has a chance to report a useful error. Framework checks structure metadata, counts and bounded string termination first. This storage check is separate from asking whether a command task has enough information to run.

## Exercise the shape case

Run the lab with shape. The example deliberately sets input_count to SIZE_MAX in a complete initialized object. Validation and another builder call must refuse it without reading imaginary rows or changing the object. Inspect the comparison with the saved snapshot. Do not try the same experiment with a dangling pointer: no field validation can make invalid memory ownership safe.

## Inspect active rows

A task may reserve sixteen inputs but use only one. Only that active row is part of the input list. Compare this with an unterminated task ID, which is always an active scalar field. Explain why clearing unused storage is useful during initialization but is not a substitute for checking the declared count at an import boundary.

## Review and recover

If configuration or linking fails, identify the installed SDK and compiler before changing the source. Keep an assertion failure with its selected case and source revision. Do not weaken expected outputs to hide a mismatch.

[Read the C exercise](https://github.com/umicom-foundation/Bits2Banking/blob/main/labs/native/framework-tasks/main.c) · [Full setup and native commands](https://github.com/umicom-foundation/Bits2Banking/blob/main/labs/native/framework-tasks/README.md) · [Shared contract](https://github.com/umicom-foundation/umicom-framework/blob/main/docs/learning/task-admission.md)

[Course contents](index.md) · [Previous lesson](deployment-revisions-and-layered-qualification.md) · [Next lesson](task-command-and-directory-transaction.md)
