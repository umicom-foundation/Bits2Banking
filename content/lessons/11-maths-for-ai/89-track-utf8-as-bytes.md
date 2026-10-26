# Mathematics for AI · Unit 89 — Track UTF-8 As Bytes

**Bits to Banking · Umicom Foundation**  
**Author:** Sammy Hegab

> **Learning objective:** Count byte-token IDs without splitting characters

## 1. Begin with an ordinary calculation

A Unicode scalar can occupy one, two, three or four bytes in UTF-8. The current Umicom byte vocabulary deliberately models raw bytes, so one visible character may require several generated token IDs.

A mathematical formula is a compact description of specific operations. Read each symbol aloud, identify what its input values represent and check the dimensions before using it in code. Integers describing positions or byte counts should remain exact; floating-point results require justified numerical tolerances when appropriate.

## 2. Work through the numbers

The euro sign € is UTF-8 `E2 82 AC`: decimal bytes 226,130,172. The native tokenizer maps them to IDs 230,134,176 (each byte plus 4). A UI must assemble all three bytes before emitting that complete character.

The operation's result should be checked against an independent calculation or a precisely defined invariant. A good test makes the comparison meaningful even if two implementations happen to choose the same final token. Keep observed quantities separate from proposed optimisations.

## 3. Connect the calculation to Umicom Framework

The production-facing C23 APIs are declared under `framework/include/umicom/ai/training/`. Applications should consume those APIs; they should not copy the underlying attention, sampling, checkpoint or random-number algorithms. All example calculations here use small numbers for education and do not represent results measured on a trained commercial model.

For the larger model, tensor operations, checkpoint identity, future-token masking and model-memory ownership must all use their existing Framework contracts. A written expression is not a substitute for the original native tests.

## 4. Exercise

**Question:** How many byte-token IDs represent the UTF-8 text €A?

<details><summary>Show the worked answer</summary>

Three bytes for € plus one ASCII byte for A: four byte-token IDs.

</details>

## 5. Further learning

Return to [the mathematics course](../../courses/maths-for-ai/advanced-units.html), or read [this unit in HTML](../../courses/maths-for-ai/lessons/89-track-utf8-as-bytes.html). The full native AI course provides engineering examples in C23.

*Service to Many Leads to Greatness.*
