<!--
Umicom Bits2Banking
File: content/lessons/06-umicom/umicom-kernel-from-scratch/45-reject-extra-storage-image-bytes.md

PURPOSE:
Explain the lesson: Reject extra storage-image bytes.

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->

# Reject extra storage-image bytes

## Prepare

Open block_store.c and block_store.h in labs/native/writeback-sector-store. Its README gives the C23, CMake and Ninja commands for PowerShell and bash. This four-sector model runs in memory; no physical disk is accessed by staging or crash simulation.

## Understand the idea

After reading the exact expected sector count, ImportStable calls fgetc and checks both EOF and ferror. This requires an exact image and distinguishes a clean end from an I/O error.

## Work through the example

Compare an exact image, a truncated image and an exact image with one extra byte. Predict each status and whether the old store is replaced.

## Check your reasoning

Only the exact image with clean EOF is published. Truncated and extra-byte images return IO_ERROR. A prefix of a larger format is not silently accepted.

## If something differs

If a future format needs a header or version field, define that format explicitly. Do not weaken exact-length checks merely to make an unknown file load.


## Source for this lesson

[Open the example source](https://github.com/umicom-foundation/Bits2Banking/blob/main/labs/native/writeback-sector-store/block_store.c). Keep the source revision with your exercise notes so later changes can be compared.

[Course contents](index.md) · [Previous lesson](44-import-into-a-candidate-first.md) · [Next lesson](46-copy-a-request-before-publication.md)

