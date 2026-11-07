<!--
Umicom Bits2Banking
File: content/lessons/06-umicom/umicom-kernel-from-scratch/54-describe-a-service-request.md

PURPOSE:
Explain the lesson: Describe a service request.

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->

# Describe a service request

## Prepare

Open `labs/native/syscall-dispatch/dispatch.h` and `dispatch.c`. A request asks a service to do work; a reply carries its result. This is a hosted teaching model with ordinary function calls, not an actual processor trap. Read the header's ownership rules before changing an example.

## Understand the idea

A service interface needs more than the name of an operation. The request structure contains the caller identity, rights, operation, expected revision and input bytes. Each field answers a separate question about who is asking, what they may do and which state they saw.

## Work through the example

1. Draw one row for every field in `BtbServiceRequest`.
2. Create a paper request for caller 7 to publish `ready`.
3. Set input length to 5 and the expected revision to 1.
4. Choose the publish operation and right from the header.
5. Keep the reply in separate storage.

## Check your reasoning

The request describes five printable bytes. Its input does not need to include a terminator in that length. The model requires request buffers and replies not to alias service state.

## If something differs

Do not treat a caller-supplied numeric identity as authentication. The header marks this as a classroom trust assumption; a real kernel derives identity from its execution context.


## Source for this lesson

[Open the example source](https://github.com/umicom-foundation/Bits2Banking/blob/main/labs/native/syscall-dispatch/dispatch.c). Keep the source revision with your exercise notes so later changes can be compared.

[Course contents](index.md) · [Previous lesson](53-retire-a-slot-before-generation-wrap.md) · [Next lesson](55-read-a-service-without-changing-it.md)

