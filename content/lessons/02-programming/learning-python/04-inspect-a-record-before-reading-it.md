<!--
Umicom Bits2Banking
File: content/lessons/02-programming/learning-python/04-inspect-a-record-before-reading-it.md

PURPOSE:
Explain the lesson: Inspect a record before reading it.

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->

# Inspect a record before reading it

## Prepare

Open the existing notes.py laboratory in a text editor. Use a disposable folder when trying it: notes.json is relative to the current terminal directory. The course's first two lessons explain installing Python and opening a terminal. This exercise reads existing Python code; Umicom's shared native engine remains C.

## Understand the idea

A dictionary stores named values. note.get("id") returns None when the key is absent; it does not invent a valid identifier. Validation checks the container before reading its fields. This makes an unexpected number or string produce a deliberate error.

## Work through the example

Write three inputs on paper: {"id":1,"text":"Read"}, {"text":"Read"}, and 17. Follow validate_notes from the outer list check to the per-record checks. Put each record inside a list first.

## Check your reasoning

The complete record passes. The missing identifier fails the integer rule. The number fails the dictionary rule before .get is called. Validation order determines which operation is safe next.

## If something differs

If your result differs, distinguish the outer list from the dictionary inside it. A valid dictionary alone is not the file format.


## Source for this lesson

[Open the example source](https://github.com/umicom-foundation/Bits2Banking/blob/main/content/labs/python-notes/notes.py). Keep the source revision with your exercise notes so later changes can be compared.

[Course contents](index.md) · [Next lesson](05-distinguish-booleans-and-identifiers.md)


[Previous: Validate records before saving](03-validate-records-before-saving.md)
