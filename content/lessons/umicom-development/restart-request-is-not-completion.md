<!--
Umicom Bits2Banking
File: content/lessons/umicom-development/restart-request-is-not-completion.md

PURPOSE:
Separate a stop request from completion

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->

# Separate a stop request from completion

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

## Follow time explicitly

Cancellation is a request to an executor. The executor may be finishing an output write or waiting for a child to terminate. A user interface must remain responsive while this happens. Starting another program immediately after setting a flag can overlap two executions and mix their results.

## Inspect two states

UmiBuildRunRestartRequest stores one pending intent and requests cancellation. Advance reads the session snapshot, including the task queue’s final access to the task. It returns BUSY while either worker or queue is still active. A timer should advance this intent, not repeatedly create new restart requests.

## Exercise

Read the waiting regression case. Its executor observes cancellation but waits for an explicit release flag before returning. Predict the result of Advance during that gap and the number of executor calls. The expected BUSY result and one call establish that a stop signal alone did not start a replacement.

## Recover without guessing

If the worker never reaches a terminal state, retain output and investigate the executor’s cancellation contract. Increasing timeouts or immediately submitting another task hides the ownership problem. Destruction requests cancellation and joins the worker; it must never turn an unfinished restart into a new launch.

## Review and recover

A missing header or linker symbol requires a matching Framework SDK. For a failed runtime assertion, preserve the command, output and source revision. The four lab cases do not verify native process termination or GUI lifetime; execute Framework and Studio checks separately before making those claims.

[Read the C exercise](https://github.com/umicom-foundation/Bits2Banking/blob/main/labs/native/run-restart/main.c) · [Shared service contract](https://github.com/umicom-foundation/umicom-framework/blob/main/include/umicom/build/run_restart.h)

[Course contents](index.md) · [Previous lesson](restart-own-the-right-operation.md) · [Next lesson](restart-retain-the-old-result.md)
