# Lesson 345 — Why K/V store allocation churn matters

**Bits to Banking · Umicom Foundation**  
**Author:** Sammy Hegab  
**Native implementation:** C23 · **Prerequisite:** Lesson 344; Mathematics Unit 209.

## Learning objectives

Understand the ownership, arithmetic and measurable behaviour of **why k/v store allocation churn matters**. Distinguish reusable allocated storage from a valid neural K/V history, and identify the invariant that protects a returning user or a concurrent session.

## 1. Explanation

An autoregressive decoder repeatedly executes the same Transformer for successive tokens. Apart from the neural calculations, serving software also acquires and releases buffers. A session that opens for each request can trigger heap allocation, page initialisation, and cleanup even when the model shape is identical. These costs are *allocation churn*. They are separate from attention FLOPs and separate from context-rollover recomputation.

An existing `UmiAiTrainingStackedKvPool` owns a K/V store for each admitted session. In its default lifecycle, every successful `Acquire` creates a store and `Release` destroys it. This is an explicit and predictable baseline. An *idle retention* mode may keep a **reset** store's allocation after the lease ends, allowing a later session of the same shape to use that storage. It must not reuse the departed session's K/V values.

## 2. Worked example

Consider 100 sequential requests to an identical two-layer model, each requiring a 512-byte cache. The original policy performs up to 100 store allocations after pool creation. If one store is retained and every later request reuses it, 1 allocation and 99 reuses are possible. That is a count of store allocations—not a claim about wall-clock time, heap fragmentation or the model's quality.

## 3. Relevant Umicom Framework contract

`UmiAiTrainingStackedKvPool` remains the public owner of session allocation. `UmiAiTrainingStackedKvStore` owns actual token rows and K/V tensors. The new optional `UmiAiTrainingStackedKvPoolSetIdleRetention` governs only the retention of **reset idle allocations**. Its default limit is zero. Use `UmiAiTrainingStackedKvPoolInspect` to observe active, idle and physical raw payload separately; a returning session must receive a fresh generation-stamped lease.

The pool never independently verifies neural numerical parity, never creates shared-prefix attention states and never guarantees secure forensic erasure. Explicitly verify the live model checkpoint before reusing any cached projections for inference. Evidence for model correctness requires comparison with the canonical Transformer.

## 4. Practical laboratory

Reproduce the worked example using the native C23 demonstration and regression tests under `framework/learning/native-ai-kv-pool-reuse/`. Record the prior lease, current lease, active session count, idle store count, physical raw K/V bytes, number of new store allocations and number of warm reuses. Test a rejection before assuming an operation is failure-atomic. The exercises use synthetic token IDs and FP32 arrays so they do not require personal or proprietary data.

## 5. Self-assessment

**Question:** Why is it incorrect to report a 100× generation-speed improvement from a 100-to-1 allocation reduction?

<details><summary>Reveal the worked answer</summary>
<p>Generation still performs model computation and may rebuild complete contexts; allocation was only one component of the measured workload.</p>
</details>

## 6. Continue learning

[Previous lesson](344-complete-the-multi-session-kv-lifecycle-capstone.md) · [Mathematics Unit 209](../11-maths-for-ai/209-derive-raw-kv-payload-per-store.md) · [Next lesson](346-separate-active-idle-and-physical-kv-bytes.md) · [Browser learning path](../../courses/llm-from-scratch/kv-reuse-learning-path.html)

*Service to Many Leads to Greatness.*
