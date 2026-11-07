<!--
Umicom Bits2Banking
File: content/lessons/06-umicom/umicom-os-from-scratch/16-keep-revisions-moving-forward.md

PURPOSE:
Explain the lesson: Keep revisions moving forward.

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->

# Keep revisions moving forward

## Prepare

Open `labs/native/service-recovery/recovery.c` and its README in the Bits2Banking checkout. This is an in-memory model: a small program that demonstrates decisions without changing the operating system. A revision is a positive number identifying a proposed change. Use a three-column paper table: operation, in-flight revision, committed revision.

## Understand the idea

Revision order prevents an older request from replacing a newer accepted result. Zero is reserved for no in-flight operation, so it is not a valid requested revision.

## Work through the example

1. Set the accepted revision to 9 in a paper example.
2. Trace Begin requests 0, 8, 9 and 10 on an idle started service.
3. Separate invalid-argument and wrong-stage results.

## Check your reasoning

Zero is an invalid argument; 8 and 9 are not newer than the accepted result. Only 10 reaches the ownership-entry step, which still needs to succeed.

## If something differs

Do not solve revision exhaustion by wrapping to zero. A production policy must explicitly define how a new revision identity is created without confusing earlier work.


## Source for this lesson

[Open the example source](https://github.com/umicom-foundation/Bits2Banking/blob/main/labs/native/service-recovery/recovery.c). Keep the source revision with your exercise notes so later changes can be compared.

[Course contents](index.md) · [Previous lesson](15-recover-before-retrying-a-revision.md) · [Next lesson](17-stop-after-active-work-is-resolved.md)

