# Lesson 353 — Retain checkpoint boundaries during store reuse

**Bits to Banking · Umicom Foundation**  
**Author:** Sammy Hegab  
**Native implementation:** C23 · **Prerequisite:** Lesson 352; Mathematics Unit 215.

## Learning objectives

Understand the ownership, arithmetic and measurable behaviour of **retain checkpoint boundaries during store reuse**. Distinguish reusable allocated storage from a valid neural K/V history, and identify the invariant that protects a returning user or a concurrent session.

## 1. Explanation

Model identity is more than the tensor shape. Two checkpoints can have the same number of layers, channels and heads yet produce different projections. A cache store bound to one checkpoint cannot be transplanted into a second model merely because its buffer fits. The pool is created with a checkpoint digest, and every owned store inherits that identity. A reused idle store is still associated with that same immutable pool configuration.

A SHA-256 digest is a content identity, not proof that the publisher is trusted. Active model use must independently verify the current decoder identity; the pool does not inspect or pin a live neural model. A new checkpoint ordinarily needs a separate pool or an explicit migration policy that validates the new checkpoint and discards incompatible caches.

## 2. Worked example

A pool records digest A and releases a store to idle. A client supplies digest B to `UmiAiTrainingStackedKvPoolCheckIdentity`. If the bytes differ, the operation returns `UMI_STATUS_INVALID_STATE` even if both models have eight channels and four context positions. Reusing idle memory must never become a shortcut around this check.

## 3. Relevant Umicom Framework contract

`UmiAiTrainingStackedKvPool` remains the public owner of session allocation. `UmiAiTrainingStackedKvStore` owns actual token rows and K/V tensors. The new optional `UmiAiTrainingStackedKvPoolSetIdleRetention` governs only the retention of **reset idle allocations**. Its default limit is zero. Use `UmiAiTrainingStackedKvPoolInspect` to observe active, idle and physical raw payload separately; a returning session must receive a fresh generation-stamped lease.

The pool never independently verifies neural numerical parity, never creates shared-prefix attention states and never guarantees secure forensic erasure. Explicitly verify the live model checkpoint before reusing any cached projections for inference. Evidence for model correctness requires comparison with the canonical Transformer.

## 4. Practical laboratory

Reproduce the worked example using the native C23 demonstration and regression tests under `framework/learning/native-ai-kv-pool-reuse/`. Record the prior lease, current lease, active session count, idle store count, physical raw K/V bytes, number of new store allocations and number of warm reuses. Test a rejection before assuming an operation is failure-atomic. The exercises use synthetic token IDs and FP32 arrays so they do not require personal or proprietary data.

## 5. Self-assessment

**Question:** Does matching tensor geometry demonstrate that cached projections can be shared across checkpoints?

<details><summary>Reveal the worked answer</summary>
<p>No. Projection values depend on checkpoint parameters and on the complete position/history contract.</p>
</details>

## 6. Continue learning

[Previous lesson](352-trim-idle-stores-without-interrupting-active-work.md) · [Mathematics Unit 215](../11-maths-for-ai/215-measure-the-peak-physical-memory-watermark.md) · [Next lesson](354-respect-borrowed-pointer-lifetimes.md) · [Browser learning path](../../courses/llm-from-scratch/kv-reuse-learning-path.html)

*Service to Many Leads to Greatness.*
