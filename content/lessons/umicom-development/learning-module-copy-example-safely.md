<!--
Umicom Bits2Banking
File: content/lessons/umicom-development/learning-module-copy-example-safely.md

PURPOSE:
Copy an example into a learner-chosen file

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->
# Copy an example into a learner-chosen file

A learning module is a collection of lessons and examples that an application can read. This module follows the same C services used by Umicom Studio IDE. A manifest is the small JSON document that identifies the collection and records which files belong to it. JSON is a text format made of named values, lists and objects.

## Prepare for this lesson

1. Open PowerShell on Windows, or a terminal on Linux. A terminal runs the commands you type; PowerShell and Bash are two command interpreters.
2. Choose a practice directory that you can find again. Keep the original course files unchanged.
3. Locate your built `umicom` program. The examples use `C:\umicom\Umicom-Applications\build\windows-ucrt64-all-debug\bin\umicom.exe`. Use the corresponding path on your computer.
4. Run `umicom learning-pack --help` using the full executable path if it is not on PATH. If the command is unavailable, your executable predates this feature; rebuild it before continuing.

The exercises use a content pack compatible with reader version `0.9.0`. A host version identifies the application reading the pack. Check your product and manifest compatibility before substituting another version. Nothing in these lessons requires a remote marketplace or an account.

## A lesson is not permission to run code

A learner may read an example before deciding to compile it. Studio should let the learner choose where practice work is saved. Framework already supplies the safe copy operation; an application should not implement another unchecked file copy.

The manifest can link a lesson to an example through its `example` identifier. `UmiLearningPracticeResolveExample` looks up that relationship without reading the file. The interface can then show the example title and proposed destination.

## Perform the copy

~~~c
UmiLearningPracticeResult result;
UmiStatus status = UmiLearningPracticeCopy(
    pack, selected_id, practice_root, "exercise.c",
    65536U, &result);
if (status == UMI_STATUS_OK) {
    /* Show that the complete file was copied. */
}
~~~

This excerpt uses `umicom/teacher/learning_practice.h`. `pack` remains alive throughout the call. `selected_id` names a resource. `practice_root` is a directory the learner selected. `65536U` bounds the permitted source size to 65,536 bytes; it is not an instruction to truncate larger examples.

1. Resolve the example and confirm the destination in the interface.
2. Run the blocking copy on a worker.
3. Read `status` and the result before displaying success.
4. If the destination already exists, ask the learner for another name.
5. If a new partial file was created, describe it accurately and preserve the original source.

Framework verifies source bytes before attempting the destination. It does not create parent folders, overwrite an existing file, build, run or download anything. It copies one resource, so a multi-file project needs an explicit higher-level project workflow.

## Failure exercise

Choose a destination that already contains a note. The copy must refuse it and leave the note unchanged. A test should compare the complete note bytes afterwards, not merely check that an error message appeared.

## Read the source

[Open the example source](https://github.com/umicom-foundation/umicom-framework/blob/main/include/umicom/teacher/learning_practice.h).

## Continue learning

[Course contents](../../courses/umicom-development/index.html) · [Previous: Understand how Studio opens a bundled learning module](learning-module-studio-installation-boundary.md) · [Next: Test a learning module through observable outcomes](learning-module-regression-design.md)
