# Native AI Laboratory — Qualifying an Inference Benchmark

**Bits to Banking · Umicom Foundation**  
**Author:** Sammy Hegab  
**Level:** Advanced native Transformer development.

## Goal

Compare a reference growing-prefix decoder and a retained-K/V candidate using one model checkpoint, identical prompts and deterministic sampling. The laboratory combines the **canonical Framework services** rather than building a second neural-network implementation.

## Equipment

A C23 compiler, CMake and the Umicom Framework source tree are sufficient for the bounded CPU demonstration. GPU acceleration is not part of the experiment.

## Measurement contract

The Framework's `UmiAiTrainingStackedBenchmarkRun` accepts a borrowed decoder, a nonempty prompt and a bounded plan with 0–8 warmups and 1–21 measured pairs. It alternates execution order and rejects a pair if any generated token ID differs. It returns the median, minimum and maximum elapsed **nanoseconds** for complete generation calls, plus observed Framework work counters. Neither output represents TTFT, peak process RSS or a production speedup claim.

## Experiment

Begin with one layer and a short prompt. Repeat with two and three layers. Hold the checkpoint seed, prompt length and generated-token count fixed within each paired comparison. Create a separate case with a full context, which forces rollover after the first generated token. Observe whether the cached run continues to spend time in canonical rebuilds.

Reproduce Mathematics Units 163, 165, 167 and 168 by hand. Interpret measured times separately from `cachedAttentionQueryTokenLayerRows`. Preserve the raw environment details alongside the conclusions.

## Independent correctness checks

The paired benchmark verifies generated-token IDs. It does **not** independently compare every intermediate logit or K/V row. The established stacked decoder's numerical parity regressions are required for that stronger claim. Inspect both the one-step and session-level tests before interpreting new measurements.

## Questions

1. Why can the cached candidate be slower even when it evaluates fewer query rows?
2. Why is a full-window rollover different from an append while the prefix is growing?
3. What additional evidence would be needed before extending the result to GPU or enterprise serving?

<details><summary>Worked guidance</summary>

1. Session allocation, tape operations, cache copying, sampler work, cache rebuilds and CPU memory effects can exceed the savings.
2. With learned absolute positions, all retained tokens shift position after an eviction; their previous projections cannot be reused unchanged.
3. Independent numerical qualification, Release builds, representative workloads, measured resident memory, multiple independent runs and a precise hardware profile.

</details>
