# Mathematics for AI · Unit 81 — Pending Samples And Append Counts

**Bits to Banking · Umicom Foundation**  
**Author:** Sammy Hegab

> **Learning objective:** Count only the tokens actually appended to the model context

## 1. Begin with an ordinary calculation

The first `Next` call samples from the initial prefix. The returned ID becomes pending and is appended only if the caller requests the next sample. This avoids work for an output that will never be queried again.

A mathematical formula is a compact description of specific operations. Read each symbol aloud, identify what its input values represent and check the dimensions before using it in code. Integers describing positions or byte counts should remain exact; floating-point results require justified numerical tolerances when appropriate.

## 2. Work through the numbers

For `G` successfully produced tokens, there are exactly `G - 1` pending-token appends. With initial `P=3`, capacity `C=8` and `G=5`, four appends fill positions 3 through 6. Retained context becomes 7 tokens and no eviction is needed.

The operation's result should be checked against an independent calculation or a precisely defined invariant. A good test makes the comparison meaningful even if two implementations happen to choose the same final token. Keep observed quantities separate from proposed optimisations.

## 3. Connect the calculation to Umicom Framework

The production-facing C23 APIs are declared under `framework/include/umicom/ai/training/`. Applications should consume those APIs; they should not copy the underlying attention, sampling, checkpoint or random-number algorithms. All example calculations here use small numbers for education and do not represent results measured on a trained commercial model.

For the larger model, tensor operations, checkpoint identity, future-token masking and model-memory ownership must all use their existing Framework contracts. A written expression is not a substitute for the original native tests.

## 4. Exercise

**Question:** For prompt 3, context 8 and generated 7, how many appends and evictions are required?

<details><summary>Show the worked answer</summary>

Six appends occur. Five fill the context and the sixth evicts the oldest token: one eviction.

</details>

## 5. Further learning

Return to [the mathematics course](../../courses/maths-for-ai/advanced-units.html), or read [this unit in HTML](../../courses/maths-for-ai/lessons/81-pending-samples-and-append-counts.html). The full native AI course provides engineering examples in C23.

*Service to Many Leads to Greatness.*
