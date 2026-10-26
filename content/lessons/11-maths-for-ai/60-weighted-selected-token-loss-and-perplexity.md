# Unit 60 — Weighted selected-token loss and perplexity

**Mathematics for AI · Bits to Banking · Umicom Foundation**  
**Author:** Sammy Hegab

## Begin with familiar quantities

This is a self-contained numerical lesson for new contributors to Umicom Framework. A symbol is explained as it appears; the example contains artificial values rather than banking customer data. Native C23 code must preserve the stated formula, shape, memory ownership and numerical acceptance conditions.

## A worked mathematical explanation

Suppose two held-out examples contain one and three supervised target tokens. Their mean cross-entropies are 0.4 and 0.8. The combined token-weighted loss is `(1×0.4 + 3×0.8)/(1+3) = 2.8/4 = 0.7`. If the loss is in natural-log units, perplexity is `exp(0.7) ≈ 2.014`. If instead we averaged the two example losses without weighting, we would get 0.6: a different statistic. Loss masks define which targets count, while the per-example selected-target count defines each example's contribution. Perplexity is meaningful only with the associated tokenisation and held-out task; a low number is not evidence of factual accuracy or authorised financial decisions.

## Move from numbers to C23

When implementing a mathematical rule, first identify the input types and units, then compute a small result independently. Only after that should you compare it against a Framework API. Floating-point agreement uses a justified tolerance; token IDs, array capacities and SHA-256 byte representations require exact checking.

The associated native implementation is in `framework/src/ai/training/` and its public declarations are in `framework/include/umicom/ai/training/`. In particular, the stacked inference, evaluation and model-selection APIs reuse the existing Transformer, training tape, optimiser and tokeniser rather than duplicating those calculations in Bits2Banking.

## Practice

**Question:** Two examples supervise two and six targets, with losses 0.3 and 0.9. What is their combined loss?

<details>
<summary>Show the worked result</summary>

`(2×0.3+6×0.9)/8 = (0.6+5.4)/8 = 0.75`. The six-target example contributes more weight.

</details>

Continue with the [mathematics learning path for stacked inference](stacked-inference-mathematics.md), or return to the [native AI inference course](../10-native-ai/stacked-inference-learning-path.md). All examples are educational and do not represent live trades, payments or investment advice.
