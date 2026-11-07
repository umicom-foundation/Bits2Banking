<!--
Umicom Bits2Banking
File: content/lessons/06-umicom/umicom-os-from-scratch/11-separate-accepted-and-in-flight-work.md

PURPOSE:
Explain the lesson: Separate accepted and in-flight work.

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->

# Separate accepted and in-flight work

## Prepare

Open `labs/native/service-recovery/recovery.c` and its README in the Bits2Banking checkout. This is an in-memory model: a small program that demonstrates decisions without changing the operating system. A revision is a positive number identifying a proposed change. Use a three-column paper table: operation, in-flight revision, committed revision.

## Understand the idea

A service can be working on a newer change while retaining an earlier accepted result. `inFlight` names the unfinished revision; `committed` names the accepted revision. Keeping both values makes interruption understandable.

## Work through the example

1. Start with both fields zero.
2. Find the assignment in `BtbServiceBegin`.
3. Trace beginning revision 7 without committing.
4. Write which value a status screen should call accepted.

## Check your reasoning

The table ends with in-flight 7 and committed 0. Calling a change accepted merely because it began would hide an interrupted operation.

## If something differs

Do not interpret `committed` as a disk guarantee. The example deliberately stores both fields in memory; durable saving needs a separate storage design.


## Source for this lesson

[Open the example source](https://github.com/umicom-foundation/Bits2Banking/blob/main/labs/native/service-recovery/recovery.c). Keep the source revision with your exercise notes so later changes can be compared.

[Course contents](index.md) · [Next lesson](12-reject-overlapping-service-work.md)


[Previous: Understand why a process ID is not ownership](10-understand-why-a-process-id-is-not-ownership.md)
