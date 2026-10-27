# Mathematics for AI — Unit 173: Evaluate an absolute-plus-relative threshold

**Bits to Banking · Umicom Foundation**  
**Author:** Sammy Hegab · **Prerequisite:** Arithmetic and the previous mathematics units.

## Learning outcome

Calculate evaluate an absolute-plus-relative threshold and identify which quantities are measured, estimated or exact counts.

## Definition and formula

`|candidate − reference| ≤ a + r × max(|candidate|, |reference|)`

The formula defines a checkable scalar result. Token positions are zero-based in the native tensor layouts, while the course numbers lessons from one. Keep count units distinct from timings, memory bytes and model quality.

## Fully worked example

Take reference 1000.0, candidate 1000.05, a=0.001 and r=0.0001. Absolute error is 0.05; allowance is 0.001 + 0.0001×1000.05 = 0.101005. The pair qualifies.

Verify the expression by substituting each number, recording intermediate terms and keeping the same units in every multiplication or division.

## Practise the calculation

**Question:** With reference 0 and candidate 0.002, a=0.001 and r=0.0001, does it qualify?

<details><summary>Reveal the complete calculation</summary>

The allowance is 0.0010002; error 0.002 exceeds it, so the comparison fails.

</details>

## Native AI context

The companion [LLM Lesson 299](../10-native-ai/299-apply-a-declared-absolute-and-relative-tolerance.md) applies this calculation to the native C23 stacked-decoder qualification. A count of compared scalars is a correctness-coverage measure, not a performance result. A ratio computed from illustrative numbers does not establish measured runtime behaviour.

## Continue learning

[Previous unit](172-compare-mha-and-gqa-cache-capacity.md) · [HTML study route](../../courses/maths-for-ai/numerical-qualification-mathematics.html)
