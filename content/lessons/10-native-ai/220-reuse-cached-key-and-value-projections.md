# Lesson 220 — Reuse cached key and value projections

**Bits to Banking · Umicom Foundation**  
**Author:** Sammy Hegab  
**Language:** Native C23 · **Level:** Building beyond the introductory Transformer.

**Learning objective:** Follow an actual C23 one-token proposal without implementing a second neural kernel.

## 1. The engineering question

The new token uses the original Framework `EmbeddingLookup`, `LayerNorm` and `Matmul` operations to calculate query, key and value. The earlier rows are read from `UmiAiTrainingStackedKvStore`. Only the new row has fresh Q/K/V projections; previous K/V are not regenerated in the proposal.

## 2. Work through a concrete example

If a layer has retained three K/V rows, the step computes one new 1×C query, key and value, then builds a four-row attention input. The old three K/V rows are copied from cache; the fourth row comes from the live projection.

## 3. How Umicom Framework implements the idea

`UmiAiTrainingStackedKvStepPropose` uses the private decoder parameter ordering already defined by Framework. The training tape owns numerical execution and temporary allocations; `TapeRollback` removes the transient graph after the result is copied.

The relevant public contract is `umicom/ai/training/stacked_kv_step.h`. The native implementation and numerical tests belong to Umicom Framework; this manuscript does not introduce an alternative application-local training or inference service. The training tape owns mathematical operators and tensor lifetimes, while consumers use explicit C23 handles and status results.

## 4. Check the mathematical foundation

For a step-by-step explanation of the arithmetic, read [Mathematics Unit 114](../11-maths-for-ai/114-calculate-one-query-attention-by-hand.md). Keep tensor **shape**, **absolute position**, **model checkpoint identity** and **actual executed work** distinct when describing a cache.

## 5. Practice and verify

**Question:** Why is retaining only K and V sufficient when the next token attends to earlier tokens?

<details>
<summary>Reveal the worked explanation</summary>

The next query is calculated from the new token. Attention compares it with earlier K values and combines their V vectors. Old queries are not required for the new token’s weighted result.

</details>

## 6. Limits and responsible interpretation

The current tape attention primitive computes additional placeholder query rows, so fewer Q/K/V projections do not automatically mean faster latency.

A passing test in an isolated demonstration is not a production integration result. Evaluate against the actual Framework checkout and document any numerical or timing limitations before making deployment claims.

## Continue learning

[Previous lesson](219-prefill-from-the-authoritative-transformer.md) · [Next lesson](221-normalise-the-new-token-without-changing-the-model.md) · [Browser learning path](../../courses/llm-from-scratch/incremental-attention-learning-path.html)

*Service to Many Leads to Greatness.*
