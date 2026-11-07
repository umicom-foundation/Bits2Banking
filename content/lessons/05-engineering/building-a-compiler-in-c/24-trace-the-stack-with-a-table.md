<!--
Umicom Bits2Banking
File: content/lessons/05-engineering/building-a-compiler-in-c/24-trace-the-stack-with-a-table.md

PURPOSE:
Trace the evaluation stack with a table

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->
# Trace the evaluation stack with a table

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


## A stack holds temporary values

A stack is a collection where the most recently added value is the first one removed. Here it holds temporary integers while an expression is evaluated. PUSH adds a value. A binary operation removes two values and puts their result back. NEGATE changes the top value. RETURN requires exactly one value.

For the example, the stack can be followed without running a computer:

| Instruction | Stack after the instruction | Depth |
| --- | --- | --- |
| PUSH 2 | 2 | 1 |
| PUSH 3 | 2, 3 | 2 |
| PUSH 4 | 2, 3, 4 | 3 |
| MULTIPLY | 2, 12 | 2 |
| ADD | 14 | 1 |
| NEGATE | -14 | 1 |
| RETURN | returns -14 | 1 |

Depth means the number of values currently present. Peak depth means the largest depth seen at any point. The final depth is one, while the peak is three. These answer different questions.

## Read the shared implementation

1. Open src/vm.c and find inspect_program, below the preserved earlier validator.
2. Find depth and peak. Both start at zero.
3. Follow PUSH: the function checks the stack limit before increasing depth, then updates peak.
4. Follow ADD, SUBTRACT, MULTIPLY and DIVIDE: each requires two values and reduces depth by one.
5. Follow RETURN: it rejects an incorrect depth and any instructions after the return.

The inspection walk does not need actual temporary integer values. It only needs how each operation changes the number of them. The execution function separately computes the values with overflow and division checks.

## Try another expression

Trace (2 + 3) * 4. Its sequence pushes 2 and 3, adds them, pushes 4, multiplies and returns. The peak is two. Compare that with 2 + 3 * 4, whose peak is three. Count the operations carefully before checking your answer with inspect.

A smaller peak does not by itself prove a program is faster. The inspector reports properties of this interpreter's instruction sequence, not processor cache use or elapsed time. If your table disagrees with the report, use disassemble on a compiled bytecode file to inspect the actual operation order.

## Read the source

[Open the example source](../../../../../umicom-c/src/vm.c).

## Continue learning

[Course contents](../../../courses/building-a-compiler-in-c/index.html) · [Previous: Inspect a program before running it](23-inspect-a-program-before-running-it.md) · [Next: Distinguish structure from arithmetic safety](25-distinguish-structure-from-arithmetic-safety.md)
