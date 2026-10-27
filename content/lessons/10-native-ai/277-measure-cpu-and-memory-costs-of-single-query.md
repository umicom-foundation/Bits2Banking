# Lesson 277 — Measure CPU time and memory costs of a single query

**Bits to Banking · Umicom Foundation**  
**Author:** Sammy Hegab  
**Course:** Building an LLM from Scratch · Native C23

**Learning objective:** Separate theoretical work reduction from actual execution costs.

## 1. Concept and motivation

A forward-only single-query kernel still reads every visible K/V row and performs dot products and value accumulation. For dense multi-head attention with model width `C` and `T` retained rows, the query-key product and weighted sum each involve approximately `T*C` scalar terms. In a small educational model, allocator overhead and cache handling may dominate arithmetic; an optimised kernel can be slower despite doing fewer query rows.

## 2. Worked example

At `T=6` and `C=8`, the query performs `48` scalar Q×K terms and `48` scalar probability×V terms. Its row-oriented temporary buffers are O(T+C), while K/V storage is O(T*C) for each layer. The previous multi-row tape implementation also created intermediate nodes for unused earlier queries.

## 3. Native Framework implementation and evidence

Benchmark warm and cold runs separately. Record median and upper-tail latency, compiler, build type, hardware, seed, number of rollovers and allocations. Measure whole-session tokens/s as well as the isolated kernel; both can be legitimate results with different conclusions.

## 4. Mathematical companion

Read [Mathematics Unit 157 — Estimate KV read bandwidth floors](../11-maths-for-ai/157-estimate-kv-read-bandwidth-floor.md). Check each numerical assumption against the example above before running a program.

## 5. Exercise

**Question:** Why might removing four unnecessary query rows fail to improve wall-clock performance?

<details>
<summary>Reveal the worked answer</summary>

The reduction can be overshadowed by allocations, memory copies, cache misses and the rest of the Transformer computation.

</details>

## 6. Interpretation

Do not confuse operation counters, memory-byte estimates and observed timings.

## Continue learning

[276 — Build a multi-axis integration-test matrix](276-build-a-multi-axis-integration-test-matrix.md) · [278 — Treat MQA and GQA as distinct model contracts](278-keep-multi-query-and-grouped-query-as-new-contracts.md) · [Browser learning path](../../courses/llm-from-scratch/integrated-attention-learning-path.html)
