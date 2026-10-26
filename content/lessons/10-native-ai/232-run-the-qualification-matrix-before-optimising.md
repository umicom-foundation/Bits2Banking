# Lesson 232 — Run the qualification matrix before optimising

**Bits to Banking · Umicom Foundation**  
**Author:** Sammy Hegab  
**Language:** Native C23 · **Level:** Building beyond the introductory Transformer.

**Learning objective:** Execute a complete native acceptance path before discussing accelerated Transformer inference.

## 1. The engineering question

The acceptance matrix has different axes: one-, two- and three-layer models; short and full prompts; deterministic greedy and sampled top-p policies; every vocabulary-logit comparison; stored K/V shape parity; first and repeated rollovers; model-update invalidation; short-buffer rejection; and actual work counters.

## 2. Work through a concrete example

A four-token context permits three unchanged-position appends from a one-token prompt. The next proposed change would evict an earlier token and must take the canonical fallback path. A regression that checks only the first three steps misses the hardest boundary.

## 3. How Umicom Framework implements the idea

Build `learning/native-ai-stacked-incremental` against the actual Umicom Framework, run `ctest -R ^framework\.ai\.stacked_incremental\.`, and inspect failures rather than widening tolerances. A separate Release benchmark can follow only after numeric parity is independently established.

The relevant public contract is `umicom/ai/training/stacked_kv_step.h`. The native implementation and numerical tests belong to Umicom Framework; this manuscript does not introduce an alternative application-local training or inference service. The training tape owns mathematical operators and tensor lifetimes, while consumers use explicit C23 handles and status results.

## 4. Check the mathematical foundation

For a step-by-step explanation of the arithmetic, read [Mathematics Unit 119](../11-maths-for-ai/119-measure-logit-parity-with-an-absolute-tolerance.md). Keep tensor **shape**, **absolute position**, **model checkpoint identity** and **actual executed work** distinct when describing a cache.

## 5. Practice and verify

**Question:** Which is stronger evidence: ten matching generated tokens or ten sequences whose every intermediate logit vector also agrees?

<details>
<summary>Reveal the worked explanation</summary>

Full-vector comparison is stronger: equal sampled IDs can conceal mismatched probabilities and future behavioural divergence.

</details>

## 6. Limits and responsible interpretation

This remains a bounded educational implementation. Its attention matrix composition may be slower than full reference execution; no GPU, fused attention or production LLM claims are made.

A passing test in an isolated demonstration is not a production integration result. Evaluate against the actual Framework checkout and document any numerical or timing limitations before making deployment claims.

## Continue learning

[Previous lesson](231-preserve-inference-state-on-errors.md) · [Browser learning path](../../courses/llm-from-scratch/incremental-attention-learning-path.html)

*Service to Many Leads to Greatness.*
