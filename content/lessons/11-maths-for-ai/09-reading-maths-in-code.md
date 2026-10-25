# Mathematics for AI — Unit 9: Read Mathematical Formulas in C23

**Bits to Banking · Umicom Foundation**  
**Author:** Sammy Hegab  
**Prerequisites:** [Functions](02-variables-and-functions.md), [matrices](04-matrices-and-shapes.md) and [attention](08-attention-and-kv-work.md).

## Learning objectives

Read a mathematical expression aloud; identify the dimensions and units of its inputs; translate it into a small native C23 operation; and construct an independent numerical check rather than trusting a calculation merely because it compiles.

## 1. A formula is a concise description of work

Mathematical notation hides several steps in a short line. Consider `y = 2x + 1`. Read it as “multiply x by two, then add one”. With `x = 3`, `y = 2 × 3 + 1 = 7`.

```c
float CalculateExample(float x)
{
    const float result = 2.0F * x + 1.0F;
    return result;
}
```

The `*` operator means multiplication in C23; `const` prevents reassignment of this local result. The `F` suffix makes the literal a `float`, rather than a `double`. The function calculates a value; it is not a replacement for any existing Umicom Framework tensor service.

## 2. Translate common symbols

| Symbol | Meaning | Application |
|---|---|---|
| `=` | Exactly equal, within the mathematical model | Assignments and assertions require a separate programming interpretation |
| `≈` | Approximately equal | Rounded measurements |
| `×` | Multiply | Scaling values |
| `·` | Dot product for vectors | Query–key attention scores |
| `Σ` | Sum specified terms | Losses and gradient reductions |
| `√d` | Square root of `d` | Attention scaling |
| `x²` | `x` multiplied by itself | Squared error |
| `∂L/∂x` | Rate of change of loss with respect to `x` | Backpropagation |
| `Rᵀ` | Transposed matrix `R` | Reverse rotation of gradients |

A formula's symbol dictionary is not complete without **shape** and **units**. For a row vector `[2,1]` multiplied by a matrix of shape `2 × 3`, the result has shape `1 × 3`. A model score and an amount denominated in GBP should never be confused just because both can be stored in a floating-point type.

## 3. From mathematical equality to a numerical test

Take a 90° counter-clockwise rotation of `[1,0]`. The expected result is `[0,1]`. A real floating-point implementation might return `[0.00000004, 0.99999994]`. A numerical test should check **finite outputs** and an independently justified tolerance, for example:

```c
#include <math.h>

float actual = 0.99999994F;
float reference = 1.0F;
float tolerance = 0.000001F;
int agrees = isfinite(actual) &&
             fabsf(actual - reference) <= tolerance;
```

`agrees` is non-zero for this example. The same method would be inappropriate for an exact integer account identifier, a byte-for-byte checkpoint or a SHA-256 digest; those require exact comparison.

## 4. A loss expression in ordinary language

`L = (1/n) × Σᵢ(predictionᵢ − targetᵢ)²` means: for each of `n` measured outputs, subtract the target, square the difference, add the squares and divide by `n`. This is mean squared error (MSE). A training run seeks a lower loss, but a low training loss alone does not establish reliable performance on unseen work.

## Practise

**Exercise A.** For `f(x) = 3x − 2`, calculate `f(4)` and translate it to C23.  
**Answer.** `3 × 4 − 2 = 10`; the expression is `3.0F * x - 2.0F`.

**Exercise B.** What shape results from multiplying `(5 × 3)` by `(3 × 2)`?  
**Answer.** `(5 × 2)`; the shared inner dimension is three.

**Exercise C.** Why is comparing a model against another invocation of its own function insufficient evidence?  
**Answer.** Both calls can reproduce the same underlying defect. Use an independent expected calculation or a genuinely independent reference implementation.

**Further study:** [Illustrated Unit 9](../../courses/maths-for-ai/lessons/09-reading-maths-in-code.html) · [Gradient descent](10-gradient-descent-and-learning-rate.md). The Umicom Framework owns real tensor maths and its tests.
