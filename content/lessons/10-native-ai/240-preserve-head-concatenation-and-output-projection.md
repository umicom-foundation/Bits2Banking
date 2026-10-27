# Lesson 240 — Preserve head concatenation and output projection

**Bits to Banking · Umicom Foundation**  
**Course lead:** Sammy Hegab  
**Language:** Native C23 and Assembly where justified · **Level:** Advanced native Transformer engineering.

**Learning objective:** Track the shape and ordering of the attention result before the residual connection.

## 1. Understand the problem

Multi-head attention is not a simple average of heads. Each head produces a vector of width `d_h`; these vectors are concatenated in **model-defined head order** to form a width-`d_model` vector when `d_model = heads × d_h`. The established output-projection matrix then transforms that concatenated vector, after which the correct residual, normalisation and feed-forward sequence continues.

An optimiser that computes each head correctly but changes concatenation order can alter the whole model. The candidate may optimise the way data moves, but it must not change learned matrices, transposes, activation functions or arithmetic operation ordering without an explicitly qualified equivalence.

## 2. Fully worked example

For two heads of width two, outputs `h0=(0.8,0.4)` and `h1=(0.1,-0.2)` concatenate to `(0.8,0.4,0.1,-0.2)`. Swapping the heads gives `(0.1,-0.2,0.8,0.4)`. Even if both vectors have shape `[4]`, a non-symmetric output projection maps them to different residual updates. A unit test with identity `W_O` makes the swap immediately visible.

## 3. Engineering verification and connection to Umicom Framework

Verify head order using asymmetric labelled values, the decoder’s real weight layout and the canonical output-projection result. Inspect one- and multi-head cases. Preserve the Framework’s exact pre-/post-layer-normalisation ordering rather than assuming the architecture in a different textbook.

The existing Umicom Framework decoder, training tape and K/V ownership services remain the authority for implementation. This educational lesson specifies behaviour; it does **not** introduce a competing application-local inference engine or claim that the proposed single-query kernel is already merged or performance-qualified.

## 4. Mathematics connection

Review [Mathematics for AI — Unit 130](../11-maths-for-ai/130-reconstruct-multihead-output-shapes.md). The mathematics companion includes a calculation that can be verified independently of a compiled model.

## 5. Exercise

**Question:** Why is shape equality not enough to qualify head concatenation?

<details>
<summary>Reveal the worked answer</summary>

Both correct and permuted head arrangements have length `d_model`; only value- and order-aware comparisons detect the model change.

</details>

## 6. Acceptance note

Educational calculations and design specifications are not substitutes for running the complete numerical and memory-safety qualification suite against the actual Windows and other supported Framework builds. Do not claim an inference speedup from hypothetical arithmetic counts.

## Continue learning

[Previous lesson](239-keep-learned-position-embeddings-consistent.md) · [Browser learning path](../../courses/llm-from-scratch/single-query-attention-learning-path.html) · [Next lesson](241-qualify-layer-by-layer-and-vocabulary-logit-parity.md)

*Service to Many Leads to Greatness.*
