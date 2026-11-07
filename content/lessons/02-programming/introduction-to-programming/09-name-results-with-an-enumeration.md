<!--
Umicom Bits2Banking
File: content/lessons/02-programming/introduction-to-programming/09-name-results-with-an-enumeration.md

PURPOSE:
Explain the lesson: Give results meaningful names.

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->

# Give results meaningful names

## Prepare
Open deadline.h in labs/native/monotonic-deadlines. The directory's README gives independent CMake build commands. For the reading exercise, no compiler is required.

An enumeration gives names to a set of integer values. BtbTimerResult includes OK, INVALID, STATE, OVERFLOW, NOT_DUE and DUE, each prefixed with BTB_TIMER_.

## Read a decision
BtbDeadlineStatus returns DUE when a finite pending deadline has been reached. DUE is a successful observation, even though its numeric value is not zero.

A caller should compare the named result it expects. Treating every nonzero result as the same error would lose this distinction.

## Lab
Write a switch statement on paper with separate cases for DUE and NOT_DUE. DUE can enable a “run task” action; NOT_DUE can leave the task waiting. Other results require explaining invalid input or state.

Expected: the decision uses meaning rather than assuming that every result follows a Boolean convention.

## Connect to code
Search deadline.c for BtbDeadlineFire. It asks Status first, then accepts only DUE before changing state to FIRED. The name of each result makes the condition readable.

## Troubleshoot
If a program fires too early, inspect whether it checked for DUE specifically. A condition such as “result is not INVALID” accepts several states that do not permit firing.

## Check understanding
An enumeration describes possible values; it does not automatically enforce the entire timer lifecycle. Functions still validate which operation is allowed in the current state. Read both the names and their documented contracts.

## Source for this lesson

[Open the example source](https://github.com/umicom-foundation/Bits2Banking/blob/main/labs/native/monotonic-deadlines/deadline.c). Keep the source revision with your exercise notes so later changes can be compared.

[Course contents](index.md) · [Previous lesson](08-observe-output-and-completion.md) · [Next lesson](10-model-a-clock-with-a-record.md)

