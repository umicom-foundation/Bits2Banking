# Lesson 149 — Why upper-layer KV caches need their full hidden-state history

**Bits to Banking · Umicom Foundation**  
**Author:** Sammy Hegab  
**Level:** Native C23 and AI engineering.

## Learning objectives

Understand the core engineering invariant, work through a bounded example, identify what Umicom Framework already implements and distinguish verified facts from proposed improvements.

## 1. The idea from first principles

An attention key is not necessarily a function of the token ID alone. In a first Transformer block, a key may be projected from a fixed token embedding and a fixed position encoding. In a second block, the key is projected from the output of the first block. That output has already incorporated earlier context through causal attention.

Imagine a window with tokens `A B C D`. The first block computes representations for all four positions. When `A` is removed, the visible window becomes `B C D E`. A fresh calculation for `B` may no longer include `A`. But a cached second-block representation of `B` originally contained some influence from `A`. Reusing it and recomputing it from the truncated window are **different computations**, even when position encodings are rotary.

RoPE makes position-dependent query/key comparisons possible without relabelling retained absolute indices; it does **not** erase earlier information from already-computed upper-layer states. A multi-layer cache needs a precise context policy: preserve historical hidden states, or recompute truncated-window states and compare under the new policy. Neither policy can be mixed silently with old checkpoints.

## 2. Connect the lesson to Umicom Framework

The Framework's `UmiAiTrainingStackedDecoderLogits` remains the numerical reference for a complete fixed context. Its current streaming service recomputes that context at every step; it does not claim a qualified multi-layer cache. Keep the existing single-block `UmiAiTrainingRotaryWindow` research separate from a stacked decoder.

A credible test records the checkpoint identity, chosen positional semantics, prompt tokens, window length and exact logits at the eviction boundary. Compare **every vocabulary logit**, not only the most likely token. Use finite tolerances chosen before inspecting results.

## 3. Practice

**Question:** When the first token disappears from a three-layer model, why might the cached key for a surviving token in layer three disagree with a freshly recomputed key?

<details><summary>Reveal the worked answer</summary>

Its layer-three input depends on earlier layers that may already contain information from the removed token. Fixed rotary angles alone do not make these hidden-state histories equivalent.

</details>

## Further reading

Review [the multi-layer inference lesson](148-build-and-qualify-native-stacked-inference.md), [the introduction to the stacked decoder](121-build-a-real-multi-layer-transformer.md) and [the mathematics companion](../11-maths-for-ai/stacked-inference-mathematics.md).

*All numerical examples are educational; no model-generated source or financial transaction is executed. Service to Many Leads to Greatness.*
