# Mathematics for AI — Unit 21: Cross-entropy for next-token learning

**Bits to Banking · Umicom Foundation**  
**Author:** Sammy Hegab

## Learning objectives

Explain why a classifier produces *logits* rather than probabilities, calculate stable softmax probabilities, calculate the loss for one next-token target, and understand why low-rank adapter training can minimise exactly the same objective.

## 1. From scores to probabilities

Suppose a toy language model predicts one of three symbols: **A**, **B** or **C**. Its raw logits are `[2, 1, 0]`. A logit is a numerical score that does not need to be nonnegative or add to one.

Softmax converts logits into a probability distribution:

`P(i) = exp(zᵢ − m) / Σⱼ exp(zⱼ − m)`

Here `zᵢ` is the logit for choice `i`; `m` is the largest logit; `exp` is the exponential function; `Σ` means sum across all choices. Subtracting the maximum improves numerical stability without changing the probabilities.

For `[2, 1, 0]`, subtract `m = 2` to obtain `[0, −1, −2]`. Their exponentials are approximately `[1, 0.367879, 0.135335]`; the total is **1.503214**. Divide each by that total:

| Token | Approximate probability |
| --- | ---: |
| A | 0.66524 |
| B | 0.24473 |
| C | 0.09003 |

The values add to one up to rounding. The largest score corresponds to the most probable token, but this does not prove it is factually correct.

## 2. How cross-entropy measures one prediction

Assume **B** was the actual next token. The negative log-likelihood is:

`L = −ln(P(B)) ≈ −ln(0.24473) ≈ 1.408`.

`L` is loss. `ln` is the natural logarithm. A model that assigns more probability to the observed target receives a lower loss. If we had observed **A** instead, the loss would be approximately `−ln(0.66524) = 0.408`.

For `N` training positions, mean cross-entropy is:

`L_mean = (1 / N) × Σₜ −ln(P(targetₜ))`.

Each position needs an explicit target token ID. If an application needs **assistant-response-only** loss, it must supply a separately qualified masking policy; simply averaging every position also trains on prompt-token predictions.

## 3. Why the Framework's tape matters

In C23, the Umicom training tape owns logits, the stable cross-entropy calculation and reverse-mode differentiation. Applications do not reimplement softmax gradients. The canonical operation is:

```c
UmiAiTrainingTensor *loss = NULL;
UmiStatus status = UmiAiTrainingCrossEntropy(
    tape, logitsTensor, targetIds, tokenCount, &loss);
```

This is an excerpt; `tape`, `logitsTensor` and `targetIds` are already-created, caller-owned handles or arrays. After a successful forward and loss computation, `UmiAiTrainingBackward(tape, loss)` calculates gradients. The optimiser then updates only the parameters explicitly designated trainable.

## 4. Practice and worked answer

Suppose a two-choice model produces equal logits `[0, 0]`. Each probability is 0.5. What is the loss when the target is the first choice?

**Answer:** `L = −ln(0.5) ≈ 0.693147`. If the target probability increases to 0.8, its loss decreases to `−ln(0.8) ≈ 0.223144`. Cross-entropy rewards a better assigned probability, not merely an unchanged top-1 prediction.

**Important distinction:** lower training loss does not demonstrate improved generalisation. An evaluation split built from genuinely held-out source documents must be measured separately.

[Mathematics index](index.md) · [Previous: computation graphs](20-matrix-chain-rule-and-computation-graphs.md) · [Native adapter lesson](../10-native-ai/train-a-frozen-decoder-logit-adapter.md)
