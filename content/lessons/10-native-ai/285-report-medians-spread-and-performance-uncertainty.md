# Lesson 285 — Report medians, spread and performance uncertainty

**Bits to Banking · Umicom Foundation**  
**Author:** Sammy Hegab · **Implementation:** C23 / Assembly where justified  
**Prerequisites:** Transformer Lessons 265–280 and Mathematics Unit 165.

## Learning objective

A median is useful, but not a confidence interval, and a single benchmark run cannot justify a broad speedup claim.

## Understand the mechanism

Sort measurements before selecting their median. For an odd number of readings the median is the middle number; for an even number it is the average of the two central numbers. Preserve minimum and maximum as descriptive diagnostics but do not use them alone as the headline result. For serious performance decisions include interquartile range, confidence intervals or repeated independent-run distributions. Very short samples can mask tail latency and outliers.

Speed ratio must state its direction. For a reference median of 10 ms and a cached median of 8 ms, reference ÷ cached = 1.25; the candidate would be 1.25 times as fast **for that workload**, assuming the measurements are valid. The reverse value (8 ÷ 10 = 0.8) is a runtime ratio, not a speed ratio. If the candidate median exceeds the reference, the candidate is slower despite any theoretical arithmetic savings.

## Fully worked example

Canonical: [9, 10, 10, 11, 25] ms; cached: [8, 9, 10, 10, 12] ms. Both medians equal 10 ms; there is no measured median latency improvement. The 25 ms reference outlier remains important evidence about run variability and is not silently deleted.

## Native C23 laboratory

Plot or tabulate every paired latency alongside its order. Record units and conversion. If a summary contains only a single elapsed value, treat the result as exploratory rather than as a performance qualification.

The numerical and inference services are owned by **Umicom Framework**. Existing samplers, stacked decoder, K/V store and training tape remain authoritative. Where this lesson discusses a proposed capability, it is labelled as a design rather than a verified implementation. No numerical equivalence or runtime acceleration is inferred merely from an operation count.

## Connect the mathematics

See [Mathematics Unit 165](../11-maths-for-ai/165-compute-medians-and-spread.md) for the corresponding numerical reasoning and a worked exercise.

## Self-assessment

**Question:** Five paired runs show 9, 10, 11, 12 and 50 ms for reference. What is the median?

<details><summary>Reveal the worked answer</summary>

11 ms. The 50 ms sample remains part of the recorded dataset.

</details>

## References and further reading

- [IETF LLM benchmarking terminology draft (work in progress)](https://datatracker.ietf.org/doc/draft-gaikwad-llm-benchmarking-terminology/)
- [vLLM documentation — inference serving concepts](https://docs.vllm.ai/en/latest/)

## Continue learning

[Previous lesson](284-counterbalance-order-and-run-warmups.md) · [HTML study route](../../courses/llm-from-scratch/inference-benchmark-learning-path.html)

*Service to Many Leads to Greatness.*
