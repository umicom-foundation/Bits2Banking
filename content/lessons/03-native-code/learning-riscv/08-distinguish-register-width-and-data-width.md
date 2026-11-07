<!--
Umicom Bits2Banking
File: content/lessons/03-native-code/learning-riscv/08-distinguish-register-width-and-data-width.md

PURPOSE:
Explain the lesson: Distinguish register width and data width.

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->

# Distinguish register width and data width

RV64 provides 64-bit integer registers. A program still needs to specify the meaning and size of values passed between functions.

## Prepare

Read sequences.h and check.c. The header uses uint64_t for unsigned 64-bit values and int64_t for signed 64-bit values. size_t represents an object count or size and is checked to occupy eight bytes in this lab.

A type is part of the agreement between C and Assembly.

## Follow the array

Each data element occupies eight bytes. BtbSum64 loads eight bytes and advances its pointer by eight. Those choices must agree with the declaration.

If the header described 32-bit elements while the Assembly still loaded eight bytes, one access could combine adjacent elements and the loop could read beyond the array.

## Interpret the same bits

The all-one bit pattern represents the largest uint64_t value. Interpreted as a signed two's-complement 64-bit value, it represents -1.

The bits alone do not choose signed or unsigned ordering. The selected instruction and interface contract do.

## Exercise

Draw two adjacent eight-byte elements. Label their starting addresses A and A + 8. Mark the address after three elements.

Next explain why a count of zero permits no loads, even if the address is null.

## Check a build mismatch

The C harness contains a static assertion for size_t. A failed assertion is a compile-time indication that the selected data model does not match the lesson.

Do not remove it to make another target compile. Choose the documented RV64 toolchain or deliberately design a separate interface for that target.

This boundary discipline is also necessary when a Framework C API calls an architecture-specific optimization.

## Source for this lesson

[Open the example source](https://github.com/umicom-foundation/Bits2Banking/blob/main/labs/native/riscv-sequences/sequences.h). Keep the source revision with your exercise notes so later changes can be compared.

[Course contents](index.md) · [Previous lesson](07-read-an-instruction-contract.md) · [Next lesson](09-understand-signed-and-unsigned-order.md)

