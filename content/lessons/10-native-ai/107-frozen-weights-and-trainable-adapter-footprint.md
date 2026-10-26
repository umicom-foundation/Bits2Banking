# Frozen base weights and adapter memory

**Bits to Banking · Native AI Engineering**  
**Author:** Sammy Hegab · Umicom Foundation

## Learning objectives

Understand the main engineering distinction in this lesson, calculate a small numerical example where appropriate, and identify which responsibilities belong to Umicom Framework rather than educational applications. The worked examples are for learning; they do not operate on financial customer data.

## Start with the idea

Parameter-efficient tuning keeps a large pretrained weight matrix frozen and learns much smaller low-rank matrices. Frozen storage is still needed during inference and backpropagation.

## Worked example

For a C × C matrix, rank r introduces C × r + r × C = 2Cr adapter parameters, instead of C² weights. For C=16 and r=2 that is 64 adapter values versus 256 original weights.

## Engineering application

Optimizer state is necessary only for trainable parameters in an adapter-only optimisation, but activations and frozen parameters still consume memory.

## A practical review sequence

1. Record the input dimensions, data classification and ownership.
2. Identify the applicable Framework owner or public C23 API before implementing functionality.
3. Calculate the expected result independently; do not use the implementation itself as its own proof.
4. Verify rejection behaviour, memory limits and data provenance.
5. Separate numerical correctness, measured performance and deployment approval.

## Exercise

For C=32 and r=4, how many adapter values are trained?

<details><summary>Reveal the worked answer</summary>

2 × 32 × 4 = 256 values.

</details>

## Further study

Read the [Mathematics for AI introduction](../11-maths-for-ai/index.md) and the [native AI learning path](index.md). The Framework is the source of truth for executable logic; a curriculum example is not an alternative library.
