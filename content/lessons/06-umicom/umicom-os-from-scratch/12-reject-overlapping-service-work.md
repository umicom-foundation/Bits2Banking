<!--
Umicom Bits2Banking
File: content/lessons/06-umicom/umicom-os-from-scratch/12-reject-overlapping-service-work.md

PURPOSE:
Explain the lesson: Reject overlapping service work.

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->

# Reject overlapping service work

## Prepare

Open `labs/native/service-recovery/recovery.c` and its README in the Bits2Banking checkout. This is an in-memory model: a small program that demonstrates decisions without changing the operating system. A revision is a positive number identifying a proposed change. Use a three-column paper table: operation, in-flight revision, committed revision.

## Understand the idea

One service instance has one in-flight slot. An additional request cannot safely overwrite that slot, because the original completion would then refer to the wrong revision.

## Work through the example

1. Begin revision 7.
2. Trace `BtbServiceBegin(service, 8)` before completion.
3. Locate the guard on `inFlight`.
4. Explain what the caller can tell the user while work remains active.

## Check your reasoning

The second Begin returns a wrong-stage result and retains revision 7. A useful message is that work is already active; silently reporting revision 8 as queued would be inaccurate.

## If something differs

If a real application needs a queue, introduce explicit bounded queue ownership through the shared Framework service. Do not remove the guard and assume requests will finish in order.


## Source for this lesson

[Open the example source](https://github.com/umicom-foundation/Bits2Banking/blob/main/labs/native/service-recovery/recovery.c). Keep the source revision with your exercise notes so later changes can be compared.

[Course contents](index.md) · [Previous lesson](11-separate-accepted-and-in-flight-work.md) · [Next lesson](13-publish-after-completion-checks.md)

