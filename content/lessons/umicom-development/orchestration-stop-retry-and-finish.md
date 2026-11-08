<!--
Umicom Bits2Banking
File: content/lessons/umicom-development/orchestration-stop-retry-and-finish.md

PURPOSE:
Distinguish stopping, retrying and finishing an operation

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->

# Distinguish stopping, retrying and finishing an operation

## Prepare the exercise

Install the matching Framework SDK and run these PowerShell commands separately. Use the scenario named in the lesson and stop on unexpected errors.

```powershell
Set-Location "C:\umicom\Umicom-Bits2Banking"
$env:Path = "C:\msys64\ucrt64\bin;$env:Path"
cmake -S .\labs\native\framework-task-orchestration -B .\build\framework-task-orchestration -G Ninja -DCMAKE_C_COMPILER=C:/msys64/ucrt64/bin/gcc.exe -DCMAKE_PREFIX_PATH=C:/umicom/installed/framework -DBUILD_TESTING=ON
cmake --build .\build\framework-task-orchestration --parallel 2
ctest --test-dir .\build\framework-task-orchestration --output-on-failure --no-tests=error
& .\build\framework-task-orchestration\btb-framework-task-orchestration.exe selected
```

Selected plans two tasks; parallel, retry and reject complete four; stop leaves three waiting tasks canceled after the active task finishes. These are modeled outcomes, not actual process results.

## Stop scheduling before claiming cancellation

Run stop. Waiting tasks become canceled while configure remains active until the host reports its completion. The owner's stop flag is published only after graph cancellation succeeds. This prevents a failed nested operation from leaving a misleading half-applied stop state. The final operation is Cancelled even though the already-running task completed successfully.

## Retry within explicit budgets

Run retry to record one failed configure attempt and then a successful second attempt. Task attempts and the operation's retry count describe different aspects of the same recovery. Both observation identities and counters must remain representable. A refusal preserves prior state, allowing the host to explain which limit prevented recovery.

## Require a real lifecycle before finish

Finish cannot turn an idle or merely planned object into success. Begin establishes the operation lifecycle, and active tasks must reach terminal outcomes before finish can accept it. An intentionally empty plan can succeed after begin because it contains no work; that is different from accidentally finishing an unplanned owner. Write these two cases as separate assertions in your own integration report.

## Review and recover

Verify installed headers, archive and compiler when a contract differs. Keep the selected scenario and failure line. Preserve real process evidence separately from any refused graph observation.

[Read the C exercise](https://github.com/umicom-foundation/Bits2Banking/blob/main/labs/native/framework-task-orchestration/main.c) · [Full setup and native commands](https://github.com/umicom-foundation/Bits2Banking/blob/main/labs/native/framework-task-orchestration/README.md) · [Shared contract](https://github.com/umicom-foundation/umicom-framework/blob/main/docs/learning/task-orchestration.md)

[Course contents](index.md) · [Previous lesson](orchestration-parallel-slots-and-outcomes.md) · [Next lesson](orchestration-layered-regression-evidence.md)
