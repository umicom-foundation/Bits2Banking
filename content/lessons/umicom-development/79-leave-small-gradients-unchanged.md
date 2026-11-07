<!--
Umicom Bits2Banking
File: content/lessons/umicom-development/79-leave-small-gradients-unchanged.md

PURPOSE:
Explain the lesson: Leave small gradients unchanged.

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->

# Leave small gradients unchanged

## Prepare

Open Framework's `src/ai/training/gradient_clipping.c` and its header. A gradient is a collection of numbers describing how a model's error changes when its parameters change. A norm is one number summarising their combined size. Use a calculator or paper; no model training is needed.

## Understand the idea

Clipping is a ceiling, not a requirement to enlarge every gradient to the limit. A vector already within the limit keeps scale 1.

## Work through the example

1. Use gradients 0.3 and 0.4 with limit 2.
2. Compute norm 0.5.
3. Read the strict greater-than comparison.
4. Repeat with a vector exactly at the limit.

## Check your reasoning

Both within-limit and exactly-at-limit vectors keep scale 1 and are not marked clipped. Zero gradients also remain zero.

## If something differs

If an implementation scales small vectors upward, it is normalising them rather than implementing this clipping policy. Name and test the intended operation clearly.


## Source for this lesson

[Open the example source](https://github.com/umicom-foundation/umicom-framework/blob/main/src/ai/training/gradient_clipping.c). Keep the source revision with your exercise notes so later changes can be compared.

[Course contents](index.md) · [Previous lesson](78-derive-a-common-clipping-scale.md) · [Next lesson](80-reject-nonfinite-gradient-input.md)

