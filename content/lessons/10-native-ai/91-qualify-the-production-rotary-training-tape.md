# Lesson 91 — Qualify the Real Native Rotary Training Tape

**Umicom Foundation · Bits to Banking · Sammy Hegab**  
**Implementation:** existing Umicom Framework C23 training tape  
**Companion:** [Illustrated Lesson 91](../../courses/llm-from-scratch/lessons/91-qualify-the-production-rotary-training-tape.html)

> This written study companion follows the published illustrated lesson. Editorial review is required before promoting this adaptation as an independently verified original manuscript.

## What you will learn

The previous rotary-position exercises established forward rotation and a small training graph. This lesson asks a stronger question: **does reverse-mode differentiation agree with an independent numerical measurement when the actual Umicom Framework training tape owns the calculation?** The answer cannot be established by compiling a copied mathematical function.

By the end you should be able to describe a tensor shape, calculate a scalar gradient, reconstruct a finite-difference check and distinguish verified component mathematics from a trained language model.

## From an ordinary table to projected attention

Imagine a completely fictional set of three support messages. An educational model represents each message using four numerical features. The array shape is `[3, 4]`: three rows × four channels = **12 floating-point values**. Two attention heads receive two channels each because `4 / 2 = 2`.

Queries and keys are also `[3, 4]`. They are computed from earlier values and may depend on trainable matrices. RoPE rotates each two-channel query/key pair using its absolute token position. The Framework's training tape retains the operation graph so gradients can reach the original projections.

## Check one derivative by hand

Use a simpler scalar model before considering twelve values:

- Prediction: `p = 2w + 1`.
- Desired result: `p = 5`.
- Loss: `L = (p - 5)² / 2`.

At `w = 1`, prediction is `3`, and loss is `(3 - 5)² / 2 = 2`. The chain rule gives:

`dL/dw = (p - 5) × 2 = (-2) × 2 = -4`.

That is an **analytical** gradient. To check it independently, evaluate the loss at a slightly higher and lower weight:

`estimated gradient ≈ [L(w + h) - L(w - h)] / [(w + h) - (w - h)]`.

Here `h` is a deliberately chosen positive perturbation. Using the *actual represented* spacing matters for FP32 values that cannot represent a decimal exactly. Change only one query/key component at a time; otherwise you cannot attribute the observed loss change to a particular derivative.

The published real-tape gradient regression examines **72 component comparisons**: twelve query components and twelve key components at three starting positions. Its declared tolerance is `0.0020`. This is a threshold for that bounded experiment, not a universal AI rule.

## Follow the real C23 ownership boundary

```c
#include "umicom/ai/training/tape.h"

/* The caller has already built one valid tape graph and scalar loss. */
UmiStatus status = UmiAiTrainingBackward(tape, loss);
if (status == UMI_STATUS_OK) {
    status = UmiAiTrainingTensorGradients(query, queryGradient, 12U);
}
```

`queryGradient` is caller-owned output. `query` and `loss` are tape-owned handles. The code above is an excerpt, not a complete program: it assumes valid tensors and explicit lifetime management. No teaching project should implement its own gradient engine as a substitute for these Framework services.

## How to interpret the evidence

Agreement between an analytical derivative and finite differences supports the backward calculation. Agreement with an **independent forward-loss oracle**, as studied in [Lesson 89](89-audit-rotary-gradients-against-an-oracle.md), supports different aspects of the forward calculation. Neither alone proves a production model, safe financial decisions, or an efficient multi-layer decoder.

A further acceptance requirement is memory safety: nodes created by a failed operation must not replace existing results. [Lesson 92](92-measure-tape-memory-and-rewind.md) examines that separately.

## Practical exercises and answers

1. How many values are stored in `[3, 4]`? **Twelve.**
2. If reference gradient is `0.0030` and the tape reports `0.0034`, what is the difference? **0.0004**, within this lesson's `0.0020` bound.
3. Why not compare the Framework's backward method against itself? **A repeated implementation can reproduce the same defect.**
4. Why retain the decoder's original checkpoint codec? **This gradient test does not define a new model architecture or migration.**

Continue with [Mathematics Unit 17](../11-maths-for-ai/17-backpropagation-from-a-small-example.md) for a slower chain-rule explanation, then study native tape memory and rollback in Lesson 92.
