# Mathematics for AI — Unit 180: Calculate full-window replacement counts

**Bits to Banking · Umicom Foundation**  
**Author:** Sammy Hegab · **Prerequisite:** Arithmetic and the previous mathematics units.

## Learning outcome

Calculate calculate full-window replacement counts and identify which quantities are measured, estimated or exact counts.

## Definition and formula

`growing=min(N, context − prefix); rollover=N − growing`

The formula defines a checkable scalar result. Token positions are zero-based in the native tensor layouts, while the course numbers lessons from one. Keep count units distinct from timings, memory bytes and model quality.

## Fully worked example

With prefix two, context six and nine continuations, four fit without eviction. Nine minus four equals five full-window replacements, each recomputing all contextual layers.

Verify the expression by substituting each number, recording intermediate terms and keeping the same units in every multiplication or division.

## Practise the calculation

**Question:** With full prompt length six, context six and four continuation tokens, how many replacements?

<details><summary>Reveal the complete calculation</summary>

Every transition evicts history, so four replacements.

</details>

## Native AI context

The companion [LLM Lesson 304](../10-native-ai/304-rebuild-all-layers-on-absolute-position-rollover.md) applies this calculation to the native C23 stacked-decoder qualification. A count of compared scalars is a correctness-coverage measure, not a performance result. A ratio computed from illustrative numbers does not establish measured runtime behaviour.

## Continue learning

[Previous unit](179-count-complete-cache-readback-values.md) · [HTML study route](../../courses/maths-for-ai/numerical-qualification-mathematics.html)
