<!--
Umicom Bits2Banking
File: content/lessons/06-umicom/umicom-kernel-from-scratch/55-read-a-service-without-changing-it.md

PURPOSE:
Explain the lesson: Read a service without changing it.

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->

# Read a service without changing it

## Prepare

Open `labs/native/syscall-dispatch/dispatch.h` and `dispatch.c`. A request asks a service to do work; a reply carries its result. This is a hosted teaching model with ordinary function calls, not an actual processor trap. Read the header's ownership rules before changing an example.

## Understand the idea

A read operation observes existing state. `GET_TICKS` returns the stored tick value and revision. It accepts no input payload, which prevents ambiguous requests whose unused fields might hide mistakes.

## Work through the example

1. Initialise state with tick value 250.
2. Set the operation to `GET_TICKS`, input to null and length to zero.
3. Follow the first operation branch.
4. Record reply value and revision.
5. Repeat and compare the service's event count.

## Check your reasoning

The reply contains 250 and revision 1. Neither reading nor repeating the read appends an event. The model's stored tick value does not advance by itself.

## If something differs

A non-null input pointer with zero length is refused for this operation. Match the complete documented request shape.


## Source for this lesson

[Open the example source](https://github.com/umicom-foundation/Bits2Banking/blob/main/labs/native/syscall-dispatch/dispatch.c). Keep the source revision with your exercise notes so later changes can be compared.

[Course contents](index.md) · [Previous lesson](54-describe-a-service-request.md) · [Next lesson](56-check-a-publish-right.md)

