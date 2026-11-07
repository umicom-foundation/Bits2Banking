<!--
Umicom Bits2Banking
File: content/lessons/06-umicom/umicom-kernel-from-scratch/41-retry-only-remaining-storage-work.md

PURPOSE:
Explain the lesson: Retry only remaining storage work.

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->

# Retry only remaining storage work

## Prepare

Open block_store.c and block_store.h in labs/native/writeback-sector-store. Its README gives the C23, CMake and Ninja commands for PowerShell and bash. This four-sector model runs in memory; no physical disk is accessed by staging or crash simulation.

## Understand the idea

After a partial flush, successful sectors have their dirty markers cleared. A later Flush skips them. This makes progress visible and prevents the model from charging the same completed work against the next budget.

## Work through the example

Continue the three-dirty-sector example after its first budget-two flush. Call Flush with budget one, then call it again when nothing is dirty.

## Check your reasoning

The next call writes sector three and reports zero remaining. A subsequent call writes zero sectors and returns OK. No-op completion is valid.

## If something differs

If retries repeatedly write earlier sectors, inspect when dirty markers are cleared. Also check whether another Stage call intentionally made them dirty again.


## Source for this lesson

[Open the example source](https://github.com/umicom-foundation/Bits2Banking/blob/main/labs/native/writeback-sector-store/block_store.c). Keep the source revision with your exercise notes so later changes can be compared.

[Course contents](index.md) · [Previous lesson](40-flush-with-a-limited-budget.md) · [Next lesson](42-simulate-loss-of-unflushed-data.md)

