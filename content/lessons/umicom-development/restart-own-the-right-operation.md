<!--
Umicom Bits2Banking
File: content/lessons/umicom-development/restart-own-the-right-operation.md

PURPOSE:
Choose the operation you actually own

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->

# Choose the operation you actually own

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

## Identify the owner

A project session owns one queued workflow. Its requested phase describes the original action, while current_phase describes the step executing now. Build and Run can currently be configuring, compiling or running. A restart command must inspect both fields before selecting the program it intends to stop.

## Read the shared check

Open Framework’s run_restart.inc and find UmiBuildRunRestartReview. It requires requested_phase and current_phase to equal RUN, an active session, no earlier cancellation and a matching admitted profile. A debugger or separate program console has a different owner; a familiar menu label does not grant this session control over either.

## Exercise

Run the lab with restart, then inspect the Framework configure, build, test, run-configure and run-build regression cases. Write a table of requested/current phase pairs and predict which rows should be admitted. The tests use a controlled executor that holds a selected phase, making the distinction observable.

## Explain a refusal

If Restart is disabled during compilation, wait for the Run phase or cancel the build explicitly. Do not change the command to kill an arbitrary process by name. The service boundary is a specific owned operation, and its copied settings protect the running worker from unrelated frontend edits.

## Review and recover

A missing header or linker symbol requires a matching Framework SDK. For a failed runtime assertion, preserve the command, output and source revision. The four lab cases do not verify native process termination or GUI lifetime; execute Framework and Studio checks separately before making those claims.

[Read the C exercise](https://github.com/umicom-foundation/Bits2Banking/blob/main/labs/native/run-restart/main.c) · [Shared service contract](https://github.com/umicom-foundation/umicom-framework/blob/main/include/umicom/build/run_restart.h)

[Course contents](index.md) · [Previous lesson](evidence-runtime-and-patch-identity.md) · [Next lesson](restart-request-is-not-completion.md)
