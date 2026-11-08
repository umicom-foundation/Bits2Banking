<!--
Umicom Bits2Banking
File: content/lessons/umicom-development/restart-preserve-cross-thread-stop.md

PURPOSE:
Keep Stop effective across thread boundaries

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->

# Keep Stop effective across thread boundaries

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

## Give state one writer

The frontend owns mutable restart intent. The worker owns execution. A cancellation request may come from another thread, so directly editing the frontend’s pending flag from Cancel would introduce a data race: unsynchronized threads could read and write the same storage.

## Use a narrow atomic signal

The session uses an atomic stop signal for cross-thread communication. Owner-thread calls consume that signal into the restart snapshot. During restart submission, the signal remains sticky across cancellation-token reset so a Stop arriving during admission cannot be silently discarded. Other session inputs remain owner-thread operations.

## Exercise

Read the thread-stop regression case. A Framework thread calls ordinary cancellation, joins, and the owning thread then advances the restart. Predict NOT_FOUND and no second executor call. Compare it with stop in the lab, where the same public cancellation is requested on the main thread.

## State the remaining timing limit

A Stop can arrive after a replacement task is queued. That task then reports cancellation through its terminal result; queue acceptance is not a promise of successful execution. Never use an atomic flag as permission to destroy a session while another caller still uses it. Object lifetime still requires coordination.

## Review and recover

A missing header or linker symbol requires a matching Framework SDK. For a failed runtime assertion, preserve the command, output and source revision. The four lab cases do not verify native process termination or GUI lifetime; execute Framework and Studio checks separately before making those claims.

[Read the C exercise](https://github.com/umicom-foundation/Bits2Banking/blob/main/labs/native/run-restart/main.c) · [Shared service contract](https://github.com/umicom-foundation/umicom-framework/blob/main/include/umicom/build/run_restart.h)

[Course contents](index.md) · [Previous lesson](restart-renew-project-authority.md) · [Next lesson](restart-retain-separate-transcripts.md)
