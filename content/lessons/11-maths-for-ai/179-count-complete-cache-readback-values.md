# Mathematics for AI — Unit 179: Count complete cache readback values

**Bits to Banking · Umicom Foundation**  
**Author:** Sammy Hegab · **Prerequisite:** Arithmetic and the previous mathematics units.

## Learning outcome

Calculate count complete cache readback values and identify which quantities are measured, estimated or exact counts.

## Definition and formula

`readback count = (Σ retained rows observed) × layers × channels × 2`

The formula defines a checkable scalar result. Token positions are zero-based in the native tensor layouts, while the course numbers lessons from one. Keep count units distinct from timings, memory bytes and model quality.

## Fully worked example

With initial two rows, context six and eight continuations, the observed row counts are [2,3,4,5,6,6,6,6,6], summing to 44. Two layers, eight channels and K/V give 44×2×8×2=1,408 retained-value comparisons.

Verify the expression by substituting each number, recording intermediate terms and keeping the same units in every multiplication or division.

## Practise the calculation

**Question:** For one layer, width four and observed retained row counts [1,2,3], calculate readback comparisons.

<details><summary>Reveal the complete calculation</summary>

(1+2+3)×1×4×2 = 48.

</details>

## Native AI context

The companion [LLM Lesson 303](../10-native-ai/303-read-back-retained-cache-state-after-each-append.md) applies this calculation to the native C23 stacked-decoder qualification. A count of compared scalars is a correctness-coverage measure, not a performance result. A ratio computed from illustrative numbers does not establish measured runtime behaviour.

## Continue learning

[Previous unit](178-count-layered-key-value-proposal-scalars.md) · [HTML study route](../../courses/maths-for-ai/numerical-qualification-mathematics.html)
