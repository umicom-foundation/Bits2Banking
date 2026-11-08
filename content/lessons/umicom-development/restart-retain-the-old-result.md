<!--
Umicom Bits2Banking
File: content/lessons/umicom-development/restart-retain-the-old-result.md

PURPOSE:
Retain the old result before a new run

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->

# Retain the old result before a new run

## Prepare the exercise

Install a C23 compiler, CMake 3.25 or later, Ninja and a matching Framework SDK containing the restart service. Open a terminal in the lab directory. A terminal runs commands; CMake prepares build instructions and Ninja compiles them. Stop on a configure or build error before using an existing executable. Substitute your own SDK location for the Windows example.

~~~powershell
Set-Location "C:\umicom\Umicom-Bits2Banking\labs\native\run-restart"
$env:Path = "C:\msys64\ucrt64\bin;$env:Path"
cmake -S . -B build -G Ninja -DCMAKE_PREFIX_PATH="C:/umicom/installed/framework"
cmake --build build
.\build\run-restart.exe "$PWD\build\run-restart.exe" handover
ctest --test-dir build --output-on-failure --no-tests=error
~~~

In handover mode, expect two controlled executor calls and zero child processes after the old result is retained. Run stop and revoke for one-call refusals. These are expected outcomes to verify, not results asserted for your machine.

## Distinguish display from history

A live output panel is a bounded view of current bytes. Completed results record the outcome of a phase. Beginning another operation may replace live state, so the frontend must retain the previous completed results before acknowledging that restart can continue.

## Count within one operation

The service accepts consumed_results as the frontend’s acknowledgement. It waits when the count is below completed_phase_count and rejects an excessive count. Studio increments its count only after appending the copied result to its normal history. It resets that count when the replacement operation is accepted.

## Exercise

Run the lab in handover mode. It first supplies zero after one phase has finished. Observe the wait message, then find the call that copies result zero before acknowledging one. Change the acknowledgement to two in a scratch copy and predict the rejection. Keep the actual error rather than treating a failed exercise as success.

## Respect the contract

Framework cannot prove that a caller really saved a copied result. A truthful count is part of the host contract. Never use a lifetime total from several operations or a count of log lines. For Build and Run, the old operation may contain several completed phases, all of which need their ordinary handover.

## Review and recover

A missing header or linker symbol requires a matching Framework SDK. For a failed runtime assertion, preserve the command, output and source revision. The four lab cases do not verify native process termination or GUI lifetime; execute Framework and Studio checks separately before making those claims.

[Read the C exercise](https://github.com/umicom-foundation/Bits2Banking/blob/main/labs/native/run-restart/main.c) · [Shared service contract](https://github.com/umicom-foundation/umicom-framework/blob/main/include/umicom/build/run_restart.h)

[Course contents](index.md) · [Previous lesson](restart-request-is-not-completion.md) · [Next lesson](restart-renew-project-authority.md)
