<!--
Umicom Bits2Banking
File: content/lessons/umicom-development/78-derive-a-common-clipping-scale.md

PURPOSE:
Explain the lesson: Derive a common clipping scale.

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->

# Derive a common clipping scale

## Prepare

Open Framework's `src/ai/training/gradient_clipping.c` and its header. A gradient is a collection of numbers describing how a model's error changes when its parameters change. A norm is one number summarising their combined size. Use a calculator or paper; no model training is needed.

## Understand the idea

When the norm exceeds a positive limit, a common scale reduces every gradient by the same proportion. With norm 5 and limit 2, the scale is 2/5.

## Work through the example

1. Calculate the scale for gradients 3 and 4 with limit 2.
2. Multiply each gradient by it on paper.
3. Recalculate the resulting norm.

## Check your reasoning

The scale is 0.4 and the scaled values are 1.2 and 1.6, whose norm is 2. Their ratio remains unchanged.

## If something differs

The measurement function reports the scale; inspect the optimizer policy to learn where it is applied. Do not assume this function mutates the gradient arrays.


## Source for this lesson

[Open the example source](https://github.com/umicom-foundation/umicom-framework/blob/main/src/ai/training/gradient_clipping.c). Keep the source revision with your exercise notes so later changes can be compared.

[Course contents](index.md) · [Previous lesson](77-measure-several-parameter-arrays-together.md) · [Next lesson](79-leave-small-gradients-unchanged.md)

