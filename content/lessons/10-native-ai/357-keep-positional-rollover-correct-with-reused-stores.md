# Lesson 357 — Keep positional rollover correct with reused stores

**Bits to Banking · Umicom Foundation**  
**Author:** Sammy Hegab  
**Native implementation:** C23 · **Prerequisite:** Lesson 356; Mathematics Unit 205.

## Learning objectives

Understand the ownership, arithmetic and measurable behaviour of **keep positional rollover correct with reused stores**. Distinguish reusable allocated storage from a valid neural K/V history, and identify the invariant that protects a returning user or a concurrent session.

## 1. Explanation

Allocation reuse and Transformer KV reuse are different operations. When an existing session grows within its fixed learned-position window, its new token may append to the canonical store using unchanged positional embeddings. Once the context is full, shifting the window changes positions and often the upper-layer history. The correct action is a complete canonical K/V recomputation and replacement across **every** layer.

Idle reuse happens only between sessions after Reset. It never changes the within-session positional policy. The existing `UmiAiTrainingStackedKvStoreReplaceRolled` remains authoritative for full-window replacement; no ring-buffer optimisation is introduced by idle retention.

## 2. Worked example

For context length four, a session processes [10,11,12,13], then wants to include token 14. The only valid full-window state has IDs [11,12,13,14] and newly recomputed K/V projections for all four positions and all layers. If that session is later released, its entire store is reset before another session can obtain the allocation. The second session starts from an empty K/V history.

## 3. Relevant Umicom Framework contract

`UmiAiTrainingStackedKvPool` remains the public owner of session allocation. `UmiAiTrainingStackedKvStore` owns actual token rows and K/V tensors. The new optional `UmiAiTrainingStackedKvPoolSetIdleRetention` governs only the retention of **reset idle allocations**. Its default limit is zero. Use `UmiAiTrainingStackedKvPoolInspect` to observe active, idle and physical raw payload separately; a returning session must receive a fresh generation-stamped lease.

The pool never independently verifies neural numerical parity, never creates shared-prefix attention states and never guarantees secure forensic erasure. Explicitly verify the live model checkpoint before reusing any cached projections for inference. Evidence for model correctness requires comparison with the canonical Transformer.

## 4. Practical laboratory

Reproduce the worked example using the native C23 demonstration and regression tests under `framework/learning/native-ai-kv-pool-reuse/`. Record the prior lease, current lease, active session count, idle store count, physical raw K/V bytes, number of new store allocations and number of warm reuses. Test a rejection before assuming an operation is failure-atomic. The exercises use synthetic token IDs and FP32 arrays so they do not require personal or proprietary data.

## 5. Self-assessment

**Question:** Does keeping a physical buffer alive after Release allow the next session to skip full-context prefill?

<details><summary>Reveal the worked answer</summary>
<p>No. The contents are reset, and every prompt must be evaluated through the legitimate model computations.</p>
</details>

## 6. Continue learning

[Previous lesson](356-preserve-failure-atomic-idle-admission.md) · [Mathematics Unit 205](../11-maths-for-ai/205-count-projected-rows-at-a-full-window-rollover.md) · [Next lesson](358-distinguish-reset-hygiene-from-cryptographic-erasure.md) · [Browser learning path](../../courses/llm-from-scratch/kv-reuse-learning-path.html)

*Service to Many Leads to Greatness.*
