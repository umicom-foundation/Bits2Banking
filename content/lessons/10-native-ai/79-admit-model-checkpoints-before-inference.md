# Lesson 79 — Admit native decoder checkpoints before inference

**Bits to Banking · Umicom Foundation**  
**Author:** Sammy Hegab  
**Implementation owner:** Umicom Framework (C23)

## Learning objectives

After this lesson you should be able to distinguish a well-formed model file from an *approved* model, explain why checkpoint and positional-policy identities must match, and use the existing Framework API without creating another model loader.

## 1. Model bytes and model meaning

A language model's checkpoint contains numerical weights. Two checkpoints can have the same tensor shapes and still describe different trained models. A separate position-policy record must identify both the checkpoint bytes and the rules used to place tokens in the decoder context. In the current native teaching decoder, positions are **learned absolute positions**; shifting a token changes its positional embedding.

The existing Framework's position record uses a fixed 128-byte binary representation. It records a checkpoint digest, model dimensions, training-step identity and a declared context mode. The historic generator fills a short context with beginning-of-sequence tokens on the **left**. The newer growing-prefix generator begins its first actual token at position zero. These conventions are not numerically interchangeable.

## 2. Check before constructing the model

The Framework owns `UmiAiTrainingPositionBoundCheckpointDecode`, not Bits2Banking. It receives caller-owned buffers and an explicitly selected context mode. It validates the separate record, its checksum, the exact checkpoint length and SHA-256, and only then loads the native decoder. After loading, it checks the model identity again.

```c
#include "umicom/ai/training/position_admission.h"

/* The caller obtained checkpointBytes and sidecarBytes from an approved source. */
UmiAiTrainingDecoder *model = NULL;
UmiStatus status = UmiAiTrainingPositionBoundCheckpointDecode(
    checkpointBytes, checkpointLength,
    sidecarBytes, sidecarLength,
    UMI_AI_POSITION_CONTEXT_GROWING_UNPADDED,
    &model);

if (status == UMI_STATUS_OK) {
    /* Only a completely verified model becomes caller-owned. */
    UmiAiTrainingDecoderDestroy(model);
}
```

**Pointer ownership:** `checkpointBytes` and `sidecarBytes` remain owned by the caller. On success, `model` must be destroyed by that caller. On failure, the output pointer remains unchanged; a partially decoded model is not published.

**Security:** SHA-256 proves byte agreement, not publisher identity. A malicious party could replace a checkpoint and recalculate the sidecar. File trust, provenance and signing must therefore be decided separately through authorised Framework controls.

## 3. Worked example

Consider two hypothetical checkpoints, A and B, each with eight context positions and the same vocabulary size. Their weights differ. A sidecar approved for A contains `SHA256(A)`. Loading B under that sidecar must fail even if both files parse correctly and have identical shapes. Equally, the right checkpoint with the wrong declared context mode must fail.

| Input | Expected decision | Reason |
| --- | --- | --- |
| Approved A + matching sidecar + declared context | Admit | Bytes and interpretation agree |
| B + sidecar for A | Reject | Checkpoint SHA-256 differs |
| A + mismatched generation context | Reject | Learned token positions differ |
| Unauthenticated A + internally consistent unsigned sidecar | Do not trust yet | Integrity is not authentication |

## 4. Practice and evidence

Explain the difference between a checksum, a digital signature and an explicit model-generation policy. Then corrupt one byte of a *copy* of a synthetic training checkpoint and check that the existing Framework admission regression rejects it without replacing an already held model pointer.

**Takeaway:** model loading is an authorised state transition, not merely parsing a binary file.

[Illustrated lesson](../../courses/llm-from-scratch/lessons/79-admit-model-checkpoints-before-inference.html) · [Previous lesson](78-write-and-verify-position-sidecars.md) · [Next lesson](80-qualify-policy-bound-generation-and-benchmarks.md)
