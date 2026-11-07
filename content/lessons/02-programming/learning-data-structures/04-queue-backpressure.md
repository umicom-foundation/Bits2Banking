<!--
Umicom Bits2Banking
File: content/lessons/02-programming/learning-data-structures/04-queue-backpressure.md

PURPOSE:
Explain the lesson: Handle a full queue without losing work.

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->

# Handle a full queue without losing work

## A queue is a promise about order

A queue stores waiting items so the oldest accepted item is taken first. A producer adds work; a consumer removes it. If the producer is faster, the waiting space eventually fills. Backpressure means reporting that limit so the producer can slow down or retain its work elsewhere.

## Setup recap

The [collections lab guide](https://github.com/umicom-foundation/Bits2Banking/blob/main/labs/native/collections/README.md) explains the C23 compiler, CMake, Ninja and PowerShell or Bash commands. No Framework installation is needed for this bounded teaching model. Begin with `BtbQueue queue = {0};`; the zero initialiser creates an empty queue.

## Accepted and attempted are different

The capacity is eight integers. `BtbQueuePush` returns `BTB_FULL` on a ninth insertion. That rejected value was attempted, but it was not accepted. The caller must not announce it as queued.

~~~text
accept 10,20,30,40,50,60,70,80 -> count 8
attempt 90                    -> FULL; count remains 8
remove oldest                 -> value 10; count 7
retry 90                      -> accepted; count 8
~~~

The implementation checks fullness before writing to the array. It does not silently overwrite the oldest item.

## Lab

1. Draw eight boxes and label their physical indexes 0 to 7.
2. Follow the four steps in the trace.
3. Record both the head index and count after each removal.
4. Inspect the full-queue and wraparound tests in `test_collections.c`.
5. Build and run the existing checks.
6. In an exercise copy of the caller, retain a value after `BTB_FULL` and retry it only after a successful removal.

This lab is single-threaded. Running producer and consumer on separate threads without coordination would introduce a different ownership problem.

## Decide a policy explicitly

A live audio queue might choose to drop old samples to keep latency bounded. A payment instruction queue must not quietly lose accepted work. The container reports capacity; the application chooses a documented response. Reusable queue mechanics and durable services belong in Framework.

## Troubleshooting

Repeatedly retrying a full queue in a tight loop will not create space when the same thread is supposed to consume it. Decide when the consumer runs. If values appear out of order, check the logical head and count rather than assuming physical index zero is always oldest.

## Exercise with a worked answer

After retrying 90, what should the next removal return? It should return 20. The new item belongs behind all remaining accepted items, even though its physical slot may now be index zero.

## Source for this lesson

[Open the example source](https://github.com/umicom-foundation/Bits2Banking/blob/main/labs/native/collections/collections.c). Keep the source revision with your exercise notes so later changes can be compared.

[Course contents](index.md) · [Next lesson](05-container-invariants.md)


[Previous lesson](03-queues-and-wraparound.md)
