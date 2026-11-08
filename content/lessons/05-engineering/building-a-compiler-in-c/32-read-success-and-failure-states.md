<!--
Umicom Bits2Banking
File: content/lessons/05-engineering/building-a-compiler-in-c/32-read-success-and-failure-states.md

PURPOSE:
Read successful and failed stack states

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->
# Read successful and failed stack states

## Setup recap

Build the trace-enabled compiler using lesson 31. Keep a text editor open and create a new local example named division.uc containing the program below. Save it as UTF-8 without a byte-order mark; use a folder you own.

```c
int main(void) { return 7 / 0; }
```

## Define when a snapshot is taken

A successful trace row describes the stack after the instruction. A failed row describes the unchanged stack before the rejected instruction. This distinction lets the reader see the operands that caused the fault. The runtime performs arithmetic checks before changing either the stack depth or its value.

For division.uc the two pushes should succeed. The divide row should report depth 2, top 0 and an arithmetic error. There should be no RETURN row and no Result line. The top field shows only the right operand; it does not show both inputs or the entire stack.

## Follow the failed operation

In src/vm.c, execute_validated reads left and right without first reducing depth. It checks division by zero and the INT32_MIN divided by -1 overflow case. Only successful arithmetic publishes the new depth and value. Ordinary execution and traced execution use this same path.

1. Launch umicom-c trace with the full path to division.uc. Expect exit code 1.
2. Read the divide row before the human-readable diagnostic. Its source offset identifies the division operator in the original source.
3. Change the divisor to 2, save and launch again. Expect integer division to produce 3, followed by a successful RETURN.

## Exercise

Predict the trace for return -(2147483647 + 1);. The addition overflows before NEGATE runs. Expect the failing addition to keep its two-input stack, and expect neither a NEGATE nor a RETURN row. The compiler accepts the individual literals; runtime arithmetic still needs its own check.

A failed API call leaves the result object unchanged. A caller must read the returned status before displaying an old result. The Framework adapter deliberately clears its presentation result at the beginning of a new request; the low-level runtime keeps its unchanged-output contract.

## Read the source

[umicom-c/src/vm.c](https://github.com/umicom-foundation/umicom-c/blob/main/src/vm.c). Read the matching checkout when qualifying your own build.

## Continue learning

[Course contents](index.md) · [Previous: Observe an execution trace](31-observe-an-execution-trace.md) · [Next: Reserve trace storage before execution](33-reserve-trace-storage-before-execution.md)
