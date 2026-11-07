<!--
Umicom Bits2Banking
File: content/lessons/03-native-code/safer-c-programming/17-subtract-only-after-checking.md

PURPOSE:
Explain the lesson: Check subtraction before using the result.

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->

# Check subtraction before using the result

## Prepare
Open arena.c and find available - padding. size_t is the unsigned type used for storage sizes. Subtracting a larger value from a smaller unsigned value wraps instead of producing a useful negative capacity.

The allocator avoids that mistake by checking padding <= available first.

## Follow the order
First check that used does not exceed capacity. Then compute available as capacity minus used. Check padding against available. Finally compare the requested byte count with available minus padding.

Each subtraction is justified by an earlier comparison.

## Lab
Trace a capacity of sixteen, used count fourteen, padding three and request one.

Expected: available is two; padding exceeds it; the allocation returns insufficient space before computing a usable start position.

Repeat with padding one and request one. This request fits exactly.

## Exercise and explanation
Why not compare used + padding + byteCount against capacity? The sum itself can overflow before the comparison. Subtraction after validated bounds makes the reasoning explicit.

## Troubleshoot
Keep integer representability and memory capacity as separate checks. The source also checks address arithmetic using uintptr_t before rounding. A region can have sufficient declared capacity while an arithmetic expression is still unrepresentable.

When reviewing a new allocator, write the inequality that makes each subtraction safe. Do not rely on small demonstration inputs to establish the general boundary.

## Source for this lesson

[Open the example source](https://github.com/umicom-foundation/Bits2Banking/blob/main/labs/native/arena-allocator/arena.c). Keep the source revision with your exercise notes so later changes can be compared.

[Course contents](index.md) · [Previous lesson](16-understand-alignment-padding.md) · [Next lesson](18-preserve-output-on-allocation-failure.md)

