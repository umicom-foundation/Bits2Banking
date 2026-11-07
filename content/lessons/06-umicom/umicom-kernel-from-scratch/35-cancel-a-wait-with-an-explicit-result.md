<!--
Umicom Bits2Banking
File: content/lessons/06-umicom/umicom-kernel-from-scratch/35-cancel-a-wait-with-an-explicit-result.md

PURPOSE:
Explain the lesson: Cancel a waiting task explicitly.

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->

# Cancel a waiting task explicitly

## Prepare
Read BtbRoundRobinCancelWait. In this teaching model, cancelling a matching wait stops the task. It does not return that task to the ready queue.

Read that contract before using a familiar word such as cancel.

## Trace the operation
Dispatch A and wait on key eight. Cancel with key seven: refusal, still waiting. Cancel with key eight: STOPPED, waitKey zero and waitingCount reduced.

A later wake with the old handle is stale because the task is stopped.

## Lab
Create a table with the two cancellation attempts and the expected task state after each. Locate the assertions in the refusal test.

Expected: only the matching cancellation changes the task.

## Exercise and explanation
Could another scheduler define cancellation as resuming with an error result? Yes, but it would need a different explicit transition and result-delivery contract. Do not infer that behaviour here.

## Troubleshoot
If a UI offers “cancel operation” for a real application, decide whether it stops an entire task, aborts one request, or merely stops waiting for a result. These are different behaviours.

The model is useful because its transition is small and visible. Production cancellation also requires ownership of external requests and rules for late completion, covered by separate lifecycle laboratories.

## Source for this lesson

[Open the example source](https://github.com/umicom-foundation/Bits2Banking/blob/main/labs/native/round-robin-scheduler/round_robin.c). Keep the source revision with your exercise notes so later changes can be compared.

[Course contents](index.md) · [Previous lesson](34-exit-and-reuse-task-slots.md) · [Next lesson](36-check-scheduler-accounting.md)

