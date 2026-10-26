# Track tensor shapes from embeddings to logits

**Bits to Banking · Umicom Foundation**  
**Author:** Sammy Hegab · **Licence:** MIT  
**Level:** Gentle mathematics for native AI

## Think of a table of numbers

Four tokens are four rows. Eight channels are eight columns. The model's hidden state therefore has shape `[4,8]`. Multiplying it by an `[8,8]` matrix produces another `[4,8]` table. Two Transformer blocks can be stacked because both accept and return the same hidden width.

The feed-forward expansion is `[4,8] × [8,12] = [4,12]`. Its contraction is `[4,12] × [12,8] = [4,8]`. The output head then maps `[4,8] × [8,16] = [4,16]`.

## Why heads must divide evenly

Eight channels and two heads give four channels per attention head. Eight divided by three is not an integer, so three equal heads do not fit this shape without redesign. This is a validation condition, not a subjective modelling preference.

## A shape is not a byte count

A `[4,16]` FP32 logit table contains 64 numbers and occupies 256 bytes for raw values. If you also need its gradient, that can add another 256 bytes before counting metadata and auxiliary storage. Real operators have more temporary arrays.

## Practice

If hidden width is 12 and the vocabulary contains 200 IDs, what is the shape and FP32 value storage of final logits for six token positions?

<details><summary>Worked answer</summary>

Shape `[6,200]` means 1,200 values. At four bytes each, its raw values occupy 4,800 bytes. The output projection matrix itself has shape `[12,200]` and contains 2,400 weights, a *separate* storage cost.

</details>

---

[Mathematics reading path](stacked-transformer-mathematics.md) · [Native LLM course](../10-native-ai/stacked-transformer-learning-path.md)
