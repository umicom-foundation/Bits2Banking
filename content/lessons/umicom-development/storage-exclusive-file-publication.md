<!--
Umicom Bits2Banking
File: content/lessons/umicom-development/storage-exclusive-file-publication.md

PURPOSE:
Create a file without replacing an existing leaf

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->
![Umicom](../../assets/branding/umicom-logo.svg)

# Create a file without replacing an existing leaf

Prepare the installed-SDK lab using its README. The following command is a qualification step, not a recorded execution result.

~~~powershell
& .\build\framework-filesystem-clients\filesystem-clients.exe existing-file C:/umicom/Umicom-Bits2Banking/build/framework-filesystem-clients/qualification/existing-file
~~~

## Make the intended effect explicit

Saving edits to an existing document and creating a new generated file need different policies. This lesson uses UmiRootedFileCreate, whose final file creation is exclusive. It accepts an explicitly selected root, a portable relative path, bytes and a byte count. It does not create parent directories, remove an earlier file, or grant permission to run generated content. Prepare the parent separately through the shared directory service.

~~~c
UmiRootedFileCreation progress;
UmiStatus status = UmiRootedFileCreate(
    root, "notes/record.bin", content, content_size, &progress);
if (status != UMI_STATUS_OK) {
    /* created and bytes_written may still describe partial work. */
}
~~~

## Read the native example

The lab creates notes, then writes a four-byte binary record. The existing-file scenario attempts a second creation with replacement bytes. It expects ALREADY_EXISTS, created false, complete false and zero accepted bytes for the second attempt. It then reads the original record and compares its exact bytes. That final check matters: a refusal code alone would not establish that earlier content survived.

## Separate creation from completion

A native file can be created successfully before writing, flushing or closing fails. The report records created as soon as the native create succeeds, and bytes_written records accepted bytes. complete becomes true only when the full operation succeeds. An application must keep the returned status alongside those fields. A message saying files written can conceal an incomplete result; files created and bytes accepted describe the observed effects more accurately.

## Keep failure recovery deliberate

If a partial file remains, this API does not delete it or reopen it through replacement mode. Preserve the path and report, diagnose the failed operation, then decide on a separate reviewed recovery action. Retrying Create at the same path may correctly return ALREADY_EXISTS. Automatically switching APIs would turn a safe new-file operation into an overwrite without the caller making that decision.

## Extend and qualify

Run new-file and existing-file in separate retained fixture folders. Compare their observations, then inspect the content of record.bin with a binary-aware tool. Native access, link and short-write behavior needs additional platform qualification; the small lab does not simulate every failure. Framework has dedicated injected-boundary cases for partial progress, which complement rather than replace native evidence.

## Expected observation

Both scenarios should preserve the original byte sequence and exit zero when their expected scoped outcomes match. Record the installed SDK identity and retained fixture path. No application source is compiled or launched by these file operations.

## Source and next steps

<!-- Previous source-tree links are retained for review; public repository routes
     below remain usable after the lesson is published.
[Lab build and source guide](../../../labs/native/framework-filesystem-clients/README.md) · [Qualification record](../../../labs/native/framework-filesystem-clients/QUALIFICATION.md) · [HTML edition](../../courses/umicom-development/lessons/storage-exclusive-file-publication.html)
-->
[Lab build and source guide](https://github.com/umicom-foundation/Bits2Banking/blob/main/labs/native/framework-filesystem-clients/README.md) · [Qualification record](https://github.com/umicom-foundation/Bits2Banking/blob/main/labs/native/framework-filesystem-clients/QUALIFICATION.md) · [HTML edition](../../courses/umicom-development/lessons/storage-exclusive-file-publication.html)

[Previous lesson](storage-exclusive-directory-reservation.md) · [Course index](index.md) · [Next lesson](storage-empty-files-owned-reads.md)
