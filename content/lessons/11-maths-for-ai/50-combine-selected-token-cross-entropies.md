# Combine cross-entropy for selected answer tokens

**Bits to Banking · Umicom Foundation**  
**Author:** Sammy Hegab · **Licence:** MIT  
**Level:** Gentle mathematics for native AI

## A probability becomes a loss

Cross-entropy measures how surprised a model is by the correct next token. The loss for one selected row is `L = −ln(p)`, where `p` is the model's predicted probability for that correct token. The natural logarithm `ln` grows as we move towards certainty in the other direction: a high correct-token probability gives a smaller loss.

Suppose a response has two selected targets. The model gives the first correct token probability 0.5 and the second 0.25. Their losses are `−ln(0.5) ≈ 0.6931` and `−ln(0.25) ≈ 1.3863`. The mean over selected targets is `(0.6931 + 1.3863) / 2 ≈ 1.0397`.

## Why padding changes the denominator if mishandled

Imagine the model's complete context has eight positions, but only these two response targets should contribute to the objective. Dividing by all eight positions would artificially reduce the loss. A zero/one response mask specifies which rows count. The Framework's selected cross-entropy already implements this rule.

## Combining different examples

If one example has mean loss 1.0 across one selected token and another mean loss 3.0 across three selected tokens, the correct overall mean is `(1×1.0 + 3×3.0) / 4 = 2.5`. An unweighted average of example means would misleadingly produce 2.0.

## Practice

Two selected correct-token probabilities are 1.0 and 0.5. What is their mean cross-entropy?

<details><summary>Worked answer</summary>

`−ln(1.0) = 0`, `−ln(0.5) ≈ 0.6931`; mean `(0 + 0.6931) / 2 ≈ 0.3466`. Real softmax probabilities from finite logits are usually strictly between zero and one.

</details>

---

[Mathematics reading path](stacked-transformer-mathematics.md) · [Native LLM course](../10-native-ai/stacked-transformer-learning-path.md)
