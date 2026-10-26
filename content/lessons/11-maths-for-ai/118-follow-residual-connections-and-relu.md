# Mathematics for AI — Unit 118: Follow residual connections and ReLU

**Bits to Banking · Umicom Foundation**  
**Author:** Sammy Hegab · **Prerequisite:** Familiarity with simple arithmetic is enough.

## What will you learn?

A residual connection adds a transformed vector back to its input. ReLU keeps positive values and converts negative values to zero. Operator order matters because ReLU is nonlinear.

## A fully worked example

Let x=[1,-2], projected attention a=[0.5,1]. The first residual is x+a=[1.5,-1]. Suppose feed-forward output is [0.2,0.3]. The second residual is [1.7,-0.7]. ReLU([-1,0.2,4])=[0,0.2,4].

**Helpful symbols:** `×` means multiplication, `÷` means division, `[rows, columns]` states a tensor shape, and a token row is one position in a text sequence. Each byte count and score is specific to the example, not a measured production model.

## Practise the calculation

**Question:** What is ReLU([-3,0,2.5])? Could moving a bias through ReLU preserve every output?

<details>
<summary>Show the worked answer</summary>

ReLU returns [0,0,2.5]. Moving a bias generally changes which values are positive and therefore is not algebraically equivalent.

</details>

## Connect the idea to native C23

The native one-row composition must reuse the Framework Transformer’s exact LayerNorm → affine → ReLU → residual order.

The actual mathematical implementation remains in Umicom Framework. The connected [native Transformer learning path](../../courses/llm-from-scratch/incremental-attention-learning-path.html) applies this principle to a bounded real-model experiment.

## Continue learning

[Previous unit](117-calculate-layer-normalisation-by-hand.md) · [Next unit](119-measure-logit-parity-with-an-absolute-tolerance.md) · [Complete mathematics route](../../courses/maths-for-ai/incremental-attention-mathematics.html)

*Service to Many Leads to Greatness.*
