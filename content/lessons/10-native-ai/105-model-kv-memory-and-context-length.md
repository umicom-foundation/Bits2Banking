# KV caches, context length and model memory

**Bits to Banking · Native AI Engineering**  
**Author:** Sammy Hegab · Umicom Foundation

## Learning objectives

Understand the main engineering distinction in this lesson, calculate a small numerical example where appropriate, and identify which responsibilities belong to Umicom Framework rather than educational applications. The worked examples are for learning; they do not operate on financial customer data.

## Start with the idea

A decoder can preserve attention keys and values for past tokens. The persistent KV capacity scales with the number of layers, concurrent sequences, context length, channel width and bytes per value.

## Worked example

For 2 layers, 3 sequences, 16 tokens, 8 channels and FP32, the two key/value arrays require 2 × 3 × 16 × 8 × 2 × 4 = 6,144 bytes.

## Engineering application

This is a cache-data calculation, not process RSS: temporary matrices, alignment, allocator overhead and model storage are additional.

## A practical review sequence

1. Record the input dimensions, data classification and ownership.
2. Identify the applicable Framework owner or public C23 API before implementing functionality.
3. Calculate the expected result independently; do not use the implementation itself as its own proof.
4. Verify rejection behaviour, memory limits and data provenance.
5. Separate numerical correctness, measured performance and deployment approval.

## Exercise

Double the context length while keeping everything else fixed. What happens to the KV data size?

<details><summary>Reveal the worked answer</summary>

It doubles to 12,288 bytes.

</details>

## Further study

Read the [Mathematics for AI introduction](../11-maths-for-ai/index.md) and the [native AI learning path](index.md). The Framework is the source of truth for executable logic; a curriculum example is not an alternative library.
