# Lesson 346 — Separate active, idle and physical K/V bytes

**Bits to Banking · Umicom Foundation**  
**Author:** Sammy Hegab  
**Native implementation:** C23 · **Prerequisite:** Lesson 345; Mathematics Unit 210.

## Learning objectives

Understand the ownership, arithmetic and measurable behaviour of **separate active, idle and physical k/v bytes**. Distinguish reusable allocated storage from a valid neural K/V history, and identify the invariant that protects a returning user or a concurrent session.

## 1. Explanation

Capacity planning often fails when a single word such as “reserved” is used for several different quantities. **Active reservation** is the raw payload owned by currently valid leases. **Idle retention** is the raw payload associated with reset stores that still occupy storage. **Physical payload held by the pool** is their sum. Token occupancy is yet another quantity: a full reserved store can be empty of live token rows.

The pool reports these quantities separately. Process RSS will generally be larger, because it includes allocator metadata, the model, the training tape, stacks, libraries and other temporary buffers. No conversion from the raw K/V figure to precise process memory is valid without measurement.

## 2. Worked example

Each store reserves 512 bytes. With two active stores and one reset idle store, active raw bytes = 1,024, idle raw bytes = 512 and physical raw bytes = 1,536. If the idle store is reused, active becomes 1,536, idle becomes zero, and physical remains **1,536**. No new K/V payload allocation was necessary for that acquisition.

## 3. Relevant Umicom Framework contract

`UmiAiTrainingStackedKvPool` remains the public owner of session allocation. `UmiAiTrainingStackedKvStore` owns actual token rows and K/V tensors. The new optional `UmiAiTrainingStackedKvPoolSetIdleRetention` governs only the retention of **reset idle allocations**. Its default limit is zero. Use `UmiAiTrainingStackedKvPoolInspect` to observe active, idle and physical raw payload separately; a returning session must receive a fresh generation-stamped lease.

The pool never independently verifies neural numerical parity, never creates shared-prefix attention states and never guarantees secure forensic erasure. Explicitly verify the live model checkpoint before reusing any cached projections for inference. Evidence for model correctness requires comparison with the canonical Transformer.

## 4. Practical laboratory

Reproduce the worked example using the native C23 demonstration and regression tests under `framework/learning/native-ai-kv-pool-reuse/`. Record the prior lease, current lease, active session count, idle store count, physical raw K/V bytes, number of new store allocations and number of warm reuses. Test a rejection before assuming an operation is failure-atomic. The exercises use synthetic token IDs and FP32 arrays so they do not require personal or proprietary data.

## 5. Self-assessment

**Question:** Does `retainedTokens == 0` imply that physical raw storage is zero?

<details><summary>Reveal the worked answer</summary>
<p>No. A reset store still reserves space for its maximum context and every layer while its allocation is retained.</p>
</details>

## 6. Continue learning

[Previous lesson](345-why-kv-store-allocation-churn-matters.md) · [Mathematics Unit 210](../11-maths-for-ai/210-prove-active-plus-idle-equals-physical-payload.md) · [Next lesson](347-reset-before-making-cache-storage-reusable.md) · [Browser learning path](../../courses/llm-from-scratch/kv-reuse-learning-path.html)

*Service to Many Leads to Greatness.*
