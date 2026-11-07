<!--
Umicom Bits2Banking
File: content/lessons/06-umicom/umicom-os-from-scratch/14-fault-without-replacing-the-last-result.md

PURPOSE:
Explain the lesson: Fault without replacing the last result.

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->

# Fault without replacing the last result

## Prepare

Open `labs/native/service-recovery/recovery.c` and its README in the Bits2Banking checkout. This is an in-memory model: a small program that demonstrates decisions without changing the operating system. A revision is a positive number identifying a proposed change. Use a three-column paper table: operation, in-flight revision, committed revision.

## Understand the idea

A fault describes an operation that could not complete normally. The previous accepted result remains useful when the new operation fails.

## Work through the example

1. Assume revision 4 was committed.
2. Begin revision 5, then call `BtbServiceFault`.
3. Read which fields Fault assigns directly.
4. Record the last accepted revision and the unfinished revision.

## Check your reasoning

The accepted revision remains 4 and the in-flight revision remains 5 until recovery. The underlying ownership object records the fault state.

## If something differs

Avoid inventing a successful result from a fault notification. In a user interface show the last accepted revision separately from the failure and any pending recovery action.


## Source for this lesson

[Open the example source](https://github.com/umicom-foundation/Bits2Banking/blob/main/labs/native/service-recovery/recovery.c). Keep the source revision with your exercise notes so later changes can be compared.

[Course contents](index.md) · [Previous lesson](13-publish-after-completion-checks.md) · [Next lesson](15-recover-before-retrying-a-revision.md)

