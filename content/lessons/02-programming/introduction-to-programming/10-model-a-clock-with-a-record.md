<!--
Umicom Bits2Banking
File: content/lessons/02-programming/introduction-to-programming/10-model-a-clock-with-a-record.md

PURPOSE:
Explain the lesson: Model a clock with one explicit value.

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->

# Model a clock with one explicit value

## Prepare
Read BtbLogicalClock and BtbClockInit in the deadline lab. A record, called a struct in C, groups named fields. This one has a single unsigned 64-bit field named now.

The model has logical ticks. A tick has no automatic relationship to seconds, milliseconds or processor cycles.

## Initialise before use
BtbClockInit sets now to zero. BtbClockAdvance accepts a new tick only when it is strictly greater than the current value.

Starting at zero, advancing to ten succeeds. Advancing to ten again is refused, as is advancing to nine.

## Lab
Draw a table with requested tick, result and stored tick. Use requests 3, 7, 7, 2 and 9 in that order.

Expected stored values are 3, 7, 7, 7 and 9. A refused request preserves the previous value.

## Why model time?
A test can move a logical clock directly to an interesting boundary. It does not need to wait ten real seconds to test a deadline ten ticks away. This makes experiments repeatable.

## Troubleshoot
Do not add a sleep call to make this model advance. The source changes now only through BtbClockAdvance. Waiting in the terminal has no effect.

## Connect to Umicom
Real applications need an operating-system timing source with documented units. Framework services can adapt that source. This laboratory isolates the rules for comparing times so the learner can understand them before introducing platform clocks and asynchronous callbacks.

## Source for this lesson

[Open the example source](https://github.com/umicom-foundation/Bits2Banking/blob/main/labs/native/monotonic-deadlines/deadline.c). Keep the source revision with your exercise notes so later changes can be compared.

[Course contents](index.md) · [Previous lesson](09-name-results-with-an-enumeration.md) · [Next lesson](11-draw-a-state-machine.md)

