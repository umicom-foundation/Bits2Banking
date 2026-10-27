# Mathematics for AI — Unit 174: Count active-prefix vocabulary logits

**Bits to Banking · Umicom Foundation**  
**Author:** Sammy Hegab · **Prerequisite:** Arithmetic and the previous mathematics units.

## Learning outcome

Calculate count active-prefix vocabulary logits and identify which quantities are measured, estimated or exact counts.

## Definition and formula

`N = V × Σ(active prefix length at each observation)`

The formula defines a checkable scalar result. Token positions are zero-based in the native tensor layouts, while the course numbers lessons from one. Keep count units distinct from timings, memory bytes and model quality.

## Fully worked example

Context 6, starting prefix 2, eight fixed steps: active lengths are 2,3,4,5,6,6,6,6,6. Their sum is 44; with V=260 there are 44×260 = 11,440 canonical-versus-trace logit comparisons.

Verify the expression by substituting each number, recording intermediate terms and keeping the same units in every multiplication or division.

## Practise the calculation

**Question:** What is the comparison count for V=100 and active lengths [1,2,3]?

<details><summary>Reveal the complete calculation</summary>

100×(1+2+3)=600 scalar comparisons.

</details>

## Native AI context

The companion [LLM Lesson 298](../10-native-ai/298-compare-entire-vocabulary-logit-vectors.md) applies this calculation to the native C23 stacked-decoder qualification. A count of compared scalars is a correctness-coverage measure, not a performance result. A ratio computed from illustrative numbers does not establish measured runtime behaviour.

## Continue learning

[Previous unit](173-evaluate-an-absolute-plus-relative-threshold.md) · [HTML study route](../../courses/maths-for-ai/numerical-qualification-mathematics.html)
