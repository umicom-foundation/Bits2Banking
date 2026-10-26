# SGD, AdamW and memory for continuation

**Bits to Banking · Native AI Engineering**  
**Author:** Sammy Hegab · Umicom Foundation

## Learning objectives

Understand the main engineering distinction in this lesson, calculate a small numerical example where appropriate, and identify which responsibilities belong to Umicom Framework rather than educational applications. The worked examples are for learning; they do not operate on financial customer data.

## Start with the idea

Ordinary stateless SGD can continue from weights and its exact training cursor. AdamW additionally keeps two moment arrays for every trainable weight, plus its step number and schedule policy.

## Worked example

If 1,000 adapter parameters each use FP32 values and FP32 gradients, those arrays need 8,000 bytes. If both AdamW moments are stored in binary64, the two moment arrays need a further 16,000 bytes.

## Engineering application

The existing Umicom Framework AdamW state cannot be reconstructed from model weights alone. A valid restart requires the matching optimiser snapshot.

## A practical review sequence

1. Record the input dimensions, data classification and ownership.
2. Identify the applicable Framework owner or public C23 API before implementing functionality.
3. Calculate the expected result independently; do not use the implementation itself as its own proof.
4. Verify rejection behaviour, memory limits and data provenance.
5. Separate numerical correctness, measured performance and deployment approval.

## Exercise

How much space do two binary64 moment arrays require for 500 values?

<details><summary>Reveal the worked answer</summary>

500 × 2 × 8 = 8,000 bytes.

</details>

## Further study

Read the [Mathematics for AI introduction](../11-maths-for-ai/index.md) and the [native AI learning path](index.md). The Framework is the source of truth for executable logic; a curriculum example is not an alternative library.
