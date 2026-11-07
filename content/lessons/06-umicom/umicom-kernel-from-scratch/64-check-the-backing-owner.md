<!--
Umicom Bits2Banking
File: content/lessons/06-umicom/umicom-kernel-from-scratch/64-check-the-backing-owner.md

PURPOSE:
Check who owns the backing frame

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->
# Check who owns the backing frame

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


## Translation alone is not enough

The page walker can translate an address, but the user-memory service also consults Kernel-owned records. Each record identifies a virtual page, its expected physical frame and its expected permissions. This catches a mapping changed to point at another owner's memory or widened permissions.

1. Locate UmicomKernelUserMemoryLocate.
2. Follow the translation into physical and observed permissions.
3. Find virtualBase and physicalBase; masking away the page offset identifies the whole page.
4. Read the loop that matches the backing record and compares both frame and permissions.

## An explicit trust boundary

The records passed to this service are internal, live Kernel data. An untrusted user cannot supply an arbitrary pointer to a replacement record array. Checking pageCount bounds does not make an arbitrary host pointer safe to dereference.

## Exercise

Follow span-write-mismatched-second in the tests. It deliberately makes one ownership record disagree with the mapping. Predict the refusal and unchanged destination. Then compare unregistered-page: a valid translation without an ownership record must also be refused. These tests teach different checks, so retain both.

## Read the source

[Open the example source](https://github.com/umicom-foundation/umicom-kernel/blob/main/kernel/user_memory.c).

## Continue learning

[Course contents](../../../courses/umicom-kernel-from-scratch/index.html) · [Previous: Read the permission bits attached to a page](63-read-permission-bits.md) · [Next: Check the last requested byte without wrapping](65-check-the-last-requested-byte.md)
