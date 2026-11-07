<!--
Umicom Bits2Banking
File: content/lessons/05-engineering/building-a-text-editor/05-open-an-existing-document.md

PURPOSE:
Explain the lesson: Open an existing document without losing work.

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->

# Open an existing document without losing work

Opening a file replaces the text displayed by an editor. That replacement must have a clear rule when the current text contains unsaved changes.

## Setup recap

The example is in labs/native/text-editor. Its OPENING.md gives complete CMake, Ninja and terminal commands. You need a C23 compiler. This lesson can also be followed by reading editor.c and tracing the model on paper.

A document is represented by a BtbEditor value. The dirty field records whether the model contains changes that have not been saved through its current save operation.

## 1. Follow the guard

BtbEditorLoadFile checks the editor, the path and the dirty field before opening a stream. If dirty is nonzero, it returns BTB_EDIT_DIRTY. It does not silently discard the current document.

The command-line front end reports that refusal. It asks the learner to save to a new path before opening another file. The model does not invent a storage directory.

## 2. Try a short session

After building the example, enter these commands at its own command prompt:

```text
append First document
open existing.txt
show
```

The open request is expected to be refused because the appended text is unsaved. The show command should still display First document. A failed command makes the session's final exit status nonzero even if later commands succeed.

Choose a new filename that does not already exist and use save followed by that path. The example deliberately refuses overwriting an existing destination.

## 3. Load only after a successful save

After saving, open a small plain ASCII file using its full path. Spaces inside the path are accepted directly by this example prompt; shell quotation marks are not interpreted there.

A successful load begins a new undo history. Undo does not restore the document that was open before loading.

## Exercise and recovery

Write down the expected dirty flag after append, successful save, failed open and successful open. Explain why failed open must preserve both the visible text and its undo state.

If a path cannot be opened, check that it names a readable file. If content is refused, inspect its encoding and size. This bounded teaching editor supports printable ASCII, tabs and line endings; it is not a Unicode editor.

## Source for this lesson

[Open the example source](https://github.com/umicom-foundation/Bits2Banking/blob/main/labs/native/text-editor/editor.c). Keep the source revision with your exercise notes so later changes can be compared.

[Course contents](index.md) · [Next lesson](06-load-into-a-private-candidate.md)


[Previous lesson: Test the model and the whole editing session](04-test-the-whole-editing-session.md)
