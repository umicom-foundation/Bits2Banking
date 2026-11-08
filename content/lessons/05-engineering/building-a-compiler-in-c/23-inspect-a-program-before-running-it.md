<!--
Umicom Bits2Banking
File: content/lessons/05-engineering/building-a-compiler-in-c/23-inspect-a-program-before-running-it.md

PURPOSE:
Inspect a program before running it

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->
# Inspect a program before running it

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


## What is being inspected?

A source file is text written for people. Umicom C turns a supported source file into a sequence of instructions. An instruction is one operation such as pushing an integer or adding two integers. Inspection reads that sequence and reports its structure without performing the arithmetic.

The example returns the negative of two plus three times four:

```c
int main(void) { return -(2 + 3 * 4); }
```

The parentheses make the addition happen before the outer negation. Multiplication still happens before addition. The expected result of running the program is -14, but an inspection report should not claim that execution has already succeeded.

## Follow the command

1. Open examples/inspection.uc in a text editor. Notice that its explanatory header is a comment, not executable code.
2. Run the inspect command from the setup section. Read each of its five numbers.
3. Run check on the same file. This reports acceptance of syntax and bytecode structure, without the detailed counts.
4. Run run on the same file. This is the command that executes the arithmetic and should report Result: -14.

The CLI reads the file into a bounded buffer. umc_compile creates instructions; umc_inspect validates and counts them. Neither function opens a window or saves a project. The caller owns those user-interface and storage decisions.

## Exercise and expected observation

Change only the explanatory comment and inspect again. The operation counts should remain the same, although source-byte locations can move. Then change 4 to 5. The counts still remain the same, while the executed result becomes -17. Resource counts describe shape, not mathematical equivalence.

If the parser rejects a change, read the reported line and column and check the punctuation around return. Restore the small example before adding another experiment. Keep acceptance, inspection and execution as separate observations in your notes.

## Read the source

[Open the example source](../../../../../umicom-c/examples/inspection.uc).

## Continue learning

[Course contents](../../../courses/building-a-compiler-in-c/index.html) · [Next: Trace the evaluation stack with a table](24-trace-the-stack-with-a-table.md)

<!-- Course metadata owns the reading order; retain the existing lesson and add its missing continuation. -->
[Previous lesson](22-separate-editor-support-from-language-semantics.md)

[Written course contents](index.md)
