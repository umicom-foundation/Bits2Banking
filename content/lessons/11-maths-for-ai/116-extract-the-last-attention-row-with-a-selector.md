# Mathematics for AI — Unit 116: Extract the last attention row with a selector

**Bits to Banking · Umicom Foundation**  
**Author:** Sammy Hegab · **Prerequisite:** Familiarity with simple arithmetic is enough.

## What will you learn?

A row selector is a matrix with one row and a single value of one. Multiplying it by a larger table extracts one exact row without writing a new indexing operator.

## A fully worked example

Suppose attention output A has shape [4,3]. Define S=[0,0,0,1] with shape [1,4]. Then S×A has shape [1,3] and equals row 3 of A. No earlier row contributes because all other coefficients are zero.

**Helpful symbols:** `×` means multiplication, `÷` means division, `[rows, columns]` states a tensor shape, and a token row is one position in a text sequence. Each byte count and score is specific to the example, not a measured production model.

## Practise the calculation

**Question:** Write S for the third row of a five-row matrix using zero-based row indices.

<details>
<summary>Show the worked answer</summary>

The selector is [0,0,1,0,0]. It has shape [1,5].

</details>

## Connect the idea to native C23

The Framework’s `Matmul` composes this extraction; it currently computes extra intermediate attention rows for teaching correctness.

The actual mathematical implementation remains in Umicom Framework. The connected [native Transformer learning path](../../courses/llm-from-scratch/incremental-attention-learning-path.html) applies this principle to a bounded real-model experiment.

## Continue learning

[Previous unit](115-keep-softmax-stable-by-subtracting-the-maximum.md) · [Next unit](117-calculate-layer-normalisation-by-hand.md) · [Complete mathematics route](../../courses/maths-for-ai/incremental-attention-mathematics.html)

*Service to Many Leads to Greatness.*
