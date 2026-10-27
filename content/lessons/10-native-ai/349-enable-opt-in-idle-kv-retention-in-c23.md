# Lesson 349 — Enable opt-in idle K/V retention in C23

**Bits to Banking · Umicom Foundation**  
**Author:** Sammy Hegab  
**Native implementation:** C23 · **Prerequisite:** Lesson 348; Mathematics Unit 211.

## Learning objectives

Understand the ownership, arithmetic and measurable behaviour of **enable opt-in idle k/v retention in c23**. Distinguish reusable allocated storage from a valid neural K/V history, and identify the invariant that protects a returning user or a concurrent session.

## 1. Explanation

Backward compatibility can be a measurable engineering property. The pool's original behaviour is allocate on acquisition and destroy on release. The extended policy starts with a limit of **zero idle stores**, so callers that do nothing new keep the old lifecycle. A caller explicitly enables retention using `UmiAiTrainingStackedKvPoolSetIdleRetention(pool, limit)`.

The limit cannot exceed the pool's maximum number of session slots. The public contract remains synchronous and caller-serialised. A pool with one shared checkpoint identity can only reuse a reset store for the same configured model. It does not perform cross-checkpoint sharing or infer whether a checkpoint is trusted.

## 2. Worked example

Create a pool with `maximumSessions=3` and `rawKvBudgetBytes=1024` for a 512-byte cache. With retention limit 0, release destroys the only store. Set the limit to 1, then acquire and release a store; the active count falls to zero and the idle count becomes one. The next acquisition can reuse this allocation; changing the policy back to 0 trims it after active leases have ended.

## 3. Relevant Umicom Framework contract

`UmiAiTrainingStackedKvPool` remains the public owner of session allocation. `UmiAiTrainingStackedKvStore` owns actual token rows and K/V tensors. The new optional `UmiAiTrainingStackedKvPoolSetIdleRetention` governs only the retention of **reset idle allocations**. Its default limit is zero. Use `UmiAiTrainingStackedKvPoolInspect` to observe active, idle and physical raw payload separately; a returning session must receive a fresh generation-stamped lease.

The pool never independently verifies neural numerical parity, never creates shared-prefix attention states and never guarantees secure forensic erasure. Explicitly verify the live model checkpoint before reusing any cached projections for inference. Evidence for model correctness requires comparison with the canonical Transformer.

## 4. Practical laboratory

Reproduce the worked example using the native C23 demonstration and regression tests under `framework/learning/native-ai-kv-pool-reuse/`. Record the prior lease, current lease, active session count, idle store count, physical raw K/V bytes, number of new store allocations and number of warm reuses. Test a rejection before assuming an operation is failure-atomic. The exercises use synthetic token IDs and FP32 arrays so they do not require personal or proprietary data.

## 5. Self-assessment

**Question:** Does merely calling `PoolCreate` enable idle retention?

<details><summary>Reveal the worked answer</summary>
<p>No. Retention is explicitly opt-in and defaults to zero, preserving the established lifecycle.</p>
</details>

## 6. Continue learning

[Previous lesson](348-understand-stale-leases-and-the-aba-problem.md) · [Mathematics Unit 211](../11-maths-for-ai/211-admit-warm-stores-under-a-raw-budget.md) · [Next lesson](350-keep-a-physical-cache-budget-across-idle-retention.md) · [Browser learning path](../../courses/llm-from-scratch/kv-reuse-learning-path.html)

*Service to Many Leads to Greatness.*
