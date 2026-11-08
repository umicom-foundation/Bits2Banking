<!--
Umicom Bits2Banking
File: content/lessons/umicom-development/task-graph-transactions-and-regression-evidence.md

PURPOSE:
Verify graph transactions across public and private boundaries

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->

# Verify graph transactions across public and private boundaries

## Prepare the exercise

Install the matching Framework SDK, then run these commands separately. Select the scenario named by the lesson and stop on an unexpected error.

```powershell
Set-Location "C:\umicom\Umicom-Bits2Banking"
$env:Path = "C:\msys64\ucrt64\bin;$env:Path"
cmake -S .\labs\native\framework-task-graph -B .\build\framework-task-graph -G Ninja -DCMAKE_C_COMPILER=C:/msys64/ucrt64/bin/gcc.exe -DCMAKE_PREFIX_PATH=C:/umicom/installed/framework -DBUILD_TESTING=ON
cmake --build .\build\framework-task-graph --parallel 2
ctest --test-dir .\build\framework-task-graph --output-on-failure --no-tests=error
& .\build\framework-task-graph\btb-framework-task-graph.exe complete
```

Complete and retry model three successes; fail models one failure and two blocked tasks; cancel leaves two waiting tasks canceled; reject preserves the running graph. These are task-state observations, not actual build results.

## Test the failure boundary directly

The transaction suite reaches graph and node revision limits and forces candidate-allocation failure by including the production implementation in an isolated regression target. This avoids adding counter setters to the public SDK. Each refusal compares the complete saved graph, detecting partial changes that an error-code assertion alone would miss.

## Retain policy coverage separately

The public policy suite covers chains, diamonds, retries, disabled tasks, continuation, cancellation and aggregate progress. Keeping these scenarios alongside transaction checks prevents a memory-safety repair from silently changing workflow semantics. The installed lab then checks the archive and headers a consumer actually uses, rather than assuming source tests prove packaging consistency.

## Report only executed observations

The two Framework suites declare 49 cases and the SDK lab declares five scenarios. Their presence in source is not a pass. Record selected counts and failures after owner execution, and identify the compiler and source revision. The lab supplies fictional provider outcomes, so successful graph checks still leave real configure, build, test and launch qualification outstanding.

## Review and recover

Confirm the installed archive and headers when behavior differs. Preserve the selected scenario and assertion output. Do not change scheduling policies or expected counts merely to obtain a passing result.

[Read the C exercise](https://github.com/umicom-foundation/Bits2Banking/blob/main/labs/native/framework-task-graph/main.c) · [Full setup and native commands](https://github.com/umicom-foundation/Bits2Banking/blob/main/labs/native/framework-task-graph/README.md) · [Shared contract](https://github.com/umicom-foundation/umicom-framework/blob/main/docs/learning/task-graph-transactions.md)

[Course contents](index.md) · [Previous lesson](task-graph-cancellation-and-process-ownership.md) · [Next lesson](orchestration-select-a-dependency-closure.md)
