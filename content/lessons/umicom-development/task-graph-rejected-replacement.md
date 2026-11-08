<!--
Umicom Bits2Banking
File: content/lessons/umicom-development/task-graph-rejected-replacement.md

PURPOSE:
Keep a running graph when replacement is invalid

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->

# Keep a running graph when replacement is invalid

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

## Treat replacement as a transaction

A running workflow has task definitions, a source revision and recorded outcomes. Clearing that state before checking a replacement recipe makes an error destructive. Run reject in the lab. The proposed registry names a missing dependency, and the old running graph must remain intact. Compare the aggregate snapshots captured before and after the refused rebuild.

## Validate a candidate before publication

Framework builds a temporary graph, resolves enabled dependencies and calculates readiness before publishing it. This allocation belongs to rebuild because task values are changing. Ordinary progress updates use much smaller staged runtime records. Explain why the large task arrays belong on the heap rather than a thread stack.

## Read the correct evidence

A snapshot describes the graph that was actually committed. After refusal, it intentionally still describes the previous graph. Use the rebuild return status to explain the failed candidate; do not label the old graph cyclic because a new candidate had a cycle. Keep the proposed registry available for the user to correct and retry.

## Review and recover

Confirm the installed archive and headers when behavior differs. Preserve the selected scenario and assertion output. Do not change scheduling policies or expected counts merely to obtain a passing result.

[Read the C exercise](https://github.com/umicom-foundation/Bits2Banking/blob/main/labs/native/framework-task-graph/main.c) · [Full setup and native commands](https://github.com/umicom-foundation/Bits2Banking/blob/main/labs/native/framework-task-graph/README.md) · [Shared contract](https://github.com/umicom-foundation/umicom-framework/blob/main/docs/learning/task-graph-transactions.md)

[Course contents](index.md) · [Previous lesson](task-source-sdk-and-runtime-evidence.md) · [Next lesson](task-graph-readiness-and-diamonds.md)
