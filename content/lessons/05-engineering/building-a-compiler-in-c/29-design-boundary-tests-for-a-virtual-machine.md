<!--
Umicom Bits2Banking
File: content/lessons/05-engineering/building-a-compiler-in-c/29-design-boundary-tests-for-a-virtual-machine.md

PURPOSE:
Design boundary tests for a virtual machine

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->
# Design boundary tests for a virtual machine

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


## Boundaries reveal mistakes

A boundary is the point where an allowed input becomes disallowed. For a stack limited to 64 values, 64 is allowed and 65 is rejected. Testing only a two-value sum would never reach that boundary.

The inspection regression constructs a program that pushes 64 ones, combines them with 63 additions and returns. Its peak is 64, its result is 64 and its instruction count is 128. Replacing the first addition with another push attempts a 65th value and must produce a stack-overflow status before writing the report.

1. Find boundary in test_inspection.c.
2. Count the pushes, additions and return yourself.
3. Read the loop that changes the program to overflow. Explain why the altered instruction is encountered before the remaining additions.
4. Follow the later 256-instruction case: one push, 254 negations and one return. This reaches the instruction limit with a peak stack of one.

## Rejection cases need precise expectations

The same test covers an early RETURN with a suffix, an unknown opcode, a reserved nonzero operand, insufficient stack values and an out-of-range source offset. Each must preserve the previous output. The separate CLI test checks argument handling, binary decoding and the wording that distinguishes inspection from execution.

These tests exercise different boundaries. They are not hundreds of copies of the same successful addition. A small set of carefully chosen cases can expose a broader range of mistakes than a large set of repetitive examples.

## Exercise

Design one additional case on paper: a program with two final values at RETURN. Predict the status and the location of the diagnostic. Explain why valid opcodes alone do not make the whole sequence valid.

When running tests, record the source revision, command and result. A test that has only been written has no pass result. A skipped test is missing coverage, and a failing test needs its output retained. Re-run the affected group after a change, then follow the project's wider qualification requirements before release.

## Read the source

[Open the example source](../../../../../umicom-c/tests/test_inspection.c).

## Continue learning

[Course contents](../../../courses/building-a-compiler-in-c/index.html) · [Previous: Preserve output when inspection fails](28-preserve-output-when-inspection-fails.md) · [Next: Present program facts in an IDE](30-present-program-facts-in-an-ide.md)

[Written course contents](index.md)
