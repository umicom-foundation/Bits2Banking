# Mathematics for AI — Unit 13: Attention Scores and Causal Masks

**Bits to Banking · Umicom Foundation · Sammy Hegab**

## What you will learn

A Transformer combines information from earlier tokens using **attention**. You will calculate query–key scores, convert them into positive weights, apply those weights to value vectors, and explain why a causal mask blocks future information. No existing model is required for this numerical lesson.

## 1. Three roles, not three kinds of words

A **query** (Q) describes what the current token is seeking; a **key** (K) describes what each available token offers for comparison; a **value** (V) is the numerical content that can be mixed into the output. All three are learned projections in a real Transformer. Their coordinates should not be interpreted as literal English meanings.

Consider the query for the **second** token and two available earlier/current tokens:

| Item | Vector |
|---|---|
| Query Q | `[1, 1]` |
| First key K₁ | `[1, 0]` |
| Second key K₂ | `[0, 1]` |
| First value V₁ | `[2, 4]` |
| Second value V₂ | `[6, 8]` |

All vectors have two entries, so the attention-head width is `d = 2`.

## 2. Calculate scaled scores

The **dot product** multiplies matching coordinates and sums the products:

`Q · K₁ = (1 × 1) + (1 × 0) = 1`

`Q · K₂ = (1 × 0) + (1 × 1) = 1`

The scaled attention-score formula is:

`scoreⱼ = (Q · Kⱼ) / √d`

Here `j` identifies a candidate key, and `√d` is the square root of the number of channels in the head. With `d = 2`, both scores are `1 / √2 ≈ 0.7071`. Their equality is the important fact.

## 3. Convert scores into weights

**Softmax** converts any finite score vector into nonnegative weights summing to one. For score `sⱼ`:

`weightⱼ = exp(sⱼ) / Σₖ exp(sₖ)`

The symbol `Σ` means to sum over every **allowed** key. Because our two scores are equal, both exponentials are equal and both weights are `0.5`. We do not have to approximate an exponential to find this result.

The output combines the value vectors:

`output = 0.5 × [2, 4] + 0.5 × [6, 8] = [4, 6]`

Compute the first coordinate as `0.5 × 2 + 0.5 × 6 = 4`, and the second as `0.5 × 4 + 0.5 × 8 = 6`.

## 4. Why the first token gets a different answer

A left-to-right language model may use the **current** token and all **earlier** tokens, but not later ones. This restriction is the **causal mask**. The first query can see only K₁, so its only allowed attention weight is 1 and its output is V₁, `[2, 4]`. The second query may see both keys and produces `[4, 6]` in our example.

Masking should happen **before** softmax, so a future position receives zero probability. Implementations often use a negative-infinity sentinel or an equivalent masked softmax algorithm; finite-precision behaviour must still be validated.

In the Umicom Framework the reusable operation `UmiAiTrainingMultiHeadCausalAttention` handles masking, scaled scores and differentiation. Bits2Banking explains the mathematics but does not reimplement the numerical engine.

## 5. A failure to detect

If token 1's output changes when you modify token 2's future input, the causal boundary may have been broken. A rigorous regression checks more than the highest-scoring token: it compares relevant logits or intermediate outputs with a declared numerical tolerance.

## Practice and worked answer

**Question:** With weights `0.5` and `0.5`, replace V₁ with `[10, 2]` and V₂ with `[4, 6]`. What is the output?

**Answer:** First coordinate: `(10 + 4) / 2 = 7`. Second coordinate: `(2 + 6) / 2 = 4`. The combined vector is **`[7, 4]`**. For the first causal position, only its own value is visible.

**Explain:** Why would changing the order of the tokens change which keys are permitted for an earlier query? What does the head width `d` control?

Read the [illustrated HTML lesson](../../courses/maths-for-ai/lessons/13-attention-scores-and-causal-masks.html) for its diagram and interactive worked answer. Earlier foundations: [vectors](03-vectors-and-dot-products.md), [softmax](05-probability-softmax-and-loss.md) and [attention workloads](08-attention-and-kv-work.md).
