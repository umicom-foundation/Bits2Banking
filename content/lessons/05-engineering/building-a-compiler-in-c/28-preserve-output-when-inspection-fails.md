<!--
Umicom Bits2Banking
File: content/lessons/05-engineering/building-a-compiler-in-c/28-preserve-output-when-inspection-fails.md

PURPOSE:
Preserve output when inspection fails

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->
# Preserve output when inspection fails

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


## A result has a publication point

A caller may already display information about a valid program. When it asks to inspect a new malformed program, a failed call should not leave half of a new report mixed with half of the previous one. umc_inspect therefore leaves the output structure unchanged on failure.

This is a failure-atomic contract: all result fields are published together after success, or none are changed. It does not mean multiple threads can access the same object without synchronization. The caller still owns concurrency and must keep the input immutable during the call.

1. Read the UmcProgramInfo fields in the public header.
2. In test_inspection.c, find the sentinel values 91 through 95. These distinctive values make accidental partial writes visible.
3. Follow an invalid case, such as ADD after only one PUSH. The function must reject it without changing any sentinel field.
4. Find the final assignments in inspect_program. They occur only after every instruction and the final RETURN check.

The diagnostic is separate from the result. It is expected to change to describe the failure. Passing NULL for the optional diagnostic is allowed. Passing NULL for the required info pointer is an invalid argument.

## A user-interface example

Imagine selecting an invalid bytecode file after a valid one. Keep the last successful report labeled with its original file identity. Show the new failure beside the attempted file, or clear the visible report deliberately in the caller. Never silently present the old numbers as if they describe the rejected file.

## Exercise

Draw three boxes: immutable input, output report and diagnostic. List who owns each and when each may change. Then inspect the public comment requiring disjoint buffers. Disjoint means that their memory regions do not overlap. This requirement prevents writing a diagnostic or report over the instructions being read.

The library cannot prove that an arbitrary C pointer names a large enough readable object. Bounds and immutability remain part of the caller contract. Testing malformed contents is valuable, but it does not make invalid pointer arguments safe.

## Read the source

[Open the example source](../../../../../umicom-c/tests/test_inspection.c).

## Continue learning

[Course contents](../../../courses/building-a-compiler-in-c/index.html) · [Previous: Embed the inspector in a C application](27-embed-the-inspector-in-a-c-application.md) · [Next: Design boundary tests for a virtual machine](29-design-boundary-tests-for-a-virtual-machine.md)

[Written course contents](index.md)
