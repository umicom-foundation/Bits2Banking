<!--
Umicom Bits2Banking
File: content/lessons/02-programming/learning-data-structures/15-quiesce-then-drain.md

PURPOSE:
Explain the lesson: Stop admission before draining a service.

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->

# Stop admission before draining a service

## Prepare
Open BtbDispatchQuiesce and BtbDispatchDrained. The work-dispatch README explains the independent build. Quiescing means refusing new work while allowing work already accepted to finish or be cancelled.

## Follow shutdown
Submit two requests, then call Quiesce. A third submission should return QUIESCING. The first two still belong to the dispatcher.

Run or cancel them, then receive their terminal notices. Only when the work slots and notices are empty should Drained report true.

This is different from immediately erasing the dispatcher. Erasure would lose accepted work and pending results.

## State table
| Stage | Accepts submissions? | Drained? |
|---|---|---|
| Two queued requests | Yes | No |
| After quiesce | No | No |
| Both executed, receipts pending | No | No |
| Both receipts received | No | Yes |

## Exercise
Stop after execution but before receiving results. Inspect the queued count: it may be zero. Then inspect pending notices and Drained.

Expected: zero queued work does not mean shutdown is complete. The caller still has results to collect and slots to release.

## Troubleshoot
If shutdown waits forever, identify which stage owns the outstanding item. Repeatedly asking Drained does not itself process work or receive notices. The caller must perform the allowed progress operations.

## Connect to applications
Closing a media export panel, stopping a build or disconnecting a broker can all involve pending work. Their domain-specific services need explicit shutdown contracts. This lab provides a small state model to reason about the distinction between admission, completion and delivery, not a ready-made replacement for those Framework services.

## Source for this lesson

[Open the example source](https://github.com/umicom-foundation/Bits2Banking/blob/main/labs/native/work-dispatch/dispatch.c). Keep the source revision with your exercise notes so later changes can be compared.

[Course contents](index.md) · [Previous lesson](14-budget-a-dispatch-turn.md) · [Next lesson](16-count-invariants.md)

