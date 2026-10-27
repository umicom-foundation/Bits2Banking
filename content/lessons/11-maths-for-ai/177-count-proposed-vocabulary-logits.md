# Mathematics for AI — Unit 177: Count proposed vocabulary logits

**Bits to Banking · Umicom Foundation**  
**Author:** Sammy Hegab · **Prerequisite:** Arithmetic and the previous mathematics units.

## Learning outcome

Calculate count proposed vocabulary logits and identify which quantities are measured, estimated or exact counts.

## Definition and formula

`candidate logit checks = growing-prefix steps × vocabulary size`

The formula defines a checkable scalar result. Token positions are zero-based in the native tensor layouts, while the course numbers lessons from one. Keep count units distinct from timings, memory bytes and model quality.

## Fully worked example

A prompt length two with context six has four available growing appends. Four proposed logits vectors at vocabulary 260 require 4×260=1,040 scalar comparisons. Rollover forwards are separate.

Verify the expression by substituting each number, recording intermediate terms and keeping the same units in every multiplication or division.

## Practise the calculation

**Question:** How many candidate logits are checked for context 5, prompt 4, V=100?

<details><summary>Reveal the complete calculation</summary>

One growing step remains, so 1×100=100.

</details>

## Native AI context

The companion [LLM Lesson 302](../10-native-ai/302-qualify-incremental-kv-projections-per-layer.md) applies this calculation to the native C23 stacked-decoder qualification. A count of compared scalars is a correctness-coverage measure, not a performance result. A ratio computed from illustrative numbers does not establish measured runtime behaviour.

## Continue learning

[Previous unit](176-calculate-layer-major-kv-scalar-offsets.md) · [HTML study route](../../courses/maths-for-ai/numerical-qualification-mathematics.html)
