<!--
Umicom Bits2Banking
File: content/lessons/05-engineering/building-a-text-editor/08-check-failure-state-and-command-results.md

PURPOSE:
Explain the lesson: Check failure state and command results.

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->

# Check failure state and command results

A regression check should observe the behavior that matters to a user. For file loading, receiving an error code is only half the requirement: the current document must survive.

## Setup recap

Open test_load.c and CMakeLists.txt in labs/native/text-editor. OPENING.md supplies the build and CTest commands. The load test receives a build-owned fixture directory as an argument; it does not choose a personal documents folder.

## 1. Capture the complete relevant state

The test copies BtbEditor before a failing operation. SameState compares text, previous text, lengths, the undo flag and the dirty flag.

It compares the members explicitly rather than comparing the entire structure as raw bytes. C structures can contain padding bytes whose values are not part of the logical editor state.

## 2. Cover distinct boundaries

The fixtures include invalid control bytes, embedded zero, non-ASCII bytes, excess capacity, exact capacity and an empty file. Each case targets a different rule.

The unsaved-document case uses a valid file. That matters: otherwise a refusal could come from a nonexistent path instead of the dirty-state guard.

A failed load must preserve the previous undo state as well as the visible text. A successful load must clear intermediate validation snapshots.

## 3. Interpret the executable's status

The command-line example remembers whether any command was refused. A later successful command does not erase that fact. Automated callers can inspect the final exit status and output together.

An intentional failure exercise can therefore produce the expected refusal and still end with a nonzero status. This differs from a regression test executable, which returns success when every assertion—including expected refusals—holds.

## Exercise and recovery

Change one fixture in a separate practice copy to printable text. Predict which assertion should now fail and explain why. Do not weaken the loader just to make that assertion pass.

If a test cannot create its fixture, inspect the supplied build directory and permissions. If it reports a line number, read the condition at that line and compare the expected state with the operation immediately before it.

Authored assertions are a specification until executed. Keep the tested revision and command with any recorded result.

## Source for this lesson

[Open the example source](https://github.com/umicom-foundation/Bits2Banking/blob/main/labs/native/text-editor/test_load.c). Keep the source revision with your exercise notes so later changes can be compared.

[Course contents](index.md) · [Previous lesson](07-recognise-line-endings-and-eof.md)

