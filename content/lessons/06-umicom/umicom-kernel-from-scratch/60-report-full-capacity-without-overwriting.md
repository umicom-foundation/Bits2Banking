<!--
Umicom Bits2Banking
File: content/lessons/06-umicom/umicom-kernel-from-scratch/60-report-full-capacity-without-overwriting.md

PURPOSE:
Explain the lesson: Report full capacity without overwriting.

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->

# Report full capacity without overwriting

## Prepare

Open `labs/native/syscall-dispatch/dispatch.h` and `dispatch.c`. A request asks a service to do work; a reply carries its result. This is a hosted teaching model with ordinary function calls, not an actual processor trap. Read the header's ownership rules before changing an example.

## Understand the idea

A bounded service has a known maximum. The teaching model stores four events. Refusing a fifth event protects earlier records and gives the caller a clear result instead of silently discarding information.

## Work through the example

1. Starting from revision 1, publish four valid events using the current revision each time.
2. Predict count 4 and revision 5.
3. Submit a fifth valid request expecting revision 5.
4. Find the full-capacity check.
5. Verify on paper that neither state nor reply changes.

## Check your reasoning

The fifth request returns full. The service has no removal operation in this lab, so the caller must report the limit rather than pretending a retry will free space.

## If something differs

Do not reset the whole service merely to hide a full response. Retention and removal are separate features with explicit ownership requirements.


## Source for this lesson

[Open the example source](https://github.com/umicom-foundation/Bits2Banking/blob/main/labs/native/syscall-dispatch/dispatch.c). Keep the source revision with your exercise notes so later changes can be compared.

[Course contents](index.md) · [Previous lesson](59-publish-event-and-reply-together.md) · [Next lesson](61-design-a-kernel-boundary-test-table.md)

