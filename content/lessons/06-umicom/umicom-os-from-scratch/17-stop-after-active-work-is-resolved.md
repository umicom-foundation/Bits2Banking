<!--
Umicom Bits2Banking
File: content/lessons/06-umicom/umicom-os-from-scratch/17-stop-after-active-work-is-resolved.md

PURPOSE:
Explain the lesson: Stop after active work is resolved.

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->

# Stop after active work is resolved

## Prepare

Open `labs/native/service-recovery/recovery.c` and its README in the Bits2Banking checkout. This is an in-memory model: a small program that demonstrates decisions without changing the operating system. A revision is a positive number identifying a proposed change. Use a three-column paper table: operation, in-flight revision, committed revision.

## Understand the idea

Stopping releases ownership that future callbacks might otherwise reference. Releasing it while an operation is active could leave that operation referring to an invalid resource.

## Work through the example

1. Trace Stop during revision 5.
2. Locate the in-flight guard.
3. Trace a successful Commit followed by Stop.
4. Mark cancellation, release and the stopped flag.

## Check your reasoning

Stop refuses active work. In the idle path, the stopped flag changes only after release succeeds; a request to stop and completed shutdown are distinct observations.

## If something differs

If a UI closes while work is active, it needs a documented cancellation or wait path. Do not discard the service state simply because its window is no longer visible.


## Source for this lesson

[Open the example source](https://github.com/umicom-foundation/Bits2Banking/blob/main/labs/native/service-recovery/recovery.c). Keep the source revision with your exercise notes so later changes can be compared.

[Course contents](index.md) · [Previous lesson](16-keep-revisions-moving-forward.md) · [Next lesson](18-design-a-service-recovery-checklist.md)

