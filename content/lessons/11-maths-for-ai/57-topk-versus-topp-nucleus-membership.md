# Unit 57 — Top-K versus top-p nucleus membership

**Mathematics for AI · Bits to Banking · Umicom Foundation**  
**Author:** Sammy Hegab

## Begin with familiar quantities

This is a self-contained numerical lesson for new contributors to Umicom Framework. A symbol is explained as it appears; the example contains artificial values rather than banking customer data. Native C23 code must preserve the stated formula, shape, memory ownership and numerical acceptance conditions.

## A worked mathematical explanation

Top-K first limits consideration to the largest K logits. Nucleus sampling then retains the smallest descending prefix whose normalised probability mass reaches the selected top-p threshold. For candidate probabilities `[0.50,0.30,0.15,0.05]` and K=4, top-p 0.8 retains the first two candidates (0.50+0.30=0.80). Top-p 0.9 needs the first three (0.95). A sampler may renormalise retained candidates before drawing. If the model's vocabulary reserves IDs for control symbols, the allowed range must be applied before ranking. Token probability depends on temperature and on the allowed candidate set; top-K and top-p therefore cannot be compared as if they were interchangeable scalar thresholds.

## Move from numbers to C23

When implementing a mathematical rule, first identify the input types and units, then compute a small result independently. Only after that should you compare it against a Framework API. Floating-point agreement uses a justified tolerance; token IDs, array capacities and SHA-256 byte representations require exact checking.

The associated native implementation is in `framework/src/ai/training/` and its public declarations are in `framework/include/umicom/ai/training/`. In particular, the stacked inference, evaluation and model-selection APIs reuse the existing Transformer, training tape, optimiser and tokeniser rather than duplicating those calculations in Bits2Banking.

## Practice

**Question:** For probabilities `[0.6,0.2,0.1,0.1]` and top-p 0.75, how many ranked candidates are needed?

<details>
<summary>Show the worked result</summary>

Two. The first has mass 0.6, below 0.75; the first two total 0.8, meeting the threshold.

</details>

Continue with the [mathematics learning path for stacked inference](stacked-inference-mathematics.md), or return to the [native AI inference course](../10-native-ai/stacked-inference-learning-path.md). All examples are educational and do not represent live trades, payments or investment advice.
