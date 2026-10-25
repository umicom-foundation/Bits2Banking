# Lesson 83 — Differentiate Rotary Position Mathematics in Native C23

**Bits to Banking · Umicom Foundation**  
**Author:** Sammy Hegab  
**Implementation authority:** Umicom Framework (C23)

## What you will learn

A position-aware attention system needs two related operations: the **forward rotation** used to calculate attention scores and the **reverse derivative** that carries training loss back into the original query and key vectors. This lesson derives both operations before considering an entire Transformer. The corresponding [illustrated lesson](../../courses/llm-from-scratch/lessons/83-differentiate-rotary-position-in-c23.html) provides the visual explanation.

You should already recognise vectors, matrix multiplication and the chain rule. Revisit [Maths Unit 7](../11-maths-for-ai/07-angles-and-rotary-position.md) and [Maths Unit 6](../11-maths-for-ai/06-derivatives-and-chain-rule.md) if those topics are unfamiliar.

## 1. Begin with one pair of coordinates

Let a vector contain two values, `x` and `y`. At a given token position, rotary positional encoding (RoPE) chooses an angle `θ` and calculates:

```text
u = x × cos(θ) − y × sin(θ)
v = x × sin(θ) + y × cos(θ)
```

Here `(u,v)` is the rotated vector. For a quarter turn, `cos(θ)=0` and `sin(θ)=1`. The input `(2,0)` becomes `(0,2)`. The rotation changes direction, not Euclidean length.

In matrix notation the same forward calculation is `rotated = R(θ) × original`, where:

```text
R(θ) = [ cos(θ)  −sin(θ) ]
       [ sin(θ)   cos(θ) ]
```

## 2. Backpropagate through the rotation

Suppose a loss `L` depends on the two rotated outputs. The training procedure already knows the upstream derivatives `du = ∂L/∂u` and `dv = ∂L/∂v`. It must calculate how the loss responds to the original inputs:

```text
∂L/∂x = du × cos(θ) + dv × sin(θ)
∂L/∂y = −du × sin(θ) + dv × cos(θ)
```

This is the transpose rotation: `inputGradient = R(θ)ᵀ × rotatedGradient`. Applying the *forward* rotation again is generally incorrect. It happens to look correct at angle zero, which is why tests must include nonzero positions.

For a quarter turn and upstream gradient `(3,4)`, the input gradient becomes `(4,−3)`. Check this by substituting `cos(θ)=0`, `sin(θ)=1` into the two derivative equations.

## 3. Derive a query/key dot-product gradient

For a query `q` at position `p_q` and a key `k` at position `p_k`, the unscaled score is:

```text
d = dot(R(p_q) × q, R(p_k) × k)
```

If the later loss contributes scalar gradient `g = ∂L/∂d`, then:

```text
∂L/∂q = g × R(p_q)ᵀ × R(p_k) × k
∂L/∂k = g × R(p_k)ᵀ × R(p_q) × q
```

These equations differentiate **the rotated dot product only**. A complete attention backward pass additionally differentiates the score scale, softmax and value aggregation. Do not mistake the dot-product derivative for a complete trainable decoder.

## 4. Use the existing Framework API

The canonical declarations are in `umicom/ai/training/rotary_position.h` and `umicom/ai/training/rotary_training.h`. The latter exposes `UmiAiTrainingRotaryDotBackward` and delegates the rotation mathematics to the former.

```c
#include "umicom/ai/training/rotary_training.h"
#include <stdint.h>

const UmiAiTrainingRotaryConfig rotary = {4U, 4U, 10000.0};
const float query[4] = {0.4F, -0.3F, 0.2F, 0.5F};
const float key[4] = {-0.1F, 0.4F, 0.8F, -0.2F};
float queryGradient[4] = {0};
float keyGradient[4] = {0};

UmiStatus status = UmiAiTrainingRotaryDotBackward(
    &rotary, query, key, 4U, UINT64_C(21), UINT64_C(18),
    1.0, queryGradient, 4U, keyGradient, 4U);
```

The upstream gradient `1.0` is a teaching input, **not** a learning rate. The caller owns the buffers, and the Framework must preserve them on failure.

## 5. Independent numerical verification

An independent test perturbs one original query component by a small positive `ε` and evaluates the forward score twice:

```text
numericalGradient ≈ [d(q + ε) − d(q − ε)] / (2ε)
```

For the actual test, only the selected component is perturbed. Compare this estimate with `UmiAiTrainingRotaryDotBackward` using an explicitly selected tolerance. Repeat for key components, multiple position pairs, different rotary widths and a nonrotary tail. This is stronger evidence than comparing two calls to the same backward routine.

## Exercises

1. Rotate `(1,0)` through a quarter turn and apply the transpose to upstream gradient `(0,1)`.
2. Why would checking only token position zero fail to detect a forward/transpose mix-up?
3. Explain why the dot-product gradient is not yet the gradient of a complete masked-attention block.
4. Describe which input buffers must remain unchanged after an invalid or nonfinite gradient request.

**Worked answer to Exercise 1:** The forward result is `(0,1)`; the transpose maps `(0,1)` back to `(1,0)`.

**Next:** [Lesson 84 — Qualify batched rotary gradients](84-qualify-batched-rotary-gradients.md). Existing learned-absolute decoder checkpoints are **not** reinterpreted as rotary models.
