<!--
Umicom Bits2Banking
File: content/lessons/02-programming/learning-python/08-bound-reading-before-parsing.md

PURPOSE:
Explain the lesson: Bound reading before parsing.

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->

# Bound reading before parsing

## Prepare

Open the existing notes.py laboratory in a text editor. Use a disposable folder when trying it: notes.json is relative to the current terminal directory. The course's first two lessons explain installing Python and opening a terminal. This exercise reads existing Python code; Umicom's shared native engine remains C.

## Understand the idea

The loader reads at most MAX_FILE_BYTES plus one. The extra byte distinguishes an exactly allowed file from an oversized one. It then refuses oversize input before decoding and parsing JSON.

## Work through the example

Use a small paper limit of four. Consider files containing three, four and five bytes. Write the amount requested, amount returned and result of len(data) > limit for each.

## Check your reasoning

Three and four bytes pass this size gate; five fails. Passing this gate says nothing yet about UTF-8, JSON syntax or record validity. Those checks follow.

## If something differs

If a large file is read fully in your adaptation, look for an unbounded read before this check. A limit after allocation does not bound the earlier allocation.


## Source for this lesson

[Open the example source](https://github.com/umicom-foundation/Bits2Banking/blob/main/content/labs/python-notes/notes.py). Keep the source revision with your exercise notes so later changes can be compared.

[Course contents](index.md) · [Previous lesson](07-measure-text-and-encoded-bytes.md) · [Next lesson](09-allocate-note-identifiers-from-existing-data.md)

