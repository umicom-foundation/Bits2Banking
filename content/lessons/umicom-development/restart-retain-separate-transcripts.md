<!--
Umicom Bits2Banking
File: content/lessons/umicom-development/restart-retain-separate-transcripts.md

PURPOSE:
Preserve separate transcripts for each run

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->

# Preserve separate transcripts for each run

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

## Separate operation evidence

Two runs can print identical output while using different operation identifiers. Reopening the old transcript for writing would erase evidence of the first run. A restart needs a fresh destination, and failure to reserve it must not destroy the original file.

## Trace the naming rule

When capture was enabled, the service appends .restart-<next operation id> to the complete old pathname. It uses the same trusted directory and performs exclusive creation at submission. No parent folders are created. A run without capture restarts without making a transcript.

## Exercise

Inspect the Framework log and log-collision cases. The collision fixture writes a distinct sentence into the proposed new file before advancing. Its assertions require both that sentence and the first run’s transcript to remain unchanged. Predict how many executors ran and why a new filename does not itself prove a new launch.

## Recover without losing history

Keep a colliding file for review. Choose a fresh log path through the ordinary launch workflow, then make a new explicit run request. Do not delete all matching log files as a convenience. Transcripts can contain private output; store them in an appropriate evidence directory rather than committing them with public teaching material.

## Review and recover

A missing header or linker symbol requires a matching Framework SDK. For a failed runtime assertion, preserve the command, output and source revision. The four lab cases do not verify native process termination or GUI lifetime; execute Framework and Studio checks separately before making those claims.

[Read the C exercise](https://github.com/umicom-foundation/Bits2Banking/blob/main/labs/native/run-restart/main.c) · [Shared service contract](https://github.com/umicom-foundation/umicom-framework/blob/main/include/umicom/build/run_restart.h)

[Course contents](index.md) · [Previous lesson](restart-preserve-cross-thread-stop.md) · [Next lesson](restart-connect-menu-and-refresh.md)
