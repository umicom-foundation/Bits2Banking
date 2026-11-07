<!--
Umicom Bits2Banking
File: content/lessons/umicom-development/41-signed-values-at-a-platform-boundary.md

PURPOSE:
Explain the lesson: Validate values at a platform boundary.

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->

# Validate values at a platform boundary

## Before you begin

Open `labs/native/activity-adapters/bridge.h` and `bridge.c`. No compiler is needed for the first trace. An integer is a whole number. A signed integer can represent negative values; an unsigned integer represents zero and positive values in its range.

## Why this bridge exists

The existing activity function accepts an unsigned count and reports a Framework status. Some screen bindings are easier to teach with a single signed integer result. `BtbActivityNext` returns the next count, or -1 when the request is rejected.

This compact interface is appropriate for this bounded lesson. A larger API should expose distinct error reasons when callers need to respond differently. Returning -1 is not a universal replacement for Framework status codes.

~~~c
int result = BtbActivityNext(current);
if (result >= 0) {
    current = result;
}
~~~

## Follow conversion order

1. Receive a signed value from the caller.
2. Reject negative values while their meaning is still clear.
3. Convert the accepted nonnegative input to unsigned.
4. Call the existing activity function.
5. Convert the successful bounded output back to int.

Converting -1 to unsigned first produces a large positive value. Checking before conversion makes the boundary easier to reason about. The activity function still owns its upper limit.

## Work through examples

For 0, expect 1. For 999, expect 1000. For 1000, expect -1 and leave the screen count unchanged. For -1, the bridge rejects before invoking the model. For a very large positive int, the model rejects it.

## Lab

Read `test_bridge.c`. Match every input to one branch of the bridge or activity contract. Add a paper case for 500 and predict 501. Explain why a result of -1 must never be assigned to an unsigned displayed count.

To execute the host checks later, follow the exact setup and CMake commands in the adapter README. A source trace is a prediction until the chosen compiler and tests run.

## Diagnose a mismatch

Check the language binding's integer width and signedness. Do not fix an invalid value by silently clamping it: that changes the requested operation and hides the error.

## Source for this lesson

[Open the example source](https://github.com/umicom-foundation/Bits2Banking/blob/main/labs/native/activity-adapters/bridge.c). Keep the source revision with your exercise notes so later changes can be compared.

[Course contents](index.md) · [Previous lesson](40-one-model-several-interfaces.md) · [Next lesson](42-desktop-events-and-state.md)

