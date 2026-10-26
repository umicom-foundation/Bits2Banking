# Lesson 228 — Stream deterministic tokens from the cache

**Bits to Banking · Umicom Foundation**  
**Author:** Sammy Hegab  
**Language:** Native C23 · **Level:** Building beyond the introductory Transformer.

**Learning objective:** Connect retained K/V execution to the original deterministic top-k/top-p nucleus sampler.

## 1. The engineering question

A streaming session owns its sampling RNG and a pending generated token. The newest sampled token is not appended to the context until the next pull. This convention makes the current logits unambiguous and prevents an unnecessary final cache update.

## 2. Work through a concrete example

For prompt length two and three requested tokens: sample A from the prefilled prompt; append A and sample B; append B and sample C. C remains pending until another pull. Only two post-prefill store transitions occurred.

## 3. How Umicom Framework implements the idea

`UmiAiTrainingStackedKvIncrementalSessionNext` delegates sampling to `UmiAiTrainingSampleLogitsNucleus` with a copied RNG state, then commits the pending token and RNG only after the proposed K/V transition succeeds.

The relevant public contract is `umicom/ai/training/stacked_kv_incremental.h`. The native implementation and numerical tests belong to Umicom Framework; this manuscript does not introduce an alternative application-local training or inference service. The training tape owns mathematical operators and tensor lifetimes, while consumers use explicit C23 handles and status results.

## 4. Check the mathematical foundation

For a step-by-step explanation of the arithmetic, read [Mathematics Unit 120](../11-maths-for-ai/120-understand-seeded-nucleus-sampling.md). Keep tensor **shape**, **absolute position**, **model checkpoint identity** and **actual executed work** distinct when describing a cache.

## 5. Practice and verify

**Question:** Why does identical model state, prompt, sampling policy and seed need to reproduce the same sequence?

<details>
<summary>Reveal the worked explanation</summary>

Deterministic sampling makes parity comparisons meaningful. Without the same seed and policy, two correct executions could legitimately produce different tokens.

</details>

## 6. Limits and responsible interpretation

The 260-ID byte vocabulary is not a promise of well-formed UTF-8; treat byte output as binary and assemble characters through the existing Framework UTF-8 stream API.

A passing test in an isolated demonstration is not a production integration result. Evaluate against the actual Framework checkout and document any numerical or timing limitations before making deployment claims.

## Continue learning

[Previous lesson](227-reuse-projections-across-several-transformer-layers.md) · [Next lesson](229-handle-full-window-rollover-correctly.md) · [Browser learning path](../../courses/llm-from-scratch/incremental-attention-learning-path.html)

*Service to Many Leads to Greatness.*
