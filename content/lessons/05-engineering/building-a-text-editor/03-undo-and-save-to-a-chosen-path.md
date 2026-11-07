<!--
Umicom Bits2Banking
File: content/lessons/05-engineering/building-a-text-editor/03-undo-and-save-to-a-chosen-path.md

PURPOSE:
Explain one concept through a practical example and an observable result.

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->
# Undo and save to a chosen path

[Course contents](index.md) · [Previous: Insert and erase text without losing the tail](02-insert-and-erase-text.md) · [Next: Test the model and the whole editing session](04-test-the-whole-editing-session.md)

## Preserve a useful previous state
Undo lets a user recover from an edit. This lab stores one complete previous text state before each successful non-empty edit. A rejected command does not replace that state.

## Prepare a session
Build with [the course instructions](index.md). Start the editor in a writable practice folder. Choose a filename that does not already exist.
~~~text
append ac
insert 1 b
erase 1 1
show
undo
show
save my note.txt
quit
~~~
The first show prints ac. The second prints abc. Saving reports OK and creates my note.txt in the current folder. The contents are exactly abc, without an automatically appended newline.

## How one-level undo works
1. Before erasing, copy the current text and length into previous.
2. Apply the erase and set dirty.
3. On undo, check that a previous state exists.
4. Copy the previous state back.
5. Consume that undo entry.

A second undo without a new edit is refused. This is deliberately one level; it is not an undo history. The [stack lessons](../../02-programming/learning-data-structures/index.md) explain a structure that can support a later multi-step design.

## Save where the user chooses
The command accepts the full remainder after save as the path, including spaces. Do not add shell quotation marks inside the running editor: this parser would treat them as part of the filename. An absolute Windows example is:
~~~text
save C:\umicom\practice\my note.txt
~~~
Create the parent practice folder beforehand. The program does not select an AppData directory or create missing parent folders.

The save function refuses existing destinations. If you need to keep another revision, choose a new filename. This first project teaches safe new-file creation before overwrite and conflict resolution.

## Dirty state
Dirty means there may be unsaved edits. After undo, the model conservatively remains dirty even when the visible text happens to match an earlier saved version. Tracking exact saved content is a later feature.

quit asks you to save or discard when dirty. discard explicitly ends without saving. End-of-input also ends the process and reports unsaved changes; it cannot preserve the document by itself.

## Exercise and answer
Try saving to my note.txt again after changing the text. Expect an error and confirm that the existing file still contains abc. The current session remains dirty so you can save elsewhere.

## Production connection
Framework owns document storage, conflict handling and richer history for applications. Read those interfaces rather than expanding this teaching lab into a separate production persistence service.

## If a save fails
Check the path, parent directory and permissions. A failed write may leave a partial new file; inspect it before retrying. This example does not claim atomic saving or power-loss durability.

## Read the Framework contract
Open [document/edit.h](https://github.com/umicom-foundation/umicom-framework/blob/main/include/umicom/document/edit.h). Find UmiDocumentCoordinatorUndo. Its documentId identifies the document the command belongs to, even if the user selects another tab before the command completes. A coordinator owns the related document operations; the application does not create another undo history.

Next read UmiDocumentCoordinatorSaveAs in [document/coordinator.h](https://github.com/umicom-foundation/umicom-framework/blob/main/include/umicom/document/coordinator.h). Its arguments include the same document identity and a destination path. The comment says the operation belongs on the coordinator's owning thread. A thread is an independently scheduled sequence of work. Passing a document ID is not permission to call an owner-thread API from any thread.

Write down two differences from the lab: the production service handles multiple named documents and coordinates with existing conflict-aware storage. Use the production API when adding a Studio command; keep the small lab for learning.

## Source map
Read `labs/native/text-editor/editor.c` in the Bits2Banking checkout. The lesson names the specific functions to study; you do not need to understand every file at once.

[Course contents](index.md) · [Previous: Insert and erase text without losing the tail](02-insert-and-erase-text.md) · [Next: Test the model and the whole editing session](04-test-the-whole-editing-session.md)
