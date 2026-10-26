# Weights, optimisers, cursors and approval

**Bits to Banking · Native AI Engineering**  
**Author:** Sammy Hegab · Umicom Foundation

## Learning objectives

Understand the main engineering distinction in this lesson, calculate a small numerical example where appropriate, and identify which responsibilities belong to Umicom Framework rather than educational applications. The worked examples are for learning; they do not operate on financial customer data.

## Start with the idea

A resumable checkpoint must contain enough state to reproduce the next update. A release approval additionally answers who has authorised the resulting model for distribution.

## Worked example

A stateless-SGD continuation requires weights, run configuration, source snapshot identity, progress cursor and deterministic example order. AdamW requires moments and step/schedule identity as well.

## Engineering application

SHA-256 protects accidental changes, not publisher identity. Use the Framework trust and signing services when provenance requires cryptographic authenticity.

## A practical review sequence

1. Record the input dimensions, data classification and ownership.
2. Identify the applicable Framework owner or public C23 API before implementing functionality.
3. Calculate the expected result independently; do not use the implementation itself as its own proof.
4. Verify rejection behaviour, memory limits and data provenance.
5. Separate numerical correctness, measured performance and deployment approval.

## Exercise

Is a checksum equivalent to a signed publisher approval?

<details><summary>Reveal the worked answer</summary>

No. Anyone can calculate an unkeyed checksum for bytes they control.

</details>

## Further study

Read the [Mathematics for AI introduction](../11-maths-for-ai/index.md) and the [native AI learning path](index.md). The Framework is the source of truth for executable logic; a curriculum example is not an alternative library.
