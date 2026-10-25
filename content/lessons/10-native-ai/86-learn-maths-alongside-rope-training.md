# Lesson 86 — Learn the Mathematics Behind Rotary Training Tests

**Bits to Banking · Umicom Foundation**  
**Author:** Sammy Hegab  
**Implementation authority:** Umicom Framework (C23)

## Learning outcomes

Read a small model loss aloud, calculate it using ordinary arithmetic, find its gradient and understand how the answer becomes evidence for a native C23 training test. The [illustrated lesson](../../courses/llm-from-scratch/lessons/86-learn-maths-alongside-rope-training.html) and the [mathematics index](../11-maths-for-ai/index.md) provide a path for readers without previous advanced mathematics.

## 1. Start from two predictions

Suppose a teaching model predicts `[0.6, 0.2]` when the intended values are `[0.4, 0.5]`. The differences are `0.2` and `−0.3`. Squaring gives `0.04` and `0.09`.

Mean squared error (MSE) is the average of the squared differences:

```text
MSE = (0.04 + 0.09) / 2 = 0.065
```

The general notation is `MSE = (1/n) × Σᵢ (predictionᵢ − targetᵢ)²`. The Greek letter `Σ` means add terms, `i` identifies each measured element and `n` is the count. The numerical operation is simply subtract, square, add and divide.

For a true next-token language model, cross-entropy is normally more relevant than MSE. MSE remains an excellent teaching tool for the derivatives and projector comparisons in this lesson.

## 2. Calculate the gradient of that loss

For the average squared loss across `n` values, the derivative with respect to each prediction is:

```text
∂L/∂predictionᵢ = (2/n) × (predictionᵢ − targetᵢ)
```

For two predictions, `(2/n)=1`; the gradients are therefore `[0.2, −0.3]`. A positive component tells the optimiser that increasing that prediction would locally increase loss; a negative component means the opposite.

In a Transformer training tape, these derivatives flow backwards through residual additions, projections, attention and possibly rotary-position operations. The chain rule connects each dependent operation.

## 3. Verify a derivative independently

Let `L(w) = w²`. Test the derivative at `w = 2` with `ε = 0.01`:

```text
L(2.01) = 4.0401
L(1.99) = 3.9601
central difference = (4.0401 − 3.9601) / 0.02 = 4
```

The exact derivative is `2w = 4` at `w=2`, so the numerical estimate agrees. If a C23 tape reports another gradient, the correct response is to investigate operator mathematics, shape rules, floating-point tolerances or ownership—not to relax the threshold until a failing result passes.

## 4. What the rotary transpose does

The forward rotation moves vector coordinates using `R(p)`. Backpropagation maps a later gradient through `R(p)ᵀ`. Because a pure rotation is orthogonal, the transpose reverses the rotation. The result is not an additional trainable weight or a second loss function; it is an application of the chain rule.

The existing `UmiAiTrainingRotaryTapeAttention` composes this numerical behaviour inside the authoritative tape. Its tests compare the resulting tensor and gradients with separately derived expectations. Read [Maths Unit 7](../11-maths-for-ai/07-angles-and-rotary-position.md), [Unit 12](../11-maths-for-ai/12-finite-differences-and-floating-point.md) and [Unit 20](../11-maths-for-ai/20-matrix-chain-rule-and-computation-graphs.md) for each underlying idea.

## 5. Inspect the evidence, not just a green test indicator

A successful compile proves that a compiler accepted the code. A passing numerical regression demonstrates behaviour for its declared inputs and tolerances. Neither proves that the model is useful for source-code completion, that a production checkpoint is approved, or that a small CPU experiment scales to a large LLM.

Memory is another independent dimension: a failed graph allocation must roll back unpublished nodes; the historical peak can remain higher than current usage even after successful cleanup. Learn more in [Maths Unit 18](../11-maths-for-ai/18-memory-budgets-and-rollback.md).

## Self-assessment

1. Explain in words how two numerical errors produce an MSE of `0.065`.
2. Recalculate the central difference of `L(w)=w²` at `w=2` using `ε=0.005`.
3. Why is the backward rotary operation a transpose rather than another forward rotation?
4. Explain the difference between successful numerical qualification and having trained a complete, production-worthy LLM.

**Answers:** (1) Square `0.2` and `−0.3`, sum `0.13`, divide by two. (2) The result is `4`. (3) The chain rule requires the Jacobian transpose to move the upstream gradient back to original coordinates. (4) Numerical tests cover individual mathematical contracts; end-to-end models also need controlled data, training, checkpoints, inference tests and independently measured quality.

**Next:** [Fine-tuning Transformer projections with reusable low-rank adapters](adapt-attention-and-feed-forward-projections.md).
