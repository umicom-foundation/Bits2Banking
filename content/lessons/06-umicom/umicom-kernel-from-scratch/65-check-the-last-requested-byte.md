<!--
Umicom Bits2Banking
File: content/lessons/06-umicom/umicom-kernel-from-scratch/65-check-the-last-requested-byte.md

PURPOSE:
Check the last requested byte without wrapping

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->
# Check the last requested byte without wrapping

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


## Unsigned arithmetic still needs bounds

An unsigned integer wraps when a result exceeds its largest representable value. A wrapped range could look small even when the request is huge. UmicomKernelAddressAddChecked compares the amount with maximumAddress - base before adding. The successful comparison proves the addition fits.

1. Read the zero-length return in UmicomKernelUserMemoryCheck.
2. For a nonempty request find address + bytes - 1, computed through the checked helper.
3. Explain why the subtraction bytes - 1 is safe only after excluding zero.
4. Find the canonical-address checks for the first and last byte. Canonical means the address representation obeys the architecture's required high-bit form.

## Exercise

Use a small imaginary 8-bit address space, whose maximum is 255. Starting at 250 with six bytes ends at 255 and fits; seven bytes would require 256. Now explain the same reasoning using the Kernel's actual address type. This arithmetic exercise does not authorize reading any of those addresses.

## Expected refusal

The range-wrap case should return BAD_ADDRESS without copying. A numeric range fitting the type is necessary, but mapped pages and permissions must still be checked.

## Read the source

[Open the example source](https://github.com/umicom-foundation/umicom-kernel/blob/main/kernel/address.c).

## Continue learning

[Course contents](../../../courses/umicom-kernel-from-scratch/index.html) · [Previous: Check who owns the backing frame](64-check-the-backing-owner.md) · [Next: Inspect every page in the requested span](66-inspect-every-page-in-a-span.md)
