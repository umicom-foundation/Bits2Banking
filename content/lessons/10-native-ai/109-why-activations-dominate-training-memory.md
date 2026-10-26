# Activation memory and backpropagation

**Bits to Banking · Native AI Engineering**  
**Author:** Sammy Hegab · Umicom Foundation

## Learning objectives

Understand the main engineering distinction in this lesson, calculate a small numerical example where appropriate, and identify which responsibilities belong to Umicom Framework rather than educational applications. The worked examples are for learning; they do not operate on financial customer data.

## Start with the idea

A trainer stores or recomputes intermediate values so gradients can flow backwards. These activation tensors vary with context, sequence count, number of blocks and attention implementation.

## Worked example

A naive full attention-probability tensor for 4 heads and 64 tokens contains 4 × 64 × 64 = 16,384 values for one sequence, or 65,536 bytes in FP32. Additional Q/K/V and feed-forward activations increase the footprint.

## Engineering application

A capacity planner that counts only weights and K/V data is incomplete. Verify peak allocations using the actual Framework tape and operating-system measurements.

## A practical review sequence

1. Record the input dimensions, data classification and ownership.
2. Identify the applicable Framework owner or public C23 API before implementing functionality.
3. Calculate the expected result independently; do not use the implementation itself as its own proof.
4. Verify rejection behaviour, memory limits and data provenance.
5. Separate numerical correctness, measured performance and deployment approval.

## Exercise

For 2 heads and 32 tokens, how many attention score values are possible per sequence?

<details><summary>Reveal the worked answer</summary>

2 × 32 × 32 = 2,048.

</details>

## Further study

Read the [Mathematics for AI introduction](../11-maths-for-ai/index.md) and the [native AI learning path](index.md). The Framework is the source of truth for executable logic; a curriculum example is not an alternative library.
