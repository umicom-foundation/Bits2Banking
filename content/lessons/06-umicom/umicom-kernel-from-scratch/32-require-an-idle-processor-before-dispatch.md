<!--
Umicom Bits2Banking
File: content/lessons/06-umicom/umicom-kernel-from-scratch/32-require-an-idle-processor-before-dispatch.md

PURPOSE:
Explain the lesson: Require an idle processor before dispatch.

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->

# Require an idle processor before dispatch

## Prepare
Find the runningSlot guard in BtbRoundRobinNext. The output handle tells the caller which task was selected. Dispatch is allowed only when the teaching processor is idle.

An existing running task must yield, wait or exit before another selection.

## Trace refusal
Admit A and B. Dispatch A, then immediately call Next again.

Expected: BUSY. B remains ready and A remains running. The second request cannot silently replace A.

## Lab
Write the initial ready count, first dispatch result, second dispatch result and final running state. Locate the corresponding assertion in test_round_robin.c.

Then add a paper trace in which A yields before the second Next. This time B should run.

## Exercise and explanation
Why not let Next automatically yield the old task? That would combine two state transitions and hide the caller's intent. This API makes the scheduling boundary explicit.

## Troubleshoot
A BUSY result is not necessarily corruption. It may mean that the caller skipped a required transition. Examine the operation history before changing the scheduler.

In Umicom Kernel, the point at which execution can safely change is tied to saved registers and privilege state. This hosted model teaches the state rule; it does not establish those hardware conditions.

## Source for this lesson

[Open the example source](https://github.com/umicom-foundation/Bits2Banking/blob/main/labs/native/round-robin-scheduler/round_robin.c). Keep the source revision with your exercise notes so later changes can be compared.

[Course contents](index.md) · [Previous lesson](31-dispatch-in-ready-queue-order.md) · [Next lesson](33-match-a-wakeup-to-its-wait.md)

