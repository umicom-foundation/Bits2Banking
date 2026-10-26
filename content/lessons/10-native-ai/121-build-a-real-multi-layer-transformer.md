# Build a real multi-layer Transformer in C23

**Bits to Banking · Umicom Foundation**  
**Author:** Sammy Hegab · **Licence:** MIT  
**Level:** Progressive native C23 / AI engineering

## The engineering question

A Transformer block is not an entire language model. One block takes a matrix of token representations and returns a matrix of the same width. A *stack* sends that output into the next block. The Umicom Framework already owns the pre-layer-normalised block, so the correct next step is to compose several copies, not to write a second attention implementation.

For an input `X` of shape `[T, C]`, the first block returns `H1 = Block1(X)` and the second returns `H2 = Block2(H1)`. `T` is the number of token positions; `C` is the feature width. The blocks share an architecture but have **different trainable weights**. A token embedding table and a position embedding table produce the initial `X`; an output projection maps the final hidden state to vocabulary logits.

## Follow the Framework implementation

The new `UmiAiTrainingStackedDecoderCreate` owns a training tape and the parameter leaves for every layer. `UmiAiTrainingStackedDecoderLogits` performs one full-context forward evaluation. Each layer calls the already established `UmiAiTrainingTransformerBlockForward`, with the exact public parameter order. Applications use this Framework API; they do not calculate attention or maintain model tensors themselves.

```c
#include "umicom/ai/training/stacked_decoder.h"
UmiAiTrainingStackedDecoderConfig config = {
    16U, 4U, 8U, 12U, 2U, 2U, UINT64_C(20261026)
};
UmiAiTrainingStackedDecoder *model = NULL;
UmiStatus status = UmiAiTrainingStackedDecoderCreate(&config, &model);
/* Inspect status before using model; destroy it once when finished. */
```

Here the model has vocabulary 16, four positions, eight features, 12 feed-forward features, two attention heads and **two distinct Transformer blocks**. It remains deliberately small enough to inspect.

## What this does not provide

The old single-block checkpoint is not a stacked checkpoint. The stacked model is a separately identified family. It still uses learned absolute positions, FP32 tape arithmetic and a complete context forward pass. It is neither a modern GPU-scale model nor proof of useful prose generation.

## Practice

Draw the operations from token IDs through two blocks to logits. Which components are shared implementations, and which parameters must be independent?

<details><summary>Worked answer</summary>

Token IDs → token embeddings + learned position embeddings → Block 1 → Block 2 → logits projection. The same Framework operators implement both blocks, but their Q/K/V, normalisation and feed-forward parameter values are separate.

</details>

---

[Native stacked Transformer reading path](stacked-transformer-learning-path.md) · [Mathematics for AI](../11-maths-for-ai/stacked-transformer-mathematics.md)
