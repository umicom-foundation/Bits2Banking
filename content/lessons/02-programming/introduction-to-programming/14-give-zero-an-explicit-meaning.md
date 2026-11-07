<!--
Umicom Bits2Banking
File: content/lessons/02-programming/introduction-to-programming/14-give-zero-an-explicit-meaning.md

PURPOSE:
Explain the lesson: Give a special value an explicit meaning.

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->

# Give a special value an explicit meaning

## Prepare
Read the interval comment in deadline.h. In this lab, interval zero means an unbounded wait. It does not mean “fire immediately.”

A special value has meaning only because the API defines it.

## Follow the representation
BtbDeadlineArm stores until equal to zero for an unbounded wait. Status checks that until is nonzero before comparing the clock.

Consequently, advancing the clock does not make an unbounded wait due. It can still be cancelled while pending.

## Lab
Arm interval zero, advance the clock to one hundred and query the timer. Then cancel it.

Expected: NOT_DUE followed by successful cancellation. The timer ends in CANCELLED.

## Compare a finite wait
Arm a fresh timer with interval one at tick one hundred. At tick one hundred and one it becomes due.

The difference comes from the explicit zero policy, not from the integer type.

## Troubleshoot
When connecting two libraries, check their conventions. Another API may use zero for immediate completion, no timeout, invalid input or a default duration. Passing the value unchanged across an adapter can silently change behaviour.

## Design exercise
Write a function contract for a timeout with separate finite and unlimited modes. Explain how it avoids overloading a number with two meanings. Such a design can improve clarity, but it must preserve compatibility if replacing an existing public interface.

## Source for this lesson

[Open the example source](https://github.com/umicom-foundation/Bits2Banking/blob/main/labs/native/monotonic-deadlines/deadline.c). Keep the source revision with your exercise notes so later changes can be compared.

[Course contents](index.md) · [Previous lesson](13-separate-a-query-from-a-command.md) · [Next lesson](15-define-cancellation-at-a-deadline.md)

