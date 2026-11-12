<!--
Umicom Bits2Banking
File: content/lessons/06-umicom/umicom-kernel-from-scratch/101-qualify-kernel-storage-on-disposable-media.md

PURPOSE:
Qualify storage with disposable images and fresh readback

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->

![Umicom](../../../assets/branding/umicom-wordmark.svg)

# Qualify storage with disposable images and fresh readback

## Before you begin
Read the FAT16 and block-device chapters. Use the repository's synthetic fixtures and an isolated build directory. This lesson does not ask you to write a physical USB drive or a production filesystem.

## Separate the writer from the evidence reader
A writer can keep successful-looking values in memory. To demonstrate persistence, the suite starts a fresh reader against the disposable image after the writer exits. The reader does not share the writer's cached state.

~~~text
Known synthetic fixture
    -> checked disposable copy
    -> read-only admission check
    -> explicit writer guest
    -> fresh readback guest
    -> compare expected bytes and metadata
    -> remove the disposable test copy
~~~

1. Read the prepare and cleanup branches in cmake/DiskWritableFilesystem.cmake.
2. Identify the checked original fixture and the test-owned destination.
3. Follow the fixture dependencies that order read-only, writer and readback checks.
4. Keep interrupted-write cases distinct from clean committed cases.

## Expected result
A clean write is followed by a readback of the intended data. An intentionally interrupted sequence should trigger its documented recovery/refusal behavior. A nonzero process exit alone does not identify the expected recovery cause.

## Exercise
Draw a dependency graph for the writable-filesystem test group. Explain why starting the reader before the writer finishes would create misleading results. Then identify which cleanup operation may run after a failed dependent test and which source fixture must remain intact.

## Recovery
If a test fails, keep its logs and the failed disposable artifact when the diagnostic workflow supports retention. Compare the exact source and expected fixture hashes before interpreting the on-disk structure. Never replace the test destination with a real device path just because QEMU accepts a different argument.

Run the documented Kernel build before the tests. CTest fixture relationships protect ordering, but the complete build and source receipt remain part of the evidence. A successful synthetic emulator suite is not qualification of a firmware bootloader, a USB installer or physical hardware power-loss behavior.


[Course contents](index.md) · [Previous lesson](100-bind-a-guest-run-to-current-source.md) · [Next lesson](102-read-a-packet-as-a-bounded-capture.md)
