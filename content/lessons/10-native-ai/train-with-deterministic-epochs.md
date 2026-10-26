# Train a Frozen Decoder Adapter with Deterministic Epochs

**Bits to Banking · Umicom Foundation · Sammy Hegab**

## Learning outcome

Run a complete, bounded, native C23 training experiment using **every approved training example once per epoch**, while keeping held-out examples out of the optimiser. Learn why the random number generator, dataset identity and optimiser-step counter are part of reproducibility.

## What is an epoch?

An epoch is one traversal of the training examples. If the dataset contains three training windows and we request two epochs, the optimiser receives **six successful update calls**. Changing the order can affect intermediate gradients and therefore the resulting adapter weights.

It is common to shuffle examples between epochs. Umicom does not create another random-number algorithm for this task. `UmiAiTrainingSupervisedDatasetOrder` uses the existing Framework seeded integer RNG and Fisher–Yates permutation to obtain a deterministic order with **no repeated or omitted training records within an epoch**.

A held-out example is not included in that permutation. It is used only for evaluation.

## The real Framework workflow

```c
#include "umicom/ai/training/supervised_experiment.h"

/* adapter is an existing, caller-owned frozen-decoder projection adapter.
 * dataset comes from approved reviewed JSONL via SupervisedDatasetCreate. */
const UmiAiTrainingSupervisedExperimentPlan plan = {
    .epochs = 3U,
    .evaluateEveryEpochs = 1U,
    .shuffleSeed = UINT64_C(42),
    .learningRate = 0.025F,
    .stopAtEvaluationLoss = 0.0
};
UmiAiTrainingSupervisedExperimentReport report = {0};
UmiStatus status = UmiAiTrainingSupervisedExperimentRun(
    adapter, dataset, &plan, &report);
```

The Framework checks the dataset context against the decoder's actual context. It calculates baseline held-out metrics, runs the selected adapter's existing `TrainStep` for each training window, evaluates at the requested interval and checks that completed adapter steps increase as expected. Base-model identity comes from the adapter's frozen checkpoint SHA-256 binding.

The experiment reports **pre-update training loss** separately from **post-epoch held-out loss**. Those are not the same measurement. Training loss can fall simply because the model repeatedly sees its training examples; held-out loss is an independent signal for deciding whether the narrow training objective generalises.

## The danger of conflating repeatability and good results

Equal seeds and unchanged data should reproduce the *order* of examples. They do not guarantee that different CPUs, compilers, floating-point modes or numerical libraries will always produce bit-identical model weights. Reproducibility also requires recording the exact model, build configuration, training plan and dataset revision.

No acceptance test should require loss to decrease monotonically after each update. SGD can temporarily increase loss even when a longer run improves the objective. Check finiteness, step identity and independent evaluation rather than retroactively changing tolerances.

## Questions and worked answers

1. Four training examples, five epochs: how many update calls? **20**, provided every call succeeds.
2. Why shuffle without replacement? **Each example is seen once per epoch**, independent of position in the shuffle.
3. Why is the baseline held-out loss measured before SGD? **It provides a true comparison against the original adapter.**
4. Is an unchanged base-model SHA-256 proof the adapter did not change? **No; trainable adapter weights are separate objects.**

Next study: [held-out token metrics](measure-held-out-token-loss-and-accuracy.md) and [failure and continuation limits](understand-training-failures-and-resume-limits.md).
