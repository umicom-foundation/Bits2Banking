<!--
Umicom Bits2Banking
File: content/lessons/06-umicom/umicom-kernel-from-scratch/42-simulate-loss-of-unflushed-data.md

PURPOSE:
Explain the lesson: Simulate loss of unflushed data.

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->

# Simulate loss of unflushed data

## Prepare

Open block_store.c and block_store.h in labs/native/writeback-sector-store. Its README gives the C23, CMake and Ninja commands for PowerShell and bash. This four-sector model runs in memory; no physical disk is accessed by staging or crash simulation.

## Understand the idea

Crash copies stable data back over staged data and clears dirty markers. It models losing pending writes during a restart. It does not power off the computer or test a drive's actual guarantees.

## Work through the example

Stage A in sector zero and B in sector one. Flush with budget one, then simulate Crash. Read both sectors and explain the difference.

## Check your reasoning

Sector zero retains A in the model. Sector one returns its earlier stable content because B was never flushed. The failure budget gives a repeatable experiment.

## If something differs

If you describe this as proof of hardware durability, narrow the claim. Real devices can reorder writes or tear sectors; this model assumes complete sector copies.


## Source for this lesson

[Open the example source](https://github.com/umicom-foundation/Bits2Banking/blob/main/labs/native/writeback-sector-store/block_store.c). Keep the source revision with your exercise notes so later changes can be compared.

[Course contents](index.md) · [Previous lesson](41-retry-only-remaining-storage-work.md) · [Next lesson](43-export-the-stable-view.md)

