<!--
Umicom Bits2Banking
File: content/lessons/06-umicom/umicom-kernel-from-scratch/58-bound-and-validate-service-text.md

PURPOSE:
Explain the lesson: Bound and validate service text.

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->

# Bound and validate service text

## Prepare

Open `labs/native/syscall-dispatch/dispatch.h` and `dispatch.c`. A request asks a service to do work; a reply carries its result. This is a hosted teaching model with ordinary function calls, not an actual processor trap. Read the header's ownership rules before changing an example.

## Understand the idea

The model has 48 bytes per event, including space for a trailing zero. It therefore accepts one through 47 input bytes. Each byte must be printable ASCII. A local zero-filled array keeps a terminator after the copied text.

## Work through the example

1. Trace input `ready` with length 5.
2. Trace length 0, then length 48.
3. Trace a five-byte input containing a newline.
4. Locate the byte-range check from `0x20` to `0x7e`.
5. Observe that publication follows the complete scan.

## Check your reasoning

The ordinary word is accepted if the other checks pass. Empty, oversized and control-character inputs are refused before the event list changes.

## If something differs

This deliberately narrow text contract does not support arbitrary Unicode. A production text service needs an explicit encoding and its own validation policy.


## Source for this lesson

[Open the example source](https://github.com/umicom-foundation/Bits2Banking/blob/main/labs/native/syscall-dispatch/dispatch.c). Keep the source revision with your exercise notes so later changes can be compared.

[Course contents](index.md) · [Previous lesson](57-refuse-a-stale-revision.md) · [Next lesson](59-publish-event-and-reply-together.md)

