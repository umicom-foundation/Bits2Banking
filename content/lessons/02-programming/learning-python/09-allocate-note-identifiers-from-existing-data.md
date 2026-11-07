<!--
Umicom Bits2Banking
File: content/lessons/02-programming/learning-python/09-allocate-note-identifiers-from-existing-data.md

PURPOSE:
Explain the lesson: Allocate note identifiers from existing data.

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->

# Allocate note identifiers from existing data

## Prepare

Open the existing notes.py laboratory in a text editor. Use a disposable folder when trying it: notes.json is relative to the current terminal directory. The course's first two lessons explain installing Python and opening a terminal. This exercise reads existing Python code; Umicom's shared native engine remains C.

## Understand the idea

The next identifier is one greater than the largest existing id, with zero used for an empty collection. It is not the list length plus one. Gaps can remain after earlier records were removed elsewhere.

## Work through the example

For ids 1 and 9, calculate the next id. Repeat for an empty list. Finally use MAX_NOTE_ID as an existing id and follow the overflow-bound refusal.

## Check your reasoning

The results are 10 and 1. At the maximum, adding another note is refused. Python integers can grow, but the file contract intentionally limits identifiers.

## If something differs

If a reused id appears, check for len(notes)+1 or concurrent writers. This single-writer laboratory does not coordinate two processes allocating ids simultaneously.


## Source for this lesson

[Open the example source](https://github.com/umicom-foundation/Bits2Banking/blob/main/content/labs/python-notes/notes.py). Keep the source revision with your exercise notes so later changes can be compared.

[Course contents](index.md) · [Previous lesson](08-bound-reading-before-parsing.md) · [Next lesson](10-preserve-unknown-record-fields.md)

