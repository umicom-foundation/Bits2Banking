# Lesson 87 — Train Query and Key Projections in Native Rotary Attention

**Bits to Banking · Umicom Foundation**  
**Author:** Sammy Hegab  
**Implementation authority:** Umicom Framework, C23

## Learning outcomes

Understand one complete optimisation step through native rotary attention; read every tensor shape; explain the distinction between training and merely running a forward pass; and verify that a loss is measured again **after** updating the weights.

The [original illustrated lesson](../../courses/llm-from-scratch/lessons/87-train-rotary-attention-projections.html) remains the complete visual companion. Study [Mathematics Unit 10](../11-maths-for-ai/10-gradient-descent-and-learning-rate.md) before attempting the optimiser exercise if gradients are unfamiliar.

## 1. Begin with a small, explicit model

This experiment has three token rows and four numerical channels. Each projection weight matrix has four rows and four columns; there are two attention heads with two channels per head.

| Object | Shape | Elements |
| --- | --- | ---: |
| Input token features, `X` | 3 × 4 | 12 |
| Query weights, `Wq` | 4 × 4 | 16 |
| Key weights, `Wk` | 4 × 4 | 16 |
| Projected queries, `Q = XWq` | 3 × 4 | 12 |
| Projected keys, `K = XWk` | 3 × 4 | 12 |
| Fixed values and desired output | 3 × 4 each | 12 each |

A matrix product with shape `(3 × 4)(4 × 4)` produces `3 × 4`. The input width and weight height agree: both are four. RoPE rotates the two-dimensional pairs within each attention head. The Framework-owned causal attention operator then combines the rotated queries, keys and original value features.

## 2. Walk through the training transaction

1. Calculate the query and key projections using the existing `UmiAiTrainingMatmul` operator.
2. Call `UmiAiTrainingRotaryTapeAttention` to rotate query/key positions and calculate causal attention on the existing tape.
3. Compare the 12 output values against the 12 fixed targets using mean squared error (MSE): `MSE = Σ(prediction − target)² / 12`.
4. Call `UmiAiTrainingBackward` to calculate gradients of the loss with respect to `Wq` and `Wk`.
5. Call the established `UmiAiTrainingSgdStepMany` to update **both** matrices transactionally.
6. Rewind temporary graph nodes; rebuild the forward pass using the new weights and measure the loss again.

The learning rate controls the size of the attempted update. A smaller loss is evidence about this particular supervised numeric objective; it does **not** prove that a language model understands C23 or banking.

## 3. Reuse the native Framework optimisation service

```c
#include "umicom/ai/training/rotary_optimisation.h"

/* problem and plan are fully populated, reviewed Framework structures. */
UmiAiTrainingRotaryOptimisationResult evidence = {0};
UmiStatus status = UmiAiTrainingRotaryOptimisationRun(
    &problem, &plan, &evidence);

if (status == UMI_STATUS_OK) {
    /* Compare evidence.initialLoss, evidence.lossAfterStep[] and
       evidence.finalLoss. Inspect gradients and memory evidence too. */
}
```

This excerpt assumes the caller has already created a valid problem and plan; it is not a complete `main` function. The real implementation remains in `framework/src/ai/training/rotary_optimisation.c`. Do not duplicate the training tape or write another optimiser inside Bits2Banking.

## 4. A worked numeric step

Imagine a single weight with current value `w = 0.8`, measured gradient `g = 0.2`, and learning rate `α = 0.1`. Standard SGD applies `w(next) = w − αg = 0.8 − 0.1 × 0.2 = 0.78`. In the real experiment, the Framework applies the same rule simultaneously to 32 trainable matrix entries, subject to validation and failure-atomic publication.

## 5. Build and inspect

The existing Framework native-LLM prefix laboratory owns this demonstration. From the **Applications root**, build it after configuration:

```powershell
Set-Location "C:\umicom\Umicom-Applications"
$env:Path = "C:\msys64\ucrt64\bin;$env:Path"
cmake -S ".\framework\learning\native-llm\prefix-work" -B ".\build\windows-ucrt64-native-llm-prefix-debug" -G Ninja -DCMAKE_BUILD_TYPE=Debug -DBUILD_TESTING=ON
cmake --build ".\build\windows-ucrt64-native-llm-prefix-debug" --target umicom-native-llm-rotary-optimisation --parallel 2
```

Record the model shape, initial loss, gradient norms, updated losses, tape peak memory, compiler and revision. A successful build is not itself a numerical verification.

## 6. Exercises

**Exercise A.** Why should the tape discard intermediate results after an update? **Answer:** they were calculated with old weight values. A new forward graph is required for new parameters.

**Exercise B.** If a 4 × 4 projection contains 16 trainable values, how many are in two independent query/key matrices? **Answer:** 32.

**Exercise C.** Can decreasing MSE on three teaching tokens certify the quality of a general assistant? **Answer:** no. Quality and generalisation require separate held-out language-model evaluations.

**Next:** [Lesson 88 — Verify rotary training results](88-verify-rope-optimisation-and-results.md).
