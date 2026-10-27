# Mathematics for AI — Unit 128: Accumulate weighted value vectors

**Bits to Banking · Umicom Foundation**  
**Course lead:** Sammy Hegab · **Prerequisite:** Basic arithmetic and an interest in neural networks.

## What will you learn?

Multiply attention probabilities by values and sum coordinate-wise.

## Step-by-step calculation

Take softmax probabilities `p=(0.25,0.75)` and value vectors `v0=(4,0,-2)`, `v1=(0,8,2)`. The output is `0.25×(4,0,-2)+0.75×(0,8,2)=(1,6,1)`. The weights are shared across value channels **within the same head**, but other heads have their own score and value arrays.

With `T` tokens and head width `D`, direct accumulation uses roughly `T×D` weight–value products plus additions. In a one-query kernel this calculates only the requested output row; it is not a new learned operation.

**Notation guide:** `H` = number of attention heads; `T` = valid causal token count; `D` = channels per head; `L` = Transformer layers. The symbols describe *example data*, not the size or performance of an actual deployed model.

## Work it out yourself

**Question:** For weights `(0.6,0.4)` and scalar values `(10,-5)`, what is the output?

<details>
<summary>Show the worked answer</summary>

`0.6×10+0.4×(-5)=6-2=4`.

</details>

## Connect the numbers with native C23

[LLM Lesson 235](../10-native-ai/235-calculate-one-query-causal-attention.md) explains where this calculation belongs in the planned single-query kernel. The numerical implementation remains Framework-owned; these educational numbers are for checking reasoning, not a substitute for integrated decoder tests.

## Continue learning

[Previous unit](127-derive-stable-online-softmax.md) · [Browser mathematics path](../../courses/maths-for-ai/single-query-attention-mathematics.html) · [Next unit](129-reason-about-masked-softmax.md)

*Service to Many Leads to Greatness.*
