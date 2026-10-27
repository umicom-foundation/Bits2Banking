# Lesson 258 — Distinguish absolute positions from rotary positions

**Bits to Banking · Umicom Foundation**  
**Author:** Sammy Hegab  
**Course:** Building an LLM from Scratch · **Implementation language:** C23

**Learning objective:** Explain why changing positional schemes requires architectural and checkpoint compatibility.

## 1. Understand the concept

The current Umicom stacked decoder adds learned **absolute positional embeddings** to token embeddings. If a full window evicts its oldest token and shifts the rest of the sequence left, surviving tokens now receive different absolute position IDs. Their hidden states and upper-layer K/V projections may change, so a cache built for the old positions cannot simply be shifted and reused. The canonical full-context rebuild is the safe reference behaviour.

**Rotary positional embeddings (RoPE)** instead rotate paired components of query and key vectors according to position-dependent angles. The inner product of rotated vectors depends on relative positional differences in a particular way. This can support position handling policies different from a learned absolute table, but it does not magically make every arbitrary cache eviction correct: attention windows, absolute counters and model-specific implementation choices still matter.

## 2. Work through the numbers

For a two-dimensional pair `(x,y)` and angle θ, rotation produces `(x cosθ − y sinθ, x sinθ + y cosθ)`. With vector `(1,0)` and angle π/2, the result is `(0,1)` to floating-point tolerance. If query and key are rotated by angles corresponding to positions 7 and 5, their dot product reflects an angular difference associated with `7−5=2`, not merely the unrotated values.

This derivation explains the mathematical structure; it does not authorise loading a checkpoint trained with learned positional vectors into a RoPE model.

## 3. Apply the concept to native model engineering

A new position scheme needs explicit checkpoint metadata, parameter compatibility, training decisions and independent causal regression tests. Inference engines should not guess the scheme from tensor shapes alone. The current full-window fallback remains correct for the existing learned-absolute-position decoder.

RoFormer describes the research foundations. Read it separately from the implementation contract of the Umicom educational stack.

## 4. Check the mathematical foundation

The related exercise is [Mathematics for AI — Unit 145](../11-maths-for-ai/145-rotate-a-two-dimensional-position-pair.md). Work out the arithmetic independently before inspecting an implementation.

## 5. Test your understanding

**Question:** Can the existing learned-absolute-position model be converted to RoPE by changing only the decoder function?

<details>
<summary>Reveal the worked answer</summary>
<p>No. The parameterisation changes and the original checkpoint was trained under a different positional representation. Such a change requires a defined conversion or retraining procedure and new qualification.</p>
</details>

## 6. Key distinctions

The mathematical examples are deliberately small and inspectable. Changes to attention topology, positional schemes, quantisation and decoding policy require explicit model or algorithm contracts. A standalone operator test does not establish complete Transformer equivalence or measured inference acceleration.

## Continue learning

[257 — Understand paged KV memory and block tables](257-understand-paged-kv-memory.md) · [259 — Compare IO-aware tiling with single-query streaming](259-compare-io-aware-tiling-with-single-query-streaming.md) · [HTML learning path](../../courses/llm-from-scratch/efficient-decoding-learning-path.html)

*Service to Many Leads to Greatness.*
