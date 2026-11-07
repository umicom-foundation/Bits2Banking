<!--
Umicom Bits2Banking
File: content/lessons/06-umicom/umicom-kernel-from-scratch/57-refuse-a-stale-revision.md

PURPOSE:
Explain the lesson: Refuse a stale revision.

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->

# Refuse a stale revision

## Prepare

Open `labs/native/syscall-dispatch/dispatch.h` and `dispatch.c`. A request asks a service to do work; a reply carries its result. This is a hosted teaching model with ordinary function calls, not an actual processor trap. Read the header's ownership rules before changing an example.

## Understand the idea

A revision identifies a version of state. A caller supplies the revision it last observed. Comparing it before an update detects a request based on old state, which may otherwise overwrite another completed action.

## Work through the example

1. Start at revision 1 with an empty event list.
2. Publish a valid event expecting revision 1.
3. The state advances to revision 2.
4. Try another request still expecting revision 1.
5. Trace the conflict return before the text copy.

## Check your reasoning

The second request is refused and does not create a second event. A caller should re-read state and decide whether the intended operation is still appropriate.

## If something differs

Do not automatically retry an old operation forever. Refreshing a number without reconsidering the action can create duplicate work.


## Source for this lesson

[Open the example source](https://github.com/umicom-foundation/Bits2Banking/blob/main/labs/native/syscall-dispatch/dispatch.c). Keep the source revision with your exercise notes so later changes can be compared.

[Course contents](index.md) · [Previous lesson](56-check-a-publish-right.md) · [Next lesson](58-bound-and-validate-service-text.md)

