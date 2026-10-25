# Mathematics for AI — Unit 14: Independent Gradient Checks

**Bits to Banking · Umicom Foundation · Sammy Hegab**

## Purpose

Automatic differentiation is convenient, but a training engine must not be verified by comparing the engine against itself. A **finite-difference gradient** supplies a second mathematical route to the slope of a loss function. We also learn to recover the gradient used during a simple SGD update.

## 1. Choose a transparent loss

Let `L(w) = (w − 3)²`, where `w` is a trainable weight, `3` is the desired value and `L` is the squared error. At `w = 2`, the loss is `(2 − 3)² = 1`.

A small positive perturbation `ε` (epsilon) lets us measure loss on either side of `w`:

`estimated gradient = [L(w + ε) − L(w − ε)] / (2ε)`

The denominator is **twice** the perturbation, because the two evaluation points are `2ε` apart. Central differences are commonly more accurate than changing the weight in one direction only, although very small `ε` can amplify floating-point rounding.

## 2. Work through every number

Choose `ε = 0.1`.

| Test weight | Loss calculation | Loss |
|---|---|---:|
| `w + ε = 2.1` | `(2.1 − 3)²` | `0.81` |
| `w − ε = 1.9` | `(1.9 − 3)²` | `1.21` |

Therefore the estimated gradient is:

`(0.81 − 1.21) / (2 × 0.1) = −0.40 / 0.20 = −2`

Differentiating the same function symbolically gives `dL/dw = 2(w − 3)`, which equals `−2` at `w = 2`. These **independent approaches agree**.

## 3. Connect the slope to a weight update

Gradient descent subtracts the learning-rate-scaled gradient:

`newWeight = oldWeight − learningRate × gradient`

For learning rate `0.1`, we get `2 − (0.1 × −2) = 2.2`. The new loss is `(2.2 − 3)² = 0.64`, lower than the original 1. This establishes progress for **one example and one step**, not general model intelligence.

If a training program reports old and new weights, the gradient that plain SGD used can be reconstructed:

`observed gradient = (oldWeight − newWeight) / learningRate`

Here `(2 − 2.2) / 0.1 = −2`. This reconstructed value can be compared against both the tape gradient and the finite-difference estimate.

**Important:** This rearrangement applies to plain SGD without momentum or decay. It does not directly recover the original gradient from an AdamW update, which also uses moment estimates and weight decay.

## 4. Expand from one number to a projection matrix

For `Y = XW`, every element `Wᵢⱼ` can influence the loss. A gradient check changes **one weight at a time**, recomputes the loss twice and compares the numerical slope with the corresponding value returned by `UmiAiTrainingTensorGradients` after `UmiAiTrainingBackward`.

The Framework's C23 training tape owns tensors, the forward computation and reverse-mode differentiation. Separate tests must provide independently expected results. A gradient comparison should record the perturbation size, the absolute/relative tolerance and the exact model configuration.

## 5. Tolerance is an engineering contract

Suppose the numerical gradient is `−2.0000` while the tape reports `−1.9998`. Their absolute difference is `0.0002`. Under a previously established tolerance of `0.0005`, this comparison passes. Under `0.0001`, it fails. Never enlarge tolerances merely to hide unexpected failures.

For very large or very small gradients, a combined absolute-plus-relative tolerance is often more meaningful; see [Unit 15](15-repeatability-and-precision.md).

## Practice and worked answer

**Question:** For `L(w) = (w − 4)²`, use `w = 3`, `ε = 0.05` and learning rate `0.2`. Calculate the finite-difference gradient and the updated weight.

**Answer:** `L(3.05) = 0.9025`, `L(2.95) = 1.1025`; estimated gradient `= (0.9025 − 1.1025) / 0.1 = −2`. Updated weight `= 3 − (0.2 × −2) = 3.4`. New loss `= (3.4 − 4)² = 0.36`.

Continue with the [illustrated HTML lesson](../../courses/maths-for-ai/lessons/14-independent-gradient-checks.html). To test actual Umicom training operators, use the Framework's regression suite rather than putting duplicate implementation code into Bits2Banking.
