# Mathematics for AI — Unit 197: Derive one FP32 K/V reservation

**Bits to Banking · Umicom Foundation**  
**Author:** Sammy Hegab  
**Prerequisite:** Basic arithmetic and the preceding mathematics units.

## Learning objective

Calculate memory from the actual K/V tensor geometry rather than the size of the token prompt.

## Step-by-step derivation

For `L` layers, `T` context positions, `H` KV heads, `D` channels per head and `B` bytes per scalar:

`reserved = 2 × L × T × H × D × B`

The first factor of two represents keys and values. In a bounded stacked model with two layers, four positions, two KV heads, four channels per head, and four bytes per FP32 value, compute `2 × 2 × 4 × 2 × 4 × 4 = 512 bytes`. This agrees with a single store owning `[layer][position][channel]` arrays for K and V. Do not divide by the current prompt length; full capacity has already been reserved.

## Check your understanding

**Exercise:** How many raw bytes if the context doubles to eight?

<details><summary>Show the worked solution</summary>

1,024 bytes; only the context factor changes.

</details>

## Native C23 connection

Use the Framework's existing checked `InferenceMemoryPlan`, `StackedKvStore` and `StackedKvPool` contracts. Arithmetic estimates do not themselves prove safe allocation, neural accuracy or measured latency.

## Continue learning

[Previous unit](196-calculate-peak-concurrent-cache-pressure.md) · [Next unit](198-convert-a-budget-into-admitted-session-count.md) · [Browser unit](../../courses/maths-for-ai/lessons/197-derive-one-fp32-kv-reservation.html)

*Service to Many Leads to Greatness.*
