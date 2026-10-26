# Mathematics for AI — Unit 119: Measure logit parity with an absolute tolerance

**Bits to Banking · Umicom Foundation**  
**Author:** Sammy Hegab · **Prerequisite:** Familiarity with simple arithmetic is enough.

## What will you learn?

Numerical parity compares corresponding values computed by two independent execution schedules. For real values a and b, absolute error is |a−b|. Every compared value must also be finite.

## A fully worked example

For canonical [-1.25,0.50,1.10] and proposed [-1.24997,0.50002,1.09999], errors are [0.00003,0.00002,0.00001]. A predeclared absolute tolerance of 0.00010 accepts all three. It would reject a mismatch of 0.003 even if the winning token stayed the same.

**Helpful symbols:** `×` means multiplication, `÷` means division, `[rows, columns]` states a tensor shape, and a token row is one position in a text sequence. Each byte count and score is specific to the example, not a measured production model.

## Practise the calculation

**Question:** If reference=0.40000 and proposed=0.40012, does a 0.00010 absolute bound pass?

<details>
<summary>Show the worked answer</summary>

No; error=0.00012 exceeds 0.00010.

</details>

## Connect the idea to native C23

The tests qualify every vocabulary logit, not just top-one IDs. Thresholds must be declared before observing failures.

The actual mathematical implementation remains in Umicom Framework. The connected [native Transformer learning path](../../courses/llm-from-scratch/incremental-attention-learning-path.html) applies this principle to a bounded real-model experiment.

## Continue learning

[Previous unit](118-follow-residual-connections-and-relu.md) · [Next unit](120-understand-seeded-nucleus-sampling.md) · [Complete mathematics route](../../courses/maths-for-ai/incremental-attention-mathematics.html)

*Service to Many Leads to Greatness.*
