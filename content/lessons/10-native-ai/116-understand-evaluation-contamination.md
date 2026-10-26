# Keep held-out evaluation independent

**Bits to Banking · Native AI Engineering**  
**Author:** Sammy Hegab · Umicom Foundation

## Learning objectives

Understand the main engineering distinction in this lesson, calculate a small numerical example where appropriate, and identify which responsibilities belong to Umicom Framework rather than educational applications. The worked examples are for learning; they do not operate on financial customer data.

## Start with the idea

Training examples should not include the answers or paraphrases of the items reserved for final evaluation. Otherwise measured loss and accuracy can exaggerate model generalisation.

## Worked example

If ten test questions are copied into training with alternative spacing, their byte records differ but the model may have memorised the substance. A fair benchmark reserves genuinely independent source groups.

## Engineering application

Umicom corpus audits should reject obvious exact overlap; a further release review is necessary for paraphrases, shared templates and prior model exposure.

## A practical review sequence

1. Record the input dimensions, data classification and ownership.
2. Identify the applicable Framework owner or public C23 API before implementing functionality.
3. Calculate the expected result independently; do not use the implementation itself as its own proof.
4. Verify rejection behaviour, memory limits and data provenance.
5. Separate numerical correctness, measured performance and deployment approval.

## Exercise

Can a low evaluation loss prove independence if the test questions appeared in training?

<details><summary>Reveal the worked answer</summary>

No. Contamination invalidates that interpretation.

</details>

## Further study

Read the [Mathematics for AI introduction](../11-maths-for-ai/index.md) and the [native AI learning path](index.md). The Framework is the source of truth for executable logic; a curriculum example is not an alternative library.
