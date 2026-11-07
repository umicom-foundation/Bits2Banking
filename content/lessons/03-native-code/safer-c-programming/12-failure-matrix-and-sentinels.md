<!--
Umicom Bits2Banking
File: content/lessons/03-native-code/safer-c-programming/12-failure-matrix-and-sentinels.md

PURPOSE:
Explain the lesson: Design checks that prove rejected calls preserve state.

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->

# Design checks that prove rejected calls preserve state

## Prepare
Use the fault-injection test as a source-reading exercise. A useful failure test establishes a valid state, introduces one failure condition, calls the function and compares the result with the original state.

A sentinel is a distinctive value chosen so an unintended write is easy to notice. In this lab the old title/body and revision act as visible sentinels.

## Build the matrix
Write columns for condition, expected status, allocations attempted, stored title, stored body and revision.
- stale revision: conflict, no new allocation;
- first allocation refused: no-memory, original state;
- second allocation refused: no-memory, temporary title released;
- embedded zero byte: invalid, no new allocation;
- oversized span: limit, no new allocation;
- valid replacement: OK, both fields changed and revision increased.

This matrix checks effects as well as return codes. A function can return the right error after already damaging data.

## Understand the assertion macro
The test's `CHECK` prints the source line and failed expression, then returns failure from main. Unlike a standard `assert` that may be disabled by a build definition, these checks remain active in the lab's ordinary release configuration.

A diagnostic should identify what failed without printing private customer content. These fixtures contain only public teaching strings.

## Exercise
Add a row on paper for an empty title and a row for an empty body. Consult Validate instead of guessing. Then locate the exact place each would be rejected or accepted.

Expected result: empty title is invalid; an empty body with a valid pointer is allowed. Neither expectation says anything about a null pointer, which has its own check.

## Recovery and evidence
When a check fails, keep the first failing expression, source revision and command. Rebuild after the repair and rerun the relevant lab. Do not label later checks as passed if the program returned before reaching them. A source review can show intended coverage; only an executed result establishes what happened in that environment.

## Source for this lesson

[Open the example source](https://github.com/umicom-foundation/Bits2Banking/blob/main/labs/native/fault-injection/test_note.c). Keep the source revision with your exercise notes so later changes can be compared.

[Course contents](index.md) · [Previous lesson](11-destruction-and-idempotence.md) · [Next lesson](13-review-before-sharing-a-model.md)

