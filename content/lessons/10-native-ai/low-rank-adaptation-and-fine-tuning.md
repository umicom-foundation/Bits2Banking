# Low-Rank Adaptation: A First Practical Step Towards Fine-Tuning

**Bits to Banking · Umicom Foundation**  
**Author:** Sammy Hegab  
**Language:** C23  
**Implementation authority:** Umicom Framework

## What we are building

Training a Transformer **from scratch** adjusts its parameters from an initial random state. **Fine-tuning** starts with existing learned parameters and adapts them to a different collection of reviewed examples. Full fine-tuning would update many or all weights. Parameter-efficient fine-tuning instead trains a smaller set of additional parameters.

Low-rank adaptation (LoRA) is one approach. A large dense matrix can be kept frozen while two smaller matrices learn an adjustment. The initial Framework educational implementation supports a **single dense projection on the native training tape**. It is a reusable mathematical component; it is **not yet** complete fine-tuning of every attention and feed-forward projection in the Umicom decoder.

## Work through the matrix idea

Suppose `X` is a row of two input values and `W` is a 2×2 dense projection. A standard projection is `Y = XW`. Low-rank adaptation adds two matrices, `A` with shape 2×r and `B` with shape r×2:

\[
Y = XW + (XA)B.
\]

Here `r` is the selected rank. The existing weights `W` stay fixed. `A` and `B` are trainable. In a larger projection with 512 inputs and 512 outputs, full adaptation would adjust `512×512 = 262,144` weights. At rank 8, the two adapter matrices contain `512×8 + 8×512 = 8,192` trainable values: a **96.875% reduction** in the count of parameters being trained for that projection. The total memory saving also depends on gradients, optimiser states, activations and storage format.

A common LoRA convention multiplies the adapter output by `α/r`, where `α` is a configurable scaling factor. The initial Framework primitive expresses this effective scale through its adapter matrix values; it does **not** yet expose a separate `alpha` argument. That distinction matters when comparing experiments across software.

## Why the up projection starts at zero

The Framework seeds the down matrix `A` reproducibly with small nonzero values and initialises `B` with zero values. At first, `(XA)B = 0`, so the adapted model reproduces the original frozen projection exactly. After calculating a loss and performing backpropagation, gradients can update the adapter matrices without changing `W`.

This makes the first forward result easy to verify independently. It also means that `A` may initially receive zero gradient through a zero `B`; updates to `B` begin the adaptation process.

## The existing tape owns training

The reusable C23 operations are declared in `umicom/ai/training/low_rank.h`. Their composition uses existing Framework methods:

1. `UmiAiTrainingLowRankCreate` creates a frozen base leaf and two trainable leaves.
2. `UmiAiTrainingLowRankForward` composes `UmiAiTrainingMatmul` and `UmiAiTrainingAdd`.
3. `UmiAiTrainingMeanSquaredError` or an appropriate existing loss operator creates a scalar error.
4. `UmiAiTrainingBackward` differentiates the graph.
5. `UmiAiTrainingSgdStepMany` or the existing AdamW optimiser updates **only** the two adapter leaves.
6. `UmiAiTrainingTapeRollback` discards temporary forward and loss nodes before the next iteration.

Example of the creation boundary:

```c
#include "umicom/ai/training/low_rank.h"

/* Caller already owns a valid training tape. The base matrix is row-major. */
const float frozenProjection[4] = {1.0F, 0.0F,
                                   0.0F, 1.0F};
UmiAiTrainingLowRankProjection adapter = {0};
UmiStatus status = UmiAiTrainingLowRankCreate(
    tape, frozenProjection, 2U, 2U, 2U,
    UINT64_C(37), &adapter);
```

No new random-number generator or private neural-network implementation is required. The tape retains the parameter tensors and the caller controls their lifetime.

## What must be tested before adding adapters to a full decoder?

- **Baseline parity:** a newly initialised adapter must reproduce `XW` when its up matrix is zero.
- **Trainability:** the adapter loss should decrease on a small, independently specified target.
- **Frozen weights:** the base parameter values must remain unchanged after optimiser steps.
- **Gradient checks:** compare automatic differentiation with finite differences, including adapter shapes and transpose conventions.
- **Failure atomicity:** invalid ranks and insufficient tensor capacities must leave earlier tape nodes and caller outputs intact.
- **Checkpointing:** a complete training continuation must preserve both adapter weights and optimiser moments, not just the frozen model.
- **Real-model integration:** adapters must be wired into chosen decoder projections and validated end to end before the system is called a fine-tuned language model.

## Exercises

**1.** For a 768×768 projection with rank 16, calculate adapter parameters.  
**Answer:** `768×16 + 16×768 = 24,576` values, compared with `589,824` dense weights.

**2.** Why does adapter-only training need a known frozen-model revision?  
**Answer:** The same adapter weights applied to different base weights may produce different results. Adapter identity includes the compatible base model and selected projection.

**3.** Why is a lower loss on a tiny training fixture insufficient to claim useful language-model fine-tuning?  
**Answer:** The fixture tests only a mathematical component. Real language models also require tokenizer consistency, whole-network integration, held-out evaluation, meaningful tasks, permissioned data and deployment testing.

## Further study

Read the [document and media preparation lesson](review-and-prepare-documents-media-for-training.md), then review the Framework's `transformer.h`, `decoder.h`, `optimizer.h` and dataset-manifest contracts. Those are the existing building blocks for an eventual complete fine-tuning pipeline.
