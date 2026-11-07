<!--
Umicom Bits2Banking
File: content/lessons/02-programming/learning-python/10-preserve-unknown-record-fields.md

PURPOSE:
Explain the lesson: Preserve unknown record fields.

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->

# Preserve unknown record fields

## Prepare

Open the existing notes.py laboratory in a text editor. Use a disposable folder when trying it: notes.json is relative to the current terminal directory. The course's first two lessons explain installing Python and opening a terminal. This exercise reads existing Python code; Umicom's shared native engine remains C.

## Understand the idea

Validation checks the id and text fields that the application consumes, then returns the original records. Extra fields are retained. This avoids silently discarding information written by another version, but it does not validate the meaning of those extra fields.

## Work through the example

Add a colour field to a disposable note. Trace load, append and save. Mark where a reconstruction using only id and text would lose colour.

## Check your reasoning

The existing flow retains colour when serializing the full list. Rejecting malformed known fields and preserving unknown fields are separate design choices.

## If something differs

If an extra field disappears, inspect transformations after validation. Never infer that preserved data is trusted simply because it survived serialization.


## Source for this lesson

[Open the example source](https://github.com/umicom-foundation/Bits2Banking/blob/main/content/labs/python-notes/notes.py). Keep the source revision with your exercise notes so later changes can be compared.

[Course contents](index.md) · [Previous lesson](09-allocate-note-identifiers-from-existing-data.md) · [Next lesson](11-separate-validation-from-durable-saving.md)

