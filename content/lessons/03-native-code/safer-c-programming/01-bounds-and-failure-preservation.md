<!--
Umicom Bits2Banking
File: content/lessons/03-native-code/safer-c-programming/01-bounds-and-failure-preservation.md

PURPOSE:
Explain one concept through a practical example and an observable result.

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->
# Bounds and preserving state on failure

[Course contents](index.md) · [Next: Overlapping memory and ownership](02-overlap-and-ownership.md)

## What safer means here
C gives direct access to memory. A pointer and a length do not automatically prove that the pointed-to storage is valid. Safer programming adds explicit contracts, bounds checks and useful tests. These techniques reduce particular risks; they do not make arbitrary C code memory-safe.

This lesson uses the small text editor model. You will learn how it rejects an edit without damaging text already stored.

## Setup and vocabulary
Use [the setup and lab commands](index.md). If arrays or functions are unfamiliar, start with [Introduction to Programming](../../02-programming/introduction-to-programming/index.md). Open labs/native/text-editor/editor.h and editor.c.

Capacity is the maximum supported content size: 1024 bytes here. Length is the number of content bytes currently used. An extra byte holds the terminating zero required by C strings.
~~~text
text storage: [content bytes ...][zero terminator][unused space ...]
length:        number of content bytes
capacity:      1024 content bytes, plus one reserved terminator byte
~~~

## Check before changing
An insertion needs a position at or before the current end. Its new text must fit. The model checks the equivalent of:
~~~c
if (position > editor->length) return BTB_EDIT_INVALID;
if (length > BTB_EDITOR_CAPACITY - editor->length)
    return BTB_EDIT_FULL;
~~~
The model first verifies that the existing length is within capacity. Only then is the subtraction valid. Checking length > capacity - used avoids adding two potentially large unsigned values before knowing whether the sum fits.

After validation the function makes its undo snapshot and changes the buffer. A rejected operation leaves the previous text, length and undo state intact.

## Follow a boundary case
1. Imagine current length 1023.
2. Inserting one byte fits exactly.
3. Inserting two bytes fails.
4. The failing insertion must not leave a half-written character or replace the undo snapshot.
5. Find the full-buffer and failure-preservation checks in test_editor.c.

An empty insertion succeeds without creating an undo step. This makes a no-change operation behave consistently.

## Understand the remaining responsibility
The caller must supply readable memory for the entire input span. Checking a null pointer cannot establish that every non-null pointer is valid. The model is single-threaded; callers must not modify it concurrently.

## Exercise with answer
A buffer holds 1000 bytes and receives an insertion of 25 bytes. Does it fit? No: 1024 - 1000 is 24. Reject before copying anything. An insertion of 24 fits and still leaves room for the separate zero terminator.

## Read production source
Compare the teaching model with the Framework document APIs under Umicom-Applications/framework/include/umicom/document. Identify which API owns the document and how it reports errors. The lab explains a mechanism; it is not a replacement document engine for Studio.

## Investigate a failure
If the boundary test fails, inspect both the returned status and the old text. A correct error code with damaged content is still a defect. Record the smallest input that reproduces it and add that case before changing the implementation.

## Source map
Read `labs/native/text-editor/editor.c` in the Bits2Banking checkout. The lesson names the specific functions to study; you do not need to understand every file at once.

[Course contents](index.md) · [Next: Overlapping memory and ownership](02-overlap-and-ownership.md)
