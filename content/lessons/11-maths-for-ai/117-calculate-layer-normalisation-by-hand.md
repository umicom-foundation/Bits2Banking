# Mathematics for AI — Unit 117: Calculate layer normalisation by hand

**Bits to Banking · Umicom Foundation**  
**Author:** Sammy Hegab · **Prerequisite:** Familiarity with simple arithmetic is enough.

## What will you learn?

Layer normalisation subtracts the mean of a token’s feature values and divides by sqrt(variance+epsilon), then applies learned scale and bias. It acts independently on each token row.

## A fully worked example

For values [1,3], mean=2. Deviations are [-1,+1], population variance=(1+1)/2=1. With epsilon 0, normalised values are [-1,+1]; with small positive epsilon they become slightly closer to zero. With scale gamma=[1,1] and bias beta=[0,0], nothing further changes.

**Helpful symbols:** `×` means multiplication, `÷` means division, `[rows, columns]` states a tensor shape, and a token row is one position in a text sequence. Each byte count and score is specific to the example, not a measured production model.

## Practise the calculation

**Question:** Calculate the mean of [2,4,6,8] and name the deviations.

<details>
<summary>Show the worked answer</summary>

Mean=5, deviations=[-3,-1,+1,+3]. Their mean squared deviation is (9+1+1+9)/4=5.

</details>

## Connect the idea to native C23

Use precisely the canonical LayerNorm epsilon and FP32 conversion; changing epsilon changes every downstream Q/K/V projection.

The actual mathematical implementation remains in Umicom Framework. The connected [native Transformer learning path](../../courses/llm-from-scratch/incremental-attention-learning-path.html) applies this principle to a bounded real-model experiment.

## Continue learning

[Previous unit](116-extract-the-last-attention-row-with-a-selector.md) · [Next unit](118-follow-residual-connections-and-relu.md) · [Complete mathematics route](../../courses/maths-for-ai/incremental-attention-mathematics.html)

*Service to Many Leads to Greatness.*
