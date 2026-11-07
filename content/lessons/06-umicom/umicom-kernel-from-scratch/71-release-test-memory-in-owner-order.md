<!--
Umicom Bits2Banking
File: content/lessons/06-umicom/umicom-kernel-from-scratch/71-release-test-memory-in-owner-order.md

PURPOSE:
Release test memory in ownership order

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->
# Release test memory in ownership order

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


## Cleanup is part of the contract

Memory that remains allocated after a test can hide a leak or affect the next case. The fixture has page-table frames owned by the address space and data frames owned by the caller. These are different responsibilities.

1. Read UmicomTestTeardown.
2. Notice that destroying the address space releases its tables.
3. Read the explicit release of caller-owned data frames.
4. Find the final allocator snapshot: allocatedFrames must be zero and freeFrames must equal totalFrames.

## Avoid double release and stale references

Destroying a mapping does not automatically mean the mapped data belongs to the mapping object. Freeing both through an assumed ownership rule can release the same frame twice. Continuing to use a borrowed address after the owner releases it can access a different object later placed there.

## Exercise

Draw the owners before cleanup and cross out each resource after its actual release operation. Explain why the final snapshot is useful but does not replace operation-specific checks. A total count can accidentally match even when the wrong frame was released; allocator validation supplies another check.

## Read the source

[Open the example source](https://github.com/umicom-foundation/umicom-kernel/blob/main/tests/user_memory/user_memory_tests.c).

## Continue learning

[Course contents](../../../courses/umicom-kernel-from-scratch/index.html) · [Previous: Keep writable executable pages outside the user policy](70-keep-writable-code-out-of-the-model.md) · [Next: Distinguish host checks from guest execution](72-distinguish-host-and-guest-evidence.md)
