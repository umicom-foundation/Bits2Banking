<!--
Umicom Bits2Banking
File: content/lessons/06-umicom/umicom-kernel-from-scratch/39-explain-a-dirty-marker.md

PURPOSE:
Explain the lesson: Explain a dirty marker.

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->

# Explain a dirty marker

## Prepare

Open block_store.c and block_store.h in labs/native/writeback-sector-store. Its README gives the C23, CMake and Ninja commands for PowerShell and bash. This four-sector model runs in memory; no physical disk is accessed by staging or crash simulation.

## Understand the idea

The dirty array records which sectors have pending changes. It is metadata: information describing the data. A zero marker selects stable content; a nonzero marker selects staged content.

## Work through the example

Stage sector one twice, first with A and then B, without flushing. Draw its staged bytes and dirty marker after each call. Ask how many versions the model retains.

## Check your reasoning

Only B remains staged. The dirty marker is still one. The model is a pending-write cache, not a history of every edit.

## If something differs

If you need undo or revision history, a dirty bit is insufficient. Use a separate history service rather than interpreting the marker as a version number.


## Source for this lesson

[Open the example source](https://github.com/umicom-foundation/Bits2Banking/blob/main/labs/native/writeback-sector-store/block_store.c). Keep the source revision with your exercise notes so later changes can be compared.

[Course contents](index.md) · [Previous lesson](38-distinguish-staged-and-stable-sectors.md) · [Next lesson](40-flush-with-a-limited-budget.md)

