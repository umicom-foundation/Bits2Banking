# Mathematics for AI · Unit 83 — Compare Actual And Planned Cache Work

**Bits to Banking · Umicom Foundation**  
**Author:** Sammy Hegab

> **Learning objective:** Keep conditional cache arithmetic separate from observations

## 1. Begin with an ordinary calculation

The conditional cache plan begins with a P-row prefill, appends one row while free positions remain, then rebuilds full windows after eviction. The full-context reference always computes C rows per generated token.

A mathematical formula is a compact description of specific operations. Read each symbol aloud, identify what its input values represent and check the dimensions before using it in code. Integers describing positions or byte counts should remain exact; floating-point results require justified numerical tolerances when appropriate.

## 2. Work through the numbers

For C=8, P=3, L=2 and G=12, the reference performs `8 × 2 × 12 = 192` token-layer rows. The conditional plan performs `(3 + 5 + 6 × 8) × 2 = 112`. A saving of 80 is hypothetical until an equivalent cache is implemented and measured.

The operation's result should be checked against an independent calculation or a precisely defined invariant. A good test makes the comparison meaningful even if two implementations happen to choose the same final token. Keep observed quantities separate from proposed optimisations.

## 3. Connect the calculation to Umicom Framework

The production-facing C23 APIs are declared under `framework/include/umicom/ai/training/`. Applications should consume those APIs; they should not copy the underlying attention, sampling, checkpoint or random-number algorithms. All example calculations here use small numbers for education and do not represent results measured on a trained commercial model.

For the larger model, tensor operations, checkpoint identity, future-token masking and model-memory ownership must all use their existing Framework contracts. A written expression is not a substitute for the original native tests.

## 4. Exercise

**Question:** Does this arithmetic establish 80 rows saved by the current prefix generator?

<details><summary>Show the worked answer</summary>

No. The current prefix generator still evaluates all 192 token-layer rows. The 80-row reduction is contingent on a future proven cache.

</details>

## 5. Further learning

Return to [the mathematics course](../../courses/maths-for-ai/advanced-units.html), or read [this unit in HTML](../../courses/maths-for-ai/lessons/83-compare-actual-and-planned-cache-work.html). The full native AI course provides engineering examples in C23.

*Service to Many Leads to Greatness.*
