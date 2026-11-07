<!--
Umicom Bits2Banking
File: content/lessons/02-programming/introduction-to-programming/12-check-before-at-and-after.md

PURPOSE:
Explain the lesson: Test a boundary from both sides.

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->

# Test a boundary from both sides

## Prepare
Use the logical timer lab. Initialise a clock, advance it to tick ten and arm a timer with interval five. Its finite deadline is tick fifteen.

A boundary is the exact value where behaviour changes.

## Build three observations
| Current tick | Expected status |
|---|---|
| 14 | NOT_DUE |
| 15 | DUE |
| 16 | DUE while still pending |

The comparison in the source uses greater than or equal to the deadline. It does not require the clock to land on the deadline exactly.

## Lab
Create a fresh clock and timer for each independent case, or advance one clock strictly forwards. Call Status without Fire when comparing the three pending observations.

Expected: jumping directly from fourteen to sixteen still reports DUE.

## Understand the contract
A logical scheduler may inspect a task later than its exact deadline. Requiring equality would miss the task forever after a skipped tick. The comparison expresses “the deadline has been reached.”

## Troubleshoot
If the sixteen-tick case returns STATE, check whether an earlier test already fired or cancelled the timer. The test setup may have changed the lifecycle before the time comparison.

## Generalise
For an array limit, test one below, exactly at and one above the allowed bound. For a text length, do the same. Boundary tests complement ordinary examples because many defects appear where an inequality changes from true to false.

## Source for this lesson

[Open the example source](https://github.com/umicom-foundation/Bits2Banking/blob/main/labs/native/monotonic-deadlines/deadline.c). Keep the source revision with your exercise notes so later changes can be compared.

[Course contents](index.md) · [Previous lesson](11-draw-a-state-machine.md) · [Next lesson](13-separate-a-query-from-a-command.md)

