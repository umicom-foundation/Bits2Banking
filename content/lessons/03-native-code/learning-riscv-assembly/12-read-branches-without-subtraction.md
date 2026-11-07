<!--
Umicom Bits2Banking
File: content/lessons/03-native-code/learning-riscv-assembly/12-read-branches-without-subtraction.md

PURPOSE:
Explain the lesson: Read branches without subtraction.

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->

# Read branches without subtraction

A comparison can select a result without computing a numeric difference. This avoids confusing the comparison's meaning with arithmetic overflow.

## Prepare

Open minimum.S. Each function accepts two values and returns their minimum. Read the signed and unsigned declarations in sequences.h first.

The branch operands are written right then left: bge a1, a0 branches when right is greater than or equal to left.

## Follow both paths

When the branch is taken, return directly because a0 already holds the smaller or equal value.

When the branch is not taken, copy the right value to a0, then return.

The result register is also the first argument register. No extra memory is needed.

## Exercise

Draw a two-path flowchart. Trace left = 4, right = -9 through the signed version. Then trace left = -9, right = 4.

For unsigned inputs UINT64_MAX and 1, use the bgeu version. Explain why changing only the branch instruction changes interpretation without changing the stored bit patterns.

## Inspect the object

Use the README's clang commands, then llvm-objdump -dr minimum.o. The disassembler may display an equivalent alias for an instruction. Compare its effect rather than expecting source text to be reproduced character for character.

## Recovery

If the result is always the larger value, check the operand order and the branch direction separately. Do not fix both at once without a trace; two reversed decisions can hide a misunderstanding.

The lab's boundary cases include equal values, reversed arguments and signed extremes. They help distinguish a general rule from a result that happens to work for two positive numbers.

## Source for this lesson

[Open the example source](https://github.com/umicom-foundation/Bits2Banking/blob/main/labs/native/riscv-sequences/minimum.S). Keep the source revision with your exercise notes so later changes can be compared.

[Course contents](index.md) · [Previous lesson](11-walk-an-array-with-loads.md) · [Next lesson](13-preserve-state-across-a-call.md)

