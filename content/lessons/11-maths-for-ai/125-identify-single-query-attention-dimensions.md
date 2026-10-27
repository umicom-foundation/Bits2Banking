# Mathematics for AI — Unit 125: Identify single-query attention dimensions

**Bits to Banking · Umicom Foundation**  
**Course lead:** Sammy Hegab · **Prerequisite:** Basic arithmetic and an interest in neural networks.

## What will you learn?

Learn to read shapes for queries, retained keys, values and one output row.

## Step-by-step calculation

Let `H=3` heads, `T=5` valid causal tokens and `D=4` channels per head. `Q` has shape `[3,1,4]` (or logically `[3,4]` after removing the singleton query axis). `K` and `V` each have `[3,5,4]`. Each head produces `[1,4]`; concatenating outputs creates a vector of length `H×D=12`.

The number of Q elements is `3×1×4=12`; K and V each contain `3×5×4=60`. With FP32 values, the three inputs contain `(12+60+60)×4=528` bytes. Capacity can exceed `T`, but padding is not eligible to receive attention.

**Notation guide:** `H` = number of attention heads; `T` = valid causal token count; `D` = channels per head; `L` = Transformer layers. The symbols describe *example data*, not the size or performance of an actual deployed model.

## Work it out yourself

**Question:** If `H=2`, `D=8`, `T=7`, how many K elements are valid?

<details>
<summary>Show the worked answer</summary>

`H×T×D = 2×7×8 = 112` valid key elements. The same count applies to V.

</details>

## Connect the numbers with native C23

[LLM Lesson 233](../10-native-ai/233-define-a-single-query-attention-contract.md) explains where this calculation belongs in the planned single-query kernel. The numerical implementation remains Framework-owned; these educational numbers are for checking reasoning, not a substitute for integrated decoder tests.

## Continue learning

[Previous unit](124-compare-release-timings-with-uncertainty.md) · [Browser mathematics path](../../courses/maths-for-ai/single-query-attention-mathematics.html) · [Next unit](126-calculate-scaled-dot-products-and-temperature.md)

*Service to Many Leads to Greatness.*
