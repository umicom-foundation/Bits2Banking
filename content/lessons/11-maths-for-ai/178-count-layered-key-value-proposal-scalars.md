# Mathematics for AI — Unit 178: Count layered key/value proposal scalars

**Bits to Banking · Umicom Foundation**  
**Author:** Sammy Hegab · **Prerequisite:** Arithmetic and the previous mathematics units.

## Learning outcome

Calculate count layered key/value proposal scalars and identify which quantities are measured, estimated or exact counts.

## Definition and formula

`candidate K/V checks = steps × layers × channels × 2`

The formula defines a checkable scalar result. Token positions are zero-based in the native tensor layouts, while the course numbers lessons from one. Keep count units distinct from timings, memory bytes and model quality.

## Fully worked example

Four growing steps, three layers and eight channels give 4×3×8×2=192 scalar checks. The factor two accounts for both keys and values.

Verify the expression by substituting each number, recording intermediate terms and keeping the same units in every multiplication or division.

## Practise the calculation

**Question:** How many K/V scalars are proposed for 5 steps, 4 layers and 16 channels?

<details><summary>Reveal the complete calculation</summary>

5×4×16×2=640.

</details>

## Native AI context

The companion [LLM Lesson 302](../10-native-ai/302-qualify-incremental-kv-projections-per-layer.md) applies this calculation to the native C23 stacked-decoder qualification. A count of compared scalars is a correctness-coverage measure, not a performance result. A ratio computed from illustrative numbers does not establish measured runtime behaviour.

## Continue learning

[Previous unit](177-count-proposed-vocabulary-logits.md) · [HTML study route](../../courses/maths-for-ai/numerical-qualification-mathematics.html)
