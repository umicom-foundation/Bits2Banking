# When to use retrieval instead of tuning

**Bits to Banking · Native AI Engineering**  
**Author:** Sammy Hegab · Umicom Foundation

## Learning objectives

Understand the main engineering distinction in this lesson, calculate a small numerical example where appropriate, and identify which responsibilities belong to Umicom Framework rather than educational applications. The worked examples are for learning; they do not operate on financial customer data.

## Start with the idea

Retrieval-augmented generation (RAG) supplies relevant source passages at inference time; fine-tuning modifies model behaviour through optimisation. They solve different problems.

## Worked example

A policy document updated weekly is often better indexed for retrieval than memorised in model weights. A consistent answer format may benefit from reviewed supervised examples.

## Engineering application

Umicom Knowledge and AI source-admission services have different responsibilities: indexing a private document does not imply approval to train on it or publish it.

## A practical review sequence

1. Record the input dimensions, data classification and ownership.
2. Identify the applicable Framework owner or public C23 API before implementing functionality.
3. Calculate the expected result independently; do not use the implementation itself as its own proof.
4. Verify rejection behaviour, memory limits and data provenance.
5. Separate numerical correctness, measured performance and deployment approval.

## Exercise

Can a private document approved for internal retrieval automatically join a public training corpus?

<details><summary>Reveal the worked answer</summary>

No. Retrieval permissions do not establish model-training rights.

</details>

## Further study

Read the [Mathematics for AI introduction](../11-maths-for-ai/index.md) and the [native AI learning path](index.md). The Framework is the source of truth for executable logic; a curriculum example is not an alternative library.
