<!--
Umicom Bits2Banking
File: content/lessons/06-umicom/umicom-os-from-scratch/13-publish-after-completion-checks.md

PURPOSE:
Explain the lesson: Publish after completion checks.

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->

# Publish after completion checks

## Prepare

Open `labs/native/service-recovery/recovery.c` and its README in the Bits2Banking checkout. This is an in-memory model: a small program that demonstrates decisions without changing the operating system. A revision is a positive number identifying a proposed change. Use a three-column paper table: operation, in-flight revision, committed revision.

## Understand the idea

Acknowledgement means the modeled operation has been accepted by its owner. Returning from the interrupt-like scope releases that active stage. These checks occur before publishing the revision.

## Work through the example

1. In `BtbServiceCommit`, mark the acknowledge call, return call and committed assignment.
2. Draw arrows in that order.
3. Trace a failed acknowledge.
4. State which assignment must remain unreachable.

## Check your reasoning

A failed acknowledge returns before the committed revision changes. Successful acknowledgement alone is insufficient if the following return check fails.

## If something differs

Read each return value independently. A function containing several successful-looking calls can still fail before publication; logging only the final assignment loses that evidence.


## Source for this lesson

[Open the example source](https://github.com/umicom-foundation/Bits2Banking/blob/main/labs/native/service-recovery/recovery.c). Keep the source revision with your exercise notes so later changes can be compared.

[Course contents](index.md) · [Previous lesson](12-reject-overlapping-service-work.md) · [Next lesson](14-fault-without-replacing-the-last-result.md)

