# Mathematics for AI · Unit 73 — Separate Logit Agreement from Token Agreement

**Bits to Banking · Umicom Foundation**  
**Author:** Sammy Hegab  
**Suitable for:** Learners who want each symbol and calculation explained.

## 1. Understand the idea using ordinary language

A logit is a score before softmax. A model can choose the same most-likely token in two different runs even when its other scores are substantially different. Engineering must inspect full numerical distributions.

We write an equation only after naming the numbers involved. A trustworthy implementation should be able to reproduce a small example independently; a name such as "fast" or "cached" is not a mathematical result.

## 2. Read the formula

**Formula:** `maximumAbsoluteDifference = max(|referenceLogit[i] − candidateLogit[i]|)`

The equals sign represents the quantity we want to calculate. Identify the input quantities, keep the units consistent and check whether a result is an exact count, an approximation or a measurement. In model development, counts of tokens, bytes, parameters and seconds are not interchangeable units.

## 3. Calculate the worked example

Suppose a reference returns `[4.0, 2.0, 0.0]` and a candidate returns `[4.0, 0.0, 2.0]`. Both choose the first token (logit 4.0), yet the second and third logits differ by 2.0. The maximum absolute difference is 2.0. An acceptance threshold of 0.0001 would fail.

Recalculate the figures without relying on another program's printed totals. Only after the arithmetic agrees should you compare it with the real C23 Framework service.

## 4. What does the result NOT prove?

A tolerance must be declared before running. Distinguish expected floating-point rounding from a changed mathematical model, and always refuse non-finite logits.

A useful mathematical estimate is often a **necessary planning input**, but it does not replace an independent regression, a held-out evaluation or a measurement taken on the actual machine.

## 5. Practice with a revealable answer

**Question:** Reference `[2.0, 1.2]`, candidate `[2.0, 1.2003]`; does an absolute threshold of 0.0002 pass?

<details>
<summary>Show each step</summary>

No. The maximum absolute difference is 0.0003, which exceeds 0.0002. Both outputs may still choose the same winning token.

</details>

## 6. Continue with the implementation

The related native [LLM Lesson 163 — Recognise Upper-Layer History Divergence After Eviction](../10-native-ai/163-recognise-upper-layer-cache-history-divergence.md) connects this mathematics to a reviewed Framework API or its planned acceptance tests. All production or reusable logic remains inside Umicom Framework; mathematics manuscripts only explain it.

[Previous: Unit 72](72-calculate-causal-prefix-invariance.md) · [Next: Unit 74](74-keep-absolute-positions-through-rolling-windows.md)

*Service to Many Leads to Greatness.*
