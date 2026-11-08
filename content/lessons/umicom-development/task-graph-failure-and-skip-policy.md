<!--
Umicom Bits2Banking
File: content/lessons/umicom-development/task-graph-failure-and-skip-policy.md

PURPOSE:
Distinguish blocked work from permitted continuation

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->

# Distinguish blocked work from permitted continuation

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

## Propagate a real failure observation

Run fail. The example records configure exit 7 and expects build and test to become Blocked. A blocked task has not failed its own compiler invocation; its prerequisite prevents admission. Present those outcomes separately in a report so users can find the first failed operation instead of treating every downstream task as an independent defect.

## Review continuation deliberately

A dependency marked continue-on-error lets consumers become ready after its failure. A skipped dependency also counts as satisfied, and disabled tasks begin skipped. These policies retain existing Framework behavior. They do not create missing object files or make a later linker succeed. Use continuation only when the workflow can tolerate the missing result.

## Specify importer requirements

The graph checks relationships among enabled tasks. Disabled-only cycles and missing references remain accepted for compatibility. A source-build recipe may need stronger rules for every declared stage, including disabled ones. Apply that policy at recipe admission and document it; do not silently reinterpret the general task graph for all existing callers.

## Review and recover

Confirm the installed archive and headers when behavior differs. Preserve the selected scenario and assertion output. Do not change scheduling policies or expected counts merely to obtain a passing result.

[Read the C exercise](https://github.com/umicom-foundation/Bits2Banking/blob/main/labs/native/framework-task-graph/main.c) · [Full setup and native commands](https://github.com/umicom-foundation/Bits2Banking/blob/main/labs/native/framework-task-graph/README.md) · [Shared contract](https://github.com/umicom-foundation/umicom-framework/blob/main/docs/learning/task-graph-transactions.md)

[Course contents](index.md) · [Previous lesson](task-graph-readiness-and-diamonds.md) · [Next lesson](task-graph-retry-and-attempts.md)
