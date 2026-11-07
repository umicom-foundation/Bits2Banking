<!--
Umicom Bits2Banking
File: content/lessons/03-native-code/learning-riscv/05-branches-and-counted-loops.md

PURPOSE:
Explain the lesson: Trace a loop and prove where it stops.

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->

# Trace a loop and prove where it stops

## Before you begin
You need paper and an editor. Review register assignment if necessary. A branch chooses the next instruction from a condition. A label names a place in the instruction sequence.

## Sum three small values
~~~asm
addi t0, zero, 3
addi t1, zero, 0
again:
add  t1, t1, t0
addi t0, t0, -1
bne  t0, zero, again
~~~
The temporary register t0 counts down. t1 accumulates the sum. bne means branch if the two compared values are not equal. Here it returns to again while t0 is not zero.

## Trace the boundary
~~~text
iteration | t0 before add | t1 after add | t0 after decrement
1         |       3       |      3       |       2
2         |       2       |      5       |       1
3         |       1       |      6       |       0
~~~
The final branch is not taken. The next instruction after the sequence would run; this fragment does not define that next instruction.

## Lab
1. Trace the loop starting from 4 instead of 3.
2. Count both additions and branch decisions.
3. Start from zero on paper. Notice that this loop body runs before its condition check.
4. Add a separate zero-count check to your design before the label.
5. Explain the precondition required by the original fragment.

## Connect to a C loop
Write a C loop that produces the same sum for positive counts. Then test zero. Matching the usual case is not enough if the boundary behaviour differs.

## Use in Umicom source studies
Kernel and compiler code often contains loops over buffers or instruction streams. Identify the quantity that moves toward termination. If it can wrap or stop changing, the loop may not finish.

## Recovery
When a trace repeats indefinitely, stop tracing after a few steps and inspect the progress variable. Do not solve a nonterminating loop by merely increasing a timeout.

## Source for this lesson

[Open the example source](https://github.com/umicom-foundation/Bits2Banking/blob/main/labs/native/assembly-functions/add_riscv64.S). Keep the source revision with your exercise notes so later changes can be compared.

[Course contents](index.md) · [Previous lesson](04-addresses-and-memory-width.md) · [Next lesson](06-call-return-and-stack.md)

