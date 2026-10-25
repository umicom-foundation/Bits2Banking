# Lesson 77 — Bind Position Policies to Checkpoint Identity

**Bits to Banking · Umicom Foundation · Sammy Hegab**

## Learning objectives

Separate a decoder's **positional mathematics** from a generation API's **context layout**, and verify a model's identity and permitted generation policy before inference. Understand why an unchanged checkpoint cannot be silently reinterpreted as a new Transformer architecture.

## 1. Architecture versus request policy

The current small Umicom decoder uses **learned absolute positional embeddings**. Each token position has a trainable vector; changing the positional rule changes the mathematical function computed by the decoder.

Two supported request conventions use that same architecture:

- **BOS-left-padded context:** short prompts are aligned to the right edge of a full fixed context.
- **Growing unpadded context:** short prompts begin at position zero and extend as tokens arrive.

Both can be valid for their declared purpose. They are not numerically interchangeable because a real token can occupy different learned positions.

For an eight-token context and the three byte tokens representing `int`, the left-padded policy places them at positions 5, 6 and 7; the unpadded policy uses positions 0, 1 and 2. Same bytes, same model parameters and same sampling seed do **not** imply identical logits.

## 2. Model identity must include the right evidence

A checkpoint's SHA-256 identifies its bytes; it is not a description of how a caller placed a prompt. A complete inference record should include both the immutable checkpoint identity and the declared context policy.

Use the existing Framework `UmiAiTrainingPositionContract` rather than inventing an application-local record. The contract describes the current architecture, supported position strategy, context policy, rollover behaviour, model configuration and completed optimisation steps.

```c
#include "umicom/ai/training/position_contract.h"

UmiAiTrainingPositionContract approval = {0};
UmiStatus status = UmiAiTrainingPositionContractBuild(
    model, UMI_AI_POSITION_CONTEXT_GROWING_UNPADDED, &approval);
if (status == UMI_STATUS_OK) {
    status = UmiAiTrainingPositionContractVerify(
        model, &approval, UMI_AI_POSITION_CONTEXT_GROWING_UNPADDED);
}
```

This excerpt assumes `model` is already created, trusted and owned by the caller. The service borrows it and performs no training.

## 3. Why changing to RoPE is not a metadata edit

Rotary positional embeddings (RoPE) rotate pairs of query and key coordinates according to position. That mechanism is different from adding learned absolute-position vectors before attention. Merely labelling an existing checkpoint as RoPE cannot make its stored weights behave like a separately trained rotary model.

A real migration would require its own architecture identifier, trained or otherwise demonstrably compatible parameters, checkpoint schema, forward and backward tests, and inference/rollover qualification. Current Framework position contracts deliberately refuse unsupported position schemes.

## 4. Admission examples

| Situation | Decision |
|---|---|
| Exact checkpoint, approved unpadded policy, matching request | Admit |
| Exact checkpoint, unpadded declaration, padded request | Reject |
| Updated checkpoint, old identity declaration | Reject |
| Learned-absolute checkpoint declared rotary | Reject |
| Unsupported metadata format | Reject |

A matching hash of **unsigned** data is not independent evidence that the source publisher is trusted.

## Practice

1. Why can two different context policies share the same checkpoint hash? **They use identical stored weights but construct different numerical inputs.**
2. If one token moves from absolute position 5 to zero, what changes? **Its positional embedding and therefore potentially all downstream values.**
3. Which layer should choose the policy in Umicom Studio? **An explicit application request checked by the shared Framework contract.**

[Illustrated HTML lesson](../../courses/llm-from-scratch/lessons/77-bind-positions-to-checkpoint-identity.html) · [Mathematics: rotary position](../11-maths-for-ai/07-angles-and-rotary-position.md)
