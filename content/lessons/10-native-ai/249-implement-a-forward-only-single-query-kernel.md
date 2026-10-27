# Lesson 249 — Implement a forward-only single-query kernel

**Bits to Banking · Umicom Foundation**  
**Author:** Sammy Hegab  
**Course:** Building an LLM from Scratch · **Implementation language:** C23

**Learning objective:** Follow one query through a bounded C23 numerical operator without changing a model checkpoint.

## 1. Understand the concept

A trained autoregressive Transformer predicts the next token from the last prefix position. The conventional causal attention operation calculates outputs for every query row in a sequence. During incremental decoding, historical key and value projections are retained, so only the newest query row needs a fresh attention result. A **forward-only attention kernel** takes that newest query plus the retained keys and values and returns one channel vector. It does not perform token embedding, normalisation, projection, residual composition or model sampling. These remain separate model responsibilities.

The kernel has three logical inputs: `Q[channels]`, `K[validRows,channels]` and `V[validRows,channels]`. Here `validRows` includes the newest token after its K/V projection. A head owns `d = channels / headCount` consecutive channels. The last query can attend to all these rows because none lies in its future. A padding token is not automatically valid: the caller must submit only causally admitted rows.

## 2. Work through the numbers

For one head of width two, let `Q=[1,0]`, `K₀=[1,0]`, `K₁=[0,1]`, `V₀=[2,4]`, and `V₁=[6,8]`. The scores after division by √2 are approximately `[0.7071,0]`. Their stable softmax probabilities are approximately `[0.6698,0.3302]`. The result is `[2×0.6698+6×0.3302, 4×0.6698+8×0.3302] ≈ [3.321,5.321]`. This single row is the output that the original two-row causal operator would produce for the final query.

## 3. Apply the concept to native model engineering

The opt-in Umicom Framework laboratory declares `UmiAiTrainingSingleQueryAttentionForward` in `include/umicom/ai/training/single_query_attention.h`. Its output is not a training-tape node: the existing `UmiAiTrainingMultiHeadCausalAttention` still owns differentiable training. Study how the source checks shapes, uses double-precision score accumulation, rounds probabilities to float, and only copies an accepted result into the caller's output.

Use the standalone native laboratory when examining this step. It deliberately neither installs itself into the stacked incremental session nor changes the reference decoder. That distinction isolates arithmetic correctness from complete model integration.

## 4. Check the mathematical foundation

The related exercise is [Mathematics for AI — Unit 137](../11-maths-for-ai/137-derive-a-stable-softmax-normaliser.md). Work out the arithmetic independently before inspecting an implementation.

## 5. Test your understanding

**Question:** Why must `validRows` exclude padding even though the query represents the last prefix token?

<details>
<summary>Reveal the worked answer</summary>
<p>Padding keys would participate in the softmax normaliser and change the weighted output unless they are explicitly excluded by a matching mask. The bounded forward interface accepts only genuinely visible rows.</p>
</details>

## 6. Key distinctions

The mathematical examples are deliberately small and inspectable. Changes to attention topology, positional schemes, quantisation and decoding policy require explicit model or algorithm contracts. A standalone operator test does not establish complete Transformer equivalence or measured inference acceleration.

## Continue learning

[Lesson 248 — Single-query kernel acceptance](248-define-the-single-query-kernel-acceptance-gate.md) · [250 — Compare a kernel against the canonical last row](250-compare-a-kernel-against-the-canonical-last-row.md) · [HTML learning path](../../courses/llm-from-scratch/efficient-decoding-learning-path.html)

*Service to Many Leads to Greatness.*
