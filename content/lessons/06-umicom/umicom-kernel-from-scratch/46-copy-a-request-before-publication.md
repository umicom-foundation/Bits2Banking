<!--
Umicom Bits2Banking
File: content/lessons/06-umicom/umicom-kernel-from-scratch/46-copy-a-request-before-publication.md

PURPOSE:
Explain the lesson: Copy a request before publication.

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->

# Copy a request before publication

## Prepare

Read queue.h and queue.c in labs/native/virtqueue-lifetime. Follow its README to prepare a C23 compiler, CMake and Ninja. The lab simulates a device with ordinary function calls; it does not implement DMA or a hardware VirtIO transport.

## Understand the idea

Prepare copies the caller's bytes into an available slot. The slot stores an owner, payload length and generation. Copying separates the caller's temporary buffer from the request retained by the queue.

## Work through the example

Draw caller buffer → slot payload. Prepare the text abc, then change the caller buffer to xyz in the supplied test scenario. Identify which bytes the slot should contain.

## Check your reasoning

The slot still contains abc. Preparation owns its copied payload; it has not yet granted the simulated device access.

## If something differs

If later edits change the queued request, inspect whether a pointer was retained instead of copying bytes. A production zero-copy design needs a different lifetime contract.


## Source for this lesson

[Open the example source](https://github.com/umicom-foundation/Bits2Banking/blob/main/labs/native/virtqueue-lifetime/queue.c). Keep the source revision with your exercise notes so later changes can be compared.

[Course contents](index.md) · [Previous lesson](45-reject-extra-storage-image-bytes.md) · [Next lesson](47-publish-only-a-prepared-request.md)

