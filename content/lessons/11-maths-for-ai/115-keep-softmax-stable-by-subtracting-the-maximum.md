# Mathematics for AI — Unit 115: Keep softmax stable by subtracting the maximum

**Bits to Banking · Umicom Foundation**  
**Author:** Sammy Hegab · **Prerequisite:** Familiarity with simple arithmetic is enough.

## What will you learn?

Exponentials become very large for large positive logits. A stable softmax subtracts the maximum score before taking exponentials; subtracting the same constant from all scores does not change their normalised ratios.

## A fully worked example

For scores [1000,1001], direct exp may overflow ordinary FP32. Subtract 1001 to obtain [-1,0]. Exponentials are approximately [0.3679,1]. Dividing by 1.3679 yields probabilities [0.2689,0.7311].

**Helpful symbols:** `×` means multiplication, `÷` means division, `[rows, columns]` states a tensor shape, and a token row is one position in a text sequence. Each byte count and score is specific to the example, not a measured production model.

## Practise the calculation

**Question:** Stabilise logits [5,7,7] by subtracting their maximum.

<details>
<summary>Show the worked answer</summary>

Subtract 7: [-2,0,0]. Their exponentials are [0.1353,1,1], which sum to 2.1353.

</details>

## Connect the idea to native C23

A new inference path must delegate stable softmax and its rounding rules to the established Framework attention operator.

The actual mathematical implementation remains in Umicom Framework. The connected [native Transformer learning path](../../courses/llm-from-scratch/incremental-attention-learning-path.html) applies this principle to a bounded real-model experiment.

## Continue learning

[Previous unit](114-calculate-one-query-attention-by-hand.md) · [Next unit](116-extract-the-last-attention-row-with-a-selector.md) · [Complete mathematics route](../../courses/maths-for-ai/incremental-attention-mathematics.html)

*Service to Many Leads to Greatness.*
