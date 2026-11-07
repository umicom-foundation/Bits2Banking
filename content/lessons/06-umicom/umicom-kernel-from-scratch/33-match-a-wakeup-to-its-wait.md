<!--
Umicom Bits2Banking
File: content/lessons/06-umicom/umicom-kernel-from-scratch/33-match-a-wakeup-to-its-wait.md

PURPOSE:
Explain the lesson: Match a wake event to its wait.

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->

# Match a wake event to its wait

## Prepare
Read BtbRoundRobinWait and BtbRoundRobinWake. A wait key is a nonzero integer identifying the event this model expects.

A task handle identifies the task; the key identifies its current wait reason.

## Work an example
Notes is running and waits for key seventeen, representing a save completion in the demo. A wake using key eighteen is refused. A wake using seventeen returns Notes to the ready queue.

The task is not dispatched immediately by Wake.

## Lab
Draw the ready queue before and after waking Notes while Reports is already ready.

Expected: Reports remains ahead of Notes. A wake adds newly ready work at the queue's end.

## Exercise and explanation
Why check both state and key? A matching number alone cannot establish that the task is currently waiting. A delayed event must not turn a running or stopped task into ready work.

## Troubleshoot
This simple model does not include a distinct generation for each wait registration. If a future design reuses the same key for separate waits and receives delayed external completions, it needs a stronger event-identity contract.

Use the model's current guarantees precisely. Do not describe a numeric key as proof of network authenticity or a complete asynchronous cancellation solution.

## Source for this lesson

[Open the example source](https://github.com/umicom-foundation/Bits2Banking/blob/main/labs/native/round-robin-scheduler/round_robin.c). Keep the source revision with your exercise notes so later changes can be compared.

[Course contents](index.md) · [Previous lesson](32-require-an-idle-processor-before-dispatch.md) · [Next lesson](34-exit-and-reuse-task-slots.md)

