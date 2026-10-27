# Mathematics for AI — Unit 126: Calculate scaled dot products and temperature

**Bits to Banking · Umicom Foundation**  
**Course lead:** Sammy Hegab · **Prerequisite:** Basic arithmetic and an interest in neural networks.

## What will you learn?

Understand why attention scores divide the query–key dot product by square root of head width.

## Step-by-step calculation

For `d_k=4`, choose `q=(2,0,2,0)` and `k=(1,0,1,0)`. The dot product is `2×1+0×0+2×1+0×0=4`. Since `sqrt(4)=2`, the scaled score is `4/2=2`.

With another key `k_2=(0,1,0,1)`, its raw dot product is zero, so scaled score is zero. These two scores produce weights `exp(2)/(exp(2)+1)≈0.880797` and `0.119203`. Dividing by `sqrt(d_k)` changes how sharply softmax concentrates; it must use the model’s trained convention, not a guessed scaling.

**Notation guide:** `H` = number of attention heads; `T` = valid causal token count; `D` = channels per head; `L` = Transformer layers. The symbols describe *example data*, not the size or performance of an actual deployed model.

## Work it out yourself

**Question:** For a head width of 9 and raw dot product 6, what is the scaled score?

<details>
<summary>Show the worked answer</summary>

`6/sqrt(9)=6/3=2`. The square root uses the key head dimension, not the number of retained tokens.

</details>

## Connect the numbers with native C23

[LLM Lesson 235](../10-native-ai/235-calculate-one-query-causal-attention.md) explains where this calculation belongs in the planned single-query kernel. The numerical implementation remains Framework-owned; these educational numbers are for checking reasoning, not a substitute for integrated decoder tests.

## Continue learning

[Previous unit](125-identify-single-query-attention-dimensions.md) · [Browser mathematics path](../../courses/maths-for-ai/single-query-attention-mathematics.html) · [Next unit](127-derive-stable-online-softmax.md)

*Service to Many Leads to Greatness.*
