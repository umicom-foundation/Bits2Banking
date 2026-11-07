<!--
Umicom Bits2Banking
File: content/lessons/03-native-code/learning-riscv-assembly/13-preserve-state-across-a-call.md

PURPOSE:
Explain the lesson: Preserve state across a nested call.

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->

# Preserve state across a nested call

A function that calls another function must protect values it still needs afterward. The calling convention defines which registers a called function may overwrite.

## Prepare

Read BtbSumAndBias64 in call.S. It receives an array address, count and bias in a0, a1 and a2. It calls BtbSum64 and adds the bias to that result.

The bias must survive the call.

## Draw the stack frame

The function subtracts 16 from sp, reserving sixteen bytes. It stores the return address ra at offset 8 and the caller's s0 at offset 0.

It then copies the bias into s0. A conforming called function preserves s0, so the bias remains available after BtbSum64 returns.

## Restore in the return path

After adding the bias, the function reloads the original s0 and ra, adds 16 back to sp and returns.

Saving s0 protects the caller's value; using s0 temporarily does not transfer ownership of that register permanently.

## Exercise

Write a table with entry, before call, after call and before return. Track sp, ra, s0 and a0 at each stage.

Explain why simply leaving the bias in a2 is insufficient: a2 is an argument register that the called routine may overwrite.

## Review limits

The frame retains standard 16-byte alignment. This is an ordinary function-call example, not a complete trap frame. Kernel trap entry has additional responsibilities because an interruption can occur at a point the interrupted code did not choose.

The behavioral harness checks returned sums. ABI preservation also requires inspecting the save/restore paths or a dedicated register-preservation test; a correct number alone does not prove every calling-convention rule.

## Source for this lesson

[Open the example source](https://github.com/umicom-foundation/Bits2Banking/blob/main/labs/native/riscv-sequences/call.S). Keep the source revision with your exercise notes so later changes can be compared.

[Course contents](index.md) · [Previous lesson](12-read-branches-without-subtraction.md) · [Next lesson](14-combine-shifts-with-or.md)

