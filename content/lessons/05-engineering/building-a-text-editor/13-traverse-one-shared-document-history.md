<!--
Umicom Bits2Banking
File: content/lessons/05-engineering/building-a-text-editor/13-traverse-one-shared-document-history.md

PURPOSE:
Teach traverse shared undo history and create a new edit branch.

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->

![Umicom](../../../assets/branding/umicom-logo.svg)

# Traverse shared undo history and create a new edit branch

<!-- The original local lab references are retained for source review. Published manuscripts use repository URLs because labs is outside the site content root.
[Course contents](index.md) · [Complete source](../../../../labs/native/shared-editor/document.c) · [Build and run](../../../../labs/native/shared-editor/README.md)
-->
[Course contents](index.md) · [Complete source](https://github.com/umicom-foundation/Bits2Banking/blob/main/labs/native/shared-editor/document.c) · [Build and run](https://github.com/umicom-foundation/Bits2Banking/blob/main/labs/native/shared-editor/README.md)

Undo is part of document ownership. If a widget, a command handler and a file model each maintain separate histories, they can disagree about the current text. The Framework document coordinator already retains bounded history for accepted edits, so the course client uses that service for every step.

## 1. Create three deliberate edits

The history scenario starts from an empty untitled document. ReplaceAll produces one, then two, then café. Each accepted change goes through the coordinator plan and commit path. The working-copy snapshot must report three available Undo steps and no Redo step. The final word contains five UTF-8 bytes even though it has four Unicode scalar values.

An edit that produces identical text is not a useful new text-history step. This scenario deliberately uses different contents at every stage. It also works with whole-document replacements to keep the history transitions easy to inspect. A normal typing adapter should group a user action according to the shared typing contract instead of recording every intermediate toolkit deletion and insertion as separate actions.

## 2. Observe the state after each traversal

~~~c
UmiStatus status = UmiDocumentCoordinatorUndo(documents, target.document_id);
/* On success, copy the current text through the view model and compare it. */
if (status == UMI_STATUS_OK)
    status = UmiDocumentCoordinatorRedo(documents, target.document_id);
~~~

The complete scenario checks the text after every call: Undo reaches two, then one, then empty; Redo returns through one and two to café. Checking only the final text would miss a broken intermediate step. HasText obtains an owned copy and releases it with UmiUiDocumentViewModelFreeText, keeping comparison lifetime independent of later edits.

## 3. Respect history limits

The current public coordinator contract allows up to 32 entries in each direction and a 16 MiB owned-text budget per stack, including terminators. Oldest entries can be evicted after a successful edit. These are bounded recovery steps, not permanent version control. Read snapshot counts instead of assuming that every change since startup is still available.

Undo does not save a file or make an untitled document acquire a path. A revision number also does not mean the same thing as a saved file timestamp. Disk saving, conflict checking and external change detection remain explicit coordinator workflows that need their own observations.

## 4. Create a new branch

redo-branch performs the same first three edits, undoes the last one, then replaces two with different. The old route back to café is no longer the Redo branch. The snapshot must report zero Redo steps. Attempting Redo should return NOT_FOUND and preserve the current text and history counts.

~~~powershell
& .\build\shared-editor\shared-editor.exe history
& .\build\shared-editor\shared-editor.exe redo-branch
~~~

## Exercise and worked explanation

Draw the sequence empty → one → two → café. Move back to two, then draw a different edge to different. Which text should Redo restore now? There is no pending Redo step, because the new edit created a new path from the current state. Keeping the abandoned future as an automatic Redo result would unexpectedly overwrite the newer choice.

## Investigate an unexpected result

Capture the first failing comparison, the scenario name, selected SDK and binary identity. A passing history scenario validates only the observed in-memory path. It does not establish that Studio native typing uses the same capture boundaries, that focus changes are correct or that recovery works after a process crash. Those are separate integration observations.


[Previous lesson](12-capture-and-apply-document-edits.md) · [Next lesson](14-test-refused-edits-and-sdk-identity.md)
