<!--
Umicom Bits2Banking
File: content/lessons/umicom-development/learning-module-prepare-reviewed-revision.md

PURPOSE:
Prepare a new revision without replacing the previous manifest

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->
# Prepare a new revision without replacing the previous manifest

A learning module is a collection of lessons and examples that an application can read. This module follows the same C services used by Umicom Studio IDE. A manifest is the small JSON document that identifies the collection and records which files belong to it. JSON is a text format made of named values, lists and objects.

## Prepare for this lesson

1. Open PowerShell on Windows, or a terminal on Linux. A terminal runs the commands you type; PowerShell and Bash are two command interpreters.
2. Choose a practice directory that you can find again. Keep the original course files unchanged.
3. Locate your built `umicom` program. The examples use `C:\umicom\Umicom-Applications\build\windows-ucrt64-all-debug\bin\umicom.exe`. Use the corresponding path on your computer.
4. Run `umicom learning-pack --help` using the full executable path if it is not on PATH. If the command is unavailable, your executable predates this feature; rebuild it before continuing.

The exercises use a content pack compatible with reader version `0.9.0`. A host version identifies the application reading the pack. Check your product and manifest compatibility before substituting another version. Nothing in these lessons requires a remote marketplace or an account.

## Review before preparing

Read every changed lesson and example first. Check that commands are appropriate for a practice directory, explanations match the current API, and no personal information or credentials have entered the material. Then prepare a separate candidate manifest:

~~~powershell
& "C:\umicom\Umicom-Applications\build\windows-ucrt64-all-debug\bin\umicom.exe" learning-pack prepare "C:\umicom\practice\offline-guide" learning-pack.json candidate.json 0.9.0
~~~

The command keeps the existing identity and resource list, recalculates digests from current files and increments the revision. It refuses to overwrite `candidate.json`. Choose a fresh filename after inspecting any earlier candidate; do not delete an unfamiliar file to make the command succeed.

## What the shared service does

1. `UmiLearningPackPrepareRevision` validates the requested revision and resource-size limit.
2. It reads each declared file using rooted-file access.
3. A shared JSON writer escapes quotes and backslashes in titles correctly.
4. It admits the complete result through the same schema parser as the reader.
5. Only a complete manifest is returned. The caller owns the returned byte buffer and releases it with `UmiLearningPackFreeBytes`.

The service itself writes no files. The CLI uses exclusive creation for the output. Exclusive means an existing destination is refused. An operating-system write failure can leave a partial newly created output; the diagnostic distinguishes that case, and the old manifest remains intact.

## Verify and compare

~~~powershell
& "C:\umicom\Umicom-Applications\build\windows-ucrt64-all-debug\bin\umicom.exe" learning-pack verify "C:\umicom\practice\offline-guide" candidate.json 0.9.0
~~~

Compare the two manifests. Expect a larger revision and changed digests for edited files, with the same resource order and identities. Preparing does not install the candidate in Studio. Distribution remains a separate reviewed action. Adding a new resource also requires explicitly editing the manifest resource list; this command does not scan your disk for files.

## Read the source

[Open the example source](https://github.com/umicom-foundation/umicom-framework/blob/main/src/teacher/learning_pack_authoring.c).

## Continue learning

[Course contents](../../courses/umicom-development/index.html) · [Previous: Verify the current bytes before reading or distribution](learning-module-verify-current-files.md) · [Next: Understand how Studio opens a bundled learning module](learning-module-studio-installation-boundary.md)
