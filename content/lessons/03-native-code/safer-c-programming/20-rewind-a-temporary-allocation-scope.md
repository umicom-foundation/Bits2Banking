<!--
Umicom Bits2Banking
File: content/lessons/03-native-code/safer-c-programming/20-rewind-a-temporary-allocation-scope.md

PURPOSE:
Explain the lesson: Rewind a group of temporary allocations.

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->

# Rewind a group of temporary allocations

## Prepare
Read BtbArenaCheckpoint and BtbArenaRewind, then locate the checkpoint taken before the report strings are allocated.

A checkpoint is a saved used count. Rewinding sets the arena's current used count back to that position so the later region can be reused.

## Draw the lifetime
Draw a bar representing the array. Mark the checkpoint, heading and body. Rewind removes the heading and body from the set of active arena allocations.

The bytes may still contain their old values. Rewind does not erase them.

## Lab
Explain why main prints the report before rewinding, and only prints arena.used afterwards.

Expected: the string pointers are no longer used as active report allocations after the rewind. The reported used count returns to zero in this example.

## Exercise and explanation
Can a saved checkpoint from another arena be trusted merely because its number fits? No. This API stores only an offset, not an arena identity or generation. The caller must keep the checkpoint associated with the correct arena and allocation scope.

## Troubleshoot
A pointer that still displays old text after rewind is not proof that continued use is correct. A later allocation can overwrite it. Draw ownership and lifetime rather than relying on what memory happens to contain.

Use this design for bounded temporary work. Persistent documents, shared objects and independently released objects require a different lifetime arrangement.

## Source for this lesson

[Open the example source](https://github.com/umicom-foundation/Bits2Banking/blob/main/labs/native/arena-allocator/arena.c). Keep the source revision with your exercise notes so later changes can be compared.

[Course contents](index.md) · [Previous lesson](19-use-a-real-void-pointer-output.md) · [Next lesson](21-review-the-arena-contract.md)

