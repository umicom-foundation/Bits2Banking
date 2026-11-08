<!--
Umicom Bits2Banking
File: content/lessons/05-engineering/building-a-compiler-in-c/34-count-the-rejected-fuel-step.md

PURPOSE:
Count the rejected fuel step

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->
# Count the rejected fuel step

## Setup recap

Use the compiler built in lesson 31 and the existing inspection.uc example. It contains seven instructions. Keep the same source for both launches so only the instruction budget changes.

```powershell
& ".\build\windows-ucrt64-debug\bin\umicom-c.exe" trace ".\examples\inspection.uc" --max-steps 7
& ".\build\windows-ucrt64-debug\bin\umicom-c.exe" trace ".\examples\inspection.uc" --max-steps 6
```

## An attempted instruction is not an executed instruction

Fuel is an instruction allowance. Each successfully executed operation consumes one unit, including RETURN. With fuel 6, the six arithmetic operations finish, but RETURN is refused. The trace contains six successful rows and a seventh row whose status is instruction budget exhausted. The seventh row describes the next instruction; it does not mean that instruction executed.

The failed row retains depth 1 and top -14 from the completed NEGATE. No Result line is published. This is why a trace entry count and an execution count are different quantities. On failure the low-level result object is unchanged rather than updated with a partial execution count.

## Understand zero and the validation pass

The C API accepts fuel zero and records the first attempted instruction with an empty stack: depth zero and top zero. The CLI deliberately accepts decimal budgets from 1 to 256, so zero is an API regression case rather than a CLI option. Both contracts are explicit.

Validation examines the entire bounded program before fuel is considered. A malformed suffix is rejected before any execution, even at zero fuel. An instruction allowance is not a wall-clock deadline, a network timeout or an operating-system sandbox.

## Exercise

For the four-instruction program 7 * 6, predict the rows at fuel 0, 1, 2 and 3. Answers: the final attempted depths are 0, 1, 2 and 1, with top values 0, 7, 6 and 42. Each trace contains fuel + 1 rows. At fuel 4 it completes with exactly four successful rows.

The fuel-boundaries regression checks these independent expectations and compares traced status with ordinary execution. Preserve the original source and actual test output when diagnosing a mismatch.

## Read the source

[umicom-c/tests/test_trace.c](https://github.com/umicom-foundation/umicom-c/blob/main/tests/test_trace.c). Read the matching checkout when qualifying your own build.

## Continue learning

[Course contents](index.md) · [Previous: Reserve trace storage before execution](33-reserve-trace-storage-before-execution.md) · [Next: Compare source and bytecode traces](35-compare-source-and-bytecode-traces.md)
