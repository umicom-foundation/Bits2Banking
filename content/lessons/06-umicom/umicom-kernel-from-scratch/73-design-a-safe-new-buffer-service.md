<!--
Umicom Bits2Banking
File: content/lessons/06-umicom/umicom-kernel-from-scratch/73-design-a-safe-new-buffer-service.md

PURPOSE:
Design a new buffer service from its contract

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->
# Design a new buffer service from its contract

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


## Begin with a small service description

Suppose a future syscall returns a short diagnostic record to a user buffer. Before writing its handler, define who owns each buffer, the maximum byte count, permissions, zero-length behavior and the result on refusal. A syscall is a controlled request from a program into the Kernel.

1. Write the public input/output contract.
2. Decide whether the operation needs read or write access and use the existing copy service.
3. Prepare a candidate diagnostic record in trusted storage.
4. Validate the complete user destination before publishing bytes.
5. Return a result the caller can distinguish from success.

## Build a test table

Include a valid one-page destination, a cross-page destination, missing second page, read-only second page, wrong backing owner, overflow, zero length and an oversized request. For every refusal state which output bytes and Kernel records must remain unchanged. Reuse the existing host fixture before adding separate guest coverage.

## Project exercise

Write a design note for an eight-byte counter response. Draw the call sequence and explain why you must not cast a user-provided register value directly to a writable Kernel pointer. This lesson is a design exercise; it does not add or advertise a new syscall.

## Read the source

[Open the example source](https://github.com/umicom-foundation/umicom-kernel/blob/main/include/umicom/kernel/user_memory.h).

## Continue learning

[Course contents](../../../courses/umicom-kernel-from-scratch/index.html) · [Previous: Distinguish host checks from guest execution](72-distinguish-host-and-guest-evidence.md)

<!-- Course metadata owns the reading order; retain the existing lesson and add its missing continuation. -->
[Next lesson](74-describe-the-startup-handoff.md)
