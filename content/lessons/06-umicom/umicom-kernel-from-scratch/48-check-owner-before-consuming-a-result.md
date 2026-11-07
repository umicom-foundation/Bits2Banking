<!--
Umicom Bits2Banking
File: content/lessons/06-umicom/umicom-kernel-from-scratch/48-check-owner-before-consuming-a-result.md

PURPOSE:
Explain the lesson: Check owner before consuming a result.

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->

# Check owner before consuming a result

## Prepare

Read queue.h and queue.c in labs/native/virtqueue-lifetime. Follow its README to prepare a C23 compiler, CMake and Ninja. The lab simulates a device with ordinary function calls; it does not implement DMA or a hardware VirtIO transport.

## Understand the idea

A token identifies a slot generation, but the public operation also checks its owner. Identity and authority are separate questions. The model's numeric owner is a teaching label, not a secure authentication system.

## Work through the example

Prepare a request for owner seven. Attempt Publish or Collect using owner eight. Trace Find first, then the owner comparison.

## Check your reasoning

A matching live token can still produce WRONG_OWNER. The request remains owned by seven and is not consumed by the refused call.

## If something differs

If you expose this model across a network, a caller-supplied integer does not establish authority. Real systems must derive ownership from an authenticated execution context.


## Source for this lesson

[Open the example source](https://github.com/umicom-foundation/Bits2Banking/blob/main/labs/native/virtqueue-lifetime/queue.c). Keep the source revision with your exercise notes so later changes can be compared.

[Course contents](index.md) · [Previous lesson](47-publish-only-a-prepared-request.md) · [Next lesson](49-record-cancellation-without-freeing-memory.md)

