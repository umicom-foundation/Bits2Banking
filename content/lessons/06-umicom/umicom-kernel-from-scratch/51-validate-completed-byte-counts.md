<!--
Umicom Bits2Banking
File: content/lessons/06-umicom/umicom-kernel-from-scratch/51-validate-completed-byte-counts.md

PURPOSE:
Explain the lesson: Validate completed byte counts.

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->

# Validate completed byte counts

## Prepare

Read queue.h and queue.c in labs/native/virtqueue-lifetime. Follow its README to prepare a C23 compiler, CMake and Ninja. The lab simulates a device with ordinary function calls; it does not implement DMA or a hardware VirtIO transport.

## Understand the idea

A completion reports how many bytes the simulated device processed. That number must not exceed the retained request length. A success code alone cannot make an impossible length safe.

## Work through the example

Prepare a four-byte request. Compare completions of zero, two, four and five bytes, keeping queue state otherwise valid. Identify which value is structurally impossible.

## Check your reasoning

Five is refused. The other lengths fit the request, but their application meaning also depends on deviceStatus and the operation's contract.

## If something differs

If a caller treats every shorter completion as full success, inspect its result handling. Bounds validation and interpretation of partial work are different steps.


## Source for this lesson

[Open the example source](https://github.com/umicom-foundation/Bits2Banking/blob/main/labs/native/virtqueue-lifetime/queue.c). Keep the source revision with your exercise notes so later changes can be compared.

[Course contents](index.md) · [Previous lesson](50-respect-the-models-completion-order.md) · [Next lesson](52-wait-for-reset-acknowledgement.md)

