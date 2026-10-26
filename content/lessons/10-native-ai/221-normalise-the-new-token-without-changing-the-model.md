# Lesson 221 — Normalise the new token without changing the model

**Bits to Banking · Umicom Foundation**  
**Author:** Sammy Hegab  
**Language:** Native C23 · **Level:** Building beyond the introductory Transformer.

**Learning objective:** Identify the exact forward sequence reused for new-token query, key and value calculations.

## 1. The engineering question

The pre-layer-normalised Transformer applies a learned affine layer normalisation to the incoming hidden state, then derives the three projections by matrix multiplication. Using different epsilon, affine weights or operand order would change logits and invalidate the new inference path.

## 2. Work through a concrete example

A token hidden row has shape 1×8. Its first normalisation retains that shape; multiplying it by an 8×8 query matrix produces one 1×8 query row. Key and value use separate 8×8 matrices. No parameter is updated during inference.

## 3. How Umicom Framework implements the idea

`UmiAiTrainingLayerNorm` and `UmiAiTrainingMatmul` are called on the original decoder-owned tape. The new code composes operations, not copied maths. Projection values are staged before the store can be advanced.

The relevant public contract is `umicom/ai/training/tape.h`. The native implementation and numerical tests belong to Umicom Framework; this manuscript does not introduce an alternative application-local training or inference service. The training tape owns mathematical operators and tensor lifetimes, while consumers use explicit C23 handles and status results.

## 4. Check the mathematical foundation

For a step-by-step explanation of the arithmetic, read [Mathematics Unit 117](../11-maths-for-ai/117-calculate-layer-normalisation-by-hand.md). Keep tensor **shape**, **absolute position**, **model checkpoint identity** and **actual executed work** distinct when describing a cache.

## 5. Practice and verify

**Question:** Explain why the inference path must use the same layer-normalisation epsilon as the canonical forward.

<details>
<summary>Reveal the worked explanation</summary>

Epsilon changes the denominator of the normalisation. A different value changes the normalised features, so even unchanged weights can produce different Q/K/V and final logits.

</details>

## 6. Limits and responsible interpretation

The new proposal does not change training history or checkpoint family. A failed forward must still restore the tape graph prefix.

A passing test in an isolated demonstration is not a production integration result. Evaluate against the actual Framework checkout and document any numerical or timing limitations before making deployment claims.

## Continue learning

[Previous lesson](220-reuse-cached-key-and-value-projections.md) · [Next lesson](222-understand-head-local-causal-attention.md) · [Browser learning path](../../courses/llm-from-scratch/incremental-attention-learning-path.html)

*Service to Many Leads to Greatness.*
