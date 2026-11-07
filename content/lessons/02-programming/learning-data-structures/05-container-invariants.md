<!--
Umicom Bits2Banking
File: content/lessons/02-programming/learning-data-structures/05-container-invariants.md

PURPOSE:
Explain the lesson: Check the promises that keep a container valid.

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->

# Check the promises that keep a container valid

## What an invariant means

An invariant is a statement that should remain true whenever an operation finishes. For the list, the count must never exceed its capacity. For the queue, the head must also identify one of the array's valid positions. These statements make every later operation easier to reason about.

## Setup recap

Prepare the [collections lab](https://github.com/umicom-foundation/Bits2Banking/blob/main/labs/native/collections/README.md) with a C23 compiler, CMake and Ninja. Open its header and implementation in a text editor. A structure groups related values; here the array, count and head together describe one container.

## Separate valid state from accepted input

A full queue is still a valid queue. It refuses another push with `BTB_FULL`. A queue whose count is greater than capacity is invalid and returns `BTB_INVALID`. These outcomes should not be treated as interchangeable.

~~~text
head 0, count 0 -> valid empty
head 7, count 8 -> valid full
head 8, count 1 -> invalid head
head 0, count 9 -> invalid count
~~~

The public contract also says that an output pointer must address storage outside the model. For example, use a separate local integer for a popped value.

~~~c
int value = -1;
BtbResult result = BtbQueuePop(&queue, &value);
if (result == BTB_OK) {
    /* Use value only after success. */
}
~~~

## Lab

1. Write down each invariant beside its structure declaration.
2. Find the checks that protect every array access in Push and Pop.
3. Trace Pop on an empty queue and verify that the output remains unchanged.
4. Read the invalid-state checks in the test file.
5. Build and run the lab checks.
6. Add an exercise case that initialises the output to a conspicuous value and confirms a rejected operation preserves it.

Do not corrupt a production object merely to investigate it. Deliberately invalid state belongs in an isolated regression test.

## Beyond bounds

A valid count does not by itself make an object safe to share between threads. Nor does it prove that a borrowed pointer stays alive. Bounds, ownership, ordering and concurrency are different parts of a contract.

## Troubleshooting and review

If a test reports the right error but the output changed, the failure contract was violated. Check the order of validation and mutation. If the failure only appears after several operations, record the operation sequence and each state transition; the final call may merely reveal earlier corruption.

## Connect to Umicom

Framework containers and document models benefit from the same explicit invariants. The teaching lab exposes the mechanism; applications should consume shared services instead of creating their own unchecked container variants.

## Source for this lesson

[Open the example source](https://github.com/umicom-foundation/Bits2Banking/blob/main/labs/native/collections/collections.h). Keep the source revision with your exercise notes so later changes can be compared.

[Course contents](index.md) · [Previous lesson](04-queue-backpressure.md)


[Next: Trace a producer and a consumer](06-trace-a-producer-and-consumer.md)
