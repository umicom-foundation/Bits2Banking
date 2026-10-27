# Lesson 351 — Choose how many idle stores to keep

**Bits to Banking · Umicom Foundation**  
**Author:** Sammy Hegab  
**Native implementation:** C23 · **Prerequisite:** Lesson 350; Mathematics Unit 214.

## Learning objectives

Understand the ownership, arithmetic and measurable behaviour of **choose how many idle stores to keep**. Distinguish reusable allocated storage from a valid neural K/V history, and identify the invariant that protects a returning user or a concurrent session.

## 1. Explanation

An idle-retention policy balances allocation churn against memory held during quiet periods. A large idle limit may be useful for bursts of short requests but keeps more raw cache payload allocated. A small limit returns more capacity to the allocator at the expense of future cold allocation. The correct limit depends on request arrivals, memory pressure and independently measured allocation costs.

The pool has two upper bounds: maximum session slots and the raw K/V budget. It cannot retain more stores than either permits. Do not confuse a minimum cache-residency target with a need to hold sensitive session content: idle stores have already been reset.

## 2. Worked example

With six session slots and 512 bytes per store, a 2,048-byte raw budget can hold at most four physical stores. Configuring six idle slots cannot make six physical stores fit. If three leases are released and the retention limit is two, two can become idle and the remaining store is destroyed. Physical raw bytes then equal 1,024.

## 3. Relevant Umicom Framework contract

`UmiAiTrainingStackedKvPool` remains the public owner of session allocation. `UmiAiTrainingStackedKvStore` owns actual token rows and K/V tensors. The new optional `UmiAiTrainingStackedKvPoolSetIdleRetention` governs only the retention of **reset idle allocations**. Its default limit is zero. Use `UmiAiTrainingStackedKvPoolInspect` to observe active, idle and physical raw payload separately; a returning session must receive a fresh generation-stamped lease.

The pool never independently verifies neural numerical parity, never creates shared-prefix attention states and never guarantees secure forensic erasure. Explicitly verify the live model checkpoint before reusing any cached projections for inference. Evidence for model correctness requires comparison with the canonical Transformer.

## 4. Practical laboratory

Reproduce the worked example using the native C23 demonstration and regression tests under `framework/learning/native-ai-kv-pool-reuse/`. Record the prior lease, current lease, active session count, idle store count, physical raw K/V bytes, number of new store allocations and number of warm reuses. Test a rejection before assuming an operation is failure-atomic. The exercises use synthetic token IDs and FP32 arrays so they do not require personal or proprietary data.

## 5. Self-assessment

**Question:** Which constraint limits idle stores when the slot limit is 6 and the budget permits only 4 full stores?

<details><summary>Reveal the worked answer</summary>
<p>The raw budget limits physical residency to 4 stores, even though six lease slots exist.</p>
</details>

## 6. Continue learning

[Previous lesson](350-keep-a-physical-cache-budget-across-idle-retention.md) · [Mathematics Unit 214](../11-maths-for-ai/214-combine-session-slot-and-memory-ceilings.md) · [Next lesson](352-trim-idle-stores-without-interrupting-active-work.md) · [Browser learning path](../../courses/llm-from-scratch/kv-reuse-learning-path.html)

*Service to Many Leads to Greatness.*
