# Lesson 205 — Observe keys and values in the real Transformer

**Bits to Banking · Umicom Foundation**  
**Author:** Sammy Hegab  
**Language:** C23  
**Scope:** Educational native model engineering; not production deployment.

**Learning objective:** Understand why a cache row must come from the decoder that actually performs attention, not from a fabricated array.

## Why this matters

A key (K) tells an attention head which earlier information matches the current query. A value (V) contains the vector eventually combined into the attended output. Every Transformer layer creates its own K and V. In the current Umicom stacked decoder, the input to an upper layer is the result of lower layers, so upper-layer K/V cannot be reconstructed merely by reusing the first layer’s token embeddings.

Before this lesson, `UmiAiTrainingStackedKvStore` could retain caller-supplied rows and validate their dimensions. That is valuable storage infrastructure, but an arbitrary test array is not evidence that the original model produced the array. This lesson introduces observing the real dense projections through an existing Framework-owned hook. The hook invokes the canonical `UmiAiTrainingMatmul` and copies its K/V outputs; it does not change the attention equation.

The observation is temporary. When the inference pass finishes, the established training tape discards transient tensors. The observer has copied finite FP32 values into caller-owned staging buffers, so no pointer to an expired tape tensor survives.

## Work through the numbers and tensor shapes

Suppose there are **three Transformer layers**, **five tokens** and **eight channels** per layer. Each of K and V contains `3 × 5 × 8 = 120` floats. Together they require `2 × 120 × 4 = 960` raw FP32 bytes. These are only the projection values, excluding logits, activation workspaces and allocator overhead.

The trace API requires the full input context because the current decoder's positional embedding table and attention graph are fixed-context. When observing a short prefix of length two in a context of five, put the real tokens at positions zero and one and use BOS to the **right** of them. This is the explicitly unpadded prefix convention; it is not interchangeable with the old left-padded generator.

## Where the implementation lives

The reusable implementation belongs to `Umicom-Applications/framework`. Use the public `umicom/ai/training/stacked_projection_trace.h` or `umicom/ai/training/stacked_kv_capture.h` interfaces, depending on the task. The trace observes the **original** decoder through its established Transformer projection hook; the existing cache store handles K/V row ownership. No C23 neural-network computations belong in the Bits2Banking course. Run the Framework CTest cases for numerical qualification on the actual model before interpreting these services as integrated.

## Limitations and engineering evidence

The current observation pipeline performs a **complete canonical Transformer forward** for each observed prompt state. A smaller number of rows accepted into a store is not proof of fewer operations, lower latency or more accurate generated text. SHA-256 identifies checkpoint bytes but does not authenticate a publisher. No generated output should be executed as source code or treated as financial advice.

## Practice

**Question:** Why is saving a matrix with the correct dimensions insufficient to establish that it is a real K/V projection?

<details><summary>Reveal the worked explanation</summary>

Dimensions constrain storage but do not establish the values or their provenance. Only a projection observed during the canonical decoder's own forward calculation can claim to represent that decoder. A separately computed reference is needed to verify correctness.

</details>

## Continue studying

[Previous lesson](204-define-the-acceptance-gate-for-true-incremental-inference.md) · [Next lesson](206-trace-projections-without-duplicating-attention.md) · [View the browser lesson](../../courses/llm-from-scratch/lessons/205-observe-keys-and-values-in-the-real-transformer.html) · [K/V projection learning path](kv-projection-observation-study-route.md).

*Service to Many Leads to Greatness.*
