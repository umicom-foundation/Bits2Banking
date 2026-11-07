<!--
Umicom Bits2Banking
File: content/lessons/umicom-development/81-avoid-overflow-while-measuring.md

PURPOSE:
Explain the lesson: Avoid overflow while measuring.

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->

# Avoid overflow while measuring

## Prepare

Open Framework's `src/ai/training/gradient_clipping.c` and its header. A gradient is a collection of numbers describing how a model's error changes when its parameters change. A norm is one number summarising their combined size. Use a calculator or paper; no model training is needed.

## Understand the idea

Squaring a large finite float directly can overflow even when a wider calculation could represent the final norm. The implementation uses a running scale and ratios in double precision.

## Work through the example

1. Find `scale`, `squares` and the two ratio branches.
2. Explain why each ratio is at most 1 in magnitude.
3. Trace values 3 then 4 through the branches.

## Check your reasoning

The first nonzero value establishes the scale. A later larger value rescales the accumulated sum instead of squaring the large value directly in float precision.

## If something differs

A numerically stable method still requires finite-result checks. Keep the final norm and scale validation; stability does not mean every conceivable input is representable.


## Source for this lesson

[Open the example source](https://github.com/umicom-foundation/umicom-framework/blob/main/src/ai/training/gradient_clipping.c). Keep the source revision with your exercise notes so later changes can be compared.

[Course contents](index.md) · [Previous lesson](80-reject-nonfinite-gradient-input.md) · [Next lesson](82-publish-a-gradient-report-atomically.md)

