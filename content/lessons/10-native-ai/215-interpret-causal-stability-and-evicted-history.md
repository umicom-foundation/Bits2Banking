# Lesson 215 — Understand causal stability and evicted history

**Bits to Banking · Umicom Foundation**  
**Author:** Sammy Hegab  
**Language:** C23  
**Scope:** Educational native model engineering; not production deployment.

**Learning objective:** Separate fixed-position prefix causality from the more difficult mathematics of context truncation.

## Why this matters

Causal attention forbids a token at position t from using tokens at later positions. If a new token is appended without changing earlier positions, the earlier tokens' hidden representations and their K/V projections should remain unchanged. This is why fixed-position growing-prefix capture can validate prior-row parity even in a multi-layer Transformer.

Eviction changes the question. In a learned-absolute decoder, token positions shift. In other architectures, even if relative positions are preserved, an upper-layer retained key can depend on an earlier token that is no longer present in a freshly truncated reference window. There is a distinction between a continuously running causal stream and recomputing the retained window from scratch.

A future accelerated cache must declare the precise semantics it promises. Is it reproducing the uninterrupted stream, or the finite-window canonical reference after truncation? Those may be different problems. The Framework should choose deliberately and bind that policy to model identity, tests and the checkpoint format.

## Work through the numbers and tensor shapes

Consider a two-layer model. At layer one, token B's hidden state may include information from earlier token A. Layer two computes B's key from that hidden state. Later, A leaves the retention window. If the model recomputes B **from scratch in a truncated window**, its layer-one representation might no longer include A. A retained layer-two key from the uninterrupted stream is not generally equal to the recomputed key.

This is not a failure of the rotary formula: it is a dependency on hidden history. Numerical parity must specify which history convention is authoritative.

## Where the implementation lives

The reusable implementation belongs to `Umicom-Applications/framework`. Use the public `umicom/ai/training/stacked_projection_trace.h` or `umicom/ai/training/stacked_kv_capture.h` interfaces, depending on the task. The trace observes the **original** decoder through its established Transformer projection hook; the existing cache store handles K/V row ownership. No C23 neural-network computations belong in the Bits2Banking course. Run the Framework CTest cases for numerical qualification on the actual model before interpreting these services as integrated.

## Limitations and engineering evidence

The current observation pipeline performs a **complete canonical Transformer forward** for each observed prompt state. A smaller number of rows accepted into a store is not proof of fewer operations, lower latency or more accurate generated text. SHA-256 identifies checkpoint bytes but does not authenticate a publisher. No generated output should be executed as source code or treated as financial advice.

## Practice

**Question:** Does positional information alone prove that an upper-layer K/V row remains correct after an old token has been evicted?

<details><summary>Reveal the worked explanation</summary>

No. Upper-layer hidden representations can encode earlier attended history. Correctness depends on both positional semantics and the exact context-history policy.

</details>

## Continue studying

[Previous lesson](214-qualify-capture-across-multiple-layers.md) · [Next lesson](216-design-the-next-incremental-attention-reference.md) · [View the browser lesson](../../courses/llm-from-scratch/lessons/215-interpret-causal-stability-and-evicted-history.html) · [K/V projection learning path](kv-projection-observation-study-route.md).

*Service to Many Leads to Greatness.*
