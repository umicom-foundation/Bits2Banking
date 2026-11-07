<!--
Umicom Bits2Banking
File: content/lessons/06-umicom/umicom-kernel-from-scratch/59-publish-event-and-reply-together.md

PURPOSE:
Explain the lesson: Publish an event and its reply.

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->

# Publish an event and its reply

## Prepare

Open `labs/native/syscall-dispatch/dispatch.h` and `dispatch.c`. A request asks a service to do work; a reply carries its result. This is a hosted teaching model with ordinary function calls, not an actual processor trap. Read the header's ownership rules before changing an example.

## Understand the idea

Successful publication updates several related values: the event bytes, event count, revision and reply. These should describe one completed operation. The code performs all refusal checks before this group of assignments.

## Work through the example

1. Start with count 0 and revision 1.
2. Follow a successful publication of `ready`.
3. Record the bytes stored in slot 0.
4. Record count 1 and revision 2.
5. Record the reply's value and revision.

## Check your reasoning

The reply reports one stored event at revision 2. The text is copied into service-owned storage, so later changes to the caller's buffer do not change this event.

## If something differs

The example is serial. Grouping assignments after validation does not make it safe for multiple threads without an additional synchronisation design.


## Source for this lesson

[Open the example source](https://github.com/umicom-foundation/Bits2Banking/blob/main/labs/native/syscall-dispatch/dispatch.c). Keep the source revision with your exercise notes so later changes can be compared.

[Course contents](index.md) · [Previous lesson](58-bound-and-validate-service-text.md) · [Next lesson](60-report-full-capacity-without-overwriting.md)

