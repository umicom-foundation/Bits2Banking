# Mathematics for AI · Unit 87 — Choose A Numerical Parity Tolerance

**Bits to Banking · Umicom Foundation**  
**Author:** Sammy Hegab

> **Learning objective:** Calculate a complete reference-versus-candidate check

## 1. Begin with an ordinary calculation

For each vocabulary score, compute the absolute difference between the canonical decoder and a candidate. Accept only if every score is finite and within the predefined tolerance.

A mathematical formula is a compact description of specific operations. Read each symbol aloud, identify what its input values represent and check the dimensions before using it in code. Integers describing positions or byte counts should remain exact; floating-point results require justified numerical tolerances when appropriate.

## 2. Work through the numbers

If reference is 0.500000 and candidate 0.500035, the absolute difference is 0.000035. A tolerance of 0.00004 accepts that score. If another candidate score differs by 0.00006, the complete model comparison fails.

The operation's result should be checked against an independent calculation or a precisely defined invariant. A good test makes the comparison meaningful even if two implementations happen to choose the same final token. Keep observed quantities separate from proposed optimisations.

## 3. Connect the calculation to Umicom Framework

The production-facing C23 APIs are declared under `framework/include/umicom/ai/training/`. Applications should consume those APIs; they should not copy the underlying attention, sampling, checkpoint or random-number algorithms. All example calculations here use small numbers for education and do not represent results measured on a trained commercial model.

For the larger model, tensor operations, checkpoint identity, future-token masking and model-memory ownership must all use their existing Framework contracts. A written expression is not a substitute for the original native tests.

## 4. Exercise

**Question:** Does checking only the winner’s score establish all-vocabulary parity?

<details><summary>Show the worked answer</summary>

No. Every candidate score influences sampling probabilities; any unchecked value could disagree beyond tolerance.

</details>

## 5. Further learning

Return to [the mathematics course](../../courses/maths-for-ai/advanced-units.html), or read [this unit in HTML](../../courses/maths-for-ai/lessons/87-choose-a-numerical-parity-tolerance.html). The full native AI course provides engineering examples in C23.

*Service to Many Leads to Greatness.*
