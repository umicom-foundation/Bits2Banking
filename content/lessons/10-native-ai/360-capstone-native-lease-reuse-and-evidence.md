# Lesson 360 — Capstone: native lease reuse and evidence

**Bits to Banking · Umicom Foundation**  
**Author:** Sammy Hegab  
**Native implementation:** C23 · **Prerequisite:** Lesson 359; Mathematics Unit 220.

## Learning objectives

Understand the ownership, arithmetic and measurable behaviour of **capstone: native lease reuse and evidence**. Distinguish reusable allocated storage from a valid neural K/V history, and identify the invariant that protects a returning user or a concurrent session.

## 1. Explanation

A credible native cache-reuse demonstration combines correctness, memory accounting and performance into one reproducible experiment. Begin with an unchanged FP32 decoder shape and checkpoint identity. Confirm that the default retention policy is zero. Enable one idle slot, run one session that prefills and appends real K/V projections, release it, and verify that the old lease is invalid. Reacquire and inspect an empty K/V store with a new generation.

Next fill the configured memory budget, make an additional request fail without changing its output, then trim idle capacity while keeping one active lease. Finally verify that the original context-rollover tests still pass. **Evidence is layered:** store/pool tests establish ownership, canonical decoder comparisons establish numerical equivalence, and controlled whole-request timings establish any speed effect. Passing one layer is not a substitute for the other two.

## 2. Worked example

With 2 layers, 4 context positions and 8 channels, each FP32 store reserves 512 bytes. Configure 3 session slots but a 1,024-byte raw budget. Allocate A and B. Release A into idle, check active=512, idle=512, physical=1,024. Reuse A's slot for C; check that C has a fresh generation and empty token history. Release B, reduce idle retention to zero and confirm that C remains active. Complete C and verify physical returns to zero.

## 3. Relevant Umicom Framework contract

`UmiAiTrainingStackedKvPool` remains the public owner of session allocation. `UmiAiTrainingStackedKvStore` owns actual token rows and K/V tensors. The new optional `UmiAiTrainingStackedKvPoolSetIdleRetention` governs only the retention of **reset idle allocations**. Its default limit is zero. Use `UmiAiTrainingStackedKvPoolInspect` to observe active, idle and physical raw payload separately; a returning session must receive a fresh generation-stamped lease.

The pool never independently verifies neural numerical parity, never creates shared-prefix attention states and never guarantees secure forensic erasure. Explicitly verify the live model checkpoint before reusing any cached projections for inference. Evidence for model correctness requires comparison with the canonical Transformer.

## 4. Practical laboratory

Reproduce the worked example using the native C23 demonstration and regression tests under `framework/learning/native-ai-kv-pool-reuse/`. Record the prior lease, current lease, active session count, idle store count, physical raw K/V bytes, number of new store allocations and number of warm reuses. Test a rejection before assuming an operation is failure-atomic. The exercises use synthetic token IDs and FP32 arrays so they do not require personal or proprietary data.

## 5. Self-assessment

**Question:** Which distinct measurements and tests would justify a public claim that idle reuse is faster?

<details><summary>Reveal the worked answer</summary>
<p>A passing memory/lease regression suite, full canonical model correctness evidence, and comparable measured Release timings showing the improvement for the stated workload and hardware.</p>
</details>

## 6. Continue learning

[Previous lesson](359-benchmark-cold-and-warm-session-lifecycles.md) · [Mathematics Unit 220](../11-maths-for-ai/220-complete-a-cache-reuse-accounting-table.md) · [Browser learning path](../../courses/llm-from-scratch/kv-reuse-learning-path.html)

*Service to Many Leads to Greatness.*
