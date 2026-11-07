<!--
Umicom Bits2Banking
File: content/lessons/03-native-code/learning-riscv-assembly/08-map-a-trap-frame-by-byte-offset.md

PURPOSE:
Explain the lesson: Map a trap frame by byte offset.

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->

# Map a trap frame by byte offset

A trap frame is a block of memory containing saved processor state. Assembly and C must agree about the position of every field.

## Prepare the files

Open trap_integrity.h beside arch/riscv64/trap_entry.S. Begin by finding the frame-size and named-offset definitions.

The exercise is a diagram and source comparison. It requires no emulator or privileged instruction execution.

## 1. Separate size and offset

The frame occupies 288 bytes in this implementation. An offset tells how far a field starts from the frame's beginning.

The first saved return address is at offset zero. The interrupted stack pointer is at offset eight. Each RV64 integer register value occupies eight bytes.

An offset is measured in bytes, not in register numbers.

## 2. Locate the saved control state

The saved program counter begins at offset 248. Status follows at 256, cause at 264, trap value at 272 and a reserved word at 280.

Draw the final five eight-byte boxes. The last box ends at byte 287, fitting inside the 288-byte frame.

Named constants help keep the assembly stores and the C checks aligned, but they still need review together.

## 3. Follow one field through both directions

Find the store of mepc and the later load used to restore it. Both must use the same field.

Now find the old sp store at offset eight and its final restore. The current sp continues to address the owned frame until restoration is nearly complete.

## Exercise

Calculate the address of the status field if the frame begins at symbolic address BASE. Write BASE + 256, then identify the matching instruction.

Explain why replacing 256 with 32 because it is “the thirty-second word” would be wrong: assembly's displacement is already in bytes.

## Recovery

If a source change moves a field, inspect all stores, loads, declarations and validation code. A C-only host test cannot prove the assembly offsets executed correctly on target hardware.

Keep source review, emulator observations and physical-device results distinct in your notes.

## Source for this lesson

[Open the example source](https://github.com/umicom-foundation/umicom-kernel/blob/main/include/umicom/kernel/riscv64/trap_integrity.h). Keep the source revision with your exercise notes so later changes can be compared.

[Course contents](index.md) · [Previous lesson](07-exchange-the-stack-pointer-with-a-csr.md) · [Next lesson](09-understand-stack-sentinels.md)

