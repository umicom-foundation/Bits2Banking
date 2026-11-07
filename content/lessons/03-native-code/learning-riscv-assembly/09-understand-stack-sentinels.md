<!--
Umicom Bits2Banking
File: content/lessons/03-native-code/learning-riscv-assembly/09-understand-stack-sentinels.md

PURPOSE:
Explain the lesson: Understand stack sentinels.

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->

# Understand stack sentinels

A sentinel is a known value placed where it can reveal an unexpected overwrite. Kernel trap storage uses sentinels at its margins.

## Setup recap

Read UmicomRiscvMachineTrapPrepare and the definitions in trap_integrity.h. Use a drawing of the stack rather than deliberately corrupting a running kernel.

A stack is memory used for saved values and function work. Its usable region has boundaries; writing beyond those boundaries can damage unrelated state.

## 1. Find the two margins

The preparation function stores a known canary value at the lower margin and at the stack top. It also stores the bitwise complement beside each value.

Complement means each zero bit becomes one and each one becomes zero.

The upper sentinel is outside the usable stack. It must not be treated as space available to ordinary handler data.

## 2. Explain the paired values

A single repeated byte pattern could accidentally resemble one chosen sentinel. Comparing a value and its complement gives an additional check against some overwrite patterns.

This does not detect every possible corruption. A sentinel is evidence about specific memory locations, not a proof that all memory is safe.

## 3. Follow publication order

Both margins are initialised before mscratch receives the landing address. The trap path must not observe a published pointer to storage whose checks are still unprepared.

This is the same general reasoning used when building a candidate object before making it visible to callers.

## Exercise

Draw lower margin, usable stack, frame and upper margin. Mark which writes belong to preparation and which belong to trap entry.

Then list two failures a margin check might detect and two it cannot establish. For example, an unchanged margin says nothing by itself about the correctness of a saved program counter.

## Apply the lesson

When reading a protection mechanism, identify its actual claim and assumptions. Keep the canary checks together with frame validation and the emergency path.

Do not remove another check merely because the sentinel comparison passed. Several checks can protect different parts of the same operation.

## Source for this lesson

[Open the example source](https://github.com/umicom-foundation/umicom-kernel/blob/main/arch/riscv64/trap_entry.S). Keep the source revision with your exercise notes so later changes can be compared.

[Course contents](index.md) · [Previous lesson](08-map-a-trap-frame-by-byte-offset.md) · [Next lesson](10-restore-state-at-a-controlled-return.md)

