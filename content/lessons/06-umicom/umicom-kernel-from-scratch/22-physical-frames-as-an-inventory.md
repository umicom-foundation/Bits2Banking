<!--
Umicom Bits2Banking
File: content/lessons/06-umicom/umicom-kernel-from-scratch/22-physical-frames-as-an-inventory.md

PURPOSE:
Explain the lesson: Represent physical frames as an inventory.

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->

# Represent physical frames as an inventory

## Prepare
Open the physical-frame-pool lab in a complete Bits2Banking checkout. Its README provides PowerShell configure, build and test commands. A compiler translates the C files into a host program; the program models ownership without touching physical RAM.

A byte is one addressable storage unit in this model. A frame contains 4,096 consecutive bytes. The inventory holds 128 frames, so it describes 524,288 bytes. An address identifies the beginning of a range.

## Read the representation
`BtbFramePool` stores a starting address, one state byte per frame, and two counters. The state is FREE, OWNED or RESERVED. These words describe permission to use the range, not what bytes it contains.

Draw 16 boxes for the first 16 entries. Mark entries 0–7 RESERVED and 8–15 FREE. Initialization reserves eight entries for fictional boot structures. It has not loaded firmware or allocated host memory.

## Calculate an address
With start address `0x80000000`, frame 8 begins at:
```text
0x80000000 + 8 × 4096 = 0x80008000
```
Hexadecimal uses sixteen digits, 0–9 then A–F. Here 4096 is 0x1000. Adding eight frames therefore adds 0x8000.

## Lab
1. Record the initialized counters: reserved 8, owned 0.
2. Predict the first successful allocation.
3. Run the README's demo when your toolchain is ready.
4. Compare the printed address with your calculation.

Expected first address is 0x80008000. If it differs, inspect the base and reserved entries before assuming the allocation loop is wrong.

## Connect to Kernel work
Read Umicom Kernel's physical-memory guide linked in the lab README. The teaching inventory omits platform discovery, locking and process ownership. Keep those limits visible when using the example to understand the larger implementation.

## Source for this lesson

[Open the example source](https://github.com/umicom-foundation/Bits2Banking/blob/main/labs/native/physical-frame-pool/frame_pool.h). Keep the source revision with your exercise notes so later changes can be compared.

[Course contents](index.md) · [Previous lesson](21-format-a-register-without-allocation.md) · [Next lesson](23-alignment-and-address-validation.md)

