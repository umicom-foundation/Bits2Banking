<!--
Umicom Bits2Banking
File: content/lessons/03-native-code/learning-riscv/07-read-an-instruction-contract.md

PURPOSE:
Explain the lesson: Read an instruction contract.

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->

# Read an instruction contract

A processor executes instructions that move or transform values. To understand an instruction, identify its inputs, its output and any memory it accesses.

## Prepare

Open sum.S in the RISC-V sequences lab. Its README separates reading, assembling and running. Start by reading; an emulator is not required for this exercise.

The function receives an array address in a0 and an element count in a1. It returns a sum in a0.

## Read three operations

mv t0, a0 copies the address into a temporary register. It does not copy the whole array.

ld t1, 0(t0) loads an eight-byte value from the address in t0.

add a0, a0, t1 adds that value to the running sum. The destination and one source can be the same register.

## Trace one element

Suppose the first array element is 2. Before the load, write t0 = A and a0 = 0. After the load, t1 = 2. After the addition, a0 = 2.

A is a symbolic address. It is not the value stored at that address.

## Exercise

For each line in the loop, mark R for register access, M for memory access and C for control flow. Some lines have more than one role.

Then explain why moving t0 by eight advances by one element. The declaration uses uint64_t, which occupies eight bytes on this target.

## Recovery

If a trace becomes confusing, give addresses and stored values different notation. Write A + 8 for an address and [A + 8] = 5 for its contents.

The lab's functions are ordinary callable routines. Umicom Kernel uses the same instruction vocabulary inside a larger environment that also manages privilege, traps and devices.

## Source for this lesson

[Open the example source](https://github.com/umicom-foundation/Bits2Banking/blob/main/labs/native/riscv-sequences/sum.S). Keep the source revision with your exercise notes so later changes can be compared.

[Course contents](index.md) · [Previous lesson](06-call-return-and-stack.md) · [Next lesson](08-distinguish-register-width-and-data-width.md)

