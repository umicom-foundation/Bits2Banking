<!--
Umicom Bits2Banking
File: content/lessons/umicom-development/80-reject-nonfinite-gradient-input.md

PURPOSE:
Explain the lesson: Reject nonfinite gradient input.

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->

# Reject nonfinite gradient input

## Prepare

Open Framework's `src/ai/training/gradient_clipping.c` and its header. A gradient is a collection of numbers describing how a model's error changes when its parameters change. A norm is one number summarising their combined size. Use a calculator or paper; no model training is needed.

## Understand the idea

Floating-point values include infinities and NaN, meaning not a number. Allowing them through arithmetic can make later results unusable while ordinary comparisons behave unexpectedly.

## Work through the example

1. Locate the checks on `maxNorm` and each absolute gradient.
2. Consider a NaN in the last array.
3. Identify whether a candidate report is published.

## Check your reasoning

The call refuses nonfinite inputs before publishing the report. The same policy rejects a zero or negative maximum norm.

## If something differs

Do not silently replace NaN with zero during a diagnostic investigation. Find the earlier operation that produced it and retain enough non-sensitive evidence to reproduce the cause.


## Source for this lesson

[Open the example source](https://github.com/umicom-foundation/umicom-framework/blob/main/src/ai/training/gradient_clipping.c). Keep the source revision with your exercise notes so later changes can be compared.

[Course contents](index.md) · [Previous lesson](79-leave-small-gradients-unchanged.md) · [Next lesson](81-avoid-overflow-while-measuring.md)

