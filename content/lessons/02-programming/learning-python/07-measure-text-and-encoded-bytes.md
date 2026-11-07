<!--
Umicom Bits2Banking
File: content/lessons/02-programming/learning-python/07-measure-text-and-encoded-bytes.md

PURPOSE:
Explain the lesson: Measure text and encoded bytes.

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->

# Measure text and encoded bytes

## Prepare

Open the existing notes.py laboratory in a text editor. Use a disposable folder when trying it: notes.json is relative to the current terminal directory. The course's first two lessons explain installing Python and opening a terminal. This exercise reads existing Python code; Umicom's shared native engine remains C.

## Understand the idea

A string length counts Python string elements, while a saved UTF-8 file occupies bytes. Non-ASCII text can need more than one byte per character. The program checks both a per-note character limit and the serialized file's byte limit.

## Work through the example

Compare the text A with é. Inspect len(text), then len(text.encode("utf-8")) in a disposable interpreter session. Explain why the file check includes a final newline.

## Check your reasoning

A occupies one byte; é occupies two in UTF-8. Both strings have length one here. JSON punctuation, indentation and the final newline also occupy space.

## If something differs

If an editor displays another result, check the actual character and file encoding. A visually accented letter can also be represented by multiple Unicode code points.


## Source for this lesson

[Open the example source](https://github.com/umicom-foundation/Bits2Banking/blob/main/content/labs/python-notes/notes.py). Keep the source revision with your exercise notes so later changes can be compared.

[Course contents](index.md) · [Previous lesson](06-use-a-set-to-find-repeated-identities.md) · [Next lesson](08-bound-reading-before-parsing.md)

