# Lesson 246 — Benchmark one-query attention with fair controls

**Bits to Banking · Umicom Foundation**  
**Course lead:** Sammy Hegab  
**Language:** Native C23 and Assembly where justified · **Level:** Advanced native Transformer engineering.

**Learning objective:** Plan Release comparisons that separate kernel work from whole-session latency.

## 1. Understand the problem

A single-query kernel may reduce executed attention-query work while leaving memory bandwidth, projection costs, tokenisation, output callbacks and context rebuilds unchanged. Benchmarking only the kernel can therefore exaggerate the impact on end-to-end generation.

Use identical model bytes, prompt IDs, context length, generation policy, seed, CPU, thread count and precision. Warm both paths; use paired measurements with alternating order when practical. Report a distribution (median and variability), not a single best run. Keep compilation options and machine power state recorded. Check numerical parity **before** timing.

## 2. Fully worked example

Suppose five paired full-session measurements in milliseconds are reference `[4.4,4.5,4.3,4.6,4.4]`, candidate `[4.1,4.2,4.4,4.2,4.1]`. The medians are `4.4` and `4.2` ms: an illustrative median ratio `4.4/4.2≈1.0476`, about 4.8% faster for this tiny sample. The pair at position three is slower for the candidate. Neither result predicts performance on other contexts, hardware or rollover ratios.

## 3. Engineering verification and connection to Umicom Framework

Record `queries computed`, `K/V rows read`, `bytes transferred`, `time per generated token`, `rollovers`, `allocation count` and confidence or variability estimates. Explicitly label counters that are estimates rather than instrumented values. Do not claim a measured improvement until the real integrated build passes and a controlled Release comparison demonstrates it.

The existing Umicom Framework decoder, training tape and K/V ownership services remain the authority for implementation. This educational lesson specifies behaviour; it does **not** introduce a competing application-local inference engine or claim that the proposed single-query kernel is already merged or performance-qualified.

## 4. Mathematics connection

Review [Mathematics for AI — Unit 136](../11-maths-for-ai/136-read-paired-latency-measurements.md). The mathematics companion includes a calculation that can be verified independently of a compiled model.

## 5. Exercise

**Question:** Why does a two-token prompt benchmark not establish production throughput?

<details>
<summary>Reveal the worked answer</summary>

It may avoid eviction, cold-cache effects, larger working sets and output overhead; its mix of work differs from longer real workloads.

</details>

## 6. Acceptance note

Educational calculations and design specifications are not substitutes for running the complete numerical and memory-safety qualification suite against the actual Windows and other supported Framework builds. Do not claim an inference speedup from hypothetical arithmetic counts.

## Continue learning

[Previous lesson](245-design-adversarial-single-query-fixtures.md) · [Browser learning path](../../courses/llm-from-scratch/single-query-attention-learning-path.html) · [Next lesson](247-plan-portable-cpu-kernel-optimisation.md)

*Service to Many Leads to Greatness.*
