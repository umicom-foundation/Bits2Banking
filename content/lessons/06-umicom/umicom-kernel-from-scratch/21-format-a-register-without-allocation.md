<!--
Umicom Bits2Banking
File: content/lessons/06-umicom/umicom-kernel-from-scratch/21-format-a-register-without-allocation.md

PURPOSE:
Explain the lesson: Format a register without allocation.

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->

# Format a register without allocation

Hexadecimal makes binary values easier to inspect. Four bits form one hexadecimal digit, often called a nibble. A 64-bit register therefore fits into sixteen hexadecimal digits.

## Setup recap

Read UmicomTrapEmergencyHex in trap_emergency.c. You need only a text editor and paper. The function prints through the bounded emergency byte routine rather than allocating a formatted string.

The digit table contains the sixteen characters 0 through 9 and a through f.

## 1. Extract one digit

For each position, the function shifts the value right and masks with 15. In binary, 15 is 1111, so the mask retains four bits.

For the small value 0x2a, the final two selected digits are 2 and a. Earlier positions produce zero.

## 2. Follow the loop direction

The loop starts with nibble equal to sixteen and stops before zero. Its shift expression is (nibble - 1) multiplied by four.

The first shift is 60 and the last is zero. No iteration shifts the 64-bit value by 64, and subtraction does not occur with nibble already zero.

The most significant digit is printed first, giving the familiar left-to-right notation.

## 3. Understand fixed width

The function emits a 0x prefix, sixteen digits and a line ending. Leading zeroes make register values align in a report and preserve a consistent width.

Formatting every value this way does not tell the reader what it means. The caller adds labels such as cause and pc. A program counter is an address associated with execution, while a cause value describes why control entered the handler.

## Exercise and expected result

Trace 0, 1, 0x2a and a value with only the highest bit set. For 0x2a, write the expected digit sequence as 000000000000002a.

Explain why the digit-table index cannot exceed fifteen. Then describe what would go wrong if the mask were accidentally changed to 31.

This exercise concerns representation. It does not validate whether a reported address is mapped or whether the interrupted instruction can safely resume.

## Source for this lesson

[Open the example source](https://github.com/umicom-foundation/umicom-kernel/blob/main/platform/qemu-riscv64/trap_emergency.c). Keep the source revision with your exercise notes so later changes can be compared.

[Course contents](index.md) · [Previous lesson](20-bound-emergency-diagnostics.md)


[Next: Represent physical frames as an inventory](22-physical-frames-as-an-inventory.md)
