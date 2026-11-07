<!--
Umicom Bits2Banking
File: content/lessons/02-programming/learning-data-structures/07-separate-slot-and-job-identity.md

PURPOSE:
Explain the lesson: Separate storage slots from job identity.

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->

# Separate storage slots from job identity

A circular queue reuses storage slots. A slot number tells you where a value is stored; a job number tells you which piece of work it represents.

## Prepare

Read BtbQueuePush and BtbQueuePop in collections.c beside queue_pipeline.c. A queue starts with head zero and count zero. Its array has eight positions numbered zero through seven.

## Draw the storage

Draw eight boxes. Fill them with jobs 1 through 8. Now remove jobs 1 and 2.

The removed array cells may still contain old numbers. The queue's head and count determine which cells are active; clearing every released cell is unnecessary for this integer exercise.

Append jobs 9 and 10. The tail calculation is:

```c
(head + count) % BTB_COLLECTION_CAPACITY
```

The remainder operator maps a position back into the eight-slot range.

## Check your drawing

After the two removals and two additions, head is 2 and count is 8. Slot 0 holds job 9 and slot 1 holds job 10. Reading active values from head gives 3, 4, 5, 6, 7, 8, 9, 10.

The physical array order and logical queue order now differ.

## Extend the exercise

Remove all eight values. Check every received identity against the expected sequence. Finally try another removal with an output variable initialized to -1. Expect BTB_EMPTY and an unchanged output.

If your drawing gives job 9 before job 3, you followed physical slot order instead of queue order.

## Apply the distinction

A media render queue or network receive queue must preserve logical order even when its storage wraps. Do not expose a reused slot number as a permanent external job identifier.

This lab stores integers and has one caller at a time. Object lifetimes and concurrent access require additional contracts in a production Framework service.

## Source for this lesson

[Open the example source](https://github.com/umicom-foundation/Bits2Banking/blob/main/labs/native/collections/queue_pipeline.c). Keep the source revision with your exercise notes so later changes can be compared.

[Course contents](index.md) · [Previous lesson](06-trace-a-producer-and-consumer.md) · [Next lesson](08-reserve-undo-before-changing-state.md)

