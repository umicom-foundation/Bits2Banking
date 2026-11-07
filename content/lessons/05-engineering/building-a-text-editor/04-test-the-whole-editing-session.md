<!--
Umicom Bits2Banking
File: content/lessons/05-engineering/building-a-text-editor/04-test-the-whole-editing-session.md

PURPOSE:
Explain one concept through a practical example and an observable result.

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->
# Test the model and the whole editing session

[Course contents](index.md) · [Previous: Undo and save to a chosen path](03-undo-and-save-to-a-chosen-path.md)

## Two kinds of evidence
A model test calls editing functions directly. A session test starts the actual editor program and sends commands through its input. Both are useful: a correct model can still be unreachable through a broken command parser.

## Setup recap
Use [the course setup](index.md) to build with BUILD_TESTING=ON. Read test_editor.c and check_session.cmake before running ctest. The expected results below describe the checks; they are not evidence that your local build has passed.

## Model checks
The C tests exercise:
1. Inserting at the middle and at full capacity.
2. Copying text from within the editor's own buffer.
3. Erasing and undoing.
4. Rejecting invalid positions without changing text or history.
5. Handling empty operations and missing undo state.

The CHECK helper reports a failed condition and returns a failure result. It remains active in builds where the standard assert macro might be disabled.

## Session checks
The CMake check creates a unique directory under the build tree. It sends this meaningful sequence to the executable:
~~~text
append ac
insert 1 b
erase 1 1
undo
show
save [a new path chosen by the check]
quit
~~~
It checks the process exit, the displayed abc and the file's exact contents. A second session attempts to overwrite that file and must fail while leaving abc intact. Another session uses a negative position and must preserve its text.

The check uses separate temporary input and output files. It retains these files for investigation instead of erasing evidence after a failure.

## Read a failure systematically
1. Find the failed test name.
2. Read its command output.
3. Determine whether configuration, compilation, launching, a model check or file comparison failed.
4. Reproduce the smallest relevant input.
5. Fix the implementation and rerun the affected check.

A timeout says the process did not complete within the limit. It is not equivalent to a successful test with no output.

## Exercise
Add a practice check for an empty undo. Predict BTB_EDIT_NO_UNDO and an unchanged empty document. Then add a second check showing that an invalid edit does not consume a previously valid undo state.

Worked reasoning: history belongs to successful edits. If a rejected edit consumed history, an error would unexpectedly prevent recovery from earlier work.

## Plan the next project stage
Opening an existing file, Unicode selection and multiple undo levels need new contracts and tests. A graphical frontend also needs interaction checks for focus, keyboard input and window lifetime. None of those behaviours is established by these console tests.

## Connect to Umicom Studio
Use the same evidence distinction when reviewing Studio: source compilation, document model tests and native menu/editor interaction are different checks. Shared production behaviour belongs in Framework; application tests must also show that the interface reaches it.

## Source map
Read `labs/native/text-editor/check_session.cmake` in the Bits2Banking checkout. The lesson names the specific functions to study; you do not need to understand every file at once.

[Course contents](index.md) · [Previous: Undo and save to a chosen path](03-undo-and-save-to-a-chosen-path.md)

[Next lesson: Open an existing document without losing work](05-open-an-existing-document.md)
