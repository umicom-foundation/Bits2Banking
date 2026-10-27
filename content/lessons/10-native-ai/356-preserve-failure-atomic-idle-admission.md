# Lesson 356 — Preserve failure-atomic idle admission

**Bits to Banking · Umicom Foundation**  
**Author:** Sammy Hegab  
**Native implementation:** C23 · **Prerequisite:** Lesson 355; Mathematics Unit 211.

## Learning objectives

Understand the ownership, arithmetic and measurable behaviour of **preserve failure-atomic idle admission**. Distinguish reusable allocated storage from a valid neural K/V history, and identify the invariant that protects a returning user or a concurrent session.

## 1. Explanation

A rejected allocation must not create a half-valid lease or silently consume the memory budget. The pool checks active slot count, total acquisition counter capacity, raw byte arithmetic and budget ceilings before publishing a new lease. If it must create a store, the existing K/V store validates its shape and identity first. Only after a successful store creation/inspection does the pool publish its slot and counters.

Idle reuse also has an explicit publication point. A malformed policy change—for example a retention count larger than `maximumSessions`—is rejected before trimming. Existing active leases and idled stores remain unchanged. Tests should fill output buffers with sentinels so accidental partial publication becomes observable.

## 2. Worked example

Under a 1,024-byte limit, two active 512-byte stores consume the whole budget. Request a third lease into an output initialised with `generation=9876`. The call returns `UMI_STATUS_CAPACITY_EXCEEDED`, and `generation` remains 9876. The active count, physical byte count, and the two valid leases are unchanged.

## 3. Relevant Umicom Framework contract

`UmiAiTrainingStackedKvPool` remains the public owner of session allocation. `UmiAiTrainingStackedKvStore` owns actual token rows and K/V tensors. The new optional `UmiAiTrainingStackedKvPoolSetIdleRetention` governs only the retention of **reset idle allocations**. Its default limit is zero. Use `UmiAiTrainingStackedKvPoolInspect` to observe active, idle and physical raw payload separately; a returning session must receive a fresh generation-stamped lease.

The pool never independently verifies neural numerical parity, never creates shared-prefix attention states and never guarantees secure forensic erasure. Explicitly verify the live model checkpoint before reusing any cached projections for inference. Evidence for model correctness requires comparison with the canonical Transformer.

## 4. Practical laboratory

Reproduce the worked example using the native C23 demonstration and regression tests under `framework/learning/native-ai-kv-pool-reuse/`. Record the prior lease, current lease, active session count, idle store count, physical raw K/V bytes, number of new store allocations and number of warm reuses. Test a rejection before assuming an operation is failure-atomic. The exercises use synthetic token IDs and FP32 arrays so they do not require personal or proprietary data.

## 5. Self-assessment

**Question:** What does the unchanged sentinel demonstrate?

<details><summary>Reveal the worked answer</summary>
<p>That a failed admission did not partially publish a new lease into caller-owned storage.</p>
</details>

## 6. Continue learning

[Previous lesson](355-measure-allocation-hits-and-reuse-limits.md) · [Mathematics Unit 211](../11-maths-for-ai/211-admit-warm-stores-under-a-raw-budget.md) · [Next lesson](357-keep-positional-rollover-correct-with-reused-stores.md) · [Browser learning path](../../courses/llm-from-scratch/kv-reuse-learning-path.html)

*Service to Many Leads to Greatness.*
