# Precision and quantisation trade-offs

**Bits to Banking · Native AI Engineering**  
**Author:** Sammy Hegab · Umicom Foundation

## Learning objectives

Understand the main engineering distinction in this lesson, calculate a small numerical example where appropriate, and identify which responsibilities belong to Umicom Framework rather than educational applications. The worked examples are for learning; they do not operate on financial customer data.

## Start with the idea

FP32 uses four bytes per weight; idealised FP16 uses two. Real quantised formats often require per-group scales, zero points, metadata, conversion buffers and special kernels.

## Worked example

If a model has 100,000 scalar weights, its FP32 value array uses 400,000 bytes. An ideal FP16 value array would use 200,000 bytes, before any additional allocations.

## Engineering application

Quantisation changes numerical behaviour and may affect model quality. A parameter-size estimate does not establish supported machine instructions or tested throughput.

## A practical review sequence

1. Record the input dimensions, data classification and ownership.
2. Identify the applicable Framework owner or public C23 API before implementing functionality.
3. Calculate the expected result independently; do not use the implementation itself as its own proof.
4. Verify rejection behaviour, memory limits and data provenance.
5. Separate numerical correctness, measured performance and deployment approval.

## Exercise

What is the ideal FP32 storage for 250,000 weights?

<details><summary>Reveal the worked answer</summary>

1,000,000 bytes, not counting metadata or activations.

</details>

## Further study

Read the [Mathematics for AI introduction](../11-maths-for-ai/index.md) and the [native AI learning path](index.md). The Framework is the source of truth for executable logic; a curriculum example is not an alternative library.
