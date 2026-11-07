<!--
Umicom Bits2Banking
File: content/lessons/06-umicom/umicom-kernel-from-scratch/50-respect-the-models-completion-order.md

PURPOSE:
Explain the lesson: Respect the model's completion order.

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->

# Respect the model's completion order

## Prepare

Read queue.h and queue.c in labs/native/virtqueue-lifetime. Follow its README to prepare a C23 compiler, CMake and Ninja. The lab simulates a device with ordinary function calls; it does not implement DMA or a hardware VirtIO transport.

## Understand the idea

SimulateComplete requires the token at the head of the available ring. This deliberately simplified model completes requests in FIFO order. The same requirement applies when collecting from the used ring.

## Work through the example

Publish A then B. Attempt to complete B first, then A, then B. Write each expected status without removing requests manually.

## Check your reasoning

The first attempt is WRONG_ORDER. Completing A permits B next. The exercise's policy is stricter than some real devices, which can complete out of order.

## If something differs

If adapting to hardware, read that transport's ordering contract. Do not assume the teaching queue's FIFO restriction is a universal device guarantee.


## Source for this lesson

[Open the example source](https://github.com/umicom-foundation/Bits2Banking/blob/main/labs/native/virtqueue-lifetime/queue.c). Keep the source revision with your exercise notes so later changes can be compared.

[Course contents](index.md) · [Previous lesson](49-record-cancellation-without-freeing-memory.md) · [Next lesson](51-validate-completed-byte-counts.md)

