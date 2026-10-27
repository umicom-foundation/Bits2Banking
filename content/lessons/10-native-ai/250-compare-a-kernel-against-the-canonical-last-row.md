# Lesson 250 — Compare a kernel against the canonical last row

**Bits to Banking · Umicom Foundation**  
**Author:** Sammy Hegab  
**Course:** Building an LLM from Scratch · **Implementation language:** C23

**Learning objective:** Build a non-circular numerical oracle for a new operator.

## 1. Understand the concept

A numerical optimisation should be compared with an **independent canonical computation**, not with a duplicate implementation that shares its indexing mistakes. Umicom Framework already provides `UmiAiTrainingMultiHeadCausalAttention` on the training tape. It processes a full sequence and returns a matrix of outputs. The last row is an oracle for the candidate single-query calculation when both receive identical Q, K, V, sequence length and head partition.

Comparison must be performed **per channel**. Matching only the largest output component or a later sampled token hides differences. Start with one head and two rows, then use several heads, non-uniform values, negative values and different prefix lengths. Run each fixture twice if mutable memory or scratch reuse could influence results.

## 2. Work through the numbers

Let the canonical last row be `[1.0000000,-0.5000000,0.1250000]` and the candidate be `[1.0000004,-0.4999998,0.1249985]`. Absolute errors are `[0.0000004,0.0000002,0.0000015]`; the maximum is `0.0000015`. Under an absolute tolerance of `1×10⁻⁶` the fixture fails because one channel exceeds the threshold. A relative rule alone is unstable near zero; record both maximum absolute error and a scale-aware relative error when appropriate.

## 3. Apply the concept to native model engineering

Construct full-row Q/K/V leaves on the established tape, call `UmiAiTrainingMultiHeadCausalAttention`, read `[(rows−1)×channels : rows×channels]`, and compare this slice with the candidate kernel. Keep the reference operation compiled independently. An optional Framework integration test demonstrates this pattern when the canonical tape target is present.

The standalone candidate's own unit tests are valuable for deterministic arithmetic and rejection semantics. They cannot by themselves establish equivalence to a complete multi-layer Transformer. That requires independent attention-row, hidden-state and vocabulary-logit checks using actual decoder weights.

## 4. Check the mathematical foundation

The related exercise is [Mathematics for AI — Unit 143](../11-maths-for-ai/143-measure-absolute-and-scale-aware-error.md). Work out the arithmetic independently before inspecting an implementation.

## 5. Test your understanding

**Question:** Why can two different last-row output vectors still produce exactly the same next token?

<details>
<summary>Reveal the worked answer</summary>
<p>The output projection and vocabulary argmax can hide small differences. Full-vector comparisons detect them before they accumulate through more layers or later autoregressive steps.</p>
</details>

## 6. Key distinctions

The mathematical examples are deliberately small and inspectable. Changes to attention topology, positional schemes, quantisation and decoding policy require explicit model or algorithm contracts. A standalone operator test does not establish complete Transformer equivalence or measured inference acceleration.

## Continue learning

[249 — Implement a forward-only single-query kernel](249-implement-a-forward-only-single-query-kernel.md) · [251 — Protect capacities, aliasing and atomic results](251-protect-capacities-aliasing-and-atomic-results.md) · [HTML learning path](../../courses/llm-from-scratch/efficient-decoding-learning-path.html)

*Service to Many Leads to Greatness.*
