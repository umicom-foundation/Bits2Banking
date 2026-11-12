<!--
Umicom Bits2Banking
File: content/lessons/05-engineering/building-a-text-editor/12-capture-and-apply-document-edits.md

PURPOSE:
Teach capture an edit for the intended document.

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->

![Umicom](../../../assets/branding/umicom-logo.svg)

# Capture an edit for the intended document

<!-- The original local lab references are retained for source review. Published manuscripts use repository URLs because labs is outside the site content root.
[Course contents](index.md) · [Complete source](../../../../labs/native/shared-editor/document.c) · [Build and run](../../../../labs/native/shared-editor/README.md)
-->
[Course contents](index.md) · [Complete source](https://github.com/umicom-foundation/Bits2Banking/blob/main/labs/native/shared-editor/document.c) · [Build and run](https://github.com/umicom-foundation/Bits2Banking/blob/main/labs/native/shared-editor/README.md)

A clipboard request, a search result or a delayed command can finish after the user changes tabs. Looking up the active tab at that later moment can edit the wrong document. Framework separates preparing an edit from applying it and records the intended document identity in the prepared plan.

## 1. Construct the existing owners

The document scenario creates a command registry, a toolkit-neutral workbench, a document store and a document coordinator. The coordinator borrows the store and workbench; the workbench uses the registry. The cleanup order reverses those dependencies. None of these calls creates a native window in this lab.

A new untitled document receives both a document ID and a view ID. The numeric document ID identifies the managed working copy. The view ID identifies its presentation in the workbench. Keep their types and purposes separate. A title such as lesson.txt is only a suggested name; it does not mean the file has been saved.

## 2. Prepare through the authoritative coordinator

ReplaceAll in document.c is a thin convenience function. It selects the intended document, prepares a plan, applies one replacement and destroys the plan. It does not implement a buffer, a UTF-8 decoder or its own history stack. This keeps reusable editing policy in Framework.

~~~c
UmiDocumentEditPlan *plan = NULL;
UmiStatus status = UmiDocumentCoordinatorSelectAll(documents, id);
if (status == UMI_STATUS_OK)
    status = UmiDocumentCoordinatorPrepareEdit(documents, id, &plan);
if (status == UMI_STATUS_OK)
    status = UmiDocumentCoordinatorApplyEdit(documents, plan, text, strlen(text));
UmiDocumentEditPlanDestroy(plan);
~~~

The plan owns a complete captured draft and borrows its coordinator. Preparation captures saved and draft revisions, identity, path, caret and selection. The coordinator must stay alive until ApplyEdit returns. The plan can be destroyed afterwards, whether application succeeded or failed. Calls run on the coordinator owner thread; a prepared plan is not a cross-thread lock.

## 3. Read the captured selection safely

UmiDocumentEditPlanSelection returns a borrowed slice and an explicit byte count. The lab checks eight bytes spelling original with memcmp. It does not assume that the slice ends at a zero byte. The pointer remains tied to the plan lifetime and must not be freed or modified by the caller.

## 4. Change tabs before completion

The other-tab scenario prepares a replacement for the first document, creates a second document and fills it with second. It then applies the original plan using updated as the replacement. Success must change only the first document and leave the second document active. Undo and Redo are also directed to the first document by its captured ID.

~~~powershell
& .\build\shared-editor\shared-editor.exe other-tab
~~~

This exercise supplies replacement text directly; it does not read a system clipboard. It models the identity problem without depending on a native clipboard event loop. A future GTK adapter still needs separate qualification for focus, asynchronous callbacks and widget lifetime.

## Exercise and worked explanation

Explain why using umi_document_coordinator_active_snapshot immediately before applying the replacement would be wrong in this scenario. It would identify the second document, even though the request began for the first. Capturing an ID is necessary, but it is not sufficient: the prepared plan also rejects changes to that same document or selection while the request is pending.

## Failure and recovery

A stale plan returns INVALID_STATE; a closed target returns NOT_FOUND. A read-only target refuses changes. Do not silently prepare a fresh plan and apply the old user intent to an unrelated range. Keep the current document, explain that the request became stale and let the user initiate a new operation against the current text. The next lessons inspect history and refusal state directly.


[Previous lesson](11-select-source-words-and-lines.md) · [Next lesson](13-traverse-one-shared-document-history.md)
