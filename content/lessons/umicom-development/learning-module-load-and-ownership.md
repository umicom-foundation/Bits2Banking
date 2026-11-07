<!--
Umicom Bits2Banking
File: content/lessons/umicom-development/learning-module-load-and-ownership.md

PURPOSE:
Load a pack and understand its lifetime

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->
# Load a pack and understand its lifetime

A learning module is a collection of lessons and examples that an application can read. This module follows the same C services used by Umicom Studio IDE. A manifest is the small JSON document that identifies the collection and records which files belong to it. JSON is a text format made of named values, lists and objects.

## Prepare for this lesson

1. Open PowerShell on Windows, or a terminal on Linux. A terminal runs the commands you type; PowerShell and Bash are two command interpreters.
2. Choose a practice directory that you can find again. Keep the original course files unchanged.
3. Locate your built `umicom` program. The examples use `C:\umicom\Umicom-Applications\build\windows-ucrt64-all-debug\bin\umicom.exe`. Use the corresponding path on your computer.
4. Run `umicom learning-pack --help` using the full executable path if it is not on PATH. If the command is unavailable, your executable predates this feature; rebuild it before continuing.

The exercises use a content pack compatible with reader version `0.9.0`. A host version identifies the application reading the pack. Check your product and manifest compatibility before substituting another version. Nothing in these lessons requires a remote marketplace or an account.

## The C contract

A pointer is a value that refers to an object in memory. An owning pointer carries responsibility for eventually releasing that object. Framework returns an owning pack pointer only when loading succeeds.

~~~c
UmiLearningPack *pack = NULL;
UmiVersion host = {0, 9, 0};
UmiStatus status = UmiLearningPackLoad(
    root, "learning-pack.json", host, &pack);
if (status == UMI_STATUS_OK) {
    UmiLearningPackInfo info;
    status = UmiLearningPackCopyInfo(pack, &info);
    /* Use info only when this copy succeeds. */
}
UmiLearningPackDestroy(pack);
~~~

This is a function excerpt, not a complete executable. Include `umicom/teacher/learning_pack.h` in a C program linked with `Umicom::developer`. `root` must be an explicit absolute content directory. `&pack` passes the address of the pointer variable so the function can fill it. `status` tells the caller whether it can use the result. `NULL` means that no pack object is owned yet.

## Follow the operations

1. The loader reads a bounded manifest below the root.
2. The parser checks required fields, duplicate identities, relative paths and compatibility.
3. On success it copies metadata into an immutable pack. Immutable means callers do not change its fields through this API.
4. The owner keeps the pack alive while readers use it.
5. Destroy releases the owned metadata. No lesson program is executed.

Loading metadata is different from verifying every resource. A valid manifest can still describe a file that is missing. The next lesson reads each declared resource.

## Check your understanding

Why is `info` used only after success? A failed copy does not establish valid output. Why does the pack need destruction even when a later operation fails? Loading may already have allocated it. Never free it twice or keep using a pointer after destruction.

## Read the source

[Open the example source](https://github.com/umicom-foundation/umicom-framework/blob/main/include/umicom/teacher/learning_pack.h).

## Continue learning

[Course contents](../../courses/umicom-development/index.html) · [Previous: Separate a course, a manifest and a reader](learning-module-files-and-identities.md) · [Next: Verify the current bytes before reading or distribution](learning-module-verify-current-files.md)
