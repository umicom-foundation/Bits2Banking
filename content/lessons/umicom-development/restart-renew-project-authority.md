<!--
Umicom Bits2Banking
File: content/lessons/umicom-development/restart-renew-project-authority.md

PURPOSE:
Recheck project authority after waiting

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->

# Recheck project authority after waiting

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

## Treat permission as current state

A user may revoke trust while a program is stopping. A pending request records intent, not permanent permission. Restart must re-read the current open project, its trust decision and the launch settings before another operation is submitted.

## Understand the identity

Framework retains digests of the admitted project and profile settings. It compares current settings with those digests and checks that the profile belongs to the supplied project root. This prevents a delayed request from silently launching a different profile. The digest does not identify executable bytes or all inherited environment values.

## Exercise

Run revoke and confirm one executor call. Compare that path with restart, which reaches two. In the source, locate the fresh trusted argument passed to Advance. Then review the changed-after and other-project-after regression cases and explain why an unchanged menu item cannot override either refusal.

## Recover deliberately

When authority no longer matches, the intent is cleared. Open the intended project, review settings and explicitly request a new run after resolving the cause. Do not automatically restore trust or replay old arguments. An unchanged digest provides settings context, while ordinary launch preparation must still recheck file and directory availability.

## Review and recover

A missing header or linker symbol requires a matching Framework SDK. For a failed runtime assertion, preserve the command, output and source revision. The four lab cases do not verify native process termination or GUI lifetime; execute Framework and Studio checks separately before making those claims.

[Read the C exercise](https://github.com/umicom-foundation/Bits2Banking/blob/main/labs/native/run-restart/main.c) · [Shared service contract](https://github.com/umicom-foundation/umicom-framework/blob/main/include/umicom/build/run_restart.h)

[Course contents](index.md) · [Previous lesson](restart-retain-the-old-result.md) · [Next lesson](restart-preserve-cross-thread-stop.md)
