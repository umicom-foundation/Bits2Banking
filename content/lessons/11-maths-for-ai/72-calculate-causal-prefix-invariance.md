# Mathematics for AI · Unit 72 — Calculate What a Causal Prefix Can and Cannot See

**Bits to Banking · Umicom Foundation**  
**Author:** Sammy Hegab  
**Suitable for:** Learners who want each symbol and calculation explained.

## 1. Understand the idea using ordinary language

Causal attention allows a token to read its own position and earlier positions, never future positions. This creates a mathematical reason earlier token states remain fixed when a new token is appended at the end.

We write an equation only after naming the numbers involved. A trustworthy implementation should be able to reproduce a small example independently; a name such as "fast" or "cached" is not a mathematical result.

## 2. Read the formula

**Formula:** `allowedKeyPositions(queryPosition i) = {0, 1, …, i}`

The equals sign represents the quantity we want to calculate. Identify the input quantities, keep the units consistent and check whether a result is an exact count, an approximation or a measurement. In model development, counts of tokens, bytes, parameters and seconds are not interchangeable units.

## 3. Calculate the worked example

For a five-token sequence, the number of allowed key comparisons at positions 0 through 4 is `1 + 2 + 3 + 4 + 5 = 15`. A query at position 2 reads three keys, not five. Adding a sixth token at position 5 adds six possible comparisons for that new query but does not add a future dependency for previous queries.

Recalculate the figures without relying on another program's printed totals. Only after the arithmetic agrees should you compare it with the real C23 Framework service.

## 4. What does the result NOT prove?

If the first token is evicted, the retained sequence is not the same causal prefix. Previous upper-layer states may carry the evicted token’s information.

A useful mathematical estimate is often a **necessary planning input**, but it does not replace an independent regression, a held-out evaluation or a measurement taken on the actual machine.

## 5. Practice with a revealable answer

**Question:** How many allowed attention-key comparisons are in the six query rows of a full causal sequence?

<details>
<summary>Show each step</summary>

1+2+3+4+5+6 = 21 comparisons. This counts permitted query–key pairs in one head, not all floating-point operations.

</details>

## 6. Continue with the implementation

The related native [LLM Lesson 162 — Prove What Causal Prefix Growth Actually Preserves](../10-native-ai/162-causal-prefix-growth-and-hidden-state-invariants.md) connects this mathematics to a reviewed Framework API or its planned acceptance tests. All production or reusable logic remains inside Umicom Framework; mathematics manuscripts only explain it.

[Previous: Unit 71](71-count-token-layer-rows-in-a-cache-plan.md) · [Next: Unit 73](73-separate-logit-parity-from-token-agreement.md)

*Service to Many Leads to Greatness.*
