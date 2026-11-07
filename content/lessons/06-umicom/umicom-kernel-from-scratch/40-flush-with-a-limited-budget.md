<!--
Umicom Bits2Banking
File: content/lessons/06-umicom/umicom-kernel-from-scratch/40-flush-with-a-limited-budget.md

PURPOSE:
Explain the lesson: Flush with a limited budget.

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->

# Flush with a limited budget

## Prepare

Open block_store.c and block_store.h in labs/native/writeback-sector-store. Its README gives the C23, CMake and Ninja commands for PowerShell and bash. This four-sector model runs in memory; no physical disk is accessed by staging or crash simulation.

## Understand the idea

maxSectors limits how many dirty sectors one Flush call copies. The loop visits sector indices in order and reports written and remaining counts. An incomplete flush is a defined outcome.

## Work through the example

Mark sectors zero, two and three dirty. Trace Flush with a budget of two. Write the resulting stable sectors, dirty markers and report.

## Check your reasoning

Zero and two become stable; three stays dirty. The report contains two written and one remaining, and the status is INCOMPLETE.

## If something differs

If a test assumes all pending work completed, inspect the returned status and remaining count. Returning from a function is not the same as completing every write.


## Source for this lesson

[Open the example source](https://github.com/umicom-foundation/Bits2Banking/blob/main/labs/native/writeback-sector-store/block_store.c). Keep the source revision with your exercise notes so later changes can be compared.

[Course contents](index.md) · [Previous lesson](39-explain-a-dirty-marker.md) · [Next lesson](41-retry-only-remaining-storage-work.md)

