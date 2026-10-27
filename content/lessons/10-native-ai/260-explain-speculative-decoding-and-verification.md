# Lesson 260 — Explain speculative decoding and verification

**Bits to Banking · Umicom Foundation**  
**Author:** Sammy Hegab  
**Course:** Building an LLM from Scratch · **Implementation language:** C23

**Learning objective:** Understand why draft tokens must be checked against the target model.

## 1. Understand the concept

Autoregressive decoding normally commits one new token after each target-model forward pass. **Speculative decoding** allows a smaller or cheaper draft process to propose several candidate tokens. The target model evaluates those proposals in a manner that can reduce sequential target-model steps. The acceptance algorithm matters: blindly accepting a draft would change the target model's output distribution.

For greedy decoding, a simple pedagogical process compares each draft token with the target model's corresponding greedy prediction and stops at the first disagreement. Sampling-equivalent speculative algorithms are more subtle: they account for differences between draft and target probability distributions and may sample from a correction distribution. Their correctness depends on using the specified algorithm, not on a vague similarity score.

## 2. Work through the numbers

A draft proposes `[A,B,C]`. Under greedy verification, suppose the target's predictions conditional on accepted prefixes are `[A,B,D]`. The first two tokens may be accepted, but the third proposal `C` disagrees and cannot be blindly appended; the target next token is `D`. This example says nothing about sampling equivalence, which requires a mathematically defined acceptance and residual process.

If each target iteration verifies several accepted tokens, end-to-end latency can fall, but draft computation, verification cost and rejection frequency affect the result.

## 3. Apply the concept to native model engineering

An inference session needs a transaction boundary around tentative tokens: unaccepted tokens must not pollute committed K/V state, random-number generator state, counters or output bytes. After a rejection, reconstruct the committed prefix deterministically. Checkpoint identity must be pinned for the target and appropriately managed for the draft.

Leviathan, Kalman and Matias (ICML 2023) provide the theoretical algorithm for distribution-preserving speculative decoding. The bounded Umicom single-query kernel does not implement speculative decoding; this lesson introduces the separate scheduling and sampling problem.

## 4. Check the mathematical foundation

The related exercise is [Mathematics for AI — Unit 147](../11-maths-for-ai/147-follow-greedy-speculative-token-verification.md). Work out the arithmetic independently before inspecting an implementation.

## 5. Test your understanding

**Question:** In greedy speculative verification, can a proposed third token be kept after the target first disagrees at the second token?

<details>
<summary>Reveal the worked answer</summary>
<p>No. Later proposals were conditioned on a prefix containing a rejected token, so they must not be committed as if they came from the target.</p>
</details>

## 6. Key distinctions

The mathematical examples are deliberately small and inspectable. Changes to attention topology, positional schemes, quantisation and decoding policy require explicit model or algorithm contracts. A standalone operator test does not establish complete Transformer equivalence or measured inference acceleration.

## Continue learning

[259 — Compare IO-aware tiling with single-query streaming](259-compare-io-aware-tiling-with-single-query-streaming.md) · [261 — Understand continuous batching and request fairness](261-understand-continuous-batching-and-request-fairness.md) · [HTML learning path](../../courses/llm-from-scratch/efficient-decoding-learning-path.html)

*Service to Many Leads to Greatness.*
