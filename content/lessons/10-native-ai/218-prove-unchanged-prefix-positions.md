# Lesson 218 — Prove unchanged prefix positions

**Bits to Banking · Umicom Foundation**  
**Author:** Sammy Hegab  
**Language:** Native C23 · **Level:** Building beyond the introductory Transformer.

**Learning objective:** Understand why right padding is causally invisible and why growing prefixes can retain K/V.

## 1. The engineering question

With a causal mask, output at time t reads only positions 0 through t. Appending a token at position t+1 cannot change earlier layer outputs when previous absolute positions are unchanged. By induction, this remains true across stacked Transformer layers before any eviction.

## 2. Work through a concrete example

Consider original tokens [A,B] followed by right-side BOS padding. The logits at B cannot use future BOS positions. After appending C, the embeddings and hidden states for A and B remain the same, up to numerical tolerance. K/V generated from their layer inputs therefore remain valid.

## 3. How Umicom Framework implements the idea

Use `UmiAiTrainingStackedDecoderTraceProjections` as the independent reference. Compare all earlier K/V components and all vocabulary logits before relying on a proposed incremental result. The historical left-BOS-padded generator has different positional semantics and cannot be this reference.

The relevant public contract is `umicom/ai/training/stacked_projection_trace.h`. The native implementation and numerical tests belong to Umicom Framework; this manuscript does not introduce an alternative application-local training or inference service. The training tape owns mathematical operators and tensor lifetimes, while consumers use explicit C23 handles and status results.

## 4. Check the mathematical foundation

For a step-by-step explanation of the arithmetic, read [Mathematics Unit 119](../11-maths-for-ai/119-measure-logit-parity-with-an-absolute-tolerance.md). Keep tensor **shape**, **absolute position**, **model checkpoint identity** and **actual executed work** distinct when describing a cache.

## 5. Practice and verify

**Question:** Why may two identical words have different key vectors when one is left-padded and the other begins at position zero?

<details>
<summary>Reveal the worked explanation</summary>

The model adds different learned absolute-position embeddings before computing Q/K/V. Equal token identity does not imply equal layer representations at different positions.

</details>

## 6. Limits and responsible interpretation

This proof fails at rollover because retained tokens shift position. Upper-layer states can also encode history that has been removed.

A passing test in an isolated demonstration is not a production integration result. Evaluate against the actual Framework checkout and document any numerical or timing limitations before making deployment claims.

## Continue learning

[Previous lesson](217-define-the-incremental-layer-step-contract.md) · [Next lesson](219-prefill-from-the-authoritative-transformer.md) · [Browser learning path](../../courses/llm-from-scratch/incremental-attention-learning-path.html)

*Service to Many Leads to Greatness.*
