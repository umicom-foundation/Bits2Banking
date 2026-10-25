# Fine-Tune Attention and Feed-Forward Projections with C23 Low-Rank Adapters

**Bits to Banking · Umicom Foundation**  
**Author:** Sammy Hegab  
**Implementation authority:** Umicom Framework (C23)

## Objective

Connect **trainable low-rank matrices** to the actual pre-layer-normalised Transformer block while keeping its dense projection weights unchanged. Reuse the Framework's existing tape, normalisation, causal multi-head attention, feed-forward network, reverse-mode gradients and transactional optimiser. This is more than adapting output logits, but it is **not yet full end-to-end adaptation of the opaque language-model decoder**.

Prerequisites: [low-rank residuals](../11-maths-for-ai/22-low-rank-residuals-and-frozen-models.md), [matrix shapes](../11-maths-for-ai/04-matrices-and-shapes.md) and [training gradients](../11-maths-for-ai/17-backpropagation-from-a-small-example.md).

## 1. Identify the six projections inside one block

The canonical block calculates:

```text
Input → LayerNorm → Query, Key, Value projections
      → Multi-head causal attention → Attention-output projection
      → Residual addition → LayerNorm
      → Feed-forward expansion → ReLU → Feed-forward reduction
      → Residual addition → Output
```

The six dense projections are Query (`Q`), Key (`K`), Value (`V`), attention output, feed-forward up and feed-forward down. The input, context size, number of attention heads and each projection's matrix dimensions remain those of the original block.

The new Framework extension provides a **projection hook** for each of these roles. A missing hook uses the original tape-owned matrix multiplication unchanged. The established `UmiAiTrainingTransformerBlockForward` API remains operational and delegates to the same canonical composition with no hook.

## 2. One projected result with a frozen base

For input matrix `X`, original weight `W` and rank-`r` matrices `A` and `B`:

```text
adapted(X) = XW + (XA)B
```

`W` has shape `[inputChannels, outputChannels]`. `A` has `[inputChannels, r]`; `B` has `[r, outputChannels]`. If `B` starts at zero, the new forward output initially equals `XW`, so the proposed adapter does not change the model before training.

Suppose input channels=4, output channels=6 and rank=2. The original projection has `4×6=24` base parameters, while its low-rank correction has `4×2 + 2×6 = 20` trainable values. This particular tiny example is not a dramatic compression; the method becomes beneficial for much wider projections where rank remains small.

In the Framework, `UmiAiTrainingLowRankCreate` owns the copied frozen base and two trainable leaves. `UmiAiTrainingLowRankForward` composes ordinary tape matrix multiplication and addition. It does not replace or bypass the automatic-differentiation owner.

## 3. Bind selected projections

```c
#include "umicom/ai/training/transformer_low_rank.h"

/* tape and block belong to the caller; queryAdapter and upAdapter were
 * created from the EXACT corresponding canonical weights on this tape. */
UmiAiTrainingTransformerLowRankBindings bindings = {
    .query = &queryAdapter,
    .feedForwardUp = &upAdapter
};

UmiAiTrainingTensor *output = NULL;
UmiStatus status = UmiAiTrainingTransformerBlockForwardLowRank(
    tape, input, &block, &config, &bindings, &output);
```

The call composes the same Transformer architecture and attention mathematics. Only selected projections receive the low-rank residual. The optional bindings can also select Key, Value, attention output or feed-forward down.

The wrapper checks the shape and **byte-exact frozen base values** against the canonical weight tensor before graph construction. This prevents a shape-identical adapter trained against another base from silently being attached. It does not authenticate a publisher: external checkpoint signatures and trusted-source approval remain separate obligations.

## 4. Train adapter leaves, not canonical weights

```c
UmiAiTrainingTensor *weights[UMI_AI_TRANSFORMER_LOW_RANK_MAX_TRAINABLES];
size_t weightCount = 0U;

UmiStatus status = UmiAiTrainingTransformerLowRankTrainables(
    &bindings, weights, UMI_AI_TRANSFORMER_LOW_RANK_MAX_TRAINABLES,
    &weightCount);

/* After the caller has built a real scalar loss and called Backward,
 * the existing tape owns the weight-update transaction. */
if (status == UMI_STATUS_OK)
    status = UmiAiTrainingSgdStepMany(tape, weights,
                                     weightCount, 0.01F);
```

The helper returns only each adapter's `A` and `B` leaves, in stable projection order. It rejects duplicate leaves and undersized output capacity. Training must retain the original leaves, build a complete loss graph, compute `Backward`, update only these leaves, then roll back temporary nodes to the saved graph checkpoint.

The existing Transformer can also be trained through its established methods; the adapter path does not remove them. This explicit separation avoids silently changing checkpoint or optimiser semantics.

## 5. Qualification gates

Before using the adapted block in any Umicom AI application, check:

1. **Initial parity:** With all adapter-up matrices zero, output matches the unchanged block for the same inputs and parameters within a predefined numerical tolerance.
2. **Frozen weights:** Byte-exact copies of canonical base parameters remain unchanged after adapter training.
3. **Gradient path:** Backward produces gradients for the selected adapter leaves, and the existing transactional optimiser can reduce a declared teaching loss.
4. **Graph lifetime:** Rollback returns the tape node count to its retained prefix after each iteration.
5. **Wrong-base rejection:** A shape-identical adapter with different base values is refused before graph construction.
6. **Unchanged legacy behaviour:** Existing Transformer and decoder tests continue to pass, with no adapters selected.

The native regression under `framework/tests/ai_training/test_training_transformer_low_rank.c` exercises these contracts. Run it through the existing `learning/native-ai-adaptation` CMake project. A passing focused block regression is **not** proof of decoder-level training, durable optimiser resume or general language-model competence.

## 6. Next engineering milestone

The decoder currently owns an opaque tape and parameters. Safe full-model fine-tuning requires an opt-in decoder composition that can attach the new Framework projection bindings at the correct lifecycle point, preserve base-model/checkpoint identity and apply an explicit response-token training loss. This must be qualified independently before being presented as complete fine-tuning.

**Practice:** For 128 input channels, 256 output channels and adapter rank 8, calculate the dense weight count (`32,768`) and trainable low-rank count (`3,072`). Explain why freezing `W` does not mean ignoring the gradient through the adapted projection's input.
