# Mathematics for AI — Unit 129: Reason about masked softmax and invalid rows

**Bits to Banking · Umicom Foundation**  
**Course lead:** Sammy Hegab · **Prerequisite:** Basic arithmetic and an interest in neural networks.

## What will you learn?

Distinguish a valid masked score from a broken numerical input.

## Step-by-step calculation

A masked score is intentionally excluded; it contributes probability zero. An **unmasked** NaN is invalid and should cause rejection. For valid scores `[3,1]`, subtract the maximum `3` to get `[0,-2]`; probabilities are `1/(1+exp(-2))≈0.880797` and `0.119203`. If a third physical slot is masked, it contributes nothing.

A common mistake is to set padded entries to score zero and include them in the denominator. Even with a zero key vector, `exp(0)` is positive. The correct solution is exclusion based on a verified valid-length or mask contract, not choosing a special data value that “usually has little effect”.

**Notation guide:** `H` = number of attention heads; `T` = valid causal token count; `D` = channels per head; `L` = Transformer layers. The symbols describe *example data*, not the size or performance of an actual deployed model.

## Work it out yourself

**Question:** If scores `[1,1,1]` have mask `[valid,invalid,valid]`, what are the weights?

<details>
<summary>Show the worked answer</summary>

`(0.5,0,0.5)`, because the two valid equal scores split the probability mass equally.

</details>

## Connect the numbers with native C23

[LLM Lesson 236](../10-native-ai/236-preserve-causal-masks-and-padding-semantics.md) explains where this calculation belongs in the planned single-query kernel. The numerical implementation remains Framework-owned; these educational numbers are for checking reasoning, not a substitute for integrated decoder tests.

## Continue learning

[Previous unit](128-accumulate-weighted-values.md) · [Browser mathematics path](../../courses/maths-for-ai/single-query-attention-mathematics.html) · [Next unit](130-reconstruct-multihead-output-shapes.md)

*Service to Many Leads to Greatness.*
