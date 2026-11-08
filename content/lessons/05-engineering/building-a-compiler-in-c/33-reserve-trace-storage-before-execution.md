<!--
Umicom Bits2Banking
File: content/lessons/05-engineering/building-a-compiler-in-c/33-reserve-trace-storage-before-execution.md

PURPOSE:
Reserve trace storage before execution

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->
# Reserve trace storage before execution

## Setup recap

Read the caller-owned buffer examples in the preceding embedding lessons. Open include/umicom_c/trace.h and tests/test_trace.c in the Umicom C checkout. This lesson studies the API contract; the CLI already supplies the maximum storage capacity.

## Separate count from capacity

Capacity is the number of trace entries the caller can store. The returned trace_count is the number currently valid. They are both measured in entries, not bytes. A four-instruction program requires capacity of at least four before execution starts, even when its fuel would allow only one instruction.

The runtime first validates the whole program. For structurally valid input, insufficient trace storage returns UMC_BUFFER_TOO_SMALL, clears trace_count to zero, and leaves the trace array and result untouched. It does not execute a prefix and then discover that the report is incomplete.

```c
UmcTraceStep steps[UMC_PROGRAM_LIMIT];
size_t used = 0U;
UmcStatus status = umc_execute_trace(program, count, fuel, &result,
    steps, UMC_PROGRAM_LIMIT, &used, &diagnostic);
```

## Give each object an owner

The caller owns the immutable program, result, trace array, count and optional diagnostic. Keep the writable objects disjoint from each other and from the input. The runtime does not retain their addresses. Concurrent previews need independent writable storage; making two pointers to the same array does not create two owners.

Only entries below used belong to this request. Bytes after used may contain an earlier trace. Resetting a count does not securely erase the entire array. A UI must use the count to decide which rows to show.

## Exercise and check

In test_trace.c, compare short-capacity, zero-capacity and reuse. The first two require zero published entries and unchanged bytes. Reuse checks that a shorter failed run cannot inherit the previous count. Add a deliberate local capacity change only in an exercise copy, then predict the status before running your qualification.

Answer: count is cleared on entry when its pointer is valid. A NULL count pointer cannot be written and is rejected. Invalid storage is not a runtime arithmetic fault, so it has no attempted-step row. The runtime uses bounded local stack storage and no heap allocation or callback.

## Read the source

[umicom-c/include/umicom_c/trace.h](https://github.com/umicom-foundation/umicom-c/blob/main/include/umicom_c/trace.h). Read the matching checkout when qualifying your own build.

## Continue learning

[Course contents](index.md) · [Previous: Read successful and failed stack states](32-read-success-and-failure-states.md) · [Next: Count the rejected fuel step](34-count-the-rejected-fuel-step.md)
