<!--
Umicom Bits2Banking
File: content/lessons/06-umicom/umicom-kernel-from-scratch/61-design-a-kernel-boundary-test-table.md

PURPOSE:
Explain the lesson: Design a kernel-boundary test table.

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->

# Design a kernel-boundary test table

## Prepare

Open `labs/native/syscall-dispatch/dispatch.h` and `dispatch.c`. A request asks a service to do work; a reply carries its result. This is a hosted teaching model with ordinary function calls, not an actual processor trap. Read the header's ownership rules before changing an example.

## Understand the idea

A boundary test checks both accepted work and refusals. Checking only the success message misses damage caused before a failure. The header promises that state and reply remain unchanged on refusal.

## Work through the example

1. List null pointers, caller zero, unknown operation, missing right, stale revision, invalid text and full capacity.
2. For each case, write the first expected return branch.
3. Add a valid read and valid publish.
4. Compare named fields and event bytes before and after refusal.
5. Keep buffer-alias violations outside the valid caller contract.

## Check your reasoning

A useful test identifies which contract it checks and what must remain unchanged. Prefer field comparisons for structures that may contain padding.

## If something differs

If several fields are invalid, the first check determines the observed status. Isolate one invalid condition at a time to make a regression easy to diagnose.


## Source for this lesson

[Open the example source](https://github.com/umicom-foundation/Bits2Banking/blob/main/labs/native/syscall-dispatch/dispatch.c). Keep the source revision with your exercise notes so later changes can be compared.

[Course contents](index.md) · [Previous lesson](60-report-full-capacity-without-overwriting.md)

