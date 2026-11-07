<!--
Umicom Bits2Banking
File: content/lessons/umicom-development/learning-module-verify-current-files.md

PURPOSE:
Verify the current bytes before reading or distribution

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->
# Verify the current bytes before reading or distribution

A learning module is a collection of lessons and examples that an application can read. This module follows the same C services used by Umicom Studio IDE. A manifest is the small JSON document that identifies the collection and records which files belong to it. JSON is a text format made of named values, lists and objects.

## Prepare for this lesson

1. Open PowerShell on Windows, or a terminal on Linux. A terminal runs the commands you type; PowerShell and Bash are two command interpreters.
2. Choose a practice directory that you can find again. Keep the original course files unchanged.
3. Locate your built `umicom` program. The examples use `C:\umicom\Umicom-Applications\build\windows-ucrt64-all-debug\bin\umicom.exe`. Use the corresponding path on your computer.
4. Run `umicom learning-pack --help` using the full executable path if it is not on PATH. If the command is unavailable, your executable predates this feature; rebuild it before continuing.

The exercises use a content pack compatible with reader version `0.9.0`. A host version identifies the application reading the pack. Check your product and manifest compatibility before substituting another version. Nothing in these lessons requires a remote marketplace or an account.

## Verify a practice pack

Place a complete practice pack in `C:\umicom\practice\offline-guide`. The directory must already contain its manifest and every declared resource. Then run:

~~~powershell
& "C:\umicom\Umicom-Applications\build\windows-ucrt64-all-debug\bin\umicom.exe" learning-pack verify "C:\umicom\practice\offline-guide" learning-pack.json 0.9.0
~~~

On Linux, with the program on PATH, the same operation is:

~~~bash
umicom learning-pack verify "$HOME/umicom-practice/offline-guide" learning-pack.json 0.9.0
~~~

The shell expands the home directory in this example; the program still receives an absolute path. You may choose any accessible practice directory.

## Interpret the result

A successful result reports the number of verified resources and the pack revision. The command reads the exact bytes through `UmiLearningPackReadResource`, compares their SHA-256 with the manifest and then frees the buffer. It does not print lesson contents or execute examples. Each resource is limited to 1 MiB by this authoring command.

1. Run verification on the unchanged pack.
2. In the practice copy only, add one sentence to a lesson and save it.
3. Run the same command. Expect failure because the recorded digest describes the earlier bytes.
4. Keep both the edit and the old manifest for the revision exercise.

A failure is useful here: it prevents silently presenting edited material as an unchanged edition. A missing file, incompatible host version and unreadable directory have different causes; read the diagnostic before making changes. Do not update hashes just to hide a failure whose cause you have not investigated.

## Limits

Verification observes files as they are read. Keep authors from changing the folder during review. A matching digest proves consistency with this manifest, not that the material is trustworthy or that its examples are safe to run.

## Read the source

[Open the example source](https://github.com/umicom-foundation/umicom-framework/blob/main/tools/umicom/src/command_learning_pack.c).

## Continue learning

[Course contents](../../courses/umicom-development/index.html) · [Previous: Load a pack and understand its lifetime](learning-module-load-and-ownership.md) · [Next: Prepare a new revision without replacing the previous manifest](learning-module-prepare-reviewed-revision.md)
