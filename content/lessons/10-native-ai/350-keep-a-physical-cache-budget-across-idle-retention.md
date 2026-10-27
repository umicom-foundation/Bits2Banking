# Lesson 350 — Keep a physical cache budget across idle retention

**Bits to Banking · Umicom Foundation**  
**Author:** Sammy Hegab  
**Native implementation:** C23 · **Prerequisite:** Lesson 349; Mathematics Unit 211.

## Learning objectives

Understand the ownership, arithmetic and measurable behaviour of **keep a physical cache budget across idle retention**. Distinguish reusable allocated storage from a valid neural K/V history, and identify the invariant that protects a returning user or a concurrent session.

## 1. Explanation

Idle buffers consume memory even when they have no active owner. A capacity policy that counts only active leases can over-admit by overlooking idle payload. The retention-aware pool therefore distinguishes `reservedRawKvBytes` (active) from `physicalRawKvBytes` (active + idle). A **cold** acquisition adds physical bytes and must pass the physical budget check. A **warm** acquisition moves an already counted idle reservation into the active column without increasing physical bytes.

A budget of zero in this API means “no raw payload ceiling”; it does not mean infinite RAM or a guarantee against allocation failure. `maximumSessions` still limits the number of concurrently active sessions.

## 2. Worked example

Two stores of 512 bytes fill a 1,024-byte budget. Release A into idle while B remains active: active=512, idle=512, physical=1,024. A new request can reuse A's idle store, returning to active=1,024, idle=0. A further independent allocation would exceed the configured budget and must fail without modifying the rejected output lease.

## 3. Relevant Umicom Framework contract

`UmiAiTrainingStackedKvPool` remains the public owner of session allocation. `UmiAiTrainingStackedKvStore` owns actual token rows and K/V tensors. The new optional `UmiAiTrainingStackedKvPoolSetIdleRetention` governs only the retention of **reset idle allocations**. Its default limit is zero. Use `UmiAiTrainingStackedKvPoolInspect` to observe active, idle and physical raw payload separately; a returning session must receive a fresh generation-stamped lease.

The pool never independently verifies neural numerical parity, never creates shared-prefix attention states and never guarantees secure forensic erasure. Explicitly verify the live model checkpoint before reusing any cached projections for inference. Evidence for model correctness requires comparison with the canonical Transformer.

## 4. Practical laboratory

Reproduce the worked example using the native C23 demonstration and regression tests under `framework/learning/native-ai-kv-pool-reuse/`. Record the prior lease, current lease, active session count, idle store count, physical raw K/V bytes, number of new store allocations and number of warm reuses. Test a rejection before assuming an operation is failure-atomic. The exercises use synthetic token IDs and FP32 arrays so they do not require personal or proprietary data.

## 5. Self-assessment

**Question:** Why must an idle retained store count against the physical budget?

<details><summary>Reveal the worked answer</summary>
<p>Its allocation remains present; it has not been returned to the allocator.</p>
</details>

## 6. Continue learning

[Previous lesson](349-enable-opt-in-idle-kv-retention-in-c23.md) · [Mathematics Unit 211](../11-maths-for-ai/211-admit-warm-stores-under-a-raw-budget.md) · [Next lesson](351-choose-how-many-idle-stores-to-keep.md) · [Browser learning path](../../courses/llm-from-scratch/kv-reuse-learning-path.html)

*Service to Many Leads to Greatness.*
