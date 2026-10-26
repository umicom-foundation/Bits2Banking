# Separating a numerical kernel from a GPU backend

**Bits to Banking · Native AI Engineering**  
**Author:** Sammy Hegab · Umicom Foundation

## Learning objectives

Understand the main engineering distinction in this lesson, calculate a small numerical example where appropriate, and identify which responsibilities belong to Umicom Framework rather than educational applications. The worked examples are for learning; they do not operate on financial customer data.

## Start with the idea

Umicom Framework uses C23 APIs for ownership and model contracts. A future compute backend may use specialised GPU APIs but must preserve numerical acceptance tests and explicit device-memory lifetimes.

## Worked example

A matrix multiplication backend should state supported FP formats, shapes, alignment, cancellation and error handling. GPU memory estimates must include activation workspaces and host-device copies beyond parameter storage.

## Engineering application

Do not select a GPU based on a raw parameter count alone. Check actual device memory, interconnect, compiler support and measured end-to-end workload before committing hardware.

## A practical review sequence

1. Record the input dimensions, data classification and ownership.
2. Identify the applicable Framework owner or public C23 API before implementing functionality.
3. Calculate the expected result independently; do not use the implementation itself as its own proof.
4. Verify rejection behaviour, memory limits and data provenance.
5. Separate numerical correctness, measured performance and deployment approval.

## Exercise

Can an FP32 memory estimate establish that a particular GPU kernel will run?

<details><summary>Reveal the worked answer</summary>

No. Capability and runtime compatibility require separate validation.

</details>

## Further study

Read the [Mathematics for AI introduction](../11-maths-for-ai/index.md) and the [native AI learning path](index.md). The Framework is the source of truth for executable logic; a curriculum example is not an alternative library.
