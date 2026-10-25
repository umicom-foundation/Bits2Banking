# Native AI — Save a Low-Rank Adapter Without Replacing the Base Model

**Bits to Banking · Umicom Foundation**  
**Author:** Sammy Hegab  
**Learning route:** [Matrix weights](../11-maths-for-ai/11-matrix-weights-and-training.md) → [low-rank adaptation](low-rank-adaptation-and-fine-tuning.md) → adapter checkpoint verification.

## Learning objectives

Distinguish complete-model checkpoints from small adapter snapshots; understand why an adapter must be bound to its exact frozen base; inspect portable bytes and a SHA-256 digest; and distinguish adapter-weight restoration from an exact continuation of an AdamW training run.

## 1. What does a low-rank adapter store?

A frozen dense projection computes `Y = XW`. A low-rank adaptation adds `ΔY = (XA)B`, leaving `W` unchanged. Here:

- `W` has shape `[inputChannels, outputChannels]` and is **nontrainable**.
- `A` has shape `[inputChannels, rank]` and is **trainable**.
- `B` has shape `[rank, outputChannels]` and is **trainable**.

The adapted output is `Y = XW + (XA)B`. During training, the Framework tape computes gradients for A and B. It does not turn the base projection into a second mutable copy.

For `inputChannels = 128`, `outputChannels = 128`, `rank = 8`, the base contains `16,384` weights; the adapter stores `128×8 + 8×128 = 2,048` weights. This is the trainable parameter count. It does not imply that every other part of the model is eight times smaller.

## 2. Why the base identity matters

Imagine adapting a source-code assistant based on frozen projection `W₁`. Later the application loads an updated model containing `W₂` but accidentally reuses A and B trained for `W₁`. Matrix dimensions might still match, but the update has a different effect. **Matching shapes do not prove matching model weights.**

A trustworthy adapter snapshot therefore records an SHA-256 fingerprint of the **actual base projection values**. On import, the Framework hashes the proposed base again and rejects a mismatch before it creates any new trainable tensor.

An SHA-256 digest proves that two byte representations agree to a very high degree of confidence; it is **not** a digital signature, a licence, a source authorisation or an assurance that a model is safe.

## 3. Read the portable snapshot structure

The Framework `UmiAiTrainingAdapterCheckpointExport` writes a bounded binary record. It contains a format identifier, byte-order-explicit dimensions, SHA-256 of the frozen base, two row-major float32 matrices (A then B), and a final SHA-256 over all prior bytes.

All integer fields and float32 values use **little-endian** byte ordering. The importer checks format and lengths, finite numerical values, the snapshot checksum and the frozen-base digest before creating tape-owned leaves. No checkpoint bytes are executed as instructions.

This is an adapter snapshot, **not a complete decoder model** and **not an AdamW optimiser checkpoint**. Exact continuation of AdamW requires its moment buffers, step count, the original learning-rate schedule and its approved training-source identity.

## 4. Export into caller-owned memory

```c
#include "umicom/ai/training/adapter_checkpoint.h"
#include <stdlib.h>

/* projection is an existing, caller-owned, trained Framework adapter. */
size_t snapshotCapacity = 0U;
UmiStatus status = UmiAiTrainingAdapterCheckpointSize(
    &projection, &snapshotCapacity);

if (status == UMI_STATUS_OK) {
    unsigned char *snapshot = malloc(snapshotCapacity);
    if (snapshot != NULL) {
        size_t bytesWritten = 0U;
        status = UmiAiTrainingAdapterCheckpointExport(
            &projection, snapshot, snapshotCapacity, &bytesWritten);
        /* Review status and bytesWritten before using or persisting bytes. */
        free(snapshot);
    }
}
```

The service returns a complete buffer only on success and does **not** write a file. File storage and distribution remain the responsibilities of existing Framework output, signing and release services. The example intentionally does not publish model weights to a public repository.

## 5. Restore only against the correct frozen base

```c
UmiAiTrainingLowRankProjection restored = {0};
UmiStatus status = UmiAiTrainingAdapterCheckpointImport(
    tape, originalBaseWeights, originalBaseCount,
    snapshotBytes, snapshotLength, &restored);
```

The imported base tensor remains nontrainable, while A and B are trainable leaves. The caller owns `tape`, the original array and the snapshot memory. On a mismatched digest or damaged record, `restored` and the pre-existing tape graph remain unchanged. As with all tape leaves, the imported handles remain valid only while their owning tape and retained graph nodes exist.

## 6. Apply independent acceptance tests

Test a successful export–import round trip with **non-zero** adapter values. Check both arrays exactly, verify the frozen base, corrupt one byte, try a different base with matching shape, truncate the record and embed a non-finite weight with an otherwise valid checksum. All malformed cases must fail without publishing partial weights.

The Framework's focused CTest name is `framework.ai.adaptation.adapter_checkpoint`. Passing it establishes that the snapshot contract behaves correctly for those test cases; it does not demonstrate that a full Umicom decoder uses LoRA in all its attention and feed-forward layers. End-to-end adapter placement, optimiser-state continuation and held-out model-quality qualification remain separate work.

## Practise and check

**A.** If the base weight matrix has 32 inputs and 64 outputs and rank 4, how many adapter values are trainable?  
**Answer.** `32×4 + 4×64 = 128 + 256 = 384`.

**B.** Why reject an adapter with valid dimensions but a different base fingerprint?  
**Answer.** The adapter was trained as a correction to another exact set of weights; equal dimensions do not establish compatible behaviour.

**C.** Why can this checkpoint not resume AdamW exactly?  
**Answer.** It contains adapter weights but not the optimiser's first and second moments, completed-step identity or training schedule.

**Key lesson:** Portable bytes, exact base binding and fail-closed restoration are necessary foundations for future fine-tuning; they are not substitutes for controlled model training and evaluation.
