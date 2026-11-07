<!--
Umicom Bits2Banking
File: content/lessons/06-umicom/umicom-kernel-from-scratch/56-check-a-publish-right.md

PURPOSE:
Explain the lesson: Check a publish right.

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->

# Check a publish right

## Prepare

Open `labs/native/syscall-dispatch/dispatch.h` and `dispatch.c`. A request asks a service to do work; a reply carries its result. This is a hosted teaching model with ordinary function calls, not an actual processor trap. Read the header's ownership rules before changing an example.

## Understand the idea

A right is permission to perform an operation. A bit mask stores several yes/no permissions in one integer. The service checks the publish bit before inspecting the new event text or modifying state.

## Work through the example

1. Use the publish request for caller 7.
2. Set rights to zero and predict the status.
3. Set rights to `BTB_SERVICE_RIGHT_PUBLISH` and continue to the next checks.
4. Locate the bitwise `&` expression.
5. Explain why a nonzero caller alone is insufficient.

## Check your reasoning

Without the right, the model returns denied. With the right, it still checks revision, text and capacity. Passing one check does not bypass the others.

## If something differs

In a real system, never let untrusted request bytes decide their own effective rights. Derive them from a validated handle or capability.


## Source for this lesson

[Open the example source](https://github.com/umicom-foundation/Bits2Banking/blob/main/labs/native/syscall-dispatch/dispatch.c). Keep the source revision with your exercise notes so later changes can be compared.

[Course contents](index.md) · [Previous lesson](55-read-a-service-without-changing-it.md) · [Next lesson](57-refuse-a-stale-revision.md)

