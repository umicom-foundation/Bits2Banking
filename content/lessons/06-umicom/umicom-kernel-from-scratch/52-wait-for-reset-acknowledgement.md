<!--
Umicom Bits2Banking
File: content/lessons/06-umicom/umicom-kernel-from-scratch/52-wait-for-reset-acknowledgement.md

PURPOSE:
Explain the lesson: Wait for reset acknowledgement.

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->

# Wait for reset acknowledgement

## Prepare

Read queue.h and queue.c in labs/native/virtqueue-lifetime. Follow its README to prepare a C23 compiler, CMake and Ninja. The lab simulates a device with ordinary function calls; it does not implement DMA or a hardware VirtIO transport.

## Understand the idea

RequestReset sets resetPending and freezes new operations. It retains outstanding slots. SimulateResetAcknowledged is a separate event that clears rings and slots after the model observes confirmation.

## Work through the example

Create a timeline with a published request, reset request, attempted new Prepare and reset acknowledgement. Mark where BUSY is expected and when reuse becomes possible.

## Check your reasoning

Admission remains blocked while reset is pending. Only acknowledgement makes the retained slots reusable. The two calls must not be collapsed into one unverified assumption.

## If something differs

If real hardware never acknowledges reset, keep ownership unresolved and report it. Calling the simulation helper is not hardware evidence.


## Source for this lesson

[Open the example source](https://github.com/umicom-foundation/Bits2Banking/blob/main/labs/native/virtqueue-lifetime/queue.c). Keep the source revision with your exercise notes so later changes can be compared.

[Course contents](index.md) · [Previous lesson](51-validate-completed-byte-counts.md) · [Next lesson](53-retire-a-slot-before-generation-wrap.md)

