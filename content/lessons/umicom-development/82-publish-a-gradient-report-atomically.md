<!--
Umicom Bits2Banking
File: content/lessons/umicom-development/82-publish-a-gradient-report-atomically.md

PURPOSE:
Explain the lesson: Publish a gradient report together.

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->

# Publish a gradient report together

## Prepare

Open Framework's `src/ai/training/gradient_clipping.c` and its header. A gradient is a collection of numbers describing how a model's error changes when its parameters change. A norm is one number summarising their combined size. Use a calculator or paper; no model training is needed.

## Understand the idea

The report combines norm, applied scale, element count and clipping flag. Publishing them together avoids mixing a new norm with an old count after failure.

## Work through the example

1. Locate the local zero-initialized candidate.
2. Mark every field assignment.
3. Find the sole assignment through `outReport`.
4. Trace an invalid last gradient.

## Check your reasoning

The caller receives a new report only after all checks succeed. On failure its prior report remains untouched.

## If something differs

When testing preservation, compare defined fields or a deliberately captured byte snapshot. Do not assume unrelated structure assignments establish identical padding bytes.


## Source for this lesson

[Open the example source](https://github.com/umicom-foundation/umicom-framework/blob/main/src/ai/training/gradient_clipping.c). Keep the source revision with your exercise notes so later changes can be compared.

[Course contents](index.md) · [Previous lesson](81-avoid-overflow-while-measuring.md) · [Next lesson](83-write-a-gradient-measurement-lab-record.md)

