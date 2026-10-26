# Mathematics for AI · Unit 84 — Count Evictions After Context Fills

**Bits to Banking · Umicom Foundation**  
**Author:** Sammy Hegab

> **Learning objective:** Apply min and max carefully to full contexts

## 1. Begin with an ordinary calculation

Let P be initial prefix length, C context capacity and G produced tokens. The number of pending appends is A=G−1. Safe appends are `S=min(A,C−P)`, and window shifts are `R=A−S`.

A mathematical formula is a compact description of specific operations. Read each symbol aloud, identify what its input values represent and check the dimensions before using it in code. Integers describing positions or byte counts should remain exact; floating-point results require justified numerical tolerances when appropriate.

## 2. Work through the numbers

For P=3,C=4,G=8, A=7, safe S=1 and shifts R=6. A two-layer conditional plan would compute `(3 + 1 + 6×4)×2=56` token-layer rows compared with `4×2×8=64` full-context rows.

The operation's result should be checked against an independent calculation or a precisely defined invariant. A good test makes the comparison meaningful even if two implementations happen to choose the same final token. Keep observed quantities separate from proposed optimisations.

## 3. Connect the calculation to Umicom Framework

The production-facing C23 APIs are declared under `framework/include/umicom/ai/training/`. Applications should consume those APIs; they should not copy the underlying attention, sampling, checkpoint or random-number algorithms. All example calculations here use small numbers for education and do not represent results measured on a trained commercial model.

For the larger model, tensor operations, checkpoint identity, future-token masking and model-memory ownership must all use their existing Framework contracts. A written expression is not a substitute for the original native tests.

## 4. Exercise

**Question:** For P=2,C=5,G=5, how many safe appends and shifts occur?

<details><summary>Show the worked answer</summary>

A=4; three fit (`S=3`) and one shifts (`R=1`).

</details>

## 5. Further learning

Return to [the mathematics course](../../courses/maths-for-ai/advanced-units.html), or read [this unit in HTML](../../courses/maths-for-ai/lessons/84-count-evictions-after-context-fills.html). The full native AI course provides engineering examples in C23.

*Service to Many Leads to Greatness.*
