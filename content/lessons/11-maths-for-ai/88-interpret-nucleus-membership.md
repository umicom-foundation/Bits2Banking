# Mathematics for AI · Unit 88 — Interpret Nucleus Membership

**Bits to Banking · Umicom Foundation**  
**Author:** Sammy Hegab

> **Learning objective:** Understand top-p filtering without inventing a new sampler

## 1. Begin with an ordinary calculation

After temperature and top-K have restricted the eligible scores, nucleus sampling selects the shortest ranked prefix whose cumulative probability reaches the requested threshold. The probabilities are normalised over the original top-K candidate set before deciding the cutoff.

A mathematical formula is a compact description of specific operations. Read each symbol aloud, identify what its input values represent and check the dimensions before using it in code. Integers describing positions or byte counts should remain exact; floating-point results require justified numerical tolerances when appropriate.

## 2. Work through the numbers

For candidates with probabilities 0.60, 0.30 and 0.10, a threshold of 0.80 selects the first two candidates, because 0.60 alone is insufficient but 0.60+0.30=0.90 reaches 0.80. A seed then controls the random selection within the retained nucleus.

The operation's result should be checked against an independent calculation or a precisely defined invariant. A good test makes the comparison meaningful even if two implementations happen to choose the same final token. Keep observed quantities separate from proposed optimisations.

## 3. Connect the calculation to Umicom Framework

The production-facing C23 APIs are declared under `framework/include/umicom/ai/training/`. Applications should consume those APIs; they should not copy the underlying attention, sampling, checkpoint or random-number algorithms. All example calculations here use small numbers for education and do not represent results measured on a trained commercial model.

For the larger model, tensor operations, checkpoint identity, future-token masking and model-memory ownership must all use their existing Framework contracts. A written expression is not a substitute for the original native tests.

## 4. Exercise

**Question:** How many candidates remain if top-p is 0.55 in this example?

<details><summary>Show the worked answer</summary>

One candidate: the first probability is 0.60, already above 0.55.

</details>

## 5. Further learning

Return to [the mathematics course](../../courses/maths-for-ai/advanced-units.html), or read [this unit in HTML](../../courses/maths-for-ai/lessons/88-interpret-nucleus-membership.html). The full native AI course provides engineering examples in C23.

*Service to Many Leads to Greatness.*
