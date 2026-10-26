# Lesson 150 — Separate prefill work from decoding work

**Bits to Banking · Umicom Foundation**  
**Author:** Sammy Hegab  
**Level:** Native C23 and AI engineering.

## Learning objectives

Understand the core engineering invariant, work through a bounded example, identify what Umicom Framework already implements and distinguish verified facts from proposed improvements.

## 1. The idea from first principles

Inference usually begins with **prefill**: evaluate the supplied prompt to establish the model state needed for its next prediction. Then **decode** one token at a time. Both phases use the model, but their shapes and performance characteristics can differ.

For a model with four layers, eight prompt tokens and six generated tokens, a straightforward complete-context implementation performs eight token rows through each layer for every generation step. That is `4 × 8 × 6 = 192` token-layer rows. This does not count embeddings, the vocabulary projection, or the varying attention-score work.

If a genuinely qualified incremental cache could preserve all eight prompt positions and append only the five sampled tokens needed to produce six outputs, its optimistic token-layer count would be `(8 + 5) × 4 = 52`. **This is hypothetical:** the present stacked decoder does not provide that cache, and whether it is equivalent depends on model architecture and context-eviction semantics.

Report time to first token, prefill latency, inter-token latency and total elapsed time separately. Reducing a row count is not itself proof of a speed improvement.

## 2. Connect the lesson to Umicom Framework

The Framework's `UmiAiTrainingStackedGenerationSessionInspect` reports `computedFullContextTokenRows` and `computedTransformerTokenLayerRows` for the **current** full-context implementation. The statistic describes requested work; it does not measure elapsed time or permit the application to claim a speculative cache was used.

Use `UmiAiTrainingStackedGenerationSessionCreate`, `Next`, `Inspect` and `Destroy` according to the existing borrowed-model lifetime contract. Do not train or destroy the model while a session exists.

## 3. Practice

**Question:** Why are there only five appended output tokens when six tokens are sampled, and why is `52` not an observed Framework benchmark?

<details><summary>Reveal the worked answer</summary>

The final token is sampled from the current state but need not be appended unless another sample is requested. The 52-row result assumes a future qualified cache; the current stacked generator recomputes full contexts.

</details>

## Further reading

Review [the multi-layer inference lesson](148-build-and-qualify-native-stacked-inference.md), [the introduction to the stacked decoder](121-build-a-real-multi-layer-transformer.md) and [the mathematics companion](../11-maths-for-ai/stacked-inference-mathematics.md).

*All numerical examples are educational; no model-generated source or financial transaction is executed. Service to Many Leads to Greatness.*
