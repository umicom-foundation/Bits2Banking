# Mathematics for AI — Unit 130: Reconstruct multi-head output shapes

**Bits to Banking · Umicom Foundation**  
**Course lead:** Sammy Hegab · **Prerequisite:** Basic arithmetic and an interest in neural networks.

## What will you learn?

Concatenate attention heads without changing their order.

## Step-by-step calculation

Let head 0 output `(1,2)` and head 1 output `(3,4)` for `H=2, D=2`. Concatenate in head order to obtain `(1,2,3,4)`. A model output-projection matrix `W_O` of shape `[4,4]` maps this to a four-element hidden-state update. If `W_O` is the identity, the output stays `(1,2,3,4)`; reversing the heads would instead give `(3,4,1,2)`, a plainly different result.

The same shape `[4]` does not prove the same values or ordering. Tests need asymmetric data. Never average per-head vectors unless the **trained model’s architecture** actually prescribes such a reduction.

**Notation guide:** `H` = number of attention heads; `T` = valid causal token count; `D` = channels per head; `L` = Transformer layers. The symbols describe *example data*, not the size or performance of an actual deployed model.

## Work it out yourself

**Question:** Three heads each return width 8. How many concatenated values are there?

<details>
<summary>Show the worked answer</summary>

`3×8=24` values, in the exact head ordering used by the trained output projection.

</details>

## Connect the numbers with native C23

[LLM Lesson 240](../10-native-ai/240-preserve-head-concatenation-and-output-projection.md) explains where this calculation belongs in the planned single-query kernel. The numerical implementation remains Framework-owned; these educational numbers are for checking reasoning, not a substitute for integrated decoder tests.

## Continue learning

[Previous unit](129-reason-about-masked-softmax.md) · [Browser mathematics path](../../courses/maths-for-ai/single-query-attention-mathematics.html) · [Next unit](131-calculate-absolute-and-relative-parity-errors.md)

*Service to Many Leads to Greatness.*
