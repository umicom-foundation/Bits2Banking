<!--
Umicom Bits2Banking
File: content/lessons/06-umicom/umicom-kernel-from-scratch/47-publish-only-a-prepared-request.md

PURPOSE:
Explain the lesson: Publish only a prepared request.

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->

# Publish only a prepared request

## Prepare

Read queue.h and queue.c in labs/native/virtqueue-lifetime. Follow its README to prepare a C23 compiler, CMake and Ninja. The lab simulates a device with ordinary function calls; it does not implement DMA or a hardware VirtIO transport.

## Understand the idea

Publish checks owner and PREPARED state, appends the token to the available ring, then marks the slot PUBLISHED. The state transition expresses when the simulated device may access it.

## Work through the example

Trace Prepare, Publish and a second Publish with the same token. List the first successful state change and the reason for the second refusal.

## Check your reasoning

The second Publish fails with WRONG_STATE. One request cannot be inserted twice into the available queue through this API.

## If something differs

If duplicate completion appears, investigate publication history rather than weakening the state guard. A retry policy must distinguish an unsubmitted request from an already submitted one.


## Source for this lesson

[Open the example source](https://github.com/umicom-foundation/Bits2Banking/blob/main/labs/native/virtqueue-lifetime/queue.c). Keep the source revision with your exercise notes so later changes can be compared.

[Course contents](index.md) · [Previous lesson](46-copy-a-request-before-publication.md) · [Next lesson](48-check-owner-before-consuming-a-result.md)

