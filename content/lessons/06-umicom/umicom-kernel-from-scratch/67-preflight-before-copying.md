<!--
Umicom Bits2Banking
File: content/lessons/06-umicom/umicom-kernel-from-scratch/67-preflight-before-copying.md

PURPOSE:
Preflight the whole copy before changing output

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->
# Preflight the whole copy before changing output

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


## Refusal should preserve the destination

Preflight means validating the complete operation before its first visible write. A copy that writes page A and then discovers that page B is forbidden has already changed state. The shared read and write services call UserMemoryCheck for the entire span first.

1. Find the maximum-copy check.
2. Find the empty-copy and null-buffer handling.
3. Find the complete-range check before the byte loop.
4. Observe that the copy loop uses the same translation and ownership service.

## The concurrency assumption matters

This implementation relies on a single-hart, non-reentrant monitor: one hardware execution context runs this path, and mappings cannot change during validation and copy. A future concurrent mapper would require another design, such as stable ownership during the operation. Preflight alone cannot prevent a different worker from changing a page afterward.

## Exercise

Read span-read-refused-second. A destination filled with a known marker must remain entirely unchanged when the second source page is absent. Compare span-write-readonly-second, which checks both physical pages. Describe the visible corruption each check would catch if the preflight were removed.

## Read the source

[Open the example source](https://github.com/umicom-foundation/umicom-kernel/blob/main/kernel/user_memory.c).

## Continue learning

[Course contents](../../../courses/umicom-kernel-from-scratch/index.html) · [Previous: Inspect every page in the requested span](66-inspect-every-page-in-a-span.md) · [Next: Copy bytes across nonadjacent physical frames](68-copy-across-nonadjacent-frames.md)
