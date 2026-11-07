<!--
Umicom Bits2Banking
File: content/lessons/02-programming/learning-data-structures/14-budget-a-dispatch-turn.md

PURPOSE:
Explain the lesson: Give one dispatch turn a finite work budget.

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->

# Give one dispatch turn a finite work budget

## Prepare
Read BtbDispatchRun and its public comment. Configure the work-dispatch lab using its README when you are ready to execute the exercises. A budget limits how much work one call may attempt.

The accepted budget range is one through eight. Run invokes Step at most that many times and stops sooner when Step cannot proceed.

## Separate progress from stopping
Suppose three requests are queued and Run receives budget eight. It executes three, then observes EMPTY. Because progress occurred, Run returns OK and reports three through outRun.

With no queued work at entry, it reports EMPTY and zero. With a full completion queue and queued work, it reports BACKPRESSURE and zero.

The status answers whether this call made progress or why it could not. The count tells how much work actually ran.

## Trace and record
Prepare independent cases:
| Work available | Notice capacity | Budget | Expected count |
|---:|---:|---:|---:|
| 3 | 4 | 2 | 2 |
| 3 | 4 | 8 | 3 |
| 3 | 0 | 2 | 0 |

Check the associated status as well as the count.

## Invalid calls
Budget zero and a null output pointer are invalid. A rejected argument must leave an existing output count unchanged. Use SIZE_MAX as a sentinel in a test, then expect INVALID and the same sentinel.

## Application lesson
A finite turn gives the caller a chance to service other work between turns. It does not by itself make a long-running individual operation responsive. For production UI work, inspect Framework's scheduling and cancellation facilities rather than running an unbounded task inside a click handler.

## Source for this lesson

[Open the example source](https://github.com/umicom-foundation/Bits2Banking/blob/main/labs/native/work-dispatch/dispatch.c). Keep the source revision with your exercise notes so later changes can be compared.

[Course contents](index.md) · [Previous lesson](13-own-a-receipt-after-release.md) · [Next lesson](15-quiesce-then-drain.md)

