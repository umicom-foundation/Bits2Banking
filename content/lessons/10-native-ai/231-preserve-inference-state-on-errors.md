# Lesson 231 — Preserve inference state after errors and model updates

**Bits to Banking · Umicom Foundation**  
**Author:** Sammy Hegab  
**Language:** Native C23 · **Level:** Building beyond the introductory Transformer.

**Learning objective:** Examine defensive C23 inference ownership, rejection semantics and cancellation.

## 1. The engineering question

A session borrows its decoder and pins a complete canonical checkpoint identity. If the decoder changes, every subsequent pull and inspection must refuse the stale session. Training, inference and destruction on the same decoder require external serialisation.

## 2. Work through a concrete example

Create a session, train the borrowed model once and then call Next with an output sentinel 999. A correct stale-model rejection returns `UMI_STATUS_INVALID_STATE` and leaves the sentinel unchanged. Destroy remains legal and releases only session-owned cache memory.

## 3. How Umicom Framework implements the idea

Tests also reject invalid prompt token IDs, zero-length prompts, unavailable vocabularies for byte conversion and insufficient output capacities before advancing RNG or cache. One-shot generation stages its full token array until completion.

The relevant public contract is `umicom/ai/training/stacked_kv_incremental.h`. The native implementation and numerical tests belong to Umicom Framework; this manuscript does not introduce an alternative application-local training or inference service. The training tape owns mathematical operators and tensor lifetimes, while consumers use explicit C23 handles and status results.

## 4. Check the mathematical foundation

For a step-by-step explanation of the arithmetic, read [Mathematics Unit 122](../11-maths-for-ai/122-distinguish-byte-tokens-from-utf8-characters.md). Keep tensor **shape**, **absolute position**, **model checkpoint identity** and **actual executed work** distinct when describing a cache.

## 5. Practice and verify

**Question:** Why is retaining an existing output pointer or integer after rejection useful?

<details>
<summary>Reveal the worked explanation</summary>

It prevents downstream consumers from seeing an apparently completed result assembled from only part of a failed operation.

</details>

## 6. Limits and responsible interpretation

A SHA-256 hash proves byte agreement but not that a model came from a trusted publisher. Authenticity and authorisation remain separate.

A passing test in an isolated demonstration is not a production integration result. Evaluate against the actual Framework checkout and document any numerical or timing limitations before making deployment claims.

## Continue learning

[Previous lesson](230-measure-attention-work-not-just-projection-rows.md) · [Next lesson](232-run-the-qualification-matrix-before-optimising.md) · [Browser learning path](../../courses/llm-from-scratch/incremental-attention-learning-path.html)

*Service to Many Leads to Greatness.*
