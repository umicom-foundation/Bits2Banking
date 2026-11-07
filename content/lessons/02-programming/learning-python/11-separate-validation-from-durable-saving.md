<!--
Umicom Bits2Banking
File: content/lessons/02-programming/learning-python/11-separate-validation-from-durable-saving.md

PURPOSE:
Explain the lesson: Separate validation from durable saving.

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->

# Separate validation from durable saving

## Prepare

Open the existing notes.py laboratory in a text editor. Use a disposable folder when trying it: notes.json is relative to the current terminal directory. The course's first two lessons explain installing Python and opening a terminal. This exercise reads existing Python code; Umicom's shared native engine remains C.

## Understand the idea

save_notes validates and encodes before opening the destination for writing. This protects an existing file from malformed records rejected early. It is still a direct write: disk failure or interruption during writing can leave incomplete data.

## Work through the example

Draw three stages: validate, encode, write. Place malformed id, oversized encoded output and disk-full failure at their corresponding stage. Explain which stages have not yet opened the destination.

## Check your reasoning

Validation and encoded-size refusal happen before writing. A disk-full failure occurs after that boundary. A production design needs reviewed atomic replacement and recovery through shared Framework storage services.

## If something differs

If a lesson experiment damages a file, restore your disposable copy. Do not describe input validation alone as transactional storage or use important notes for failure experiments.


## Source for this lesson

[Open the example source](https://github.com/umicom-foundation/Bits2Banking/blob/main/content/labs/python-notes/notes.py). Keep the source revision with your exercise notes so later changes can be compared.

[Course contents](index.md) · [Previous lesson](10-preserve-unknown-record-fields.md)

