# Lesson 222 — Understand head-local causal attention

**Bits to Banking · Umicom Foundation**  
**Author:** Sammy Hegab  
**Language:** Native C23 · **Level:** Building beyond the introductory Transformer.

**Learning objective:** Explain the multi-head attention calculation for the newest token using retained values.

## 1. The engineering question

The existing Framework `MultiHeadCausalAttention` scales each head’s query-key dot products by the square root of that head’s channel count. Each head uses its own channels, and the causal mask prevents attention to any later token.

## 2. Work through a concrete example

With eight channels and two heads, each head has four channels. A four-token prefix produces four candidate K/V rows. The last query row can attend to all four retained positions. Its output remains eight channels when the two heads are concatenated.

## 3. How Umicom Framework implements the idea

The proposal constructs temporary Q/K/V row-major tensors, then delegates softmax, head splitting and FP32 conversion to the established tape. Earlier query rows are zero placeholders and are not interpreted as historical real queries.

The relevant public contract is `umicom/ai/training/transformer.h`. The native implementation and numerical tests belong to Umicom Framework; this manuscript does not introduce an alternative application-local training or inference service. The training tape owns mathematical operators and tensor lifetimes, while consumers use explicit C23 handles and status results.

## 4. Check the mathematical foundation

For a step-by-step explanation of the arithmetic, read [Mathematics Unit 114](../11-maths-for-ai/114-calculate-one-query-attention-by-hand.md). Keep tensor **shape**, **absolute position**, **model checkpoint identity** and **actual executed work** distinct when describing a cache.

## 5. Practice and verify

**Question:** For 12 channels and 3 heads, what head width is used? Why is 10 channels with 3 equal heads invalid?

<details>
<summary>Reveal the worked explanation</summary>

12÷3=4 channels per head. Ten channels cannot be divided evenly into three equal-width heads without changing the architecture.

</details>

## 6. Limits and responsible interpretation

The tape currently computes all query rows in this composed attention operation. Report this additional work separately from newly projected rows.

A passing test in an isolated demonstration is not a production integration result. Evaluate against the actual Framework checkout and document any numerical or timing limitations before making deployment claims.

## Continue learning

[Previous lesson](221-normalise-the-new-token-without-changing-the-model.md) · [Next lesson](223-select-only-the-last-attended-row.md) · [Browser learning path](../../courses/llm-from-scratch/incremental-attention-learning-path.html)

*Service to Many Leads to Greatness.*
