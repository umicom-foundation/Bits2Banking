# Mathematics for AI — Unit 6: Derivatives, Gradients and the Chain Rule

**Bits to Banking · Umicom Foundation**  
**Author:** Sammy Hegab  
**Companion:** [Illustrated HTML lesson](../../courses/maths-for-ai/lessons/06-derivatives-and-chain-rule.html)

## What you will learn

Training changes numerical model parameters to reduce error. A **derivative** tells us how quickly an output changes near a particular input. A **gradient** collects such derivatives for several parameters. The **chain rule** lets us follow a change through multiple calculations. This is the mathematical foundation of backpropagation.

## A derivative measures local sensitivity

Start with `f(x) = x²`. Its derivative is `f′(x) = 2x`. At `x = 3`:

- The original output is `f(3) = 9`.
- The local slope is `f′(3) = 6`.
- An input increase of `0.01` suggests an output increase of roughly `6 × 0.01 = 0.06`.
- The exact new output is `3.01² = 9.0601`.

The estimate differs from the exact change by `0.0001` because a derivative predicts change *locally*, not exactly for every finite step.

## Apply the chain rule one stage at a time

Suppose a small neural calculation contains two stages:

`z = 2x` and `y = z²`.

The symbol `dy/dx` asks how `y` changes when `x` changes. The chain rule states:

\[
\frac{dy}{dx} = \frac{dy}{dz} \times \frac{dz}{dx}.
\]

At `x = 3`, we obtain `z = 6`, `dy/dz = 2z = 12`, and `dz/dx = 2`. Multiply: `dy/dx = 12 × 2 = 24`.

We can verify independently. Substituting `z` into the output gives `y = (2x)² = 4x²`; differentiating gives `dy/dx = 8x`; at `x = 3`, this is also `24`.

## Use a gradient to update one weight

The simplest gradient-descent update is:

`newWeight = oldWeight − learningRate × gradient`.

If `oldWeight = 0.8`, `learningRate = 0.1`, and `gradient = +0.2`, the next value is `0.8 − 0.02 = 0.78`.

A positive gradient says that increasing this parameter *locally* increases loss, so gradient descent reduces it. A negative gradient generally causes the update to increase the parameter. An update can still fail to improve loss if its step is too large; measurements and finite-value checks remain necessary.

## Backpropagation through a matrix

A matrix product `Y = XA` participates in a larger chain. If a later calculation supplies an output gradient `G = ∂L/∂Y`, the input and weight gradients are:

`∂L/∂X = G Aᵀ` and `∂L/∂A = Xᵀ G`.

`ᵀ` denotes matrix transpose; it swaps rows with columns. The dimensions must agree. These formulas explain why an adaptor with two low-rank matrices can learn with ordinary automatic differentiation instead of a new training algorithm.

## Framework connection

`UmiAiTrainingBackward` computes gradients through existing Framework tape nodes. `UmiAiTrainingSgdStepMany` and the Framework AdamW optimiser govern updates. Umicom Framework owns the operators; educational exercises only explain their mathematics.

## Practise and check

**Question A.** If `y = (3x)²`, find `dy/dx` at `x = 2`.  
**Answer.** Let `z=3x`; `dy/dz=2z=12` and `dz/dx=3`, so the answer is `36`.

**Question B.** A weight is `−0.4`, gradient is `−0.5`, learning rate is `0.1`. Compute its next value.  
**Answer.** `−0.4 − (0.1 × −0.5) = −0.35`.

**Question C.** Why should a finite-difference gradient check use more than one perturbation size?  
**Answer.** A very large perturbation is not local, while an extremely tiny perturbation may lose precision through floating-point subtraction.

**Next:** [Angles, sine, cosine and rotary positions](07-angles-and-rotary-position.md).
