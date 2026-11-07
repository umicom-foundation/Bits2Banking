<!--
Umicom Bits2Banking
File: content/lessons/06-umicom/umicom-os-from-scratch/18-design-a-service-recovery-checklist.md

PURPOSE:
Explain the lesson: Design a service-recovery checklist.

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->

# Design a service-recovery checklist

## Prepare

Open `labs/native/service-recovery/recovery.c` and its README in the Bits2Banking checkout. This is an in-memory model: a small program that demonstrates decisions without changing the operating system. A revision is a positive number identifying a proposed change. Use a three-column paper table: operation, in-flight revision, committed revision.

## Understand the idea

A useful check covers transitions and retained state, not only whether a process exits. The existing recovery model provides a compact place to practise recording those observations.

## Work through the example

1. Create rows for Start, Begin, overlapping Begin, Fault, Recover, retry, Commit and Stop.
2. For each row record status and both revisions.
3. Compare with `test_recovery.c`.
4. Mark checks you only reasoned about separately from checks you ran.

## Check your reasoning

A successful recovery demonstration retains the accepted result through failure, refuses overlapping work and allows an explicit retry. The README provides optional build commands.

## If something differs

An in-memory demonstration is not proof that a bootable OS recovers from power loss. Keep that limitation beside the checklist and link later storage exercises when expanding it.


## Source for this lesson

[Open the example source](https://github.com/umicom-foundation/Bits2Banking/blob/main/labs/native/service-recovery/recovery.c). Keep the source revision with your exercise notes so later changes can be compared.

[Course contents](index.md) · [Previous lesson](17-stop-after-active-work-is-resolved.md)

