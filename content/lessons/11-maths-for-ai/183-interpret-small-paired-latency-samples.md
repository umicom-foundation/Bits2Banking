# Mathematics for AI — Unit 183: Interpret small paired latency samples

**Bits to Banking · Umicom Foundation**  
**Author:** Sammy Hegab · **Prerequisite:** Arithmetic and the previous mathematics units.

## Learning outcome

Calculate interpret small paired latency samples and identify which quantities are measured, estimated or exact counts.

## Definition and formula

`speed ratio = median(reference durations)/median(candidate durations)`

The formula defines a checkable scalar result. Token positions are zero-based in the native tensor layouts, while the course numbers lessons from one. Keep count units distinct from timings, memory bytes and model quality.

## Fully worked example

Reference trials [4.8, 5.1, 4.9] ms have median 4.9 ms; candidate [5.2, 4.9, 5.3] ms have median 5.2 ms. The ratio is 4.9/5.2 ≈ 0.9423; the candidate is slower in this small illustrative set.

Verify the expression by substituting each number, recording intermediate terms and keeping the same units in every multiplication or division.

## Practise the calculation

**Question:** If reference median is 10 ms and candidate median is 8 ms, what is the ratio?

<details><summary>Reveal the complete calculation</summary>

10/8=1.25. This is a 1.25× measured median ratio for that controlled sample, not a universal speedup.

</details>

## Native AI context

The companion [LLM Lesson 310](../10-native-ai/310-separate-numerical-qualification-from-performance.md) applies this calculation to the native C23 stacked-decoder qualification. A count of compared scalars is a correctness-coverage measure, not a performance result. A ratio computed from illustrative numbers does not establish measured runtime behaviour.

## Continue learning

[Previous unit](182-distinguish-deterministic-replay-from-sampling.md) · [HTML study route](../../courses/maths-for-ai/numerical-qualification-mathematics.html)
