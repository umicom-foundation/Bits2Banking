# Planning multiple Transformer blocks

**Bits to Banking · Native AI Engineering**  
**Author:** Sammy Hegab · Umicom Foundation

## Learning objectives

Understand the main engineering distinction in this lesson, calculate a small numerical example where appropriate, and identify which responsibilities belong to Umicom Framework rather than educational applications. The worked examples are for learning; they do not operate on financial customer data.

## Start with the idea

An individual Transformer block applies attention and a feed-forward network. Stacking blocks deepens the network, but it also multiplies parameter and activation requirements.

## Worked example

For channel width C and hidden width H, four attention matrices contribute 4C² weights; the feed-forward matrices contribute 2CH. Each block also requires biases and normalisation parameters.

## Engineering application

The Framework model-scaling estimator counts these components without creating a model; the existing teaching decoder still uses one block.

## A practical review sequence

1. Record the input dimensions, data classification and ownership.
2. Identify the applicable Framework owner or public C23 API before implementing functionality.
3. Calculate the expected result independently; do not use the implementation itself as its own proof.
4. Verify rejection behaviour, memory limits and data provenance.
5. Separate numerical correctness, measured performance and deployment approval.

## Exercise

With C=4 and H=8, count the two feed-forward matrices.

<details><summary>Reveal the worked answer</summary>

They hold 4 × 8 + 8 × 4 = 64 weights before biases.

</details>

## Further study

Read the [Mathematics for AI introduction](../11-maths-for-ai/index.md) and the [native AI learning path](index.md). The Framework is the source of truth for executable logic; a curriculum example is not an alternative library.
