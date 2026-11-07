<!--
Umicom Bits2Banking
File: content/lessons/umicom-development/77-measure-several-parameter-arrays-together.md

PURPOSE:
Explain the lesson: Measure several parameter arrays together.

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->

# Measure several parameter arrays together

## Prepare

Open Framework's `src/ai/training/gradient_clipping.c` and its header. A gradient is a collection of numbers describing how a model's error changes when its parameters change. A norm is one number summarising their combined size. Use a calculator or paper; no model training is needed.

## Understand the idea

A model can keep gradients in several arrays. A global norm measures all their elements together so a shared scale can preserve their relative proportions.

## Work through the example

1. Put 3 in array A and 4 in array B.
2. Draw the pointer list and element-count list.
3. Trace the outer group loop and inner element loop.
4. Compare with one array containing both numbers.

## Check your reasoning

Both arrangements represent two elements with global norm 5. The report also records the total element count.

## If something differs

Do not average separate array norms unless that is the intended mathematical policy. Averaging 3 and 4 gives 3.5, which is a different measurement.


## Source for this lesson

[Open the example source](https://github.com/umicom-foundation/umicom-framework/blob/main/src/ai/training/gradient_clipping.c). Keep the source revision with your exercise notes so later changes can be compared.

[Course contents](index.md) · [Previous lesson](76-measure-a-gradient-vector.md) · [Next lesson](78-derive-a-common-clipping-scale.md)

