# Unit 55 — Logit rankings and the most likely token

**Mathematics for AI · Bits to Banking · Umicom Foundation**  
**Author:** Sammy Hegab

## Begin with familiar quantities

This is a self-contained numerical lesson for new contributors to Umicom Framework. A symbol is explained as it appears; the example contains artificial values rather than banking customer data. Native C23 code must preserve the stated formula, shape, memory ownership and numerical acceptance conditions.

## A worked mathematical explanation

A logit is a numerical score; it need not be between zero and one. In a three-token example, logits `[2,1,0]` rank the first candidate highest, the second next and the third last. Ranking alone does not tell us their probabilities. Applying softmax at temperature one gives approximate probabilities `[0.665,0.245,0.090]`, which add to one. Multiplying every score by the same positive factor normally changes the probability concentration but not the ranking. Adding the same number to all logits does not change softmax probabilities. In C23, the Framework stores finite FP32 logits; the sampling service performs the stable probability calculation instead of every application implementing it separately.

## Move from numbers to C23

When implementing a mathematical rule, first identify the input types and units, then compute a small result independently. Only after that should you compare it against a Framework API. Floating-point agreement uses a justified tolerance; token IDs, array capacities and SHA-256 byte representations require exact checking.

The associated native implementation is in `framework/src/ai/training/` and its public declarations are in `framework/include/umicom/ai/training/`. In particular, the stacked inference, evaluation and model-selection APIs reuse the existing Transformer, training tape, optimiser and tokeniser rather than duplicating those calculations in Bits2Banking.

## Practice

**Question:** For scores `[3,3,1]`, what is the top-ranked candidate?

<details>
<summary>Show the worked result</summary>

There is a tie between the first and second. Umicom's greedy ordering breaks ties in favour of the lower token ID; the first of those two is chosen if its ID is lower.

</details>

Continue with the [mathematics learning path for stacked inference](stacked-inference-mathematics.md), or return to the [native AI inference course](../10-native-ai/stacked-inference-learning-path.md). All examples are educational and do not represent live trades, payments or investment advice.
