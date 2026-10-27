# Lesson 252 — Separate prefill from incremental decode

**Bits to Banking · Umicom Foundation**  
**Author:** Sammy Hegab  
**Course:** Building an LLM from Scratch · **Implementation language:** C23

**Learning objective:** Trace the different workloads for processing a prompt and one new token.

## 1. Understand the concept

**Prefill** consumes an existing prompt. It computes Transformer states and K/V projections for all prompt positions and installs the admitted rows in a cache. **Decode** consumes one newly sampled token at a time. For an unchanged prefix, previous layer-specific K/V rows can be reused; only the new token traverses layer normalisation, Q/K/V projection, attention, MLP and logits.

In a causal self-attention block with prompt length `T`, full prefill has approximately `T(T+1)/2` query–key pairs per head. One next-token decode step has `T+1` pairs per head. The difference in arithmetic shape does not account for all neural-network work: prefill also performs projections and feed-forward calculations, whereas incremental decode retains only useful historical results.

## 2. Work through the numbers

For a four-token prompt and one head, the causal prefill needs `1+2+3+4=10` query–key score pairs. The next token attends to five keys, so that decode step needs `5` pairs. Recomputing all five prefix queries would require `1+2+3+4+5=15` pairs. A true one-query kernel avoids the ten historical scores, although its scratch allocation, dispatch and cache reads may offset this saving for very small models.

## 3. Apply the concept to native model engineering

The existing stacked incremental session uses canonical tracing to prefill and to rebuild after context rollover. Its earlier one-token proposal path still invokes a full-row tape attention composition. The new standalone kernel is a candidate for replacing precisely that **inference-time attention calculation**, not prefill, training or the entire decoder.

A valid performance experiment separates time-to-first-token (which includes prefill) from per-token decode latency. Adding them together without reporting prompt length obscures what was optimised.

## 4. Check the mathematical foundation

The related exercise is [Mathematics for AI — Unit 139](../11-maths-for-ai/139-count-prefill-and-decode-score-pairs.md). Work out the arithmetic independently before inspecting an implementation.

## 5. Test your understanding

**Question:** A prompt of length six is followed by one generated token. How many score pairs does a one-head full seven-row causal calculation use, and how many does the seventh query alone use?

<details>
<summary>Reveal the worked answer</summary>
<p>Full causal work: <code>1+2+3+4+5+6+7=28</code> pairs. The last query alone uses seven pairs.</p>
</details>

## 6. Key distinctions

The mathematical examples are deliberately small and inspectable. Changes to attention topology, positional schemes, quantisation and decoding policy require explicit model or algorithm contracts. A standalone operator test does not establish complete Transformer equivalence or measured inference acceleration.

## Continue learning

[251 — Protect capacities, aliasing and atomic results](251-protect-capacities-aliasing-and-atomic-results.md) · [253 — Understand multi-query attention without rewriting a checkpoint](253-understand-multi-query-attention.md) · [HTML learning path](../../courses/llm-from-scratch/efficient-decoding-learning-path.html)

*Service to Many Leads to Greatness.*
