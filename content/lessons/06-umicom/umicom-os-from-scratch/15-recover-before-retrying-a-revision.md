<!--
Umicom Bits2Banking
File: content/lessons/06-umicom/umicom-os-from-scratch/15-recover-before-retrying-a-revision.md

PURPOSE:
Explain the lesson: Recover before retrying a revision.

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->

# Recover before retrying a revision

## Prepare

Open `labs/native/service-recovery/recovery.c` and its README in the Bits2Banking checkout. This is an in-memory model: a small program that demonstrates decisions without changing the operating system. A revision is a positive number identifying a proposed change. Use a three-column paper table: operation, in-flight revision, committed revision.

## Understand the idea

Recovery clears the failed in-flight operation only after its ownership transition succeeds. It does not pretend the failed work was accepted. A new Begin is an explicit retry decision.

## Work through the example

1. Continue the faulted revision-5 trace.
2. Find the successful recovery assignment to `inFlight`.
3. Compare revision 5 with committed revision 4.
4. Explain why a later Begin of 5 can be meaningful.

## Check your reasoning

After successful recovery, in-flight becomes 0 and committed remains 4. Revision 5 is still newer than 4, so it can be proposed again.

## If something differs

If recovery returns an error, do not clear the caller's display of unfinished work as though recovery succeeded. Preserve the error and inspect the ownership state.


## Source for this lesson

[Open the example source](https://github.com/umicom-foundation/Bits2Banking/blob/main/labs/native/service-recovery/recovery.c). Keep the source revision with your exercise notes so later changes can be compared.

[Course contents](index.md) · [Previous lesson](14-fault-without-replacing-the-last-result.md) · [Next lesson](16-keep-revisions-moving-forward.md)

