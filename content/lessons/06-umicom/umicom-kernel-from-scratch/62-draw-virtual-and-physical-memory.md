<!--
Umicom Bits2Banking
File: content/lessons/06-umicom/umicom-kernel-from-scratch/62-draw-virtual-and-physical-memory.md

PURPOSE:
Draw virtual addresses and physical storage

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->
# Draw virtual addresses and physical storage

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


## Two ways to name a byte

A byte holds eight bits. An address identifies a byte. A program uses virtual addresses, which the operating system translates to physical storage. Two consecutive virtual pages may occupy separate physical frames. In this lab each page contains 4,096 bytes.

1. Find UMICOM_TEST_DATA, the first test virtual address.
2. Find umicomTestFirst and umicomTestSecond, the physical frames used for two adjacent virtual pages.
3. Notice the allocation of umicomTestOther between them. The test intentionally prevents an assumption that physical frames are adjacent.
4. Draw arrows from each virtual page to its own physical frame.

~~~text
virtual A: offsets 0..4095 -> physical frame first
virtual B: offsets 0..4095 -> physical frame second
                          a different frame lies between them
~~~

## Exercise

A 16-byte read begins at offset 4088 of page A. Compute how many bytes come from each page. There are eight from A and eight from B. Explain why adding 16 to the first physical pointer is not a valid general implementation of that virtual read.

## Result to look for

The cross-page-read case expects the correct byte order even when physical frames are not adjacent. Passing this host case verifies the translation/copy path on this fixture, not physical hardware isolation.

## Read the source

[Open the example source](https://github.com/umicom-foundation/umicom-kernel/blob/main/tests/user_memory/user_memory_tests.c).

## Continue learning

[Course contents](../../../courses/umicom-kernel-from-scratch/index.html) · [Next: Read the permission bits attached to a page](63-read-permission-bits.md)

<!-- Course metadata owns the reading order; retain the existing lesson and add its missing continuation. -->
[Previous lesson](61-design-a-kernel-boundary-test-table.md)
