<!--
Umicom Bits2Banking
File: content/lessons/05-engineering/building-a-compiler-in-c/25-distinguish-structure-from-arithmetic-safety.md

PURPOSE:
Distinguish structure from arithmetic safety

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->
# Distinguish structure from arithmetic safety

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


## Different checks answer different questions

Structural validation asks whether every instruction is recognized, its operand is legal and the stack has enough values. Arithmetic checks ask whether an operation can produce a valid signed 32-bit result. Both matter, but passing the first does not imply passing the second.

Consider return 1 / 0;. The instruction sequence has two pushes, a divide and a return. Its stack shape is valid. Division by zero nevertheless has no supported integer result.

1. Create a separate source file containing int main(void) { return 1 / 0; }.
2. Inspect it. Expect four instructions, two peak stack values, two constants, one arithmetic operation and 44 encoded bytes.
3. Execute it with run. Expect an arithmetic error and a nonzero exit status.
4. Open tests/test_inspection.c and find zero_divisor. It asserts exactly this separation.

A nonzero exit status is a number a command returns to say it failed. In PowerShell, inspect $LASTEXITCODE immediately after the command. In Bash, inspect $? immediately. A later command can replace that value.

## Why the distinction matters in Studio

A project panel might display “Structure accepted” after inspection. It should wait for actual execution before displaying “Run succeeded.” Likewise, a build can succeed while a program later fails on input. Clear status labels help a learner identify the stage that needs attention.

The runtime uses wider intermediate arithmetic before checking the signed 32-bit range. It also handles the special division case where the smallest signed value is divided by -1. The inspector does not duplicate that evaluator; it never promises a result value.

## Exercise

Inspect and run return 2147483647 + 1;. Predict the two outcomes before issuing commands. Then try a decimal literal larger than the compiler accepts. That failure occurs during compilation, earlier than either inspection or execution. Write three rows in a notebook: rejected source, accepted structure with failing arithmetic, and successful execution. This is a useful pattern for testing any parser followed by a calculation engine.

## Read the source

[Open the example source](../../../../../umicom-c/tests/test_inspection.c).

## Continue learning

[Course contents](../../../courses/building-a-compiler-in-c/index.html) · [Previous: Trace the evaluation stack with a table](24-trace-the-stack-with-a-table.md) · [Next: Count execution budgets and encoded bytes](26-count-execution-budgets-and-wire-bytes.md)

[Written course contents](index.md)
