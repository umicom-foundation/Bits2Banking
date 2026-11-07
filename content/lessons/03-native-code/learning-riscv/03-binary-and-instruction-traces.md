<!--
Umicom Bits2Banking
File: content/lessons/03-native-code/learning-riscv/03-binary-and-instruction-traces.md

PURPOSE:
Explain the lesson: Trace a short sequence of register changes.

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->

# Trace a short sequence of register changes

## Before you begin
No hardware is required. You need paper and the Bits2Banking source file `labs/native/assembly-functions/add_riscv64.S`. A register is a small named storage location inside the processor. An instruction describes one operation.

## Start with a tiny program
~~~asm
addi a0, zero, 5
addi a1, zero, 7
add  a0, a0, a1
~~~
Read each line as destination followed by inputs. The first instruction adds the constant 5 to zero and writes a0. The second writes 7 to a1. The third adds the two register values and writes the result to a0.

The RISC-V integer model includes a register whose value is always zero. The a0 and a1 names are conventional aliases used for argument/result registers. See the [RISC-V base integer specification](https://docs.riscv.org/reference/isa/v20260120/unpriv/rv32.html).

## Make a trace table
~~~text
after instruction | a0 | a1
first             |  5 | unknown here
second            |  5 | 7
third             | 12 | 7
~~~
Do not invent an initial value for a register that the sequence has not set.

## Lab
1. Write the table before reading the expected values.
2. Change 5 to 8 on paper and recompute.
3. Change the third destination to a1. Which register now holds the sum?
4. Open the repository's addition example and identify its inputs and result.
5. Find its caller or README and check which calling convention it expects.

## Connect to C
A C function such as an addition helper has parameters and a return value. The compiler maps that interface to a platform calling convention. Reading Assembly becomes easier when you first identify that interface.

## Limits
These three lines are a trace exercise, not a complete boot program. They do not set a stack, choose a board or define what should happen after the result is computed.

## Check your understanding
Why does the first line not need to know the previous value of a0? Because both input values are defined independently of that previous destination value.

## Source for this lesson

[Open the example source](https://github.com/umicom-foundation/Bits2Banking/blob/main/labs/native/assembly-functions/add_riscv64.S). Keep the source revision with your exercise notes so later changes can be compared.

[Course contents](index.md) · [Next lesson](04-addresses-and-memory-width.md)


[Previous lesson](02-programs-and-privileges.md)
