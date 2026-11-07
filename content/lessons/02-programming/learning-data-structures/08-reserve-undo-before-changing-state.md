<!--
Umicom Bits2Banking
File: content/lessons/02-programming/learning-data-structures/08-reserve-undo-before-changing-state.md

PURPOSE:
Explain the lesson: Reserve undo history before changing state.

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->

# Reserve undo history before changing state

An undo command needs enough information to restore an earlier state. In this exercise the state is a single integer, so one previous integer is a complete undo record.

## Prepare

Open undo_trace.c. Change accepts a history stack, a pointer to the current value and a proposed replacement. A pointer lets the function update the caller's value.

Start with current equal to 10 and an empty history.

## Follow one edit

1. Append 10 to history.
2. Check the append result.
3. Only when it succeeds, replace current with 11.

This order matters. Changing current first would lose the old value if the history append then failed.

Write the state after replacements 11 and 12: current is 12, and history contains 10 followed by 11.

## Undo

BtbStackPop removes the most recently saved value. The first undo restores 11. The next restores 10.

Undo follows the reverse order of successful edits. A queue would return the oldest value first and would be the wrong structure for this simple history.

## Reach the boundary

The program performs eight edits. Current becomes 18 and history is full. An attempted change to 99 must return BTB_FULL while current stays 18.

Build and run the example using WORKFLOWS.md. The expected restoration output runs from 17 down to 10.

## Exercise

Add a printed line before the rejected edit showing current and history.count, then print them afterward. They must be unchanged.

An empty pop must also preserve current. This lets callers distinguish “nothing to undo” from a successful edit to zero.

A complete Studio editor needs records for text ranges, selections and document identity. The example teaches the ordering rule before introducing those larger records; it does not replace Framework's document history.

## Source for this lesson

[Open the example source](https://github.com/umicom-foundation/Bits2Banking/blob/main/labs/native/collections/undo_trace.c). Keep the source revision with your exercise notes so later changes can be compared.

[Course contents](index.md) · [Previous lesson](07-separate-slot-and-job-identity.md) · [Next lesson](09-design-a-container-caller-contract.md)

