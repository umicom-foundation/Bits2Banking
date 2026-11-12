<!--
Umicom Bits2Banking
File: content/lessons/umicom-development/storage-empty-files-owned-reads.md

PURPOSE:
Read empty and binary files with explicit ownership

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->
![Umicom](../../assets/branding/umicom-logo.svg)

# Read empty and binary files with explicit ownership

Prepare the installed-SDK lab using its README. The following command is a qualification step, not a recorded execution result.

~~~powershell
& .\build\framework-filesystem-clients\filesystem-clients.exe empty-file C:/umicom/Umicom-Bits2Banking/build/framework-filesystem-clients/qualification/empty-file
~~~

## A byte count is the content boundary

An empty file is a valid file with zero content bytes. A binary file may contain zero-valued bytes in the middle of its content. Neither case can be handled reliably by treating strlen as the authoritative length. Framework returns a byte count with an owned buffer and also appends a trailing NUL for convenience. The count, not that terminator, determines which bytes belong to the file.

~~~c
unsigned char *bytes = NULL;
size_t count = 0U;
UmiStatus status = UmiRootedFileRead(root, relative, 64U, &bytes, &count);
if (status == UMI_STATUS_OK) {
    /* Consume exactly count bytes, then release the owned buffer. */
    UmiRootedFileFree(bytes);
}
~~~

## Follow the shared lab helper

LabReadEquals in fixture.c compares count to the expected length, compares exactly that many bytes, checks the convenience terminator, then frees the buffer through UmiRootedFileFree. Its success condition does not require count to be nonzero. The empty-file scenario creates a zero-length record and uses that helper. The new-file scenario includes both an embedded zero byte and a byte outside ASCII to expose accidental text assumptions.

## Bound reads before allocating content

The maximumBytes argument limits what the operation will read. A limit refusal is different from an empty successful read. Keep output initialization and status handling visible: a failed read must not lead a caller to reuse a previous buffer as if it were new content. The lab uses a small bound because its fixture is intentionally small. A product should select a bound from its document contract and explain the refusal to its user.

| Observation | Meaning |
| --- | --- |
| OK, count zero | A successfully read empty file |
| OK, embedded NUL | Binary content; count still owns the boundary |
| Limit refusal | The selected input exceeds the allowed read size |
| Owned buffer released | The caller no longer retains that allocation |

## Do not overextend the result

A successful read gives a snapshot of accepted bytes. It is not a lock against later content changes, and it does not establish the file format or trustworthiness of those bytes. A parser must still validate its own structure. Keep filesystem ownership, byte-buffer ownership and application-format validation as separate steps with separately reported failures.

## Practice and diagnosis

Change the fixture bytes while keeping the expected count explicit, then qualify the corresponding scenario again. If a binary record appears truncated, inspect the client for text-length operations before changing the storage API. If an empty file fails the comparison, check whether the caller incorrectly requires a positive count or forgets that zero-length content remains valid.

## Source and next steps

<!-- Previous source-tree links are retained for review; public repository routes
     below remain usable after the lesson is published.
[Lab build and source guide](../../../labs/native/framework-filesystem-clients/README.md) · [Qualification record](../../../labs/native/framework-filesystem-clients/QUALIFICATION.md) · [HTML edition](../../courses/umicom-development/lessons/storage-empty-files-owned-reads.html)
-->
[Lab build and source guide](https://github.com/umicom-foundation/Bits2Banking/blob/main/labs/native/framework-filesystem-clients/README.md) · [Qualification record](https://github.com/umicom-foundation/Bits2Banking/blob/main/labs/native/framework-filesystem-clients/QUALIFICATION.md) · [HTML edition](../../courses/umicom-development/lessons/storage-empty-files-owned-reads.html)

[Previous lesson](storage-exclusive-file-publication.md) · [Course index](index.md) · [Next lesson](storage-progress-and-partial-results.md)
