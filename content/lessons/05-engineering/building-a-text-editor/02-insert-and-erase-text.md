<!--
Umicom Bits2Banking
File: content/lessons/05-engineering/building-a-text-editor/02-insert-and-erase-text.md

PURPOSE:
Explain one concept through a practical example and an observable result.

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->
# Insert and erase text without losing the tail

[Course contents](index.md) · [Previous: Plan a small editor with a testable model](01-plan-a-small-editor.md) · [Next: Undo and save to a chosen path](03-undo-and-save-to-a-chosen-path.md)

## Think in positions
The three-byte text acd has positions 0, 1 and 2. Inserting b at position 1 gives abcd. The tail cd must move one place to the right. Positions identify insertion boundaries as well: position 3 is the end of acd.

## Prepare
Use [the course build commands](index.md) and open editor.c. Read BtbEditorInsert before running the following session:
~~~text
append acd
insert 1 b
show
erase 2 1
show
discard
~~~
Expect TEXT: abcd followed later by TEXT: abd. The erase command takes a starting position and a count, not an ending position.

## Trace insertion
~~~text
before:  a c d zero
move:    a _ c d zero
insert:  a b c d zero
~~~
The implementation checks the requested position, available capacity and input bytes. It copies the input to temporary storage, captures undo state, then uses memmove for the overlapping tail shift. The move includes the zero terminator.

A C string requires that terminator. It is not part of the visible length and must remain within the array.

## Trace erasing
Removing one byte at position 2 from abcd shifts the tail d and the terminator left. The new length is three. Removing zero bytes makes no change and creates no new undo entry.

The check uses count <= length - position after proving position <= length. This avoids forming an unchecked position + count expression.

## Run a rejected edit
Enter erase 99 1 in a document containing abd. Expect an error. Then show must still print abd. The command parser accepts 99 as a number; the model rejects it as an invalid document position. These are different checks.

## Exercise and worked answer
Starting from abcdef, what does erase 1 3 produce? It removes b, c and d, leaving aef. Try it in a new session. Undo should restore abcdef.

## Read the tests
test_editor.c checks insertion at the middle, erasure, exact capacity, oversized requests and input that aliases the editor's own text. These cases are chosen because different mistakes can hide behind the same ordinary append example.

## From this lab to a real editor
A graphical editor additionally tracks selection, cursor movement, line endings and character boundaries. A byte index cannot automatically represent a visible character in general Unicode text. Learn those requirements before extending the model; Framework's document APIs are the production integration point.

## Recovery
If a test changes text but reports failure, preserve both the before and after values. Correcting the status alone does not repair a damaged buffer. Return to the smallest insertion or erasure that demonstrates the problem.

## Source map
Read `labs/native/text-editor/editor.c` in the Bits2Banking checkout. The lesson names the specific functions to study; you do not need to understand every file at once.

[Course contents](index.md) · [Previous: Plan a small editor with a testable model](01-plan-a-small-editor.md) · [Next: Undo and save to a chosen path](03-undo-and-save-to-a-chosen-path.md)
