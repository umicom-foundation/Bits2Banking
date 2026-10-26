# Lesson 223 — Select only the last attended row

**Bits to Banking · Umicom Foundation**  
**Author:** Sammy Hegab  
**Language:** Native C23 · **Level:** Building beyond the introductory Transformer.

**Learning objective:** Read a row-selection matrix as a simple way to obtain the token being generated.

## 1. The engineering question

The result of full causal attention is a matrix with one attended row per query row. Our new token appears at the final row. A selector of shape 1×N containing zeros except a final one extracts exactly that row through the established Matmul operator.

## 2. Work through a concrete example

For N=4, the selector is [0,0,0,1]. Multiplying it by a 4×8 attended matrix yields a 1×8 row. The preceding three outputs are mathematically discarded and cannot alter the selected result.

## 3. How Umicom Framework implements the idea

The selection matrix is a nontrainable leaf on the existing Framework tape. Its output passes to the canonical attention output projection and residual path. No alternative indexing kernel needs to be introduced.

The relevant public contract is `umicom/ai/training/stacked_kv_step.h`. The native implementation and numerical tests belong to Umicom Framework; this manuscript does not introduce an alternative application-local training or inference service. The training tape owns mathematical operators and tensor lifetimes, while consumers use explicit C23 handles and status results.

## 4. Check the mathematical foundation

For a step-by-step explanation of the arithmetic, read [Mathematics Unit 116](../11-maths-for-ai/116-extract-the-last-attention-row-with-a-selector.md). Keep tensor **shape**, **absolute position**, **model checkpoint identity** and **actual executed work** distinct when describing a cache.

## 5. Practice and verify

**Question:** Write the selector for five rows. What shape is obtained when it multiplies a 5×12 attention result?

<details>
<summary>Reveal the worked explanation</summary>

Selector [0,0,0,0,1] has shape 1×5, so multiplication with 5×12 produces 1×12.

</details>

## 6. Limits and responsible interpretation

This is a correctness-oriented composition. A future fused one-query attention operator should be benchmarked only after independent parity and gradient checks.

A passing test in an isolated demonstration is not a production integration result. Evaluate against the actual Framework checkout and document any numerical or timing limitations before making deployment claims.

## Continue learning

[Previous lesson](222-understand-head-local-causal-attention.md) · [Next lesson](224-preserve-residual-and-feed-forward-order.md) · [Browser learning path](../../courses/llm-from-scratch/incremental-attention-learning-path.html)

*Service to Many Leads to Greatness.*
