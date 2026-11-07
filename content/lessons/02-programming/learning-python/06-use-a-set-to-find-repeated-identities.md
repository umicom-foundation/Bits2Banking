<!--
Umicom Bits2Banking
File: content/lessons/02-programming/learning-python/06-use-a-set-to-find-repeated-identities.md

PURPOSE:
Explain the lesson: Use a set to find repeated identities.

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->

# Use a set to find repeated identities

## Prepare

Open the existing notes.py laboratory in a text editor. Use a disposable folder when trying it: notes.json is relative to the current terminal directory. The course's first two lessons explain installing Python and opening a terminal. This exercise reads existing Python code; Umicom's shared native engine remains C.

## Understand the idea

A set records membership without a repeated entry. The identifiers set begins empty for each validation call. A duplicate is rejected before its identifier is added again. This detects a conflict even when the two notes have different text.

## Work through the example

Trace ids 3, 8, 3. Draw the set after each successful record. Then trace 3, 8, 12. Explain why sorting the records is unnecessary for this check.

## Check your reasoning

The first input fails at the third record; the set already contains 3. The second succeeds with three members. Record order is preserved because validation does not sort the original list.

## If something differs

If duplicate detection appears inconsistent, confirm you kept one set for the entire call rather than creating a fresh set inside the loop.


## Source for this lesson

[Open the example source](https://github.com/umicom-foundation/Bits2Banking/blob/main/content/labs/python-notes/notes.py). Keep the source revision with your exercise notes so later changes can be compared.

[Course contents](index.md) · [Previous lesson](05-distinguish-booleans-and-identifiers.md) · [Next lesson](07-measure-text-and-encoded-bytes.md)

