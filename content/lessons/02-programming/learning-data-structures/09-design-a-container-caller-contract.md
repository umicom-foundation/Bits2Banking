<!--
Umicom Bits2Banking
File: content/lessons/02-programming/learning-data-structures/09-design-a-container-caller-contract.md

PURPOSE:
Explain the lesson: Design a container caller contract.

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->

# Design a container caller contract

A container's contract explains what inputs it accepts and what it changes. The caller also has responsibilities. Both sides are needed to understand an operation.

## Prepare

Read collections.h, especially the comment above the function declarations. A declaration gives a function's name, parameters and return type. The nearby contract explains facts that C's types alone cannot express.

The lab uses caller-owned models initialized with = {0}. There is no allocation or background thread.

## Separate responsibilities

The queue checks that head is within capacity and count does not exceed capacity. The caller must supply a real object with a lifetime covering the call.

An output pointer must refer to writable storage outside the model. For example:

```c
int received = -1;
BtbResult result = BtbQueuePop(&queue, &received);
```

Do not point received into the queue's own fields or array. A successful removal would then modify storage used to describe or retain the queue.

## Write a decision table

For Pop, record four cases: invalid model, invalid output pointer, empty queue and successful removal. Identify whether output and count change in each case.

An empty queue is a valid state. It is different from an impossible count greater than capacity.

## Exercise

Before calling Pop, save count and initialize received to a distinctive value. For an empty queue, verify both are unchanged. For a successful pop, verify count decreases by one.

Do not compare the complete structure using memcmp unless padding and every byte's initialization are part of the contract. Compare the meaningful fields instead.

## Continue into Framework

Look for the same information when reading a Framework API: who owns each argument, whether a pointer is borrowed, which failures leave state unchanged and whether concurrent calls are permitted. Function names alone cannot answer these questions.

## Source for this lesson

[Open the example source](https://github.com/umicom-foundation/Bits2Banking/blob/main/labs/native/collections/collections.h). Keep the source revision with your exercise notes so later changes can be compared.

[Course contents](index.md) · [Previous lesson](08-reserve-undo-before-changing-state.md)


[Next: Compose a work pipeline from existing queues](10-compose-a-work-pipeline.md)
