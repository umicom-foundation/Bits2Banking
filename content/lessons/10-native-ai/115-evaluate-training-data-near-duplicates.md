# Exact duplicates and near-duplicate leakage

**Bits to Banking · Native AI Engineering**  
**Author:** Sammy Hegab · Umicom Foundation

## Learning objectives

Understand the main engineering distinction in this lesson, calculate a small numerical example where appropriate, and identify which responsibilities belong to Umicom Framework rather than educational applications. The worked examples are for learning; they do not operate on financial customer data.

## Start with the idea

Exact record hashes can reveal byte-for-byte duplicates. Near-duplicates may have different hashes while conveying essentially the same content, leaking held-out answers into training.

## Worked example

Two versions of a tutorial may differ only in a date or punctuation. SHA-256 will report different digests although their main educational content overlaps.

## Engineering application

Use human review and similarity measures in addition to the existing Framework exact-duplicate audit. Group derivatives by original asset; test sources that were edited or republished.

## A practical review sequence

1. Record the input dimensions, data classification and ownership.
2. Identify the applicable Framework owner or public C23 API before implementing functionality.
3. Calculate the expected result independently; do not use the implementation itself as its own proof.
4. Verify rejection behaviour, memory limits and data provenance.
5. Separate numerical correctness, measured performance and deployment approval.

## Exercise

Will changing one character preserve a SHA-256 digest?

<details><summary>Reveal the worked answer</summary>

No: the resulting digest is generally different, so exact hashing alone is insufficient for semantic overlap detection.

</details>

## Further study

Read the [Mathematics for AI introduction](../11-maths-for-ai/index.md) and the [native AI learning path](index.md). The Framework is the source of truth for executable logic; a curriculum example is not an alternative library.
