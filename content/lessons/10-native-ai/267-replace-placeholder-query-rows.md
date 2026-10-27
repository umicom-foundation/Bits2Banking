# Lesson 267 — Replace placeholder query rows without changing the model

**Bits to Banking · Umicom Foundation**  
**Author:** Sammy Hegab  
**Course:** Building an LLM from Scratch · Native C23

**Learning objective:** Understand the narrow transformation from multi-row composition to one attention row.

## 1. Concept and motivation

The earlier incremental path constructed a matrix of zero-valued historical queries, inserted the newest query into its last row, ran the canonical causal-attention operator and selected only the last result. The zero rows were causally irrelevant but still cost computations and memory. The new forward kernel consumes `[channels]` for the query and `[retained+1,channels]` for K/V, then returns `[channels]` directly.

## 2. Worked example

A growing prefix with five tokens and three Transformer layers previously executed `5 × 3 = 15` attention-query rows. Only three rows were needed: one newest query per layer. The number of visible K/V positions is still five in every layer. The optimisation reduces redundant query-row work; it does not remove the need to read retained K/V.

## 3. Native Framework implementation and evidence

Keep the model projections, two layer-normalisation operations, residual branches and feed-forward ordering unchanged. The caller materialises only the newest attended row as a tape-owned value. Historical implementation logic can be retained in a disabled source block for comparison.

## 4. Mathematical companion

Read [Mathematics Unit 151 — Count single-query head operations](../11-maths-for-ai/151-count-single-query-head-operations.md). Check each numerical assumption against the example above before running a program.

## 5. Exercise

**Question:** If the prefix length doubles, does the number of executed new query rows in one incremental step double?

<details>
<summary>Reveal the worked answer</summary>

No. For a fixed number of layers, there is still one query row per layer. The number of key/value rows scored by that query increases with the prefix length.

</details>

## 6. Interpretation

A smaller query-row counter is a work reduction, not a benchmarked latency reduction.

## Continue learning

[266 — Distinguish forward inference from automatic differentiation](266-distinguish-forward-inference-from-autodiff.md) · [268 — Derive last-row attention parity with the reference](268-show-last-row-attention-parity.md) · [Browser learning path](../../courses/llm-from-scratch/integrated-attention-learning-path.html)
