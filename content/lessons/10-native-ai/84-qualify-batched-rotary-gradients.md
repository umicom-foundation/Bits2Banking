# Lesson 84 — Qualify Batched Rotary Gradients

**Bits to Banking · Umicom Foundation**  
**Author:** Sammy Hegab  
**Implementation authority:** Umicom Framework (C23)

## Learning objectives

Move from a single rotary query/key pair to a tensor containing several sequences, positions and attention heads. Learn to distinguish a **storage row** from a **token's absolute position**, and independently validate the forward/backward operators. Follow the [illustrated explanation](../../courses/llm-from-scratch/lessons/84-qualify-batched-rotary-gradients.html) for the original examples.

## 1. Read the shape before writing code

A projected attention tensor can be viewed as:

```text
[batchCount, sequenceLength, attentionHeads, headChannels]
```

A row-major C23 buffer flattens that structure. With two sequences, six positions each, two heads and four channels in each head, its element count is:

```text
2 × 6 × 2 × 4 = 96 float values
```

The flattened row count is `batchCount × sequenceLength = 12`. Each row contains `attentionHeads × headChannels = 8` floats. Assuming 32-bit floats, the numerical payload requires `96 × 4 = 384` bytes, excluding metadata and graph memory.

## 2. Absolute position is not array position

Given flattened token row `r` and sequence length `T`, the sequence index is `r / T` using integer division and local time index is `r % T`. If a sequence starts at an external absolute position `start[sequenceIndex]`, its angle is chosen using:

```text
absolutePosition = start[sequenceIndex] + localTime
```

For the second six-token sequence with start position 3071, the seventh *overall* flattened token row is its first local position, **3071**. Its sixth local token uses position 3076. A row index selects memory; the position selects RoPE geometry. Confusing them changes the calculation.

## 3. Reuse the native rotary owner

The Framework already declares `UmiAiTrainingRotaryTensorForward` and `UmiAiTrainingRotaryTensorBackward` in `umicom/ai/training/rotary_training.h`. They delegate to the same scalar rotation and adjoint owner instead of creating separate trigonometric formulae.

```c
#include "umicom/ai/training/rotary_training.h"
#include <stdint.h>

const UmiAiTrainingRotaryConfig rotary = {4U, 4U, 10000.0};
const uint64_t starts[2] = {0U, UINT64_C(3071)};
float projected[96] = {0};
float rotated[96] = {0};
float upstream[96] = {0};
float inputGradient[96] = {0};

/* Fill projected and upstream through the normal Framework learning path. */
UmiStatus status = UmiAiTrainingRotaryTensorForward(
    &rotary, projected, 12U, 6U, 2U, starts, 2U, rotated, 96U);
if (status == UMI_STATUS_OK)
    status = UmiAiTrainingRotaryTensorBackward(
        &rotary, upstream, 12U, 6U, 2U, starts, 2U,
        inputGradient, 96U);
```

This is a call example, not a second rotary implementation. Buffers are caller-owned. A successful calculation does not imply that the output came from a trained language model.

## 4. A useful adjoint identity

For every linear rotation `R`, two calculations should agree (within a justified floating-point tolerance):

```text
dot(R × x, g) ≈ dot(x, Rᵀ × g)
```

The left-hand side evaluates a rotated input against an arbitrary gradient. The right-hand side evaluates the original input against the adjoint-transformed gradient. A sign error, wrong per-head offset or incorrect transpose can violate this identity even if every output remains finite.

Test different `startPositions`, more than one head, in-place operations and values close to the allowed position limit. Ensure malformed dimensions, too-small capacity or nonfinite inputs cannot partially overwrite a result.

## 5. What this verifies, and what it does not

Passing batched rotary regression qualifies mathematical preparation, not a full Transformer model. A trainable model additionally needs a tape-connected operation, an independently identified model architecture, an appropriate checkpoint format and numerical parity across training and inference. Reusing a first-block KV entry after eviction does not automatically justify reuse of upper-layer states.

For Windows integration, configure and test the existing Framework-native laboratory instead of introducing an application-local rotation implementation:

```powershell
Set-Location 'C:\umicom\Umicom-Applications'
$env:Path = 'C:\msys64\ucrt64\bin;' + $env:Path
cmake -S '.\framework\learning\native-llm\prefix-work' `
  -B '.\build\windows-ucrt64-native-llm-prefix-debug' -G Ninja `
  -DCMAKE_BUILD_TYPE=Debug -DBUILD_TESTING=ON
cmake --build '.\build\windows-ucrt64-native-llm-prefix-debug' --parallel 2
ctest --test-dir '.\build\windows-ucrt64-native-llm-prefix-debug' `
  -R '^framework\.ai\.training\.rotary_(gradients|tensor|training_rejections)' `
  --output-on-failure --no-tests=error
```

These commands must actually succeed in the local checkout before reporting a Windows integration pass.

## Exercises

1. Calculate the element count for three sequences, eight tokens each, four heads and four channels per head. **Answer: 384.**
2. If the second sequence begins at position 120, which position belongs to its seventh local token (zero-based index six)? **Answer: 126.**
3. Why is comparing `dot(Rx,g)` with `dot(x,Rᵀg)` more informative than testing only that the results are finite?
4. Why must the entire destination remain unchanged after a rejected 95-element output capacity for a required 96-element tensor?

**Next:** [Lesson 85 — Rotary attention on the training tape](85-build-rotary-attention-on-the-training-tape.md).
