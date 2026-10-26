# Lesson 152 — Design a numerical parity test across the first eviction

**Bits to Banking · Umicom Foundation**  
**Author:** Sammy Hegab  
**Level:** Native C23 and AI engineering.

## Learning objectives

Understand the core engineering invariant, work through a bounded example, identify what Umicom Framework already implements and distinguish verified facts from proposed improvements.

## 1. The idea from first principles

A newly implemented multi-layer cache should be measured at the exact transition where the context first becomes full and an old token is evicted. A cache that only passes short-prefix tests may silently return stale hidden states after that point.

Design three controlled input families: a prefix shorter than the context, a prefix exactly at capacity, and a sequence which extends at least two tokens beyond capacity. Use fixed, finite parameters and token IDs. Independently run the canonical complete-context decoder on the reference input for each state.

For every step compare the full vocabulary logits with a predeclared absolute and, where appropriate, relative tolerance. Also compare predicted token IDs and checkpoint bytes; these are different checks. The test must reject a non-finite logit even if another path produces the same non-finite value.

Do not assume that matching **only final sampled words** proves equal probability distributions. Two vectors can have the same largest index yet materially different other scores.

## 2. Connect the lesson to Umicom Framework

Keep the canonical `UmiAiTrainingStackedDecoderLogits` implementation unchanged as an independent reference. Only after an opt-in candidate demonstrates parity in the precise model semantics should a performance benchmark compare it with that reference. Add negative tests for malformed context lengths, stale checkpoints, invalid token IDs, memory exhaustion and failed allocation.

The present package documents that acceptance design. It does **not** introduce or certify a multi-layer KV-cache implementation.

## 3. Practice

**Question:** If both an optimised implementation and its reference select token 42, which additional evidence is needed?

<details><summary>Reveal the worked answer</summary>

Compare all finite vocabulary logits within justified tolerances across the entire prefix and rollover transition. Equal argmax does not imply equivalent sampling behaviour.

</details>

## Further reading

Review [the multi-layer inference lesson](148-build-and-qualify-native-stacked-inference.md), [the introduction to the stacked decoder](121-build-a-real-multi-layer-transformer.md) and [the mathematics companion](../11-maths-for-ai/stacked-inference-mathematics.md).

*All numerical examples are educational; no model-generated source or financial transaction is executed. Service to Many Leads to Greatness.*
