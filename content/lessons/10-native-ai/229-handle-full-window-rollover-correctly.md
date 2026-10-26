# Lesson 229 — Handle full-window rollover correctly

**Bits to Banking · Umicom Foundation**  
**Author:** Sammy Hegab  
**Language:** Native C23 · **Level:** Building beyond the introductory Transformer.

**Learning objective:** Explain why learned absolute positions require a fresh canonical computation after context eviction.

## 1. The engineering question

When the retained context is full, appending a token drops the oldest token. Survivors move to new position indices and their token-plus-position embeddings change. Upper-layer hidden states may also have incorporated the old history. Reusing their old K/V would no longer implement the current model.

## 2. Work through a concrete example

For a four-token cache [A,B,C,D], appending E requires [B,C,D,E]. The Framework traces the full new context, replaces every layer’s K/V in one transaction, and samples from the new last-position logits. It does not apply a simple circular-buffer shift of old vectors.

## 3. How Umicom Framework implements the idea

The incremental session uses `UmiAiTrainingStackedDecoderTraceProjections` and `UmiAiTrainingStackedKvStoreReplaceRolled`. The latter checks exact shifted token IDs and validates the complete replacement before publication.

The relevant public contract is `umicom/ai/training/stacked_kv_store.h`. The native implementation and numerical tests belong to Umicom Framework; this manuscript does not introduce an alternative application-local training or inference service. The training tape owns mathematical operators and tensor lifetimes, while consumers use explicit C23 handles and status results.

## 4. Check the mathematical foundation

For a step-by-step explanation of the arithmetic, read [Mathematics Unit 123](../11-maths-for-ai/123-count-full-window-rollovers-correctly.md). Keep tensor **shape**, **absolute position**, **model checkpoint identity** and **actual executed work** distinct when describing a cache.

## 5. Practice and verify

**Question:** With context four and a prompt already filling all four positions, how many rollover rebuilds occur before six generated tokens are sampled?

<details>
<summary>Reveal the worked explanation</summary>

The first token uses the existing full prompt. Each of the next five pulls appends the preceding pending token, so five full-window rebuilds occur.

</details>

## 6. Limits and responsible interpretation

RoPE would have different position semantics, but multi-layer hidden-state history still needs separate qualification. Do not reinterpret the existing learned-position checkpoints as RoPE.

A passing test in an isolated demonstration is not a production integration result. Evaluate against the actual Framework checkout and document any numerical or timing limitations before making deployment claims.

## Continue learning

[Previous lesson](228-stream-deterministic-tokens-from-the-cache.md) · [Next lesson](230-measure-attention-work-not-just-projection-rows.md) · [Browser learning path](../../courses/llm-from-scratch/incremental-attention-learning-path.html)

*Service to Many Leads to Greatness.*
