<!--
Umicom Bits2Banking
File: content/lessons/umicom-development/76-measure-a-gradient-vector.md

PURPOSE:
Explain the lesson: Measure a gradient vector.

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->

# Measure a gradient vector

## Prepare

Open Framework's `src/ai/training/gradient_clipping.c` and its header. A gradient is a collection of numbers describing how a model's error changes when its parameters change. A norm is one number summarising their combined size. Use a calculator or paper; no model training is needed.

## Understand the idea

For two values, the Euclidean norm is the square root of the sum of their squares. It measures combined magnitude without cancelling positive and negative entries.

## Work through the example

1. Write gradients 3 and 4.
2. Compute 3×3 + 4×4.
3. Take the square root.
4. Repeat with -3 and 4.

## Check your reasoning

Both vectors have norm 5. Signs describe direction but do not make large opposing entries disappear from this size measurement.

## If something differs

If you obtain 7 or 1, you added signed values rather than squared magnitudes. Keep the formula beside the worked example.


## Source for this lesson

[Open the example source](https://github.com/umicom-foundation/umicom-framework/blob/main/src/ai/training/gradient_clipping.c). Keep the source revision with your exercise notes so later changes can be compared.

[Course contents](index.md) · [Previous lesson](75-review-a-split-before-training.md) · [Next lesson](77-measure-several-parameter-arrays-together.md)

