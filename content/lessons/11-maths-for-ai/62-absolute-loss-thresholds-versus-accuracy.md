# Unit 62 — Absolute loss thresholds versus accuracy thresholds

**Mathematics for AI · Bits to Banking · Umicom Foundation**  
**Author:** Sammy Hegab

## Begin with familiar quantities

This is a self-contained numerical lesson for new contributors to Umicom Framework. A symbol is explained as it appears; the example contains artificial values rather than banking customer data. Native C23 code must preserve the stated formula, shape, memory ownership and numerical acceptance conditions.

## A worked mathematical explanation

A model acceptance policy can combine distinct numeric constraints. Let baseline mean loss be 0.60, candidate loss 0.63, and maximum allowed increase 0.05: loss passes because `0.63−0.60 = 0.03 ≤ 0.05`. If the candidate top-one accuracy is 0.58 and the policy requires 0.60, accuracy fails, so the combined decision fails. The program should return a successful *comparison* with a rejected-candidate flag. A calculation error or malformed policy is different from a valid candidate that misses a threshold. Numeric thresholds must be selected before inspecting a proposed model to avoid adjusting criteria until an unsuitable model passes.

## Move from numbers to C23

When implementing a mathematical rule, first identify the input types and units, then compute a small result independently. Only after that should you compare it against a Framework API. Floating-point agreement uses a justified tolerance; token IDs, array capacities and SHA-256 byte representations require exact checking.

The associated native implementation is in `framework/src/ai/training/` and its public declarations are in `framework/include/umicom/ai/training/`. In particular, the stacked inference, evaluation and model-selection APIs reuse the existing Transformer, training tape, optimiser and tokeniser rather than duplicating those calculations in Bits2Banking.

## Practice

**Question:** Baseline loss 0.9, candidate loss 0.98, permitted increase 0.05, accuracy meets its floor. Is the candidate accepted?

<details>
<summary>Show the worked result</summary>

No. Loss increased by `0.98−0.90 = 0.08`, greater than the allowed 0.05. Passing accuracy cannot override the loss rejection when both conditions are required.

</details>

Continue with the [mathematics learning path for stacked inference](stacked-inference-mathematics.md), or return to the [native AI inference course](../10-native-ai/stacked-inference-learning-path.md). All examples are educational and do not represent live trades, payments or investment advice.
