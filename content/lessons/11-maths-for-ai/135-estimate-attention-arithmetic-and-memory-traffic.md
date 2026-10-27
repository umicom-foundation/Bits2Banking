# Mathematics for AI — Unit 135: Estimate attention arithmetic and memory traffic

**Bits to Banking · Umicom Foundation**  
**Course lead:** Sammy Hegab · **Prerequisite:** Basic arithmetic and an interest in neural networks.

## What will you learn?

Distinguish operation counts from bytes read and runtime.

## Step-by-step calculation

For one query with `H` heads, `T` cached tokens and width `D`, a rough count is `2×H×T×D` scalar operations for dot products plus approximately `2×H×T×D` for weighted-value accumulation, giving about `4×H×T×D` arithmetic operations before exponentials, masking and output projection. This is a **counting convention** (one multiply and one addition counted separately), not a hardware FLOPs measurement.

At FP32, reading both K and V once requires at least `2×H×T×D×4` payload bytes, ignoring cache-line fetch, repeat reads and intermediate tensors. For `H=4,T=64,D=16`: about `16,384` arithmetic operations and `32,768` bytes of K/V payload. Real elapsed time also depends on caches, SIMD utilisation, allocations, CPU frequency and the rest of the decoder.

**Notation guide:** `H` = number of attention heads; `T` = valid causal token count; `D` = channels per head; `L` = Transformer layers. The symbols describe *example data*, not the size or performance of an actual deployed model.

## Work it out yourself

**Question:** For `H=2,T=32,D=8`, estimate arithmetic operations under this convention.

<details>
<summary>Show the worked answer</summary>

`4×2×32×8 = 2,048` counted multiply/add operations, excluding exponentials and projections.

</details>

## Connect the numbers with native C23

[LLM Lesson 247](../10-native-ai/247-plan-portable-cpu-kernel-optimisation.md) explains where this calculation belongs in the planned single-query kernel. The numerical implementation remains Framework-owned; these educational numbers are for checking reasoning, not a substitute for integrated decoder tests.

## Continue learning

[Previous unit](134-count-rollover-rebuilds-for-bounded-context.md) · [Browser mathematics path](../../courses/maths-for-ai/single-query-attention-mathematics.html) · [Next unit](136-read-paired-latency-measurements.md)

*Service to Many Leads to Greatness.*
