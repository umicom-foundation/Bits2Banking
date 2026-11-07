<!--
Umicom Bits2Banking
File: content/lessons/06-umicom/umicom-kernel-from-scratch/26-release-and-double-release.md

PURPOSE:
Explain the lesson: Reject invalid and repeated frame releases.

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->

# Reject invalid and repeated frame releases

## Prepare
Use the host physical-frame-pool project. Open its header to see the result names. An owner is the component currently responsible for a resource. Release gives that resource back to the pool.

## Convert address to index
The release function first checks that the address is not below the pool base. Only then does it subtract the base. This order prevents unsigned subtraction from wrapping a smaller address into a huge positive distance.

It next checks alignment and the upper boundary. Dividing the validated distance by 4,096 produces the array index. The function accepts release only when that entry is OWNED and the owned count is nonzero.

## Paper trace
For a pool at 0x80000000:
- releasing 0x80000000 targets reserved frame 0: NOT_OWNED;
- releasing 0x80008001 is misaligned: INVALID;
- releasing 0x80080000 is immediately beyond the inventory: INVALID;
- releasing a successfully allocated 0x80008000 succeeds once;
- releasing it again returns NOT_OWNED.

The last case is a double release. Without the state check, a counter could be decremented twice and the inventory would stop describing reality.

## Lab
Allocate one frame. Copy its address into two local variables. Release through the first variable, then try the second. Both variables contain the same number; copying a number did not create a second ownership right.

Expected: the second call refuses and the owned count remains zero.

## Review
This model does not identify individual processes, so it cannot distinguish two callers who possess the same address. Real ownership integration needs additional contracts. Use the lab to understand state transitions, then inspect the Kernel's process and physical-memory interfaces before designing extensions.

## Source for this lesson

[Open the example source](https://github.com/umicom-foundation/Bits2Banking/blob/main/labs/native/physical-frame-pool/frame_pool.c). Keep the source revision with your exercise notes so later changes can be compared.

[Course contents](index.md) · [Previous lesson](25-first-fit-and-reuse.md) · [Next lesson](27-exhaustion-and-output-preservation.md)

