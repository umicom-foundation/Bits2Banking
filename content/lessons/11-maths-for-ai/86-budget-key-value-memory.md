# Mathematics for AI · Unit 86 — Budget Key Value Memory

**Bits to Banking · Umicom Foundation**  
**Author:** Sammy Hegab

> **Learning objective:** Multiply only the tensor dimensions being retained

## 1. Begin with an ordinary calculation

A basic FP32 key/value cache stores two arrays per layer. Each retained token contributes C channels of K and C channels of V for that layer.

A mathematical formula is a compact description of specific operations. Read each symbol aloud, identify what its input values represent and check the dimensions before using it in code. Integers describing positions or byte counts should remain exact; floating-point results require justified numerical tolerances when appropriate.

## 2. Work through the numbers

With 4 layers, 16 retained tokens, 32 channels and four bytes per FP32 value: `2 × 4 × 16 × 32 × 4 = 16,384 bytes`. This excludes base weights, residuals, activation workspaces, allocator and device memory overhead.

The operation's result should be checked against an independent calculation or a precisely defined invariant. A good test makes the comparison meaningful even if two implementations happen to choose the same final token. Keep observed quantities separate from proposed optimisations.

## 3. Connect the calculation to Umicom Framework

The production-facing C23 APIs are declared under `framework/include/umicom/ai/training/`. Applications should consume those APIs; they should not copy the underlying attention, sampling, checkpoint or random-number algorithms. All example calculations here use small numbers for education and do not represent results measured on a trained commercial model.

For the larger model, tensor operations, checkpoint identity, future-token masking and model-memory ownership must all use their existing Framework contracts. A written expression is not a substitute for the original native tests.

## 4. Exercise

**Question:** What is this raw tensor budget for three concurrent sequences?

<details><summary>Show the worked answer</summary>

`3 × 16,384 = 49,152 bytes`, excluding non-KV memory.

</details>

## 5. Further learning

Return to [the mathematics course](../../courses/maths-for-ai/advanced-units.html), or read [this unit in HTML](../../courses/maths-for-ai/lessons/86-budget-key-value-memory.html). The full native AI course provides engineering examples in C23.

*Service to Many Leads to Greatness.*
