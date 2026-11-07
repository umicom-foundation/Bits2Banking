<!--
Umicom Bits2Banking
File: content/lessons/06-umicom/umicom-kernel-from-scratch/38-distinguish-staged-and-stable-sectors.md

PURPOSE:
Explain the lesson: Distinguish staged and stable sectors.

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->

# Distinguish staged and stable sectors

## Prepare

Open block_store.c and block_store.h in labs/native/writeback-sector-store. Its README gives the C23, CMake and Ninja commands for PowerShell and bash. This four-sector model runs in memory; no physical disk is accessed by staging or crash simulation.

## Understand the idea

A sector is a fixed-size unit of storage. This model keeps a staged copy and a stable copy. Staging means accepting a new version into the model's pending area. The stable copy represents what has completed a simulated flush.

## Work through the example

Draw two boxes for sector zero. Start with zeros, stage a page containing A, then trace Read and ReadStable. Name which box each function selects.

## Check your reasoning

Read chooses staged data when dirty is set; ReadStable still returns the previous stable bytes. A successful stage does not imply a completed flush.

## If something differs

If both reads show A, check whether Flush was called between them. Keep the operation order beside every observation.


## Source for this lesson

[Open the example source](https://github.com/umicom-foundation/Bits2Banking/blob/main/labs/native/writeback-sector-store/block_store.c). Keep the source revision with your exercise notes so later changes can be compared.

[Course contents](index.md) · [Previous lesson](37-read-the-native-scheduler-boundary.md) · [Next lesson](39-explain-a-dirty-marker.md)

