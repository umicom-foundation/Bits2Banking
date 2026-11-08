<!--
Umicom Bits2Banking
File: content/lessons/umicom-development/learning-module-files-and-identities.md

PURPOSE:
Separate a course, a manifest and a reader

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->
# Separate a course, a manifest and a reader

A learning module is a collection of lessons and examples that an application can read. This module follows the same C services used by Umicom Studio IDE. A manifest is the small JSON document that identifies the collection and records which files belong to it. JSON is a text format made of named values, lists and objects.

## Prepare for this lesson

1. Open PowerShell on Windows, or a terminal on Linux. A terminal runs the commands you type; PowerShell and Bash are two command interpreters.
2. Choose a practice directory that you can find again. Keep the original course files unchanged.
3. Locate your built `umicom` program. The examples use `C:\umicom\Umicom-Applications\build\windows-ucrt64-all-debug\bin\umicom.exe`. Use the corresponding path on your computer.
4. Run `umicom learning-pack --help` using the full executable path if it is not on PATH. If the command is unavailable, your executable predates this feature; rebuild it before continuing.

The exercises use a content pack compatible with reader version `0.9.0`. A host version identifies the application reading the pack. Check your product and manifest compatibility before substituting another version. Nothing in these lessons requires a remote marketplace or an account.

## What you will build

Imagine a folder containing `guide.html`, `example.c` and `learning-pack.json`. The HTML file is the lesson; the C file is the example; the manifest describes both. The reader is the program that opens the lesson. Keeping them separate lets the same material work in a browser, in Studio and in a future mobile reader.

~~~text
content folder
  learning-pack.json -> identity, revision, allowed reader versions
  guide.html         -> explanation and links
  example.c          -> source text copied only on request
~~~

## Read one resource

1. Open the manifest in a text editor. Find `resources`, the list of files the reader knows about.
2. For one item, find `id`. This is a stable name used by the program; it need not equal the filename.
3. Find `path`, the name relative to the selected content folder. Relative means it starts inside that folder, rather than at a disk or filesystem root.
4. Find `kind`. A `lesson` or `guide` is reading material; an `example` is source material; an `image` is an illustration.
5. Find `sha256`, the recorded fingerprint of the file bytes. A fingerprint helps detect a changed file; it does not prove who wrote it.

The pack also has an `id`, `product` and positive `revision`. A revision describes an edition of the content. Editing a lesson must produce a reviewed new edition rather than silently changing what an old edition means.

## Exercise

Draw arrows from each manifest path to its file. Then explain why a lesson title may change while its stable identifier remains the same. Expected answer: bookmarks and application help can continue to refer to the same lesson. If a path has no matching file, record the missing resource; do not create an empty substitute.

## Read the source

[Open the example source](https://github.com/umicom-foundation/umicom-framework/blob/main/include/umicom/teacher/learning_pack.h).

## Continue learning

[Course contents](../../courses/umicom-development/index.html) · [Next: Load a pack and understand its lifetime](learning-module-load-and-ownership.md)

<!-- Course metadata owns the reading order; retain the existing lesson and add its missing continuation. -->
[Previous lesson](functionality-lab-map.md)
