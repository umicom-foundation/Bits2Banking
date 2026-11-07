<!--
Umicom Bits2Banking
File: content/lessons/06-umicom/umicom-kernel-from-scratch/70-keep-writable-code-out-of-the-model.md

PURPOSE:
Keep writable executable pages outside the user policy

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->
# Keep writable executable pages outside the user policy

An operating system must decide which memory a program may use. This module explains that boundary from bytes and addresses through complete checked copies. Each exercise follows actual Umicom Kernel C source; no prior kernel programming is assumed.

## Prepare for this laboratory

This is a source-reading and host-test module. A host test is an ordinary program running on your current operating system. It exercises Kernel C functions using an array as test memory; it does not boot a machine or change a disk. Install a 64-bit GCC or Clang compiler with C23 support, CMake 3.24 or later and Ninja. Keep a checkout of Umicom Kernel alongside Bits2Banking.

On Windows open PowerShell, then run one command at a time and stop on an error:

~~~powershell
Set-Location "C:\umicom\umicom-kernel"
$env:Path = "C:\msys64\ucrt64\bin;$env:Path"
cmake -S tests/user_memory -B build/host-user-memory -G Ninja -DCMAKE_C_COMPILER=C:/msys64/ucrt64/bin/gcc.exe
cmake --build build/host-user-memory --parallel 2
ctest --test-dir build/host-user-memory --output-on-failure --no-tests=error
~~~

On Linux or macOS open a terminal in the Kernel checkout:

~~~bash
cmake -S tests/user_memory -B build/host-user-memory -G Ninja -DCMAKE_C_COMPILER=clang
cmake --build build/host-user-memory --parallel 2
ctest --test-dir build/host-user-memory --output-on-failure --no-tests=error
~~~

CMake writes build instructions; the build compiles the selected host project; CTest runs its named cases. Expect each selected case to pass before extending it. A missing compiler needs a corrected tool path. An unknown C23 keyword needs a supported compiler. A failed assertion is evidence to investigate, not a reason to remove the check. Open kernel/user_memory.c and tests/user_memory/user_memory_tests.c together. The lesson's source link identifies the relevant repository file.


## Separate data changes from instruction execution

The user-memory policy rejects a page that is both writable and executable. Writable data can change; executable bytes are treated as instructions. Combining these permissions is outside this environment's intended policy. The service also rejects global leaves for these independently owned user address spaces.

1. Find the WRITE and EXECUTE combination in the locate function.
2. Find the GLOBAL check beside it.
3. Inspect the code-page fixture: it is user-readable and executable, but not writable.
4. Compare a normal read/write data page.

## State the limit accurately

A policy check is one protection layer. It does not by itself prove the whole Kernel immune to memory corruption. Its enforcement depends on mapping ownership, entry paths and actual privileged execution. A compiler warning or host test also cannot establish all of those properties.

## Exercise

Build a permission table for data, code, read-only information and supervisor-only memory. Explain which combinations a user copy needs and which it must reject. Use the table when reviewing a new syscall rather than granting every permission for convenience.

## Read the source

[Open the example source](https://github.com/umicom-foundation/umicom-kernel/blob/main/kernel/user_memory.c).

## Continue learning

[Course contents](../../../courses/umicom-kernel-from-scratch/index.html) · [Previous: Explain empty copies and work limits](69-explain-zero-and-oversized-copies.md) · [Next: Release test memory in ownership order](71-release-test-memory-in-owner-order.md)
