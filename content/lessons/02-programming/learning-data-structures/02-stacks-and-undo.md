<!--
Umicom Bits2Banking
File: content/lessons/02-programming/learning-data-structures/02-stacks-and-undo.md

PURPOSE:
Explain one concept through a practical example and an observable result.

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->
# Stacks and the order of undo

[Course contents](index.md) · [Previous: Arrays, length and capacity](01-arrays-length-and-capacity.md) · [Next: Queues and wraparound storage](03-queues-and-wraparound.md)

## Last in, first out
A stack removes the most recently added element first. This rule is called last in, first out. Imagine recording edits A, B and C: undo should first reverse C. The rule concerns ordering, not a particular screen layout.

## Setup recap
Build the collections lab from [the course contents](index.md). A list is an array plus a count. BtbListAppend adds at the end; BtbStackPop removes from that same end. Read [the programming course](../introduction-to-programming/index.md) if function parameters or return values are unfamiliar.

## Work through the transitions
~~~text
start        []
append 4     [4]
append 8     [4,8]
pop -> 8     [4]
pop -> 4     []
pop -> empty []
~~~
Pop has two results: a status saying whether it succeeded, and an output value supplied through a pointer. A pointer identifies storage owned by the caller.
~~~c
int value = 99;
BtbResult result = BtbStackPop(&list, &value);
~~~
The & operator obtains the address of an object. The caller must inspect result before using value as a popped item. On an empty stack, the implementation leaves value unchanged.

## Lab
1. Read the empty check in BtbStackPop.
2. Find where count decreases and where the previous last value is read.
3. In test_collections.c, follow the test that pops all eight values in reverse order.
4. Run the boundary tests after building. Check both ordering and the empty result.
5. Draw a second stack containing 10, 20 and 30 and predict all three successful outputs.

## Exercise and worked answer
Why must the empty check precede --count? count is unsigned. Decreasing zero wraps to a very large value, which cannot identify an array element. The status check prevents that operation rather than trying to repair it afterwards.

## From stack to editor
[The text editor project](../../05-engineering/building-a-text-editor/index.md) starts with one saved snapshot. Extending it to many undo operations requires a history policy: maximum memory, what an entry owns, how redo behaves after a new edit, and whether large operations are grouped. Adding a stack alone does not answer those questions.

## Troubleshooting and limits
BTB_EMPTY is a normal condition when no history remains. Do not display the unchanged 99 as if it were a real result. This integer stack teaches ordering; it does not own text buffers or allocate undo records. Framework's document coordinator is the production place to investigate richer editor ownership.

## Source map
Read `labs/native/collections/collections.c` in the Bits2Banking checkout. The lesson names the specific functions to study; you do not need to understand every file at once.

[Course contents](index.md) · [Previous: Arrays, length and capacity](01-arrays-length-and-capacity.md) · [Next: Queues and wraparound storage](03-queues-and-wraparound.md)
