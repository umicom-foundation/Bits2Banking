<!--
Umicom Bits2Banking
File: content/lessons/06-umicom/umicom-kernel-from-scratch/23-alignment-and-address-validation.md

PURPOSE:
Explain the lesson: Validate a frame-pool base before changing state.

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->

# Validate a frame-pool base before changing state

## Prepare
Use the physical-frame-pool lab from the previous lesson; its README contains the independent build commands. Open `BtbFramePoolInit` beside the public header. You can follow this lesson with a calculator before compiling.

Alignment means an address begins on a required boundary. A 4,096-byte frame begins at a multiple of 4,096. For this power-of-two size, the low twelve address bits must be zero.

## Follow the guard
The expression `startAddress & (BTB_FRAME_SIZE - 1U)` extracts those twelve bits. A nonzero result means misalignment. The function also rejects a null destination and a zero base, as specified in its header.

Zero needs a separate check: it is divisible by 4,096 and therefore passes the alignment expression. This is a useful example of a mathematical condition satisfying only part of a software contract.

## Trace the cases
| Base | Result | Reason |
|---|---|---|
| 0 | INVALID | excluded by the public contract |
| 0x80000000 | OK | nonzero and aligned |
| 0x80000001 | INVALID | low address bits are nonzero |

Initialization builds a temporary candidate only after its checks pass. A rejected call must leave an existing inventory unchanged.

## Exercise
Initialize a valid pool, allocate one frame, then attempt initialization with zero and with the misaligned base. Record both the status and the previous ownership count. Expected: both calls refuse and the prior inventory remains.

## Troubleshoot
A test that checks only “not OK” may hide the wrong refusal reason. Check the exact status where the API specifies one. Do not weaken the header to make an accidentally accepted input appear correct; compare callers and the intended boundary first.

## Source for this lesson

[Open the example source](https://github.com/umicom-foundation/Bits2Banking/blob/main/labs/native/physical-frame-pool/frame_pool.c). Keep the source revision with your exercise notes so later changes can be compared.

[Course contents](index.md) · [Previous lesson](22-physical-frames-as-an-inventory.md) · [Next lesson](24-reserve-a-range-before-allocation.md)

