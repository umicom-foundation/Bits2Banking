<!--
Umicom Bits2Banking
File: content/lessons/06-umicom/umicom-kernel-from-scratch/63-read-permission-bits.md

PURPOSE:
Read the permission bits attached to a page

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->
# Read the permission bits attached to a page

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


## A mapping also carries permission

A page-table entry records where a page is backed and which access is allowed. The source names READ, WRITE, EXECUTE and USER flags. A flag is a selected bit in an integer; combining flags with bitwise OR creates a set. A required set must be present before access is accepted.

1. Find the rw flags in UmicomTestPrepare.
2. Identify the read-only fixture, which has USER and READ but lacks WRITE.
3. Identify the supervisor fixture, which lacks USER.
4. Follow required = access | USER in the shared locate function.

## Read the expression

(observed & required) != required means at least one required bit is missing. The bitwise AND keeps only bits present in both operands. This expression is a set comparison, not a comparison of numeric privilege levels.

## Exercise

Write the expected result for reading the user read-only page, writing it, and reading the supervisor page through the user-copy API. Run the read-only-write and supervisor-read cases and explain their refusals. Machine-mode code might technically read those bytes; that does not grant the user program permission.

## Read the source

[Open the example source](https://github.com/umicom-foundation/umicom-kernel/blob/main/include/umicom/kernel/virtual_memory.h).

## Continue learning

[Course contents](../../../courses/umicom-kernel-from-scratch/index.html) · [Previous: Draw virtual addresses and physical storage](62-draw-virtual-and-physical-memory.md) · [Next: Check who owns the backing frame](64-check-the-backing-owner.md)
