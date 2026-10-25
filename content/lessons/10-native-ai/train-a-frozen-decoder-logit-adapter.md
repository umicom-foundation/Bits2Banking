# Native AI laboratory — Fine-tune a frozen decoder's output logits

**Bits to Banking · Umicom Foundation**  
**Author:** Sammy Hegab  
**Implementation owner:** Umicom Framework (C23)

## Learning objectives

Train a small adapter using a **real Umicom decoder's logits**, minimise token-level cross-entropy, preserve the original decoder and explain the differences between logit-head adaptation, projection-level LoRA and complete Transformer fine-tuning.

## 1. Start with the existing model

Umicom Framework already owns a small decoder-only Transformer, token/position embeddings, an automatic-differentiation tape, categorical cross-entropy and optimiser operations. Reimplementing any of those mathematical kernels inside Bits2Banking would produce two competing authorities.

The new `UmiAiTrainingDecoderLogitAdapter` borrows the existing `UmiAiTrainingDecoder` model. It obtains the model's logits using **`UmiAiTrainingDecoderLogits`**, then creates a *separate* training tape for two small correction matrices. The decoder's original parameters never become parameters of the adapter's optimiser.

For an input sequence containing `T` token positions and vocabulary size `V`, the frozen decoder produces `Z` with shape `[T, V]`. The adapter calculates:

`Z_adapted = Z + (Z × D) × U`.

`D` has shape `[V, rank]`; `U` has shape `[rank, V]`. Their elements, not the decoder's parameters, receive SGD updates. The adapter has an independent update count.

## 2. The actual token-loss objective

A next-token training example supplies one context and one target token for every position. If the input token IDs are `[4, 5, 6, 7]`, a shifted next-token target can be `[5, 6, 7, 8]`, provided every value belongs to the model's vocabulary. This teaches which next ID follows each observed input prefix under causal masking.

Mean cross-entropy uses all declared positions. This experiment deliberately does not implement assistant-response-only masking, context-length expansion or backpropagation into Transformer attention blocks. Such features need separately qualified contracts.

## 3. Native C23 usage

```c
#include "umicom/ai/training/decoder_logit_adapter.h"

/* The caller created a real native Umicom decoder called decoder. */
UmiAiTrainingDecoderLogitAdapter *adapter = NULL;
UmiStatus status = UmiAiTrainingDecoderLogitAdapterCreate(
    decoder, 3U, UINT64_C(71), &adapter);

if (status == UMI_STATUS_OK) {
    const size_t inputs[] = {4U, 5U, 6U, 7U};
    const size_t targets[] = {5U, 6U, 7U, 8U};
    UmiAiTrainingDecoderLogitStep report = {0};
    status = UmiAiTrainingDecoderLogitAdapterTrainStep(
        adapter, inputs, targets, 4U, 0.10F, &report);
    if (status == UMI_STATUS_OK) {
        /* report.crossEntropyBeforeUpdate is the loss before this update. */
    }
    UmiAiTrainingDecoderLogitAdapterDestroy(adapter);
}
```

The example assumes the decoder configuration has a four-token context and a vocabulary containing these IDs. The adapter owns its private tape; the caller owns the decoder. Destroy the adapter **before** destroying or training the borrowed decoder.

## 4. Verify the invariants

1. At creation, the adapter's up matrix is zero; its logits should equal the frozen decoder's logits within numerical tolerance.
2. A valid supervised step updates only adapter matrices, not frozen decoder weights.
3. A held-out call to `UmiAiTrainingDecoderLogitAdapterEvaluate` computes loss without performing an update.
4. Invalid token IDs, insufficient output capacity and non-finite learning rates must be rejected before publishing outputs.
5. Every training step discards temporary graph nodes; repeated training must not grow the tape indefinitely.
6. Training the decoder after creating the adapter invalidates its frozen-model identity; the old adapter must be recreated against the changed model.

## 5. What this does not establish

A lower loss on a tiny teaching sequence does **not** mean the application has acquired general coding competence. A logit-residual correction also differs from projection-level LoRA applied to Q/K/V/MLP weights. Extending the actual Transformer interior requires a separate model-interface, checkpoint and optimiser-state design. The new component is one tested, reusable step toward that destination.

**Practical task:** run `framework.ai.adaptation.decoder_logit_adapter` in the existing native adaptation CTest project, record the first and final objective values, and compare the original decoder's logits before and after adapter training.

[Mathematics: cross-entropy](../11-maths-for-ai/21-cross-entropy-for-native-fine-tuning.md) · [Mathematics: low-rank residuals](../11-maths-for-ai/22-low-rank-residuals-and-frozen-models.md) · [Video narration](../../videos/scripts/llm-from-scratch/native-decoder-logit-adaptation.md)
