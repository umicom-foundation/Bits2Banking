<!--
Umicom Bits2Banking
File: content/lessons/06-umicom/umicom-kernel-from-scratch/31-dispatch-in-ready-queue-order.md

PURPOSE:
Explain the lesson: Dispatch in ready-queue order.

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->

# Dispatch in ready-queue order

## Prepare
Read Queue and BtbRoundRobinNext in round_robin.c. FIFO means first in, first out: the task that has waited longest in this ready queue is selected first.

The queue stores slot indices, while callers receive task handles.

## Trace the queue
Admit A, B and C. The ready order is A, B, C. Next removes A from the head and marks it running. Yield appends A to the end, producing B, C, A.

The array wraps using modulo BTB_RR_TASK_LIMIT.

## Lab
Continue this sequence through six dispatch-and-yield pairs. Write the expected running task each time before checking the source.

Expected: A, B, C, A, B, C while all three remain runnable and each yields once.

## Exercise and explanation
Does FIFO imply that every task receives equal elapsed CPU time? No. The model has no time slice or execution-duration measurement. It specifies selection order under the operations supplied.

## Troubleshoot
If a task runs twice before another ready task, inspect queue insertion and head advancement. Do not add a special case based on task names.

The reusable lesson is to separate policy from mechanism. FIFO is the ordering policy; the bounded ring is its storage mechanism. A native scheduler additionally needs a safe way to save and restore execution state.

## Source for this lesson

[Open the example source](https://github.com/umicom-foundation/Bits2Banking/blob/main/labs/native/round-robin-scheduler/round_robin.c). Keep the source revision with your exercise notes so later changes can be compared.

[Course contents](index.md) · [Previous lesson](30-model-ready-running-and-waiting.md) · [Next lesson](32-require-an-idle-processor-before-dispatch.md)

