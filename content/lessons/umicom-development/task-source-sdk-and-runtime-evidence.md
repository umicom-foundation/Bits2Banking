<!--
Umicom Bits2Banking
File: content/lessons/umicom-development/task-source-sdk-and-runtime-evidence.md

PURPOSE:
Qualify task behavior at source and SDK boundaries

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->

# Qualify task behavior at source and SDK boundaries

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

## Use complementary coverage

The Framework descriptor suite checks malformed counts, text storage, enums, duplicate entries and command transactions. The registry suite checks ownership, ordering, capacity and private revision limits. The installed consumer then checks five public behaviors against the archive a learner would actually link. None of these layers is interchangeable with the others.

## Diagnose the loaded implementation

An undefined checked-reset symbol can mean the headers and library came from different revisions. Record the installed prefix, compiler and archive path before changing code. A successful compile against one checkout does not establish that a different installed SDK contains the same implementation. The exercise commands deliberately name the SDK prefix to make that dependency visible.

## Report evidence precisely

Authored tests describe intended checks; executed tests provide observations for a specific source and environment. Preserve failures and selected-test counts, including a no-tests error. The consumer stores a fictional compiler command, so even all five successful scenarios would not prove that a project built. Explain this distinction in your own lab report and list the next integration evidence needed.

## Review and recover

If configuration or linking fails, identify the installed SDK and compiler before changing the source. Keep an assertion failure with its selected case and source revision. Do not weaken expected outputs to hide a mismatch.

[Read the C exercise](https://github.com/umicom-foundation/Bits2Banking/blob/main/labs/native/framework-tasks/main.c) · [Full setup and native commands](https://github.com/umicom-foundation/Bits2Banking/blob/main/labs/native/framework-tasks/README.md) · [Shared contract](https://github.com/umicom-foundation/umicom-framework/blob/main/docs/learning/task-admission.md)

[Course contents](index.md) · [Previous lesson](task-descriptors-and-dependency-graphs.md) · [Next lesson](task-graph-rejected-replacement.md)
