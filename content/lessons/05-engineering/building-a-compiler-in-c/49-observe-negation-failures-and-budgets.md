<!--
Umicom Bits2Banking
File: content/lessons/05-engineering/building-a-compiler-in-c/49-observe-negation-failures-and-budgets.md

PURPOSE:
Observe operand failure before negation

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->

![Umicom](../../../assets/branding/umicom-wordmark.svg)

# Observe operand failure before negation

## Before you begin
Read the trace and execution-budget lessons. A compile-time structure check and a runtime arithmetic result are separate observations.

## Negation still evaluates its operand
The expression !(1 / 0) cannot become 0 or 1 because evaluating its operand fails. The equality introduced for ! is never reached after the division error.

~~~text
PUSH 1
PUSH 0
DIVIDE        refuses division by zero
PUSH 0        not reached
EQUAL         not reached
RETURN        not reached
~~~

1. Trace the stack immediately before DIVIDE.
2. Identify the instruction that reports the arithmetic failure.
3. Confirm that no successful Result is published.
4. Preserve the caller's previous result object on failure.

## Count the whole cost
!0 needs four executed instructions including RETURN. A budget of three reaches the return boundary with no fuel left. A budget of two fails before equality completes. The trace can include the refused step, so the number of trace records is not always the number of completed instructions.

## Exercise and expected result
Use the lowered !0 sequence from the previous lesson. Make a table with budgets 1, 2, 3 and 4. For each, name the next refused instruction or the final result. Only budget 4 completes this sequence.

Then compare short trace storage with short execution fuel. Insufficient storage is a pre-execution refusal; fuel exhaustion is an execution boundary. Treating both as an empty successful trace would hide useful diagnostics.

## Recovery
If a UI shows an old successful result after a failed run, inspect the presentation owner's state transition. The VM deliberately preserves the caller's result on refusal; the host must present the current failure instead of mislabelling an old result.

Use tests/test_logical_not.c as the source of the actual contract. It checks operand errors, lowered source offsets, stack cost, span boundaries and depth refusal. A passing arithmetic example does not cover those failure paths.


[Course contents](index.md) · [Previous lesson](48-lower-negation-to-existing-operations.md) · [Next lesson](50-qualify-negation-through-the-cli.md)
