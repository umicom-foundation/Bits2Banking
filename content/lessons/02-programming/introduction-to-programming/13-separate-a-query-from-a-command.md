<!--
Umicom Bits2Banking
File: content/lessons/02-programming/introduction-to-programming/13-separate-a-query-from-a-command.md

PURPOSE:
Explain the lesson: Separate observing state from changing it.

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->

# Separate observing state from changing it

## Prepare
Read BtbDeadlineStatus and BtbDeadlineFire. Both inspect a deadline, but only Fire changes it.

A query reports information. A command asks for a state change. The distinction helps a caller refresh a screen without accidentally completing work.

## Follow the difference
Calling Status on a due pending timer returns DUE and leaves it pending. Calling it again produces the same result if the clock is unchanged.

Calling Fire on that timer changes its state to FIRED. A later Status call returns STATE because this API reports due-ness only for pending timers.

## Lab
Write a sequence of two Status calls followed by Fire and another Status. Record both result and state after each call.

Expected results: DUE, DUE, OK, STATE. Expected states: PENDING, PENDING, FIRED, FIRED.

## Connect to an interface
A progress panel may query a job many times while painting. Rendering the panel should not itself mark the job complete. A separate event performs that transition.

## Troubleshoot
If opening a panel changes an operation's outcome, trace whether the refresh path calls a command instead of a query. Naming functions clearly helps, but inspect their contracts and actual writes.

## Check understanding
A function can return success without changing state, and a query can report an invalid state. Return values and mutation are separate properties. Document both when introducing a public API.

## Source for this lesson

[Open the example source](https://github.com/umicom-foundation/Bits2Banking/blob/main/labs/native/monotonic-deadlines/deadline.c). Keep the source revision with your exercise notes so later changes can be compared.

[Course contents](index.md) · [Previous lesson](12-check-before-at-and-after.md) · [Next lesson](14-give-zero-an-explicit-meaning.md)

