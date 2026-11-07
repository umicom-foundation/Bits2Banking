<!--
Umicom Bits2Banking
File: content/lessons/06-umicom/umicom-kernel-from-scratch/34-exit-and-reuse-task-slots.md

PURPOSE:
Explain the lesson: Reuse a task slot without reusing its identity.

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->

# Reuse a task slot without reusing its identity

## Prepare
Read Token, Lookup and BtbRoundRobinAdmit. The model has eight storage slots. A slot can be reused after its earlier task stops.

A handle combines a generation number in the upper 32 bits with slot index plus one in the lower 32 bits.

## Trace reuse
Admit Notes in the first available slot. Dispatch and exit it. Admit a new task into that slot.

The slot index may match, but the generation increases. The new handle therefore differs from the old Notes handle.

## Lab
Draw a handle as two boxes: generation and encoded slot. Show generation one and then generation two for slot zero.

Expected: the lower word is one, reserving zero as invalid. Lookup rejects the old generation after reuse.

## Exercise and explanation
Why not expose only the array index? A delayed client could accidentally act on a different task now occupying the same slot.

## Troubleshoot
Generation numbers are finite. Admission skips a slot whose generation has reached UINT32_MAX rather than wrapping it. Eventually capacity may be unavailable even when an exhausted slot is stopped.

A handle is a checked identity in this API, not a memory address. Do not cast it into a task pointer. Let Lookup validate the index, generation and live state.

## Source for this lesson

[Open the example source](https://github.com/umicom-foundation/Bits2Banking/blob/main/labs/native/round-robin-scheduler/round_robin.c). Keep the source revision with your exercise notes so later changes can be compared.

[Course contents](index.md) · [Previous lesson](33-match-a-wakeup-to-its-wait.md) · [Next lesson](35-cancel-a-wait-with-an-explicit-result.md)

