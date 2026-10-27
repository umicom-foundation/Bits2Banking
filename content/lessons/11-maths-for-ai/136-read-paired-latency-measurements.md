# Mathematics for AI — Unit 136: Read paired latency measurements and uncertainty

**Bits to Banking · Umicom Foundation**  
**Course lead:** Sammy Hegab · **Prerequisite:** Basic arithmetic and an interest in neural networks.

## What will you learn?

Calculate medians and refrain from over-generalising small benchmark samples.

## Step-by-step calculation

Five illustrative reference runs take `[5.0,4.8,5.1,5.0,4.9]` ms. Sorted order is `[4.8,4.9,5.0,5.0,5.1]`, giving median `5.0` ms. Candidate runs take `[4.9,4.7,5.2,4.8,4.7]` ms; sorted order is `[4.7,4.7,4.8,4.9,5.2]`, giving median `4.8` ms. The ratio `5.0/4.8≈1.0417` is about **4.2%** in this small sample. One candidate observation is still slower than its paired reference.

Because samples are few, avoid treating this difference as certain. Collect repeated paired measurements in both execution orders, include percentile/spread, note compiler and CPU, and compare real full-session workloads. Numerical parity remains a prerequisite to calling both programs interchangeable.

**Notation guide:** `H` = number of attention heads; `T` = valid causal token count; `D` = channels per head; `L` = Transformer layers. The symbols describe *example data*, not the size or performance of an actual deployed model.

## Work it out yourself

**Question:** Find the median of `3.0, 8.0, 3.5, 4.0, 3.2` ms.

<details>
<summary>Show the worked answer</summary>

Sorted: `3.0,3.2,3.5,4.0,8.0`. Median is `3.5` ms; the outlier does not determine the middle observation.

</details>

## Connect the numbers with native C23

[LLM Lesson 246](../10-native-ai/246-benchmark-one-query-attention-with-fair-controls.md) explains where this calculation belongs in the planned single-query kernel. The numerical implementation remains Framework-owned; these educational numbers are for checking reasoning, not a substitute for integrated decoder tests.

## Continue learning

[Previous unit](135-estimate-attention-arithmetic-and-memory-traffic.md) · [Browser mathematics path](../../courses/maths-for-ai/single-query-attention-mathematics.html)

*Service to Many Leads to Greatness.*
