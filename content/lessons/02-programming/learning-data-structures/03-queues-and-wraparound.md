<!--
Umicom Bits2Banking
File: content/lessons/02-programming/learning-data-structures/03-queues-and-wraparound.md

PURPOSE:
Explain one concept through a practical example and an observable result.

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->
# Queues and wraparound storage

[Course contents](index.md) · [Previous: Stacks and the order of undo](02-stacks-and-undo.md)

## First in, first out
A queue gives the oldest waiting item to the next consumer. This is first in, first out. A stack would serve the newest item first. Choosing the order is part of the required behaviour.

## Setup recap
Use [the collections setup](index.md). Open BtbQueue in collections.h and QueuePush/QueuePop in collections.c. An array is indexed storage; a count records occupied elements; head identifies the next item to remove.

## Reuse space without shifting every item
The queue stores eight integers. Removing an item advances head. Adding an item uses:
~~~c
tail = (head + count) % BTB_COLLECTION_CAPACITY;
~~~
The % operator computes the remainder. For capacity 8, index 8 wraps to 0, and 9 wraps to 1. The operands here are already bounded, so the addition cannot overflow size_t.
~~~text
head=6, count=3
logical order: slot 6 -> slot 7 -> slot 0
next insertion: (6 + 3) % 8 = slot 1
~~~
The array is physically unchanged in shape. The logical order moves around it.

## Lab
1. Initialise BtbQueue queue = {0}.
2. Read the test that pushes values 0 through 7.
3. Follow four repetitions of pop then push. Draw head and count after each.
4. Predict why the remaining removal order is 4 through 11.
5. Run the collection tests and compare their result with your trace.

## Exercise and worked answer
A queue has head = 7, count = 1. After one successful pop, head becomes 0 and count becomes 0. The next push writes slot 0. An empty queue does not have to return its head to the original starting point.

## Connect to larger systems
Umicom jobs and kernel messages need explicit queue ownership, cancellation and capacity rules. This model explains wraparound only. Before using a queue across threads, study how the production service synchronises producers and consumers; adding a shared global array is not enough.

## Troubleshooting
A corrupted head equal to 8 is invalid even when count is zero. The implementation refuses it. A full queue returns BTB_FULL and keeps all items. Decide whether a real caller should wait, reject or apply backpressure; silently overwriting an old job would change the contract.

## Next step
[Learning Algorithms](../learning-algorithms/index.md) uses the same collection source to teach search and sorting, so you can concentrate on the operation rather than learning another storage model.

## Source map
Read `labs/native/collections/collections.c` in the Bits2Banking checkout. The lesson names the specific functions to study; you do not need to understand every file at once.

[Course contents](index.md) · [Previous: Stacks and the order of undo](02-stacks-and-undo.md)

[Continue: Handle a full queue without losing work](04-queue-backpressure.md)
