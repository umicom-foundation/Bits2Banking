# Mathematics for AI — Unit 181: Handle zero and small logit scales

**Bits to Banking · Umicom Foundation**  
**Author:** Sammy Hegab · **Prerequisite:** Arithmetic and the previous mathematics units.

## Learning outcome

Calculate handle zero and small logit scales and identify which quantities are measured, estimated or exact counts.

## Definition and formula

`relative difference = |x − y|/max(|x|,|y|), with 0 when both are zero`

The formula defines a checkable scalar result. Token positions are zero-based in the native tensor layouts, while the course numbers lessons from one. Keep count units distinct from timings, memory bytes and model quality.

## Fully worked example

For x=0 and y=0 the relative difference is defined as zero for diagnostics. For x=0 and y=0.001 the relative difference is 1, but absolute tolerance can still permit it.

Verify the expression by substituting each number, recording intermediate terms and keeping the same units in every multiplication or division.

## Practise the calculation

**Question:** What is relative difference for x=2 and y=3?

<details><summary>Reveal the complete calculation</summary>

|3−2|/3 = 1/3 ≈ 0.3333.

</details>

## Native AI context

The companion [LLM Lesson 299](../10-native-ai/299-apply-a-declared-absolute-and-relative-tolerance.md) applies this calculation to the native C23 stacked-decoder qualification. A count of compared scalars is a correctness-coverage measure, not a performance result. A ratio computed from illustrative numbers does not establish measured runtime behaviour.

## Continue learning

[Previous unit](180-calculate-full-window-replacement-counts.md) · [HTML study route](../../courses/maths-for-ai/numerical-qualification-mathematics.html)
