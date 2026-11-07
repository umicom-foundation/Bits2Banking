<!--
Umicom Bits2Banking
File: content/lessons/06-umicom/umicom-kernel-from-scratch/69-explain-zero-and-oversized-copies.md

PURPOSE:
Explain empty copies and work limits

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->
# Explain empty copies and work limits

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


## Zero has a defined meaning

An empty copy reads and writes no byte. This API explicitly treats zero length as a successful no-op, even with a zero user address. That is a chosen contract, not a general rule that every API must follow. Nonempty operations require valid buffers and allowed access.

1. Find UMICOM_USER_COPY_LIMIT and the public comments.
2. Read the order of checks in Read and Write. Oversized operations are refused before following pointers.
3. Locate zero-length and oversized cases in the host tests.
4. Explain which conditions are irrelevant when no byte is accessed.

## Bound work as well as memory

The current copy budget is 64 bytes per call. A caller moving larger data needs a deliberate chunking protocol. It must handle a later failure and must not claim that many separate calls form one atomic transaction.

## Exercise

Describe a 130-byte transfer in chunks of 64, 64 and 2. If the second call fails, what may already have happened? The first chunk may have completed. Contrast this with one supported 64-byte call whose preflight fails: that call must preserve its destination.

## Read the source

[Open the example source](https://github.com/umicom-foundation/umicom-kernel/blob/main/include/umicom/kernel/user_memory.h).

## Continue learning

[Course contents](../../../courses/umicom-kernel-from-scratch/index.html) · [Previous: Copy bytes across nonadjacent physical frames](68-copy-across-nonadjacent-frames.md) · [Next: Keep writable executable pages outside the user policy](70-keep-writable-code-out-of-the-model.md)
