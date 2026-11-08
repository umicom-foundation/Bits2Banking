<!--
Umicom Bits2Banking
File: content/lessons/umicom-development/restart-qualify-each-layer.md

PURPOSE:
Qualify restart at each ownership boundary

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->

# Qualify restart at each ownership boundary

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

## Name what the exercise proves

The installed-SDK lab uses a controlled executor and creates no child process. It checks calls through the shared service, its worker lifecycle and result handover. A passing lab cannot establish that a Windows process tree terminates correctly or that a GTK menu remains usable.

## Add the appropriate next evidence

Framework’s controlled scenarios cover phases, settings, cancellation and transcript contracts. Studio’s native scenarios add a real bounded child, the actual workbench and unsaved document state. Manual pointer and keyboard checks add usability evidence beyond programmatically invoking a widget. Keep these results separate.

## Exercise

Create a four-column record containing source revision, command, observed result and uncovered behavior. Add one row for the lab, one for a Framework scenario and one for a native Studio scenario. Leave the result unexecuted until you actually run that command in the intended environment. Record skipped coverage separately from passes.

## Diagnose the first boundary that failed

A missing SDK symbol is a build/integration issue. A BUSY deadline is a lifecycle observation. A recreated marker under the wrong operation identifier is an ownership defect. Start with the precise failed assertion and preserve its environment and source identity. Authored tests and static inspection are useful preparation but cannot replace execution evidence.

## Review and recover

A missing header or linker symbol requires a matching Framework SDK. For a failed runtime assertion, preserve the command, output and source revision. The four lab cases do not verify native process termination or GUI lifetime; execute Framework and Studio checks separately before making those claims.

[Read the C exercise](https://github.com/umicom-foundation/Bits2Banking/blob/main/labs/native/run-restart/main.c) · [Shared service contract](https://github.com/umicom-foundation/umicom-framework/blob/main/include/umicom/build/run_restart.h)

[Course contents](index.md) · [Previous lesson](restart-connect-menu-and-refresh.md) · [Next lesson](workflow-admit-the-whole-request.md)
