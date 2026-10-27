# Mathematics for AI — Unit 132: Calculate cache and scratch memory separately

**Bits to Banking · Umicom Foundation**  
**Course lead:** Sammy Hegab · **Prerequisite:** Basic arithmetic and an interest in neural networks.

## What will you learn?

Budget persistent K/V bytes and temporary operator workspaces independently.

## Step-by-step calculation

For a dense FP32 K/V cache with `L` Transformer layers, `H` heads, `T` capacity and `D` channels per head, payload bytes are `2×L×H×T×D×4`. For `L=12`, `H=8`, `T=256`, `D=64`, this is `12,582,912` bytes, exactly `12 MiB` of tensor payload before metadata, alignment and allocator overhead.

A score scratch array for one query would add `H×T×4 = 8,192` bytes (8 KiB) in this example. Streaming normalisation may remove that score array, but **not** the 12 MiB K/V payload. Check every integer multiplication for overflow before allocating a real buffer.

**Notation guide:** `H` = number of attention heads; `T` = valid causal token count; `D` = channels per head; `L` = Transformer layers. The symbols describe *example data*, not the size or performance of an actual deployed model.

## Work it out yourself

**Question:** With `L=2`, `H=2`, `T=4`, `D=8`, FP32, how large is the K/V payload?

<details>
<summary>Show the worked answer</summary>

`2×2×2×4×8×4 = 1,024` bytes, excluding metadata and alignment.

</details>

## Connect the numbers with native C23

[LLM Lesson 237](../10-native-ai/237-budget-single-query-scratch-memory.md) explains where this calculation belongs in the planned single-query kernel. The numerical implementation remains Framework-owned; these educational numbers are for checking reasoning, not a substitute for integrated decoder tests.

## Continue learning

[Previous unit](131-calculate-absolute-and-relative-parity-errors.md) · [Browser mathematics path](../../courses/maths-for-ai/single-query-attention-mathematics.html) · [Next unit](133-prove-prefix-position-invariance.md)

*Service to Many Leads to Greatness.*
