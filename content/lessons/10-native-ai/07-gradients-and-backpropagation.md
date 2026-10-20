# Lesson 07 — Gradients, the Chain Rule and Automatic Differentiation

**Bits to Banking · Build Your Own LLM from Scratch**  
**Sammy Hegab · Umicom Foundation**  
**Laboratory:** `framework/tests/ai_training/test_training_gradients.c` and `test_training_numerical_gradients.c`.

## A model must learn from its mistakes

Suppose a network predicts the next token incorrectly. We can calculate a loss, but that alone does not tell us which weights to change. We need **gradients**: numerical derivatives of the loss with respect to each trainable parameter. For a parameter `w`, the derivative `dLoss/dw` measures how the loss changes for a very small increase in `w`.

A positive derivative means a small increase in `w` tends to increase the loss. Gradient descent therefore changes the weight in the opposite direction. A negative derivative means increasing the weight may decrease the loss.

## Start with one multiplication

Let the prediction be `y = w*x`, with input `x = 2` and weight `w = 3`. Suppose the target is `t = 4` and the loss is squared error: `L = (y-t)^2`.

Calculate the forward pass:

`y = 3*2 = 6`, so `L = (6-4)^2 = 4`.

The chain rule says:

`dL/dw = (dL/dy) * (dy/dw)`.

Here `dL/dy = 2*(y-t) = 4`, and `dy/dw = x = 2`, so `dL/dw = 8`.

A small gradient-descent update with learning rate `0.01` gives `w_new = 3 - 0.01*8 = 2.92`. The new prediction is `5.84` and the new squared error is lower than `4`. This is learning through calculus, not through a collection of hard-coded next-token rules.

## What automatic differentiation does

An **autodiff tape** records every differentiable operation performed in the forward pass and retains references to its input tensors. In our first C23 implementation, nodes are created in forward order, so references point only to earlier nodes in the tape. When a scalar loss is available, `UmiAiTrainingBackward` clears previous gradients, seeds the loss gradient to `1` and walks the operations in reverse order.

Each operation has its own derivative rule:

- Addition passes the upstream derivative to its inputs; broadcasting sums repeated contributions.
- Matrix multiplication uses the opposite matrix to propagate upstream derivatives to each operand.
- ReLU passes the derivative for positive inputs and blocks it for nonpositive inputs.
- Mean squared error differentiates `(prediction-target)^2` and averages over elements.
- Softmax-cross-entropy produces the probability minus the one-hot expected class.

If one tensor is used by multiple downstream operations, the tape **adds** the contributions. Replacing a gradient with the most recent contribution would be incorrect; every path affects the total derivative.

## Check the implementation against mathematics

The test `test_training_gradients.c` creates this graph:

```text
input X       weight W
   |             |
   +---- Matmul -+
           |
        Add bias
           |
          ReLU
           |
   MeanSquaredError <---- targets
           |
      scalar loss
           |
        Backward
```

For the chosen values, the output is `[3,5]` and the mean squared error is `17`. The mathematically expected gradients are `dL/dW = 13` and `dL/db = 8`. Those constants are written in the test independently of the implementation.

## Finite differences: our independent reference

Even if the code returns a number that looks reasonable, its derivative could be wrong. **Finite-difference gradient checking** estimates a derivative by evaluating two nearby forward passes:

`dL/dw ≈ (L(w+ε) - L(w-ε)) / (2ε)`.

The central-difference estimate does not call autodiff. It evaluates the ordinary loss with slightly perturbed parameters. Our test `test_training_numerical_gradients.c` compares that independent estimate against the gradients returned by `UmiAiTrainingBackward` for a combined matrix-multiplication and categorical-cross-entropy graph.

No numerical test proves correctness for all possible shapes and values, but it is a strong regression check against mistakes in derivative signs, indexing and scaling.

## Inspect and run the tests

```powershell
Set-Location 'C:\umicom\Umicom-Applications'
cmake --build '.\build\native-llm-lesson' --parallel 2
ctest --test-dir '.\build\native-llm-lesson' -R 'framework\.ai\.training\.(gradients|finite_differences)' --output-on-failure
```

If no training build exists yet, perform the configuration described in Lesson 05 first. These tests are C23 executables linked against the same Framework-owned library that the training demonstration uses.

## Important limitations

The first tape supports a subset of operations sufficient for linear regression and a one-hot next-token model. It is not a full transformer autodiff system. There is no general broadcasting, higher-rank attention, layer normalisation or accelerator backend in this batch. Gradient buffers are internal and tape-owned; a derived tensor's lifetime ends when it is rewound.

## Review questions

1. Explain why gradients must be accumulated when two operations depend on the same tensor.
2. Derive `d((wx-t)^2)/dw` using the chain rule.
3. Why is a central-difference calculation useful even when an autodiff implementation already exists?
4. Why should our training tests check both mathematical outputs and memory safety?

**Next:** [Lesson 08 — Gradient descent and native training](08-optimisers-and-first-training-run.md).
