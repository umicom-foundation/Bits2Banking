<!--
Umicom Bits2Banking
File: content/lessons/05-engineering/building-a-compiler-in-c/27-embed-the-inspector-in-a-c-application.md

PURPOSE:
Embed the inspector in a C application

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->
# Embed the inspector in a C application

This module follows one small program from text to an inspectable instruction sequence. Each lesson defines its terms, shows a concrete operation and gives an exercise with an expected observation. Inspection describes the program; execution attempts its arithmetic. A compiler, an IDE and a teaching tool can all use the same library contracts.

A terminal is a window in which commands are typed. A compiler translates source text into instructions; CMake describes a build and Ninja carries out its steps. Install Git and the MSYS2 UCRT64 GCC, CMake and Ninja packages if these tools are not available. The [Learning Build Systems course](../../../courses/learning-build-systems/index.html) explains their roles in more depth.

1. Keep the Umicom C and Bits2Banking checkouts beside each other in a folder you choose. The examples use C:\umicom. Replace that location consistently if yours differs.
2. In the MSYS2 UCRT64 terminal, install the tools with the following command. Complete the package manager's normal update instructions first if it requests them.

```bash
pacman -S --needed mingw-w64-ucrt-x86_64-gcc mingw-w64-ucrt-x86_64-cmake mingw-w64-ucrt-x86_64-ninja
```

3. Open PowerShell and build the small compiler. Run each line separately. If a command reports an error, stop and read it before continuing.

```powershell
Set-Location "C:\umicom\umicom-c"
$env:Path = "C:\msys64\ucrt64\bin;$env:Path"
cmake --preset windows-ucrt64-debug -DBUILD_TESTING=ON
cmake --build --preset windows-ucrt64-debug --parallel 2
ctest --preset windows-ucrt64-debug --output-on-failure --no-tests=error
& ".\build\windows-ucrt64-debug\bin\umicom-c.exe" inspect ".\examples\inspection.uc"
```

On Linux, install a C23-capable C compiler, CMake and Ninja with your distribution's package manager. From the umicom-c checkout use the native-debug preset:

```bash
cmake --preset native-debug -DBUILD_TESTING=ON
cmake --build --preset native-debug --parallel 2
ctest --preset native-debug --output-on-failure --no-tests=error
./build/native-debug/bin/umicom-c inspect ./examples/inspection.uc
```

The inspection example should report 7 instructions, a peak stack of 3 values, 3 constants, 3 arithmetic operations and 71 encoded bytes. These are expected results to check on your machine. The language currently supports one integer-returning main function with arithmetic; it does not compile the full C language. If inspect is an unknown command, check that the binary was rebuilt from source containing umc_inspect. Keep any previous logs when investigating a failure.


## What embedding means

Embedding a library means calling its functions from another program. The lab does this with Umicom C instead of starting its CLI. It owns a source string, an instruction array, a diagnostic and a result structure. The library borrows these objects during each call and does not retain their addresses.

1. Open labs/native/compiler-inspection/main.c.
2. Find source, a constant character array. sizeof(source) includes its terminating zero byte, so the compiler receives sizeof(source) - 1U as the text length.
3. Find program, an array with UMC_PROGRAM_LIMIT entries. count starts at zero.
4. Follow umc_compile. On failure the program prints the static diagnostic message and returns before reading any partial instruction output.
5. Follow umc_inspect. It fills info only after complete validation succeeds.
6. Follow the --run branch. Execution remains an explicit separate choice.

## Build just the lab

```powershell
Set-Location "C:\umicom\Umicom-Bits2Banking"
$env:Path = "C:\msys64\ucrt64\bin;$env:Path"
cmake -S labs/native/compiler-inspection -B build/compiler-inspection -G Ninja -DBUILD_TESTING=ON
cmake --build build/compiler-inspection --parallel 2
ctest --test-dir build/compiler-inspection --output-on-failure --no-tests=error
& ".\build\compiler-inspection\compiler-inspection.exe"
& ".\build\compiler-inspection\compiler-inspection.exe" --run
```

The first launch should report the resource counts and say that no program instructions were executed. The second should additionally report -14. The CMake project links UmicomC::Compiler and receives its Runtime dependency; it does not copy the lexer or evaluator into the lesson.

On Linux use the same cmake commands and launch ./build/compiler-inspection/compiler-inspection. If the compiler checkout is elsewhere, pass -DUMICOM_C_SOURCE followed by its absolute path when configuring. A missing checkout is a dependency-location error, not a source-language error.

## Extend the example

Change the source expression, rebuild and inspect it. Keep the error checks. Do not read info after a failed call or execute a partial compile result. Those ownership and status rules are the same ones an IDE integration needs.

## Read the source

<!-- The lab remains repository source; this earlier checkout-only link is retained for review.
[Open the example source](https://github.com/umicom-foundation/Bits2Banking/blob/main/labs/native/compiler-inspection/main.c)
-->
[Open the example source](https://github.com/umicom-foundation/Bits2Banking/blob/main/labs/native/compiler-inspection/main.c).

## Continue learning

[Course contents](../../../courses/building-a-compiler-in-c/index.html) · [Previous: Count execution budgets and encoded bytes](26-count-execution-budgets-and-wire-bytes.md) · [Next: Preserve output when inspection fails](28-preserve-output-when-inspection-fails.md)

[Written course contents](index.md)
