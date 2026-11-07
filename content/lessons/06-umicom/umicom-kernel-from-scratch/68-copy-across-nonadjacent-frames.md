<!--
Umicom Bits2Banking
File: content/lessons/06-umicom/umicom-kernel-from-scratch/68-copy-across-nonadjacent-frames.md

PURPOSE:
Copy bytes across nonadjacent physical frames

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->
# Copy bytes across nonadjacent physical frames

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


## A correct copy preserves virtual order

The test places known bytes near the end of one frame and the start of another. The read must produce their virtual sequence. This expected sequence is calculated independently of the production walker so that the test does not simply repeat the same implementation mistake.

1. Find UmicomTestSpanContract and its span-read-boundaries branch.
2. Read the loop over split values 1 through 63. Each value moves the boundary inside a 64-byte request.
3. Identify the two guard bytes around the output span.
4. Follow the expected value formula separately for the first and second page.

## Exercise

For split = 3, draw the output: the first three bytes come from the end of page A and the remaining 61 from page B. Work out the first byte and fourth byte using the test's fixture pattern. Then inspect the write-boundaries branch, which checks every byte of both destination pages, including bytes outside the request.

## Why these are functional checks

Checking only a success return would miss wrong byte order and off-by-one writes. Guards and full-region comparison test the actual memory effect. They do not prove behavior for every possible address or platform.

## Read the source

[Open the example source](https://github.com/umicom-foundation/umicom-kernel/blob/main/tests/user_memory/user_memory_tests.c).

## Continue learning

[Course contents](../../../courses/umicom-kernel-from-scratch/index.html) · [Previous: Preflight the whole copy before changing output](67-preflight-before-copying.md) · [Next: Explain empty copies and work limits](69-explain-zero-and-oversized-copies.md)
