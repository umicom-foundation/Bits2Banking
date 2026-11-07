<!--
Umicom Bits2Banking
File: content/lessons/03-native-code/learning-riscv-assembly/11-walk-an-array-with-loads.md

PURPOSE:
Explain the lesson: Walk an array with loads.

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->

# Walk an array with loads

An array walk combines a memory address, an element count and a rule for advancing to the next element.

## Prepare

Open sequences.h, sum.S and TRACE.md in the RISC-V sequences lab. The README gives object-assembly commands and a separate executable-check route.

Assume three readable uint64_t values 2, 5 and 9 begin at address A.

## Trace the registers

At entry, a0 holds A and a1 holds 3. The function copies A to t0, then reuses a0 for the sum.

After one iteration, a0 is 2, t0 is A + 8 and a1 is 2. After three, the sum is 16 and the count is zero.

ld reads the current element. addi advances the address and decreases the count. bnez repeats only while work remains.

## Check the empty case

Before the first load, beqz checks the count. For count zero, even a null pointer produces zero without a memory access.

This is a narrow permission. A null pointer with a positive count violates the interface contract.

## Exercise

Copy the worksheet and trace one element equal to UINT64_MAX. Then trace zero elements. Mark every executed memory instruction.

If your empty trace includes ld, you have followed a path the branch should prevent.

## Connect to Kernel

Kernel code often walks tables using counts, addresses and element sizes. The same questions apply: is the region readable, is the count bounded and does the stride match the element representation?

This routine borrows memory and never writes it. It does not discover whether an arbitrary address is valid. That responsibility remains with its caller.

## Source for this lesson

[Open the example source](https://github.com/umicom-foundation/Bits2Banking/blob/main/labs/native/riscv-sequences/sum.S). Keep the source revision with your exercise notes so later changes can be compared.

[Course contents](index.md) · [Previous lesson](10-restore-state-at-a-controlled-return.md) · [Next lesson](12-read-branches-without-subtraction.md)

