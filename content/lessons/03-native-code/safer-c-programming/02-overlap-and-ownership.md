<!--
Umicom Bits2Banking
File: content/lessons/03-native-code/safer-c-programming/02-overlap-and-ownership.md

PURPOSE:
Explain one concept through a practical example and an observable result.

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->
# Overlapping memory and ownership

[Course contents](index.md) · [Previous: Bounds and preserving state on failure](01-bounds-and-failure-preservation.md) · [Next: Numbers, file writes and useful checks](03-numbers-files-and-checks.md)

## The hidden complication
Suppose an editor contains abc and a caller asks it to insert its own first two bytes at position 1. The input and output share storage. This is called aliasing: more than one reference reaches the same memory.

The desired result is aabbc. Moving existing text before reading the supplied bytes can change the input. Correct code must account for the overlap.

## Prepare the source
Follow [the course setup](index.md). Open editor.c and test_editor.c in labs/native/text-editor. You can trace the arrays on paper before building.

## Give every byte a job
~~~text
before:       a b c zero
input span:   a b
insert at:      ^
after:        a a b b c zero
~~~
The model first validates and copies the input to a temporary array. It then remembers the old text for undo, moves the tail, and writes the temporary input into the gap.

The temporary array belongs to this function call. The editor structure belongs to its caller. Ownership here describes who is responsible for keeping storage alive and updating it correctly.

## Choose the right operation
memcpy copies bytes between non-overlapping regions. memmove supports overlapping source and destination regions. Shifting a tail within one buffer needs memmove. Copying from the separate temporary array can use memcpy.

The tail move includes the terminating zero. Otherwise an insertion could leave a character sequence with no valid string terminator.

## Inspect the order
1. Check that the editor's length and terminator agree.
2. Check the position and available capacity.
3. Validate each input byte and copy the span to temporary storage.
4. Capture the old state for undo.
5. Move the tail and insert the copied bytes.
6. Update length and mark the editor dirty.

Dirty means the current document may contain changes that have not been saved. It is a state flag, not a statement that the data is corrupt.

## Exercise and explanation
Would switching memcpy to memmove everywhere be sufficient? No. memmove protects one copy operation from overlap, but an earlier operation may already have changed the input. Saving the input before modifying the editor preserves the meaning of the whole edit.

## The useful test
Find the insertion whose source points inside editor.text. Verify the resulting text and then undo it. A test that inserts only unrelated string literals would miss this case.

## Connection to Framework
Studio document views and shared models can reference related data with different lifetimes. Framework's public document interfaces define those relationships. When extending them, state who owns each buffer and when callbacks may use it; do not infer lifetime from a pointer being non-null.

## Limits
This lab accepts printable ASCII plus tab and newline. Byte positions are therefore simple for the demonstrated input. Supporting general Unicode needs character-boundary and encoding decisions before adopting the same editing rules.

## Source map
Read `labs/native/text-editor/test_editor.c` in the Bits2Banking checkout. The lesson names the specific functions to study; you do not need to understand every file at once.

[Course contents](index.md) · [Previous: Bounds and preserving state on failure](01-bounds-and-failure-preservation.md) · [Next: Numbers, file writes and useful checks](03-numbers-files-and-checks.md)
