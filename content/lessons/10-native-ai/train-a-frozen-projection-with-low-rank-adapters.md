# Fine-Tuning Laboratory — Train a Frozen Projection with Low-Rank Adapters

**Bits to Banking · Umicom Foundation · Sammy Hegab**  
**Implementation:** native C23 Umicom Framework · **Level:** introductory/intermediate

## Learning objectives

By the end of this lesson you should be able to distinguish full-parameter fine-tuning from a low-rank adapter, calculate the shape of the adapter parameters, explain why the frozen base remains unchanged, perform a supervised update with existing Framework services and interpret the result without describing it as complete LLM fine-tuning.

## 1. Why adapt rather than copy a model?

In **full fine-tuning**, an optimisation procedure can adjust some or all of a pretrained model's original parameters. This may be expensive when the model has many parameters, and it complicates the storage and lifecycle of different domain variants.

In **low-rank adaptation**, we retain an original matrix and learn a smaller correction. Consider a row-vector input `X` with `I` features and a base projection `W` from `I` to `O` features. The original output is:

`Ybase = XW`

Introduce two trainable matrices `A` with shape `[I,r]` and `B` with shape `[r,O]`, where rank `r` is smaller than the original dimensions. The adapted output is:

`Yadapted = XW + (XA)B`

Both terms produce an output of width `O`, so addition is valid. The current educational Framework primitive stores the low-rank scale directly in the trainable values; it does **not** expose an additional alpha/r scaling option. That option may be introduced later under an explicit compatibility contract.

## 2. Count parameters

Suppose `I = O = 64` and rank `r = 4`.

- Original matrix: `64 × 64 = 4,096` parameters.
- Adapter A: `64 × 4 = 256` parameters.
- Adapter B: `4 × 64 = 256` parameters.
- Adapter total: `512` trainable parameters.

The adapter therefore trains 512 values instead of 4,096 values **for this projection**. It still requires access to the frozen 4,096-value base matrix for inference; low-rank adaptation does not eliminate that matrix from memory.

## 3. What the Framework already owns

The current Framework exposes `UmiAiTrainingLowRankCreate`, `UmiAiTrainingLowRankForward` and `UmiAiTrainingLowRankTrainables`. A successful creation places the base as a **nontrainable** tape leaf, and A/B as **trainable** leaves. A begins with seeded small weights and B begins with zeros. Consequently, before training, `Yadapted = XW` exactly for valid shapes: the initial correction `(XA)B` is zero.

The new training-step service `UmiAiTrainingLowRankTrainStep` composes the established tape's matrix operations, squared-error loss, backpropagation and `UmiAiTrainingSgdStepMany`. It does not provide a second tensor implementation or a separate optimiser. It updates only A and B and restores temporary graph nodes after the step.

## 4. One complete C23 training call

The surrounding program already owns a tape, a projection and two tape-owned tensors called `input` and `target`. The tensors contain the same number of rows; the input has `projection.inputChannels` columns, and the target has `projection.outputChannels` columns.

```c
#include "umicom/ai/training/low_rank_training.h"

UmiAiTrainingLowRankStepReport progress = {0};
UmiStatus status = UmiAiTrainingLowRankTrainStep(
    tape, input, target, &projection, 0.12F, &progress);
if (status == UMI_STATUS_OK) {
    /* The reported MSE was observed before this weight update. */
    /* Read progress.lossBeforeUpdate and evaluate again if required. */
}
```

The result is a **supervised mean-squared-error (MSE) step**, not cross-entropy language-model training. Source code, labels or media transcripts are not automatically converted into tensor targets by this primitive. The application must supply reviewed, shape-compatible training tensors.

## 5. Understanding the backward pass

The loss compares predicted values with the chosen target values. `UmiAiTrainingBackward` computes gradients for the graph. Both A and B receive gradients, but the **optimizer's update list** contains only A and B. Since the base matrix is absent from that list, its weights remain frozen.

The adapter's B matrix begins at zero. On the first step, the down-projection A may initially receive zero gradient through the correction path, whereas B can receive a nonzero gradient. After B changes, subsequent steps may also update A. This is normal for zero-initialised output adapters.

The training helper records the tape checkpoint, computes forward/loss/backward, requests the atomic two-matrix SGD update, and removes only the temporary graph suffix. If an update is refused, the caller's report remains unchanged. The helper's result does not claim that any future downstream validation will pass.

## 6. Save and restore the adapter independently

The existing `UmiAiTrainingAdapterCheckpointExport` stores the two adapter matrices and a digest binding them to the precise frozen base projection. `UmiAiTrainingAdapterCheckpointImport` restores an adapter only when the base weights match the checkpoint's declared base digest and the checkpoint itself validates.

A content hash detects changed bytes but is not a digital signature. A deployment must separately establish that the model and adapter came from an authorised source.

An adapter weight checkpoint is **not** an exact training-resume checkpoint when a stateful optimiser such as AdamW is used: first and second moments, learning-rate schedule position, data-order RNG state and related metadata also matter. These require their own, tested continuation contract.

## 7. Why this is not yet a complete LLM fine-tuner

A Transformer contains many projections within attention and feed-forward layers, token embeddings, normalisation and a language-modelling loss. The current Framework training helper operates on **one frozen dense projection** with MSE. To fine-tune the actual decoder, the Framework will need opt-in adapter insertion into selected native Transformer projections, token-level cross-entropy training, compatible checkpoints and independently reviewed held-out evaluation.

Calling this one projection a production LLM would conceal important missing requirements: tokenizer compatibility, dataset lineage, resource budgets, optimiser recovery, inference parity, safety and model-quality evidence.

## Exercises with worked answers

1. **Shapes:** Input `[8,64]`, A `[64,4]`, B `[4,32]`. What is the correction's shape? **`[8,32]`**.
2. **Count:** For base `[64,32]` and rank 4, how many adapter weights? **`64×4 + 4×32 = 384`**.
3. **Ownership:** Why is the frozen base excluded from the SGD update? **The experiment is designed to learn a correction without modifying the original model.**
4. **Evaluation:** Is falling training MSE sufficient proof of a better programming assistant? **No**. It measures one bounded numerical objective; programming quality needs independent held-out tasks and safety checks.

**Follow-up reading:** [Matrix gradients](../11-maths-for-ai/11-matrix-weights-and-training.md), [backpropagation](../11-maths-for-ai/17-backpropagation-from-a-small-example.md), [memory rollback](../11-maths-for-ai/18-memory-budgets-and-rollback.md), and [adapter checkpoint identity](adapter-checkpoints-and-model-identity.md).
