# Lesson 233 — Define the single-query attention contract

**Bits to Banking · Umicom Foundation**  
**Course lead:** Sammy Hegab  
**Language:** Native C23 and Assembly where justified · **Level:** Advanced native Transformer engineering.

**Learning objective:** Specify the boundary of an attention operator that computes the newest query only, without changing the established Transformer model.

## 1. Understand the problem

The last inference batch introduced a true incremental projection path, but its attention composition still handles unnecessary earlier query rows. The next optimisation is narrower: given one newly calculated query for each head, attend to keys and values representing **only the permitted causal prefix**. The output is one vector per head, not an entire sequence of attention rows. This is an execution optimisation, not a change to the learned weights or the model’s probability distribution.

A proposed C23 Framework interface must make input shapes, ownership, validity lengths, model identity and status explicit. It must not own token sampling, mutate K/V storage, advance a session cursor, or choose new positional embeddings. Those actions belong to the established Framework execution and session services. The output must be fully defined on success and not exposed as valid on failure.

## 2. Fully worked example

Assume 4 heads, head width 8 and a valid prefix of 6 tokens. A candidate reads one `Q[4,8]`, one `K[4,6,8]` and one `V[4,6,8]`, and proposes `A[4,8]`. That is 32 query elements, 192 key elements, 192 value elements and 32 output elements. At FP32, the three inputs alone occupy `(32 + 192 + 192) × 4 = 1,664` bytes; this number excludes scratch buffers, model weights and allocator overhead.

The candidate must not silently use a seventh padded row: a physical capacity of 8 does **not** mean eight valid keys.

## 3. Engineering verification and connection to Umicom Framework

A design review must reject a zero valid length, mismatched head count, invalid stride, arithmetic overflow, nonfinite unmasked inputs and overlapping buffers when aliasing is unsupported. On success, check `output shape = [heads, head_width]`; on failure, check the cache version, sampling state and token history remain unchanged. These are **proposed acceptance requirements**, not claims that a new public ABI exists.

The existing Umicom Framework decoder, training tape and K/V ownership services remain the authority for implementation. This educational lesson specifies behaviour; it does **not** introduce a competing application-local inference engine or claim that the proposed single-query kernel is already merged or performance-qualified.

## 4. Mathematics connection

Review [Mathematics for AI — Unit 125](../11-maths-for-ai/125-identify-single-query-attention-dimensions.md). The mathematics companion includes a calculation that can be verified independently of a compiled model.

## 5. Exercise

**Question:** Why must `validPrefixLength` be separate from the storage capacity?

<details>
<summary>Reveal the worked answer</summary>

Capacity describes how many rows fit in memory; the valid length says how many causal keys may contribute to the current query. Confusing them permits uninitialised or padded data to alter the softmax.

</details>

## 6. Acceptance note

Educational calculations and design specifications are not substitutes for running the complete numerical and memory-safety qualification suite against the actual Windows and other supported Framework builds. Do not claim an inference speedup from hypothetical arithmetic counts.

## Continue learning

[Previous lesson](232-run-the-qualification-matrix-before-optimising.md) · [Browser learning path](../../courses/llm-from-scratch/single-query-attention-learning-path.html) · [Next lesson](234-trace-head-local-key-value-layout.md)

*Service to Many Leads to Greatness.*
