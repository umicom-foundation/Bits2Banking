<!--
Umicom Bits2Banking
File: content/lessons/05-engineering/building-a-text-editor/09-own-a-shared-text-buffer.md

PURPOSE:
Teach own a shared text buffer and respect borrowed views.

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->

![Umicom](../../../assets/branding/umicom-logo.svg)

# Own a shared text buffer and respect borrowed views

<!-- The original local lab references are retained for source review. Published manuscripts use repository URLs because labs is outside the site content root.
[Course contents](index.md) · [Complete source](../../../../labs/native/shared-editor/buffer.c) · [Build and run](../../../../labs/native/shared-editor/README.md)
-->
[Course contents](index.md) · [Complete source](https://github.com/umicom-foundation/Bits2Banking/blob/main/labs/native/shared-editor/buffer.c) · [Build and run](https://github.com/umicom-foundation/Bits2Banking/blob/main/labs/native/shared-editor/README.md)

The first eight lessons built a deliberately small ASCII editor. Its fixed array made insertion and file loading visible. An application that grows beyond that exercise should use the existing Framework text services. This chapter changes the ownership model, while keeping the introductory implementation available for study.

## What you will build

The shared-editor lab is a C23 console program. It has no window and opens no document file. In this scenario it copies caller-owned bytes into a Framework buffer, marks the current revision as saved, inserts one byte and checks an independent copy. Complete code is in buffer.c, with its command dispatcher in main.c.

## 1. Prepare the installed SDK

Follow the lab README to configure a separate build directory against an identified installed Framework SDK. Both editor and document targets must be exported by that installation. The source checkout, installed headers, libraries and runtime dependencies must describe the same build. Do not fix a missing installed header by silently adding another checkout to the include search path.

## 2. Give each allocation one owner

A successful umi_editor_text_buffer_create call returns an opaque pointer. Opaque means the client knows the type name but cannot depend on its private members. The client must eventually call umi_editor_text_buffer_destroy. Initialising the pointer to NULL allows every failure path to share the cleanup label.

~~~c
UmiEditorTextBuffer *buffer = NULL;
UmiStatus status = umi_editor_text_buffer_create(32U, &buffer);
if (status == UMI_STATUS_OK)
    status = umi_editor_text_buffer_set(buffer, "draft", 5U);
umi_editor_text_buffer_destroy(buffer);
~~~

The value 32 is initial storage capacity, not a promise that this is the largest permitted document. A byte count excludes the C string terminator. The setter copies the supplied bytes. Changing the original array afterwards must not change the buffer. The ownership scenario deliberately changes caller[0] to X after the call and still expects draft from the buffer.

## 3. Distinguish a view from a copy

umi_editor_text_buffer_view returns a borrowed pointer and metadata. The pointer belongs to the buffer and must not be freed. A successful mutation can relocate or replace its storage, so obtain a fresh view before reading again. The copy operation writes into storage supplied by the caller. A five-byte word needs six bytes of destination capacity because this copy API also writes a terminator.

The lab keeps a copy containing draft, inserts an exclamation mark into the buffer and checks that the copy still contains draft. This is a lifetime test, not just a string comparison. A stale view might appear to work when no allocation moves; that apparent success does not extend its documented lifetime.

## 4. Interpret the saved mark

mark_saved records the current revision as the save point. It performs no filesystem write. After insertion, is_dirty becomes true because the model differs from that recorded point. A real editor must mark its content saved only after its own saving workflow succeeds. Do not use a model flag as evidence that a file exists on disk.

## Run and inspect

After building the lab, run the ownership scenario. Success requires all comparisons to complete and a zero exit code; the printed message alone is insufficient if the process later fails.

~~~powershell
& .\build\shared-editor\shared-editor.exe ownership
~~~

## Exercise and worked explanation

Change the input word to a different five-byte ASCII word in a practice copy. Update the expected contents and run again. Then explain why keeping a pointer to view.bytes across insert is unsafe even if it still prints the right text. The buffer owns that allocation, and a successful mutation ends the previous view contract. A copied array has a separate lifetime.

## Limits

This buffer stores bytes. The next chapter uses a separate service to interpret Unicode positions. Neither this scenario nor a successful installed-SDK build qualifies GTK drawing, clipboard handling, disk saving or Studio keyboard input.


[Previous lesson](08-check-failure-state-and-command-results.md) · [Next lesson](10-resolve-unicode-positions.md)
