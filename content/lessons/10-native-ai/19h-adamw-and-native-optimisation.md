# Supplement 19H — Build a Native AdamW Optimiser for Our Language Model

**Bits to Banking · Umicom Foundation · Sammy Hegab**  
**Implementation:** C23 in Umicom Framework  
**Prerequisites:** gradients, SGD, memory ownership and the existing decoder trainer

## What you will learn

This lesson explains how the gradient produced by backpropagation is converted into a change to a model's weights. You will study **AdamW**, reproduce an update by hand, inspect its C23 implementation, run a genuine training experiment and examine why optimiser state matters when resuming training.

The examples use our source-code decoder, not an unrelated demonstration. The present model is intentionally small: a successful training run teaches us how to build and test an optimiser, not how to create a competent C programming assistant in a few steps.

## 1. Start with a programming problem

Suppose a decoder sees a sequence of token IDs representing an example from a C23 financial application. Its output layer assigns scores to the next possible token. The correct token has a lower probability than we would like. Cross-entropy loss measures the error, and backpropagation calculates how that loss would change if each trainable parameter were changed slightly.

A gradient gives us a direction, but it does not tell us how far to move. **Stochastic gradient descent (SGD)** uses a simple rule:

```text
new_weight = current_weight − learning_rate × gradient
```

If a parameter equals `1.0`, its gradient equals `0.5` and the learning rate equals `0.1`, SGD produces `0.95`. Every parameter uses the same learning rate, irrespective of whether its earlier gradients have been large or small.

## 2. Why retain first and second moments?

AdamW maintains two running statistics for each parameter. The **first moment** is a moving average of gradients. The **second moment** is a moving average of the squared gradients. These statistics allow the optimiser to scale updates differently for parameters with different gradient histories.

For a gradient `g`, AdamW calculates:

```text
m_t = beta1 × m_previous + (1 − beta1) × g
v_t = beta2 × v_previous + (1 − beta2) × g²
```

Newly initialised moments start at zero. That creates an initial bias towards zero, so AdamW corrects the estimates:

```text
m_hat = m_t / (1 − beta1^t)
v_hat = v_t / (1 − beta2^t)
```

Here `t` is the one-based number of successful optimiser updates, **not** the number of tokens processed and not the number of microbatches. This difference matters when you build larger training workloads.

The final AdamW weight update is:

```text
w_new = w_old − learning_rate ×
        [m_hat / (sqrt(v_hat) + epsilon) + weight_decay × w_old]
```

The weight-decay term is **decoupled** from the adaptive moment calculation. This distinguishes AdamW from naively adding an L2 penalty to the gradient before Adam's moving averages are calculated.

## 3. Calculate one update by hand

Consider one parameter in a fictional account-processing code model:

| Quantity | Value |
| --- | ---: |
| Initial parameter `w` | 1.0 |
| Gradient `g` | 0.5 |
| First-moment coefficient `beta1` | 0.9 |
| Second-moment coefficient `beta2` | 0.999 |
| Epsilon | 0.00000001 |
| Learning rate | 0.1 |
| Weight decay | 0.1 |

At the first update, the first moment is `0.9 × 0 + 0.1 × 0.5 = 0.05`. The second moment is `0.999 × 0 + 0.001 × 0.25 = 0.00025`. Bias correction gives `m_hat = 0.5` and `v_hat = 0.25`. The adaptive gradient is approximately `0.5 / 0.5 = 1.0`. Decoupled decay contributes `0.1 × 1.0 = 0.1`.

The proposed new weight is therefore approximately:

```text
1.0 − 0.1 × (1.0 + 0.1) = 0.89
```

This is an expected value in the native regression tests. The test also verifies a negative-weight example and, crucially, checks that invalid gradients cannot partly update either the model or the moment history.

## 4. Locate the real Framework implementation

In your checked-out `C:\umicom\Umicom-Applications\framework` repository, read:

- `include/umicom/ai/training/optimizer.h` — public contracts, ownership and failure conditions.
- `src/ai/training/optimizer.c` — staged AdamW moment calculations and schedule mathematics.
- `src/ai/training/decoder.c` — reuse of the existing forward pass, cross-entropy and backpropagation.
- `src/ai/training/tape.c` — the original tape-owned transactional parameter writer.
- `tests/ai_training/test_training_adamw.c` — independent mathematical expectations and rejected-input checks.
- `tests/ai_training/test_training_decoder_adamw.c` — reproducible decoder training, binding checks and checkpoint limitations.

**Architectural point:** AdamW does not write into private tensor memory directly. It calculates finite *effective gradients* and invokes the existing Framework function `UmiAiTrainingSgdStepWithGradients`, which validates all candidate weights before committing any change. We use the established mathematical and ownership contracts rather than creating a second neural engine.

## 5. Run the native training laboratory

Open PowerShell and use the actual directory names:

```powershell
Set-Location "C:\umicom\Umicom-Applications"
$env:Path = "C:\msys64\ucrt64\bin;$env:Path"

cmake -S ".\framework\learning\native-llm" `
    -B ".\build\windows-ucrt64-native-llm-debug" -G Ninja `
    -DCMAKE_BUILD_TYPE=Debug -DBUILD_TESTING=ON
cmake --build ".\build\windows-ucrt64-native-llm-debug" --parallel 2
ctest --test-dir ".\build\windows-ucrt64-native-llm-debug" `
    --output-on-failure --no-tests=error

& ".\build\windows-ucrt64-native-llm-debug\umicom-native-llm-adamw.exe" `
    ".\framework\learning\native-llm\fixtures\manifest.txt"
```

The demonstration trains the canonical byte-level decoder on a reviewed source-code fixture. It reports a learning rate and training loss at selected steps, then evaluates one held-out source window. Training loss may improve while generalisation remains poor; do not interpret the result as proof of programming expertise.

## 6. The important checkpoint limitation

Our decoder checkpoint records trained model weights and the number of completed updates. AdamW needs **two additional pieces of information for every parameter**: the first and second moments. Without them, the next AdamW update would not reproduce the original uninterrupted training run.

The Framework therefore **rejects creating a fresh AdamW state on a decoder that has already completed training steps**. This is deliberate and testable. We are not disguising an optimizer reset as a correct resume. A future model-training snapshot will need a separate, validated optimiser-state representation and provenance checks.

## 7. Try it yourself

First, use the formula above with a negative parameter of `−2.0` and a gradient of `−0.25`. Check the answer against the regression test. Second, change the decay coefficient to zero and predict the difference in the first update. Third, inspect what happens when the gradient is not finite: the public API should reject the request without updating weights or moving averages. Finally, explain why a new model checkpoint is not sufficient to restore AdamW history.

## Review questions

1. How does AdamW use a gradient differently from SGD?
2. Why are the moments corrected during early optimisation steps?
3. What does *decoupled weight decay* mean mathematically?
4. Why must moment-state changes be committed only after weight validation?
5. Why is a model-only checkpoint insufficient for exact AdamW continuation?

**Next:** [Supplement 19I — Learning-Rate Schedules and Reproducible Resume](19i-learning-rate-schedules-and-reproducible-resume.md).
