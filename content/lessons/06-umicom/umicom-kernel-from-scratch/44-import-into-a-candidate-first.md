<!--
Umicom Bits2Banking
File: content/lessons/06-umicom/umicom-kernel-from-scratch/44-import-into-a-candidate-first.md

PURPOSE:
Explain the lesson: Import into a candidate first.

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->

# Import into a candidate first

## Prepare

Open block_store.c and block_store.h in labs/native/writeback-sector-store. Its README gives the C23, CMake and Ninja commands for PowerShell and bash. This four-sector model runs in memory; no physical disk is accessed by staging or crash simulation.

## Understand the idea

ImportStable builds a separate candidate store. It reads all expected sectors and verifies the end of the stream before assigning that candidate to the live store. This prevents partial input from replacing valid state.

## Work through the example

Draw live store L and candidate C. Trace a file that ends during the second sector. Mark which object receives bytes and whether the final assignment occurs.

## Check your reasoning

C may contain a partial read, but L stays unchanged because the function returns before publication. This is failure-atomic within the process.

## If something differs

If live data changes after rejection, look for reads directed into store rather than candidate. Failure-atomic import is different from crash-durable saving.


## Source for this lesson

[Open the example source](https://github.com/umicom-foundation/Bits2Banking/blob/main/labs/native/writeback-sector-store/block_store.c). Keep the source revision with your exercise notes so later changes can be compared.

[Course contents](index.md) · [Previous lesson](43-export-the-stable-view.md) · [Next lesson](45-reject-extra-storage-image-bytes.md)

