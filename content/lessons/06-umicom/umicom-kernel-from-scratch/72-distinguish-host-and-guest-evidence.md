<!--
Umicom Bits2Banking
File: content/lessons/06-umicom/umicom-kernel-from-scratch/72-distinguish-host-and-guest-evidence.md

PURPOSE:
Distinguish host checks from guest execution

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->
# Distinguish host checks from guest execution

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


## Ask what the test actually executes

The host project compiles real C allocator, page-walker, copy and dispatch code. Its physical RAM is an aligned array. It does not execute RISC-V privilege transitions. A guest test boots the Kernel under a machine emulator and exercises those architecture-specific paths.

1. Record the compiler, platform and source revision for a host run.
2. Record selected case names and outcomes, keeping skips separate from passes.
3. Follow the Kernel's RISC-V setup guide before attempting guest tests.
4. Keep guest results separate, including the exact image and emulator configuration.

## Read a failure carefully

A timeout means the expected finish was not observed. A missing executable means the test did not exercise the intended code. Neither result demonstrates isolation. Sanitizers add instrumentation for some classes of memory errors, but only when the actual toolchain supports and enables them.

## Exercise

Write two claims supported by a successful host boundary test and two claims it cannot support. For example, exact copied bytes are observed in the fixture; hardware page-fault handling is not. This distinction prevents a useful laboratory from becoming an unsupported release claim.

## Read the source

[Open the example source](https://github.com/umicom-foundation/umicom-kernel/blob/main/docs/USER_MEMORY_BOUNDARIES.md).

## Continue learning

[Course contents](../../../courses/umicom-kernel-from-scratch/index.html) · [Previous: Release test memory in ownership order](71-release-test-memory-in-owner-order.md) · [Next: Design a new buffer service from its contract](73-design-a-safe-new-buffer-service.md)
