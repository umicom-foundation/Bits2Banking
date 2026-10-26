# Quality gates are measured decisions

**Bits to Banking · Native AI Engineering**  
**Author:** Sammy Hegab · Umicom Foundation

## Learning objectives

Understand the main engineering distinction in this lesson, calculate a small numerical example where appropriate, and identify which responsibilities belong to Umicom Framework rather than educational applications. The worked examples are for learning; they do not operate on financial customer data.

## Start with the idea

A trained model can improve one metric while regressions appear elsewhere. Define held-out loss, accuracy, safety tests and operational boundaries before examining the candidate.

## Worked example

Suppose a baseline loss is 1.6 and candidate loss is 1.4, but candidate accuracy drops from 70% to 62%. A single favourable loss change does not resolve the trade-off automatically.

## Engineering application

Keep measurements, policy decisions and external authorisation separate. A passing quality gate does not authorise a financial action or a model publication by itself.

## A practical review sequence

1. Record the input dimensions, data classification and ownership.
2. Identify the applicable Framework owner or public C23 API before implementing functionality.
3. Calculate the expected result independently; do not use the implementation itself as its own proof.
4. Verify rejection behaviour, memory limits and data provenance.
5. Separate numerical correctness, measured performance and deployment approval.

## Exercise

If both loss and accuracy must improve, does this example pass?

<details><summary>Reveal the worked answer</summary>

No. Accuracy declines even though loss improves.

</details>

## Further study

Read the [Mathematics for AI introduction](../11-maths-for-ai/index.md) and the [native AI learning path](index.md). The Framework is the source of truth for executable logic; a curriculum example is not an alternative library.
