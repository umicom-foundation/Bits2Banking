# Lesson 224 — Preserve residual and feed-forward order

**Bits to Banking · Umicom Foundation**  
**Author:** Sammy Hegab  
**Language:** Native C23 · **Level:** Building beyond the introductory Transformer.

**Learning objective:** Trace the remainder of one Transformer layer after attention for one token.

## 1. The engineering question

The attended token passes through the output weight matrix, is added to the original layer input, is normalised for the feed-forward network, expanded by the first dense matrix, given a learned bias, activated by ReLU, contracted and added through a second residual connection.

## 2. Work through a concrete example

For an eight-channel state and twelve hidden channels, the feed-forward expansion matrix has shape 8×12; contraction has shape 12×8. Residual additions work only when both operands are 1×8.

## 3. How Umicom Framework implements the idea

The proposal calls the original `Matmul`, `Add`, `LayerNorm` and `Relu` operators in the same order as `UmiAiTrainingTransformerBlockForward`. In later layers, the current token’s residual output becomes the next layer’s input.

The relevant public contract is `umicom/ai/training/stacked_kv_step.h`. The native implementation and numerical tests belong to Umicom Framework; this manuscript does not introduce an alternative application-local training or inference service. The training tape owns mathematical operators and tensor lifetimes, while consumers use explicit C23 handles and status results.

## 4. Check the mathematical foundation

For a step-by-step explanation of the arithmetic, read [Mathematics Unit 118](../11-maths-for-ai/118-follow-residual-connections-and-relu.md). Keep tensor **shape**, **absolute position**, **model checkpoint identity** and **actual executed work** distinct when describing a cache.

## 5. Practice and verify

**Question:** What changes if the feed-forward bias is accidentally added after the ReLU rather than before it?

<details>
<summary>Reveal the worked explanation</summary>

The sign and threshold of the activation change. ReLU is nonlinear, so moving the bias usually changes the output even with unchanged weights.

</details>

## 6. Limits and responsible interpretation

This compositional inference procedure remains in Framework. Do not introduce copied neural arithmetic into Studio, Trader or educational pages.

A passing test in an isolated demonstration is not a production integration result. Evaluate against the actual Framework checkout and document any numerical or timing limitations before making deployment claims.

## Continue learning

[Previous lesson](223-select-only-the-last-attended-row.md) · [Next lesson](225-separate-proposal-from-cache-publication.md) · [Browser learning path](../../courses/llm-from-scratch/incremental-attention-learning-path.html)

*Service to Many Leads to Greatness.*
