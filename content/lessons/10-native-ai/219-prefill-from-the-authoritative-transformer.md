# Lesson 219 — Prefill from the authoritative Transformer

**Bits to Banking · Umicom Foundation**  
**Author:** Sammy Hegab  
**Language:** Native C23 · **Level:** Building beyond the introductory Transformer.

**Learning objective:** Explain a safe first inference step using the original stacked model and approved checkpoint.

## 1. The engineering question

A new inference session starts by capturing the checkpoint SHA-256 from the canonical stacked codec. The first prompt is evaluated by the original full-context projection trace. Every layer contributes K and V rows, indexed as layer, token, channel, to the existing store.

## 2. Work through a concrete example

For a prompt of length 2, three layers and eight channels, prefill transfers 3×2×8 = 48 values for keys and the same 48 for values. The original trace may still compute an entire padded context, so the prefill workload is not merely two token-layer rows.

## 3. How Umicom Framework implements the idea

`UmiAiTrainingStackedKvIncrementalSessionCreate` obtains model identity, validates the existing nucleus policy, invokes the canonical trace and performs one atomic `UmiAiTrainingStackedKvStorePrefill`. The first requested output is sampled from the last real prompt row.

The relevant public contract is `umicom/ai/training/stacked_kv_incremental.h`. The native implementation and numerical tests belong to Umicom Framework; this manuscript does not introduce an alternative application-local training or inference service. The training tape owns mathematical operators and tensor lifetimes, while consumers use explicit C23 handles and status results.

## 4. Check the mathematical foundation

For a step-by-step explanation of the arithmetic, read [Mathematics Unit 113](../11-maths-for-ai/113-count-multilayer-qkv-tensor-shapes.md). Keep tensor **shape**, **absolute position**, **model checkpoint identity** and **actual executed work** distinct when describing a cache.

## 5. Practice and verify

**Question:** For a context of 6, prompt length 2 and 2 Transformer layers, how many full-context token-layer rows are executed by the initial trace?

<details>
<summary>Reveal the worked explanation</summary>

6 context positions × 2 layers = 12 layer-token rows. This is the actual prefill work, not the four rows held in the cache.

</details>

## 6. Limits and responsible interpretation

The prefill records borrowed identity; SHA-256 agreement detects changes but is not a publisher signature. A source-governance decision remains separate.

A passing test in an isolated demonstration is not a production integration result. Evaluate against the actual Framework checkout and document any numerical or timing limitations before making deployment claims.

## Continue learning

[Previous lesson](218-prove-unchanged-prefix-positions.md) · [Next lesson](220-reuse-cached-key-and-value-projections.md) · [Browser learning path](../../courses/llm-from-scratch/incremental-attention-learning-path.html)

*Service to Many Leads to Greatness.*
