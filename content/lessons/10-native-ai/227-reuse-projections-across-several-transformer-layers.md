# Lesson 227 — Reuse projections across several Transformer layers

**Bits to Banking · Umicom Foundation**  
**Author:** Sammy Hegab  
**Language:** Native C23 · **Level:** Building beyond the introductory Transformer.

**Learning objective:** Explain why one-layer parity is not sufficient for a stacked model.

## 1. The engineering question

A layer receives the previous layer’s output for the newest token. Its newly calculated K/V depend on that input and on its own learned projections. Historical K/V for that layer were generated at earlier times by that same layer, so every layer must retain its own independent cache rows.

## 2. Work through a concrete example

For three layers, context length five and eight channels, raw stored K/V occupies 2 × 3 × 5 × 8 × 4 = 960 bytes of FP32 values. Combining all layers into one undifferentiated K/V array would scramble the attention calculation.

## 3. How Umicom Framework implements the idea

The established `StackedKvStore` maintains layer-major storage. The new C23 proposal iterates layer by layer, reading that layer’s historical values and producing only the current row for that layer.

The relevant public contract is `umicom/ai/training/stacked_kv_store.h`. The native implementation and numerical tests belong to Umicom Framework; this manuscript does not introduce an alternative application-local training or inference service. The training tape owns mathematical operators and tensor lifetimes, while consumers use explicit C23 handles and status results.

## 4. Check the mathematical foundation

For a step-by-step explanation of the arithmetic, read [Mathematics Unit 113](../11-maths-for-ai/113-count-multilayer-qkv-tensor-shapes.md). Keep tensor **shape**, **absolute position**, **model checkpoint identity** and **actual executed work** distinct when describing a cache.

## 5. Practice and verify

**Question:** What is wrong with feeding layer two the keys from layer one, even when both have eight channels?

<details>
<summary>Reveal the worked explanation</summary>

Equal shapes do not imply equal meanings or learned transformations. Layer two expects projections from its own intermediate hidden states and learned matrices.

</details>

## 6. Limits and responsible interpretation

Do not infer full-window eviction safety from prefix growth; upper-layer hidden states may depend on information outside a newly shifted window.

A passing test in an isolated demonstration is not a production integration result. Evaluate against the actual Framework checkout and document any numerical or timing limitations before making deployment claims.

## Continue learning

[Previous lesson](226-verify-every-vocabulary-logit.md) · [Next lesson](228-stream-deterministic-tokens-from-the-cache.md) · [Browser learning path](../../courses/llm-from-scratch/incremental-attention-learning-path.html)

*Service to Many Leads to Greatness.*
