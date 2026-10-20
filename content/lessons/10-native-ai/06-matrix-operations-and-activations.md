# Lesson 06 — Matrix Operations, Activations and Numerical Stability

**Bits to Banking · Build Your Own LLM from Scratch**  
**Sammy Hegab · Umicom Foundation**  
**Laboratory:** `framework/src/ai/training/tape.c`  
**Implementation status:** Matmul, row-broadcast addition, ReLU, MSE and cross-entropy are implemented and tested. General higher-rank tensor operators are not yet implemented.

## From vectors to useful predictions

Neural networks repeatedly calculate weighted combinations of inputs. Matrix multiplication is one of the central operations. In a small model, imagine two training examples where each example has two numeric features:

```text
X = [ 1  2 ]
    [ 3  4 ]

W = [ 2 ]
    [ -1 ]
```

`X` has shape `2 × 2`; `W` has shape `2 × 1`. Their product has shape `2 × 1`. The first result is `1*2 + 2*(-1) = 0`; the second is `3*2 + 4*(-1) = 2`.

This operation is valid because the inner dimensions match: the number of columns in `X` equals the number of rows in `W`.

In the native implementation, `UmiAiTrainingMatmul` checks that relationship before allocating an output tensor. It calculates each output element as a sum of products, using a double-precision intermediate to reduce numeric loss before storing a validated float32 result.

## Bias addition and broadcasting

A neural layer often calculates `Y = XW + b`. Here `b` is a bias value or vector that applies to every example. If `XW` has shape `2 × 3`, a bias of shape `1 × 3` can be added to each row:

```text
product: [ 1  2  3 ]      bias: [ 10  20  30 ]
         [ 4  5  6 ]

result:  [ 11  22  33 ]
         [ 14  25  36 ]
```

This is **broadcasting**. It saves the caller from manually constructing the same bias row twice. Our operator supports only an equal-shape addition or this single-row broadcasting rule. It does not support arbitrary broadcasting along multiple dimensions.

Broadcasting also changes how derivatives are calculated. The gradient of one shared bias value is the **sum** of the gradient contributions from every row that used it. The backward implementation handles that accumulation explicitly.

## Activation functions: introducing nonlinearity

If every layer only multiplies by a matrix and adds a bias, a stack of layers can collapse into another linear transformation. To learn more complex relationships, networks use nonlinear activation functions.

Our first activation is **ReLU**, or rectified linear unit:

`ReLU(x) = max(0, x)`.

It turns negative inputs into zero and retains positive inputs. For example, `[-2, 0, 3]` becomes `[0, 0, 3]`. Its derivative is zero for negative values and one for positive values. At zero, our implementation chooses the zero derivative, an explicit subgradient convention used by many frameworks.

ReLU is a teaching step. Contemporary transformer implementations frequently use other activation choices, normalisation and residual paths. We will add those only after verifying the simpler operations.

## Why finite numbers matter

Float32 has finite range. A weight update that produces `NaN`, positive infinity or a number outside representable float32 range can corrupt the next computation and destroy the usefulness of a training run. The native operators check that stored results are finite, and their validation failures have explicit status codes.

Cross-entropy uses a stable log-sum-exp expression instead of naively computing `log(sum(exp(z)))` at arbitrary logits. This is an example where a mathematically equivalent expression can be substantially safer on real hardware.

## Walk through the real code

Open the public header and identify the shapes:

```text
include/umicom/ai/training/tape.h
src/ai/training/tape.c
```

Trace `UmiAiTrainingMatmul`, then `UmiAiTrainingAdd`, and finally `UmiAiTrainingRelu`. Identify the validation stage, the allocation stage and the final publication of a node. Note that intermediate tensors belong to the Framework tape and can be discarded after training updates through `UmiAiTrainingTapeRewind`.

In `test_training_gradients.c`, the forward pass uses an input matrix, a weight, a bias, ReLU and mean-squared-error loss. The independent expected output is `17.0` for the selected sample values. The test also checks whether the backward pass returns the derivatives calculated by hand.

## Exercises

1. Multiply the example matrices above on paper and confirm the output shape.
2. Take `XW = [3,5]` and scalar bias `1`; calculate the activation output under ReLU.
3. Explain why the derivative of a broadcast bias must add contributions across rows.
4. Describe how a finite-number check protects an iterative training system.

**Next:** [Lesson 07 — Gradients and automatic differentiation](07-gradients-and-backpropagation.md).
