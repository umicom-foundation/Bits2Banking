# Mathematics for AI — Unit 17: Backpropagation in One Small Example

**Bits to Banking · Umicom Foundation · Sammy Hegab**

## Aim

Follow one parameter through a forward prediction, a loss calculation and a backward derivative. Then use the derivative to predict the effect of a small weight update.

## 1. A two-stage model

Let `w` be one trainable parameter. The model's prediction is:

`p = 2w + 1`

We want `p` to approach the target `5`. Define the loss:

`L = (p − 5)² / 2`

At `w = 1`, the forward prediction is `p = 2 × 1 + 1 = 3`. The error is `3 − 5 = −2`, and `L = (−2)² / 2 = 2`. The factor `1/2` simply makes the derivative of squared error easier to write; it does not change the optimal prediction.

## 2. Calculate gradients backwards

The **chain rule** multiplies how each stage responds to change:

`dL/dw = (dL/dp) × (dp/dw)`

Here `dL/dp = p − 5` and `dp/dw = 2`. At `w = 1`:

`dL/dw = (3 − 5) × 2 = −4`

The negative result says that, for a sufficiently small change near `w = 1`, increasing `w` reduces the loss. It does not guarantee that arbitrarily large updates will work.

## 3. Check the direction numerically

| Weight | Prediction | Loss |
|---|---:|---:|
| `1.0` | `3.0` | `2.00` |
| `1.1` | `3.2` | `1.62` |
| `1.2` | `3.4` | `1.28` |

For `w = 1.1`, compute `p = 2 × 1.1 + 1 = 3.2`, then `L = (3.2 − 5)² / 2 = 1.62`. This confirms the local direction in this simple example.

## 4. From one weight to a Transformer

A real training computation contains many stages: token embeddings, matrix projections, optional rotations, attention scores, normalisation, feed-forward layers and a loss. The **forward pass** computes outputs. **Reverse-mode automatic differentiation** applies the chain rule through all recorded dependencies to calculate parameter gradients.

Umicom Framework already owns this behaviour through its C23 training tape. The public operation `UmiAiTrainingBackward(tape, loss)` differentiates the recorded graph. The caller may then obtain a copy of a tensor's gradients through `UmiAiTrainingTensorGradients` and request an update through an approved Framework optimiser.

The model parameter and gradient buffers remain Framework-owned. Educational applications do not directly mutate their private memory.

## 5. What a gradient does not prove

A correctly calculated gradient validates local mathematics, not the quality of the dataset, not the model's generalisation, and not the legitimacy of a generated action. Those questions require independently reviewed held-out data, identity controls and application-specific safeguards.

For extra confidence, compare selected tape gradients with finite differences using [Unit 14](14-independent-gradient-checks.md). The two tests should not share the same faulty implementation.

## Practice and answers

1. At `w = 2`, what is `p`? **`2 × 2 + 1 = 5`**.
2. At `w = 2`, what is the loss? **`(5 − 5)² / 2 = 0`**.
3. Is the derivative negative at every weight? **No**. Here `dL/dw = 2(p − 5) = 4w − 8`; it is negative below `w = 2`, zero at the optimum and positive above it.

Open the [illustrated HTML unit](../../courses/maths-for-ai/lessons/17-backpropagation-from-a-small-example.html) for its interactive explanation.
