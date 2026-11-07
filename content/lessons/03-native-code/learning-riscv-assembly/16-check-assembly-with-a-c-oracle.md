<!--
Umicom Bits2Banking
File: content/lessons/03-native-code/learning-riscv-assembly/16-check-assembly-with-a-c-oracle.md

PURPOSE:
Explain the lesson: Check Assembly with a C reference.

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->

# Check Assembly with a C reference

A reference implementation provides an expected result against which another implementation can be compared. It is useful when the two implementations are simple enough to inspect independently.

## Prepare

Read check.c. The README gives a RISC-V Linux cross-build and QEMU user-mode command. The harness uses a C library to print failed checks, so it needs the matching Linux toolchain and libraries.

The object-only route does not provide that runtime.

## Read the expectations

The harness checks zero-length summation, unsigned wrap, signed and unsigned minima, rotations and parity.

For rotation it tries several revealing words and distances from zero through 129. This crosses two full 64-bit rotation periods and their boundaries.

For parity, the C reference counts set bits rather than copying the Assembly's toggle loop.

## Exercise

Choose one test and explain why it would fail after a specific defect. For example, replacing a logical right shift with an arithmetic shift can change behavior for values with the highest bit set.

Then identify something the test does not establish. Returning correct values does not prove memory safety for invalid pointers outside the stated contract.

## Run and record

After building successfully, run the harness. Expected success text is RISC-V sequence checks passed. Preserve the exit status, compiler version, emulator version and source revision with your result.

These are authored checks; their existence is not evidence that they have run.

## Recover thoughtfully

If a comparison fails, trace the smallest failing input. Check the reference too: two implementations can share a mistake, and a reference can be wrong.

Use explicit boundary values and paper traces alongside comparison tests. Each provides different evidence about the same function contract.

## Source for this lesson

[Open the example source](https://github.com/umicom-foundation/Bits2Banking/blob/main/labs/native/riscv-sequences/check.c). Keep the source revision with your exercise notes so later changes can be compared.

[Course contents](index.md) · [Previous lesson](15-inspect-unresolved-call-symbols.md)

