# Prove that future tokens do not change earlier outputs

**Bits to Banking · Umicom Foundation**  
**Author:** Sammy Hegab · **Licence:** MIT  
**Level:** Gentle mathematics for native AI

## The question behind a causal mask

Imagine a three-token sentence with tokens A, B and C. When the model predicts at A, C has not yet arrived. A causal decoder must prevent A from using information at B or C. When it predicts at B, it may use A and B but not C.

We can express this as a triangular permission table. With three positions numbered 0, 1 and 2, permitted key positions are: row 0 → {0}, row 1 → {0,1}, row 2 → {0,1,2}.

## Why this remains true across multiple layers

Suppose the output of one layer at position 1 depends only on its input positions 0 and 1. A second correctly masked layer at position 1 sees only the first layer's outputs 0 and 1. Neither of those depends on position 2. Therefore the second layer still cannot depend on the future token at position 2.

This is an example of an *inductive proof*: if the property holds for the first layer and each added layer preserves it, the full stack has that property. We still test the real implementation because a shape or indexing bug can violate an otherwise sound argument.

## Practice

Contexts `[A,B,C,D]` and `[A,B,X,Y]` share two positions. Which logits must remain the same for a causal model?

<details><summary>Worked answer</summary>

The logits at positions 0 and 1 must agree to the chosen numerical tolerance. Positions 2 and 3 may change. Checking **every vocabulary logit** is stronger than checking only the token ID chosen by greedy decoding.

</details>

---

[Mathematics reading path](stacked-transformer-mathematics.md) · [Native LLM course](../10-native-ai/stacked-transformer-learning-path.md)
