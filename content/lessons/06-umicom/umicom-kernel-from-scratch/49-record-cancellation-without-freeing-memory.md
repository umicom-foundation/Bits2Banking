<!--
Umicom Bits2Banking
File: content/lessons/06-umicom/umicom-kernel-from-scratch/49-record-cancellation-without-freeing-memory.md

PURPOSE:
Explain the lesson: Record cancellation without freeing memory.

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->

# Record cancellation without freeing memory

## Prepare

Read queue.h and queue.c in labs/native/virtqueue-lifetime. Follow its README to prepare a C23 compiler, CMake and Ninja. The lab simulates a device with ordinary function calls; it does not implement DMA or a hardware VirtIO transport.

## Understand the idea

CancelRequested changes a flag on a PUBLISHED slot. It leaves payload and queue membership intact. A request to cancel does not prove that a device has stopped using the bytes.

## Work through the example

Draw Publish → CancelRequested → SimulateComplete → Collect. Mark the earliest point at which ClearSlot runs. Explain why a timeout cannot substitute for completion.

## Check your reasoning

The slot is cleared during Collect after terminal completion, or after separately acknowledged reset. The completion records that cancellation was requested even if work finished.

## If something differs

If a timeout path frees the slot immediately, review device ownership. Software impatience cannot establish that external memory access has ceased.


## Source for this lesson

[Open the example source](https://github.com/umicom-foundation/Bits2Banking/blob/main/labs/native/virtqueue-lifetime/queue.c). Keep the source revision with your exercise notes so later changes can be compared.

[Course contents](index.md) · [Previous lesson](48-check-owner-before-consuming-a-result.md) · [Next lesson](50-respect-the-models-completion-order.md)

