# Lesson 359 — Benchmark cold and warm session lifecycles

**Bits to Banking · Umicom Foundation**  
**Author:** Sammy Hegab  
**Native implementation:** C23 · **Prerequisite:** Lesson 358; Mathematics Unit 218.

## Learning objectives

Understand the ownership, arithmetic and measurable behaviour of **benchmark cold and warm session lifecycles**. Distinguish reusable allocated storage from a valid neural K/V history, and identify the invariant that protects a returning user or a concurrent session.

## 1. Explanation

A performance investigation must separate cold allocation, warm reacquisition, prompt prefill, token decoding, context rollover and pool destruction. Execute controlled *paired* experiments with the same model checkpoint, prompts, generation seeds and compiler optimisation level. Alternate warm-first and cold-first order to reduce bias from CPU clock changes and operating-system scheduling. Report medians and spread, not a single best-looking result.

The pool statistics can confirm that an experiment truly exercised warm reuse (`idleStoreReuses > 0`), while the existing `UmiAiTrainingStackedInferenceBenchmark` can measure complete inference. Avoid comparing a Debug run against a Release run or applying a heuristic speedup multiplier to allocation counters.

## 2. Worked example

Suppose five Release cold acquisition timings are [0.12,0.10,0.11,0.13,0.14] ms and warm timings are [0.05,0.06,0.05,0.07,0.05] ms. Medians are 0.12 ms and 0.05 ms for *acquisition only*. To know whether a user experiences faster responses, measure complete requests and account for prefill and generated-token work.

## 3. Relevant Umicom Framework contract

`UmiAiTrainingStackedKvPool` remains the public owner of session allocation. `UmiAiTrainingStackedKvStore` owns actual token rows and K/V tensors. The new optional `UmiAiTrainingStackedKvPoolSetIdleRetention` governs only the retention of **reset idle allocations**. Its default limit is zero. Use `UmiAiTrainingStackedKvPoolInspect` to observe active, idle and physical raw payload separately; a returning session must receive a fresh generation-stamped lease.

The pool never independently verifies neural numerical parity, never creates shared-prefix attention states and never guarantees secure forensic erasure. Explicitly verify the live model checkpoint before reusing any cached projections for inference. Evidence for model correctness requires comparison with the canonical Transformer.

## 4. Practical laboratory

Reproduce the worked example using the native C23 demonstration and regression tests under `framework/learning/native-ai-kv-pool-reuse/`. Record the prior lease, current lease, active session count, idle store count, physical raw K/V bytes, number of new store allocations and number of warm reuses. Test a rejection before assuming an operation is failure-atomic. The exercises use synthetic token IDs and FP32 arrays so they do not require personal or proprietary data.

## 5. Self-assessment

**Question:** Why must the scope of timing be stated alongside the measured median?

<details><summary>Reveal the worked answer</summary>
<p>A 0.07 ms acquisition saving does not imply that end-to-end generation, network response or model prefill improved by the same proportion.</p>
</details>

## 6. Continue learning

[Previous lesson](358-distinguish-reset-hygiene-from-cryptographic-erasure.md) · [Mathematics Unit 218](../11-maths-for-ai/218-compare-warm-and-cold-median-latencies.md) · [Next lesson](360-capstone-native-lease-reuse-and-evidence.md) · [Browser learning path](../../courses/llm-from-scratch/kv-reuse-learning-path.html)

*Service to Many Leads to Greatness.*
