<!--
Umicom Bits2Banking
File: content/lessons/03-native-code/safer-c-programming/18-preserve-output-on-allocation-failure.md

PURPOSE:
Explain the lesson: Preserve results when allocation fails.

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->

# Preserve results when allocation fails

## Prepare
Read the sentinel checks in test_arena.c. A sentinel here is an ordinary known value placed in an output variable before an operation.

The test asks for more storage than the arena contains, then checks that both the output pointer and used count retain their previous values.

## Why this matters
A caller can recover from a refusal only if the API clearly defines what remains valid. BtbArenaAllocate publishes its output and advances used after all checks succeed.

A failing request therefore does not consume a partial allocation.

## Lab
Write a trace with a successful seven-byte allocation followed by a 1,024-byte request in the 128-byte test arena. Record used before the second call and after it.

Expected: the second result is BTB_ARENA_NO_SPACE and used is unchanged. The output variable still contains its sentinel.

## Exercise and explanation
May the caller use that output as the newly allocated block after refusal? No. Unchanged means no new result was published. Always branch on the returned status.

## Troubleshoot
If a failure changes used, inspect where state is assigned relative to validation. If only the output changes, look for an early output assignment.

Preserving a result on refusal is a useful API contract for Framework services too. It makes error handling predictable, but the caller must still check the status rather than interpreting an old pointer as success.

## Source for this lesson

[Open the example source](https://github.com/umicom-foundation/Bits2Banking/blob/main/labs/native/arena-allocator/arena.c). Keep the source revision with your exercise notes so later changes can be compared.

[Course contents](index.md) · [Previous lesson](17-subtract-only-after-checking.md) · [Next lesson](19-use-a-real-void-pointer-output.md)

