# Performance planning without invented speedups

**Bits to Banking · Native AI Engineering**  
**Author:** Sammy Hegab · Umicom Foundation

## Learning objectives

Understand the main engineering distinction in this lesson, calculate a small numerical example where appropriate, and identify which responsibilities belong to Umicom Framework rather than educational applications. The worked examples are for learning; they do not operate on financial customer data.

## Start with the idea

An operation count estimates work; wall-clock time measures an implementation running on specific hardware. They are not interchangeable, especially when memory bandwidth and caching vary.

## Worked example

If one run generates 40 tokens in 5 seconds, measured throughput is 8 tokens per second. It says nothing about the speed of a different model, compiler or device.

## Engineering application

Use warmed repeated measurements, parity checks and exact configurations. Do not claim a larger model will be faster merely because a kernel performs fewer operations.

## A practical review sequence

1. Record the input dimensions, data classification and ownership.
2. Identify the applicable Framework owner or public C23 API before implementing functionality.
3. Calculate the expected result independently; do not use the implementation itself as its own proof.
4. Verify rejection behaviour, memory limits and data provenance.
5. Separate numerical correctness, measured performance and deployment approval.

## Exercise

A real run produces 60 tokens in 12 seconds. What is its observed rate?

<details><summary>Reveal the worked answer</summary>

60 / 12 = 5 tokens per second.

</details>

## Further study

Read the [Mathematics for AI introduction](../11-maths-for-ai/index.md) and the [native AI learning path](index.md). The Framework is the source of truth for executable logic; a curriculum example is not an alternative library.
