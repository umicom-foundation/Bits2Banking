# Lesson 85 — Build Rotary Attention on the Existing Training Tape

**Bits to Banking · Umicom Foundation**  
**Author:** Sammy Hegab  
**Implementation authority:** Umicom Framework (C23)

## Purpose and prerequisites

A rotary rotation can produce correct numbers and still be disconnected from the parameters we want to train. This lesson connects RoPE to Umicom's existing reverse-mode automatic-differentiation tape. It follows the original [illustrated lesson](../../courses/llm-from-scratch/lessons/85-build-rotary-attention-on-the-training-tape.html) and uses [Maths Unit 17](../11-maths-for-ai/17-backpropagation-from-a-small-example.md) for a small chain-rule example.

## 1. A graph is more than a value

Suppose the original query projection is `q = xW`, where `W` is trainable. A position rotation produces `r = R(p)q`. The final loss depends on `r`, possibly through masked attention and an output projection.

A correct training graph must retain the chain:

```text
W → matrix multiplication → q → rotary rotation → attention → loss
                                        ← backwards gradients ←
```

If we copy `q` into a disconnected array, rotate those numbers and create a fresh unrelated tensor, the tape can no longer propagate the loss gradient all the way back to `W`. The **value** of the rotation might still be correct, while the **derivative** is wrong or missing.

## 2. Express a rotation with tape operations

For column-vector notation, `y = R(p)x`. The tape uses row-major row-vector operations, so the equivalent expression is `y = xMₚ`, with `Mₚ = R(p)ᵀ`.

The established research implementation constructs fixed rotation matrices and uses the existing tape's matrix multiplication, row-selection, addition and masked multi-head attention. The rotation is not itself a trained parameter. Tape operators own gradient propagation.

This graph composition is intentionally small: no more than eight token rows and eight projected channels. It is a teaching and correctness bridge, not a high-throughput production kernel.

## 3. Native Framework call

```c
#include "umicom/ai/training/rotary_tape.h"

/* tape and queries/keys/values are already valid tape-owned tensors. */
const UmiAiTrainingRotaryConfig rotary = {2U, 2U, 10000.0};
UmiAiTrainingTensor *attended = NULL;
UmiStatus status = UmiAiTrainingRotaryTapeAttention(
    tape, queries, keys, values,
    &rotary, 2U, 2U, NULL, 0U, &attended);
```

Here the tensor has two token rows, two attention heads and two channels in each head. A successful call publishes a tape-owned result, which can become an input to ordinary loss and `UmiAiTrainingBackward` operations.

## 4. Compare against independent mathematical evidence

A complete qualification combines three independent expectations:

1. **Forward values:** The tape's rotation must agree with the standalone Framework rotary function for the same fixed projection and position.
2. **Backward values:** Gradients obtained from `UmiAiTrainingBackward` must agree with the documented adjoint or a central finite-difference calculation.
3. **Ownership and rollback:** A failed tape operation must not publish a partial output or retain newly created nodes. Existing graph nodes survive, but previous gradients may be invalidated by rollback.

The second test is crucial. A forward-only unit test cannot establish that a learnable projection receives the correct gradient.

## 5. Connect this lesson to projection fine-tuning

The Framework also supports bounded, frozen-base low-rank projections. The new [projection-adaptation lesson](adapt-attention-and-feed-forward-projections.md) uses those components inside an existing pre-layer-normalised Transformer block. That path composes normalisation, attention and feed-forward operations while updating **only adapter leaves**. It is separate from the RoPE training experiment; attaching low-rank adapters does not convert a learned-absolute decoder into a rotary model.

Both capabilities illustrate the same design principle: add small, validated graph compositions around the canonical tape rather than creating an independent automatic-differentiation engine in an application.

## Exercises

1. Explain why `R(p)` is determined by the token position but `W` is trainable.
2. If the tape computes the right rotated value but a disconnected tensor receives no gradient, is training correct? **No.**
3. For two heads with two channels each, how many projected channels belong to one token? **Four.**
4. Why must a caller run `Backward` again after `TapeRollback` invalidates gradient readiness?

**Next:** [Lesson 86 — Mathematics behind the rotary training tests](86-learn-maths-alongside-rope-training.md).
