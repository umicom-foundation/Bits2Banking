# Mathematics for AI — Unit 11: Matrix Weights and Training

**Bits to Banking · Umicom Foundation**  
**Author:** Sammy Hegab  
**Prerequisites:** [Dot products](03-vectors-and-dot-products.md), [matrices](04-matrices-and-shapes.md) and [gradient descent](10-gradient-descent-and-learning-rate.md).

## Learning objectives

Calculate a matrix projection, derive gradients for a small squared-error example and explain why low-rank adapters can update a small subset of neural-network weights without changing the original base projection.

## 1. A row vector meets a weight matrix

Let one input have two features, `x = [2, 1]`. Let the weight matrix be:

`W = [[0.5, 0.1], [0.2, 0.3]]`.

`x` has shape `1 × 2`; `W` has shape `2 × 2`; the output `y = xW` has shape `1 × 2`.

- First output: `2 × 0.5 + 1 × 0.2 = 1.2`.
- Second output: `2 × 0.1 + 1 × 0.3 = 0.5`.

Therefore `y = [1.2, 0.5]`. Suppose the target is `t = [1.0, 0.6]`.

## 2. Measure mean squared error

`L = ((1.2 − 1.0)² + (0.5 − 0.6)²) / 2`.

`L = (0.04 + 0.01) / 2 = 0.025`.

For this two-output MSE, the gradient with respect to each output is simply `prediction − target`:

`∂L/∂y = [0.2, −0.1]`.

For a linear projection, the weight gradient follows `∂L/∂Wᵢⱼ = xᵢ × (∂L/∂yⱼ)`.

| Weight | Calculation | Gradient |
|---|---|---:|
| `W₀₀` | `2 × 0.2` | `+0.4` |
| `W₀₁` | `2 × (−0.1)` | `−0.2` |
| `W₁₀` | `1 × 0.2` | `+0.2` |
| `W₁₁` | `1 × (−0.1)` | `−0.1` |

## 3. Update the weights and check

With learning rate `0.1`, subtract `0.1 × gradient` from every weight:

`W(new) = [[0.46, 0.12], [0.18, 0.31]]`.

Now `xW(new) = [1.10, 0.55]`. The new MSE is

`((1.10 − 1.0)² + (0.55 − 0.6)²) / 2 = 0.00625`.

This small example improved the declared training objective. It proves nothing about performance on unseen inputs unless we evaluate independently.

## 4. Connect dense weights to low-rank adaptation

A dense layer computes `XW`. A low-rank adapter instead computes:

`Y = XW + (XA)B`, with `W` held fixed.

For input dimension `d`, output dimension `o`, and adapter rank `r`, the full matrix has `d × o` weights, whereas the adapter has `d × r + r × o` trainable weights. For `d = 128`, `o = 128` and `r = 8`, this is `2,048` adapter weights versus `16,384` base weights, or **12.5% as many trainable values**. This is a parameter-count comparison, not a guarantee of equal quality or a complete memory saving; activations and optimiser state also consume memory.

Umicom Framework owns the actual low-rank projection and training tape. A product should not implement its own matrix maths.

## Practise

**Exercise A.** Multiply `x = [1,2]` by the identity matrix `[[1,0],[0,1]]`.  
**Answer.** The result is `[1,2]`.

**Exercise B.** For `d = 16`, `o = 32`, `r = 4`, how many adapter values are trainable?  
**Answer.** `16 × 4 + 4 × 32 = 64 + 128 = 192`; the full base has `16 × 32 = 512` values.

**Further study:** [Illustrated Unit 11](../../courses/maths-for-ai/lessons/11-matrix-weights-and-training.html) · [Adapter checkpoints and model identity](../10-native-ai/adapter-checkpoints-and-model-identity.md).
