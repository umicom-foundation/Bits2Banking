<!--
Umicom Bits2Banking
File: content/lessons/06-umicom/umicom-kernel-from-scratch/66-inspect-every-page-in-a-span.md

PURPOSE:
Inspect every page in the requested span

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->
# Inspect every page in the requested span

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


## Endpoints can hide a hole

A span is a starting address plus a byte count. Its first and last pages may exist while a page in the middle is missing. The check therefore walks page boundaries instead of validating only two endpoints.

1. Find cursor = address.
2. Locate pageLast, computed by setting the offset bits to one.
3. Read the successful end condition last <= pageLast.
4. Otherwise move to pageLast + 1 and validate the next page. The comparison proves pageLast is below the largest address before this increment.

## Trace a concrete range

Draw pages A, B and C. Mark A and C mapped and B absent. Begin at the first byte of A and request 8,193 bytes: the final byte lies in C. The walker must reach B and refuse before claiming the range is usable.

## Exercise

Find span-missing-middle in the tests. It removes a mapping and creates a later one. Explain why this test calls UserMemoryCheck directly: checking a larger span is separate from the copy function's smaller per-call work limit. A bound on copied bytes does not replace a complete-range checker.

## Read the source

[Open the example source](https://github.com/umicom-foundation/umicom-kernel/blob/main/kernel/user_memory.c).

## Continue learning

[Course contents](../../../courses/umicom-kernel-from-scratch/index.html) · [Previous: Check the last requested byte without wrapping](65-check-the-last-requested-byte.md) · [Next: Preflight the whole copy before changing output](67-preflight-before-copying.md)
