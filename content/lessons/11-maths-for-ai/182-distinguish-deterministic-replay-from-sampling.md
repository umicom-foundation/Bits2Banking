# Mathematics for AI — Unit 182: Distinguish deterministic replay from sampling

**Bits to Banking · Umicom Foundation**  
**Author:** Sammy Hegab · **Prerequisite:** Arithmetic and the previous mathematics units.

## Learning outcome

Calculate distinguish deterministic replay from sampling and identify which quantities are measured, estimated or exact counts.

## Definition and formula

`replay comparison set = fixed IDs; sampled comparison set = generated IDs under one seed/policy`

The formula defines a checkable scalar result. Token positions are zero-based in the native tensor layouts, while the course numbers lessons from one. Keep count units distinct from timings, memory bytes and model quality.

## Fully worked example

Fixed replay with continuation [10,11,12] forces both mathematical paths through the same states. Seeded sampling verifies a second contract: the probability policy and RNG state deliver matching token IDs.

Verify the expression by substituting each number, recording intermediate terms and keeping the same units in every multiplication or division.

## Practise the calculation

**Question:** Does three-token fixed replay prove that top-p sampling consumes RNG state identically?

<details><summary>Reveal the complete calculation</summary>

No. Separate sampled-session tests are necessary.

</details>

## Native AI context

The companion [LLM Lesson 308](../10-native-ai/308-separate-fixed-token-replay-from-seeded-sampling.md) applies this calculation to the native C23 stacked-decoder qualification. A count of compared scalars is a correctness-coverage measure, not a performance result. A ratio computed from illustrative numbers does not establish measured runtime behaviour.

## Continue learning

[Previous unit](181-handle-zero-and-small-logit-scales.md) · [HTML study route](../../courses/maths-for-ai/numerical-qualification-mathematics.html)
