<!--
Umicom Bits2Banking
File: content/lessons/05-engineering/building-a-text-editor/06-load-into-a-private-candidate.md

PURPOSE:
Explain the lesson: Load into a private candidate before replacing state.

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->

# Load into a private candidate before replacing state

A file can fail halfway through reading. If each arriving byte were placed directly into the current document, that failure could leave half of one document mixed with another.

## Setup recap

Open BtbEditorLoadFile in labs/native/text-editor/editor.c and BtbEditor in editor.h. No additional library is required for this source-reading exercise. OPENING.md contains commands for building the executable when a C23 toolchain is available.

## 1. Identify the two models

The caller passes the existing editor. The loading function creates a separate zero-initialised BtbEditor named candidate. This value is temporary storage owned by the function.

Each accepted character is inserted into candidate. The existing editor is untouched while reading continues.

```text
current document ─────────────── stays visible
file → validation → candidate
                         │
                    all steps succeed
                         ↓
                  replace current document
```

## 2. Include closing in the operation

A successful loop is not the only condition for success. The function checks ferror and the return value of fclose. It returns the failure status before assigning candidate if either indicates an error.

The stream is closed even when a byte is refused or the capacity is exceeded. Returning early from inside the loop would need equivalent cleanup.

## 3. Publish one complete result

Before assignment, the function clears the candidate's intermediate undo snapshots and marks it clean. Those snapshots came from validating incoming bytes; they are not editing commands the user issued.

The final assignment copies the model's arrays and scalar fields. This works because this particular structure owns fixed arrays and contains no heap pointers. Copying a structure with owning pointers would require a different ownership design.

## Exercise and explanation

Trace a file containing three valid characters followed by a zero byte. At the failure, candidate contains a valid prefix, but the caller's editor retains its original content.

Now trace a valid empty file. It replaces a clean document with an empty clean document. Empty content is a successful result, not evidence that a read failed.

This example uses a small fixed capacity. Repeated insertion also copies undo data, so it is a teaching implementation, not a recommendation for loading large production documents byte by byte.

## Source for this lesson

[Open the example source](https://github.com/umicom-foundation/Bits2Banking/blob/main/labs/native/text-editor/editor.c). Keep the source revision with your exercise notes so later changes can be compared.

[Course contents](index.md) · [Previous lesson](05-open-an-existing-document.md) · [Next lesson](07-recognise-line-endings-and-eof.md)

