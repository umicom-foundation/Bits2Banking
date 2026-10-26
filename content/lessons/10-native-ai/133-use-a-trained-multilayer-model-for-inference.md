# Lesson 133 — Use a trained multi-layer model for inference

**Bits to Banking · Umicom Foundation**  
**Author:** Sammy Hegab  
**Topic:** Native C23 Transformers, inference and independent validation.

**Learning objective:** Follow the model's original fixed-context contract rather than changing its weights to make an application work.

## 1. Understand the engineering problem

The previous course created a separately identified stacked decoder with multiple pre-layer-normalised Transformer blocks. Inference is the read-only part of its lifecycle. Inputs are numerical token IDs; the decoder uses embeddings, positional embeddings, successive attention/MLP blocks and a vocabulary projection to produce one logit per candidate token. No new training step is necessary to ask the model for a prediction. That separation matters: an application should never change model weights merely because a user asks a question.

## 2. Follow a concrete example

Suppose the model has a context of four tokens, vocabulary size 260 and two Transformer layers. One call to `UmiAiTrainingStackedDecoderLogits` receives exactly four token IDs and produces a row-major `[4,260]` float array: 1,040 logits. Only the fourth row is used to choose the immediate next token. Repeating the operation after appending an output produces another full `[4,260]` result. Four decoded positions times two layers gives eight logical token-layer rows per prediction, not eight GPU operations.

## 3. Implement through the Framework

Use the new `UmiAiTrainingStackedGenerationSessionCreate`, `...Next` and `...Destroy` interfaces from `umicom/ai/training/stacked_inference.h`. They call the existing stacked decoder for actual logits and reuse the Framework's nucleus sampler. The session borrows the model; it never becomes an alternative owner of attention, tensor memory or optimisers. Its public output is one ID at a time. Alternatively, `UmiAiTrainingStackedGenerateNucleus` stages a fixed number of IDs and publishes them together.

## 4. Check the boundaries

This is a bounded experimental system: at most 64 output tokens per session. Its complete context is evaluated on every pull; no multi-layer KV cache has been introduced. Reproducible numeric tokens are not evidence that a model understands a language or can safely produce executable financial-system code. Display model identity, sampling policy and limited test scope in any educational viewer.

## Practice

**Question:** If a four-token model has three stacked Transformer layers, how many layer-token rows are evaluated for five generated tokens?

<details>
<summary>Reveal the worked answer</summary>

Each pull calculates four rows through each of three layers: `4 × 3 = 12`. Five pulls therefore request `5 × 12 = 60` layer-token rows. This is an accounting unit, not measured elapsed time.

</details>

## Continue

[Return to the native stacked inference learning path](stacked-inference-learning-path.md). For the mathematical background, read the [stacked inference mathematics guide](../11-maths-for-ai/stacked-inference-mathematics.md). The canonical APIs are in `framework/include/umicom/ai/training/`; implementations and native tests remain in Umicom Framework, not in this educational repository.

*Service to Many Leads to Greatness.*
