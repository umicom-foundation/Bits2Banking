# Fine-Tune Real Transformer Projections with Response-Only Loss

**Bits to Banking · Umicom Foundation**  
**Author:** Sammy Hegab  
**Implementation authority:** Umicom Framework, native C23

## Learning outcome

Connect three previously separate ideas: a real decoder checkpoint, low-rank
adapters in the Transformer's attention/feed-forward projections, and
assistant-response-only cross-entropy. By the end, you should be able to run a
bounded experiment, inspect frozen-model identity and explain exactly what
changes during a training step.

This lesson builds on [projection adaptation](adapt-attention-and-feed-forward-projections.md),
[assistant-response windows](prepare-assistant-response-training-windows.md)
and [selected-token cross-entropy](selected-token-cross-entropy-in-c23.md).

## 1. What changed in the Framework?

The canonical Umicom native decoder already owns token embeddings, learned
absolute positions, one pre-layer-normalised Transformer block, a vocabulary
projection, gradients, optimisation and checkpoints. The new
`UmiAiTrainingDecoderProjectionAdapter` composes those existing components.

Unlike the earlier **logit-residual adapter**, this adapter inserts low-rank
corrections into the actual Transformer projection operations. The caller
selects any nonempty combination of Query, Key, Value, attention output,
feed-forward expansion and feed-forward reduction.

The implementation creates a separate Framework training tape with **frozen
copies** of the decoder's canonical parameters and only the selected adapter
matrices marked trainable. This prevents an important lifetime error: the
historical decoder rewinds its own tape to exactly fifteen parameter leaves,
so attaching new adapter leaves directly there would make them disappear.

An exact SHA-256 of the decoder's canonical checkpoint is recorded at creation
and checked before each public adapter operation. Merely checking shapes or
training-step counts is not enough: a different checkpoint may share both.

## 2. Count trainable parameters

For one dense projection `W` of shape `[inputChannels, outputChannels]`, a
rank-`r` residual uses two matrices:

- `adapterDown`: `[inputChannels, r]`
- `adapterUp`: `[r, outputChannels]`

Therefore the additional trainable parameter count is:

`r × (inputChannels + outputChannels)`.

Suppose our educational decoder uses eight channels, a feed-forward width of
sixteen, and adapter rank two. Four chosen projections contain:

| Projection | Original shape | New trainable values |
| --- | --- | ---: |
| Query | `8 × 8` | `2 × (8 + 8) = 32` |
| Key | `8 × 8` | `32` |
| Attention output | `8 × 8` | `32` |
| Feed-forward reduction | `16 × 8` | `2 × (16 + 8) = 48` |
| **Total** | | **144** |

The original weight matrices remain frozen. There are eight trainable adapter
matrices (two for each chosen projection), not four.

## 3. A supervised training window

The Framework's byte tokenizer uses four reserved IDs and maps byte `b` to
`b + 4`. The supervised-window service prepares:

`stream = [BOS] + prompt + completion + [EOS]`.

For a one-byte prompt `Q`, one-byte completion `A`, and context length four:

| Position | Input token | Next-token target | Supervise? |
| ---: | --- | --- | :---: |
| 0 | `BOS` | `Q` | No |
| 1 | `Q` | `A` | Yes |
| 2 | `A` | `EOS` | Yes |
| 3 | `PAD` | `PAD` | No |

The loss is averaged over **two selected targets**, not four positions.
Prompt and padding tokens still contribute context but are not themselves
chosen as prediction targets. The model's causal attention prevents later
tokens from influencing earlier ones.

## 4. Use existing Framework contracts in native C23

The following is an excerpt for a programme that already owns a reviewed,
qualified `UmiAiTrainingDecoder *model`:

```c
#include "umicom/ai/training/decoder_projection_adapter.h"
#include "umicom/ai/training/supervised_window.h"
#include <stdint.h>

UmiAiTrainingDecoderProjectionAdapter *adapter = NULL;
const uint32_t selected = UMI_AI_DECODER_ADAPT_QUERY |
    UMI_AI_DECODER_ADAPT_KEY |
    UMI_AI_DECODER_ADAPT_ATTENTION_OUTPUT |
    UMI_AI_DECODER_ADAPT_FEED_FORWARD_DOWN;

UmiStatus status = UmiAiTrainingDecoderProjectionAdapterCreate(
    model, selected, 2U, UINT64_C(41), &adapter);

const uint8_t question[] = {'Q'};
const uint8_t answer[] = {'A'};
size_t inputs[4] = {0}, targets[4] = {0};
uint8_t mask[4] = {0};
UmiAiTrainingSupervisedWindowInfo window = {0};

if (status == UMI_STATUS_OK)
    status = UmiAiTrainingSupervisedByteWindowBuild(
        question, sizeof(question), answer, sizeof(answer), 4U,
        inputs, 4U, targets, 4U, mask, 4U, &window);

UmiAiTrainingDecoderProjectionStep report = {0};
if (status == UMI_STATUS_OK)
    status = UmiAiTrainingDecoderProjectionAdapterTrainStep(
        adapter, inputs, targets, mask, 4U, 0.08F, &report);

UmiAiTrainingDecoderProjectionAdapterDestroy(adapter);
```

All numerical operations execute inside Framework. The application does not
copy the Transformer's attention calculation or implement a second optimiser.

## 5. What a successful training step proves

For each call, the Framework computes a forward graph using the copied frozen
weights and current adapter weights, selects supervised vocabulary-logit rows,
computes existing cross-entropy, propagates gradients with `Backward` and
updates **only the adapter leaves** using `SgdStepMany`. It then rolls back
all transient graph nodes, retaining frozen and trainable leaves.

The reported cross-entropy is measured **before** the step's update. To
measure improvement, call `Evaluate` again after training and compare the
same held-out example or an appropriately separated evaluation set.

The original decoder retains its exact checkpoint bytes. If someone trains or
replaces the borrowed decoder, the adapter refuses further operations with
`UMI_STATUS_INVALID_STATE`. This is an identity check, not a thread lock:
callers must still serialise decoder access.

## 6. Run the real native regression

```powershell
Set-Location "C:\umicom\Umicom-Applications"
$env:Path = "C:\msys64\ucrt64\bin;$env:Path"

cmake -S ".\framework\learning\native-ai-decoder-projections" `
    -B ".\build\windows-ucrt64-decoder-projections-debug" `
    -G Ninja -DCMAKE_BUILD_TYPE=Debug -DBUILD_TESTING=ON

cmake --build ".\build\windows-ucrt64-decoder-projections-debug" `
    --target umicom-ai-training-decoder-projection-adapter-test `
    --parallel 2

ctest --test-dir ".\build\windows-ucrt64-decoder-projections-debug" `
    -R '^framework\.ai\.adaptation\.decoder_projection$' `
    --output-on-failure --no-tests=error
```

The regression must run against the **actual current Framework sources**.
A passing syntax check alone does not verify neural numerical equivalence.

## Exercises

1. If rank is four rather than two, how many trainable values are added for
   an `8 × 8` projection? **64**, from `4 × (8 + 8)`.
2. Why does adapter-up start at zero? The initial low-rank residual is zero,
   so the first prediction reproduces the frozen base's computation.
3. Why copy original parameters into a separate tape? The original decoder's
   parameter-prefix rewind was not designed to retain additional adapter
   leaves after a call.
4. Does success qualify a production language assistant? **No.** This is a
   small single-block FP32 experiment. Useful training requires reviewed data,
   held-out evaluation, model release controls and scalable implementation.

**Key point:** Genuine Transformer projection fine-tuning can be composed from
existing Framework mathematics without changing the historical decoder or
training it unintentionally.
