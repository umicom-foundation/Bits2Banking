<!--
Umicom Bits2Banking
File: content/lessons/05-engineering/building-a-compiler-in-c/67-prove-local-initialization-before-execution.md

PURPOSE:
Prove local initialization before execution

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->

![Umicom](../../../assets/branding/umicom-wordmark.svg)

# Prove local initialization before execution

## Goal

Understand why the runtime must validate local operations even when the compiler already checks names. A bytecode consumer can receive data from another producer. It must enforce its own storage contract.

## Separate two kinds of memory

The operand stack holds temporary expression values. A local slot holds an integer that can be read repeatedly during one invocation. Neither is a native address exposed to the program. The runtime has 32 slots and a 64-value operand stack.

~~~text
PUSH 42
STORE_LOCAL 31
LOAD_LOCAL 31
RETURN
~~~

STORE pops one stack value into the highest valid slot. LOAD pushes a copy. RETURN still needs exactly one value and must be last. A local store consumes one instruction of fuel just like addition.

## Construct the proof

1. Start an unsigned 32-bit initialization map at zero.
2. For a slot operation, reject negative operands and operands at least 32 before shifting or indexing.
3. For STORE, require one stack value, reduce depth and set the slot's bit.
4. For LOAD, require that bit and space on the stack, then increase depth.
5. Check every instruction and the final return before executing any instruction.

This proof works because the supported program is straight-line. A future branch would require reasoning about every path reaching a load. Reusing this single linear map unchanged for branching code would be incorrect.

The executor can use an automatic local array without reading an uninitialized element because admission proves every read has a preceding write. The array belongs to one call. Executing a valid program first must never initialize a slot for a later invalid program.

## Inspect independent tests

Read tests/test_local_runtime.c. The runtime-only target deliberately does not link the compiler. It supplies its own instruction arrays and literal format-3 bytes, checks slot 31, rejects -1 and 32, and attempts to read a different slot from the one stored. Sentinel results and trace entries prove that refusal does not publish partial success.

~~~powershell
ctest --test-dir build -R "umicom.c.locals.runtime" --output-on-failure --no-tests=error
~~~

The fuel test tries every budget below the eight-instruction workload. A failed trace includes the attempted instruction. Exhaustion before STORE leaves the stack value visible in that failed row, while the public result remains unchanged. Trace capacity failure and malformed bytecode happen before execution and publish zero trace entries.

## Preserve the wire contract

Local operations append opcode identities 14 and 15. They require format 3 while retaining the eight-byte header and nine-byte records. Arithmetic-only programs keep format 1; comparisons without locals keep format 2. The decoder requires the minimum profile, so changing a header byte cannot downgrade local operations or relabel arithmetic as format 3.

The encoder must inspect beyond an early comparison. Otherwise it could return format 2 before noticing a later STORE. The mixed-operation fixture checks this ordering directly.

## Exercise

Draw stack depth and initialized bits after each operation in the four-record example. Then replace its load operand with 30. Predict the rejection point and which output sentinels must remain intact. Explain why a successful previous execution, spare fuel or a large output buffer cannot make that read valid. Finally compare header capability macros with linked profile queries: a new header alone does not update an installed runtime.


[Course contents](index.md) · [Previous lesson](66-bind-local-names-to-slots.md) · [Next lesson](68-lower-short-circuit-logical-expressions.md)
