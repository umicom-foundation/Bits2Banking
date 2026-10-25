# Mathematics for AI — Unit 10: Gradient Descent and Learning Rates

**Bits to Banking · Umicom Foundation**  
**Author:** Sammy Hegab  
**Prerequisites:** [Derivatives and the chain rule](06-derivatives-and-chain-rule.md).

## Learning objectives

Explain a loss function, calculate a derivative, perform one stochastic-gradient-descent (SGD) update and distinguish a successful training step from a guarantee of better results on new data.

## 1. Choose one transparent learning task

Suppose a control displays the numerical value `w = 1`, and we want it to display `3`. The parameter `w` is the only value we may change. Choose the squared-error loss:

`L(w) = (w − 3)²`.

At `w = 1`, the error is `1 − 3 = −2`; squaring gives `L(1) = 4`.

The loss measures this particular objective. It is neither a probability nor a statement about whether an AI model is useful or safe.

## 2. Calculate the gradient

The derivative is `dL/dw = 2(w − 3)`. At `w = 1`:

`dL/dw = 2 × (1 − 3) = −4`.

The negative gradient indicates that raising `w` slightly should decrease this loss locally. The derivative is a local slope; it does not promise that an arbitrarily large step will help.

## 3. Apply the update

SGD uses `w(new) = w(old) − α × gradient`, where `α` (alpha) is a positive learning rate. With `α = 0.1`:

`w(new) = 1 − 0.1 × (−4) = 1.4`.

Evaluate again: `L(1.4) = (1.4 − 3)² = 2.56`. Our observed training loss has fallen from `4` to `2.56`.

A second step uses the gradient `2(1.4 − 3) = −3.2`, producing `w = 1.4 − 0.1 × (−3.2) = 1.72` and loss `(1.72 − 3)² = 1.6384`.

| Step | Weight | Gradient before update | Loss after update |
|---|---:|---:|---:|
| Starting point | 1.00 | −4.00 | 4.0000 |
| First update | 1.40 | −3.20 at new weight | 2.5600 |
| Second update | 1.72 | −2.56 at new weight | 1.6384 |

## 4. The corresponding C23 arithmetic

```c
float weight = 1.0F;
const float desired = 3.0F;
const float learningRate = 0.1F;
float gradient = 2.0F * (weight - desired);
weight -= learningRate * gradient;
```

This is a scalar teaching calculation. Real Umicom model training delegates differentiation to `UmiAiTrainingBackward` and transactional multi-tensor updates to `UmiAiTrainingSgdStepMany` or the Framework-owned AdamW optimiser. Do not duplicate these algorithms in an application.

## 5. Choose learning rates using evidence

A very small rate may reduce loss too slowly; a rate that is too large may overshoot or diverge. Production evaluation therefore uses a declared schedule, finite-value checks, held-out examples and repeatable checkpoints. An optimiser's internal state matters when resuming an AdamW run; restoring weights alone is not exact optimiser continuation.

## Practise

**Exercise A.** With `L(w) = (w − 4)²`, `w = 2` and `α = 0.25`, find the first gradient, new weight and new loss.  
**Answer.** Gradient `2(2 − 4) = −4`; new weight `2 − 0.25(−4) = 3`; loss `(3 − 4)² = 1`, down from `4`.

**Exercise B.** Why must validation use data separate from training data?  
**Answer.** Reusing exactly the training examples measures fit to those examples, not how well the updated parameters generalise.

**Further study:** [Illustrated Unit 10](../../courses/maths-for-ai/lessons/10-gradient-descent-and-learning-rate.html) · [Trainable matrix weights](11-matrix-weights-and-training.md).
