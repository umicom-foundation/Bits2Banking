<!--
Umicom Bits2Banking
File: content/lessons/02-programming/learning-python/05-distinguish-booleans-and-identifiers.md

PURPOSE:
Explain the lesson: Distinguish booleans and identifiers.

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->

# Distinguish booleans and identifiers

## Prepare

Open the existing notes.py laboratory in a text editor. Use a disposable folder when trying it: notes.json is relative to the current terminal directory. The course's first two lessons explain installing Python and opening a terminal. This exercise reads existing Python code; Umicom's shared native engine remains C.

## Understand the idea

Python's bool type is a subclass of int. A general isinstance check accepts True as an integer, although a note identifier is meant to be an explicit positive number. The source therefore uses type(identifier) is int.

## Work through the example

Compare ids 1, True, "1", 0 and -1. For each, record its type and whether it satisfies both the exact-type and positive-range checks. Do not convert inputs before tracing.

## Check your reasoning

Only integer 1 passes. Text containing a digit remains text; True remains a boolean. Accepting either by accident would make the data format ambiguous.

## If something differs

If a hand-written test passes True, inspect whether it copied the exact rule or substituted isinstance. Tests should exercise the implementation rather than an altered copy.


## Source for this lesson

[Open the example source](https://github.com/umicom-foundation/Bits2Banking/blob/main/content/labs/python-notes/notes.py). Keep the source revision with your exercise notes so later changes can be compared.

[Course contents](index.md) · [Previous lesson](04-inspect-a-record-before-reading-it.md) · [Next lesson](06-use-a-set-to-find-repeated-identities.md)

