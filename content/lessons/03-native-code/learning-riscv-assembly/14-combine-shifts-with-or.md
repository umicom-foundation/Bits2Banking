<!--
Umicom Bits2Banking
File: content/lessons/03-native-code/learning-riscv-assembly/14-combine-shifts-with-or.md

PURPOSE:
Explain the lesson: Combine shifts with OR.

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->

# Combine shifts with OR

A rotate can be built by combining two pieces of the original value. This makes the movement of bits visible before using any specialized instruction.

## Prepare

Read BtbRotateLeft64. The input is copied conceptually into two calculations, although the implementation uses temporary registers rather than duplicating memory.

The normalized distance is from zero through 63.

## Follow the nonzero path

sll places the left-shifted part in t1. The code computes 64 minus the distance and uses srl to place the wrapped part in a0. or combines them.

For distance one, the right-shifted part contains only the original highest bit in its new position zero.

## Check register lifetimes

The original a0 must remain available until both shifts have used it. In this implementation sll reads it first and writes t1; srl then reads it and overwrites a0.

If the first shift overwrote a0, the second calculation would no longer see the original bits.

## Exercise

Annotate each register with the last instruction that needs its old value. This is a small form of liveness analysis: identifying how long a value must remain available.

Trace an input with both the highest and lowest bits set. Predict the result for a one-bit rotation.

## Recover from a mismatch

Check distance normalization, the zero branch and register overwrite order independently. Each can produce different boundary failures.

The C reference avoids a shift by 64 explicitly. Machine instructions and C expressions have separate contracts; equivalent-looking source must still respect both.

Keep the implementation in the teaching lab. Production Framework optimizations require their own portability and performance evidence.

## Source for this lesson

[Open the example source](https://github.com/umicom-foundation/Bits2Banking/blob/main/labs/native/riscv-sequences/bits.S). Keep the source revision with your exercise notes so later changes can be compared.

[Course contents](index.md) · [Previous lesson](13-preserve-state-across-a-call.md) · [Next lesson](15-inspect-unresolved-call-symbols.md)

