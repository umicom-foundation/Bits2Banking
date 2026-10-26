# Mathematics for AI — Unit 35: SGD, AdamW and Restart State

**Bits to Banking · Umicom Foundation · Sammy Hegab**

## What is an optimiser?

An optimiser uses a gradient to adjust trainable numerical parameters. For simple stochastic gradient descent (SGD), a learning rate `α` and gradient `g` update a weight `w` using:

**SGD:** `w(next) = w(current) − α × g`.

With `w=1.00`, `α=0.10` and `g=0.20`, the new weight is `1.00−0.10×0.20 = 0.98`.

## Why a restart needs the correct state

If future gradients are determined by exactly the same weights, data order and numerical computation, a simple SGD run can continue from a checkpoint of its latest weights and training cursor. It does **not** maintain running averages of earlier gradients inside the optimiser.

AdamW is more sophisticated. It maintains at least a running first-moment estimate and a running second-moment estimate for every trainable element, plus a completed-update count used in bias correction. It can also apply decoupled weight decay. These quantities affect the next update.

## A two-step illustration

Imagine a fictional optimiser that remembers the average of previous gradients. Its current moment is `m=0.40`, and the next gradient is `0.20`. If a simple half-and-half average is used, the next moment is `(0.40+0.20)÷2 = 0.30`. If we mistakenly restart `m` at zero, the same averaging calculation produces `(0+0.20)÷2 = 0.10`. The weights will receive a different update even though the new input gradient is identical.

This example is only to illustrate retained state; it is **not** AdamW's complete equation.

## Framework contract

The Umicom continuation component expressly supports **stateless SGD**. It saves trained low-rank weights, the model identity, dataset identity, training-plan values and exact next-example position. It must not advertise itself as an exact AdamW continuation until the canonical Framework AdamW moments and schedule are also saved and restored.

## Practise

Why does recording only `w=0.98` fail to reproduce the next AdamW update? Because AdamW also depends on its remembered moment tensors and step count, which cannot be inferred uniquely from a single current weight value.

<details><summary>Show another calculation</summary>

SGD with `w=0.98`, learning rate `0.10` and new gradient `−0.30` gives `0.98−0.10×(−0.30)=1.01`.

</details>

**Continue:** [SGD cursor lesson](../10-native-ai/97-resume-deterministic-sgd-mid-epoch.md).

---

*Service to Many Leads to Greatness. Educational C23 examples; not a production financial or model-training certification.*
