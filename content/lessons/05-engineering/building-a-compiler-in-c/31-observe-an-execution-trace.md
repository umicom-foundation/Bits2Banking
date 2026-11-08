<!--
Umicom Bits2Banking
File: content/lessons/05-engineering/building-a-compiler-in-c/31-observe-an-execution-trace.md

PURPOSE:
Observe an execution trace

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->
# Observe an execution trace

## Setup recap

Complete the preceding compiler inspection module. You need the Umicom C checkout, a C23 compiler, CMake, Ninja and a terminal. The examples below use the existing Windows UCRT64 preset. Run each command separately and stop on errors; an unknown trace command usually means an older executable is being launched.

```powershell
Set-Location "C:\umicom\umicom-c"
$env:Path = "C:\msys64\ucrt64\bin;$env:Path"
cmake --preset windows-ucrt64-debug -DBUILD_TESTING=ON
cmake --build --preset windows-ucrt64-debug --parallel 2
& ".\build\windows-ucrt64-debug\bin\umicom-c.exe" trace ".\examples\inspection.uc"
```

## Read the rows as observations

A trace is a record of attempted execution. Earlier lessons predicted the stack with a table; this command asks the shared runtime to report what it did. Each row identifies an instruction index, a source byte offset, an operation, a stack depth, the top value and a status. The instruction index starts at zero. It is a position in the compiled instruction array, not a source line number.

The existing inspection example returns -(2 + 3 * 4). Expect seven rows: push 2, push 3, push 4, multiply, add, negate and return. Successful top values should be 2, 3, 4, 12, 14, -14 and -14. The depths should be 1, 2, 3, 2, 1, 1 and 1. The reported source offsets come from the actual file, including its comments.

## Keep inspection and execution distinct

The inspect command describes validated structure without doing the arithmetic. The trace command executes the arithmetic and can fail, just as run can. It does not save a bytecode artifact or launch native code. A successful trace includes RETURN and is followed by the result. Seeing an intermediate value of -14 alone is insufficient to claim completion.

The implementation lives in Umicom C. The CLI owns trace storage and formats the returned entries; it does not copy the evaluator. The same public API is available to Framework and freestanding consumers.

## Try it and explain it

Question: why are there two final rows with top -14? Answer: NEGATE produces the value; RETURN completes the function while retaining that value. A trace is not a breakpoint controller or a full copy of the operand stack.

1. Before launching, write the seven predicted depths on paper.
2. Compare your table with the command output. If a row differs, identify the operation that changed the depth before changing code.
3. Run the existing compiler-inspection lab with --trace after rebuilding it. Its shorter display should show the same arithmetic states.

## Read the source

[umicom-c/tools/main.c](https://github.com/umicom-foundation/umicom-c/blob/main/tools/main.c). Read the matching checkout when qualifying your own build.

## Continue learning

[Course contents](index.md) · [Previous: Present program facts in an IDE](30-present-program-facts-in-an-ide.md) · [Next: Read successful and failed stack states](32-read-success-and-failure-states.md)
