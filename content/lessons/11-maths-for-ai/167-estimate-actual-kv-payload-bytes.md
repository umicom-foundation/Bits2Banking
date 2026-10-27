# Mathematics for AI — Unit 167: Estimate actual KV payload bytes

**Bits to Banking · Umicom Foundation**  
**Author:** Sammy Hegab · **Prerequisite:** Basic arithmetic and preceding course units.

## Learning outcome

Component capacity and process RSS measure different things.

## Step-by-step worked calculation

A two-layer cache reserves six rows, eight FP32 channels, two projections per row. Bytes = 2 × 2 × 6 × 8 × 4 = **768 bytes**. If the cache retains only three rows, the active K/V payload would be 384 bytes if packed, but preallocated capacity can remain 768 bytes. The memory allocator, scratch arrays and model weights are outside both figures.

**Unit conventions.** Nanoseconds (ns), milliseconds (ms), bytes, MiB and token positions are not interchangeable. Unless otherwise stated, the displayed figures are illustrative computations rather than measured Umicom performance.

## Application to a native AI system

The calculation supports [LLM Lesson 287](../10-native-ai/287-distinguish-kv-allocation-from-peak-process-memory.md). Native C23 services can capture counters and elapsed values, but an estimated ratio cannot replace independent runtime evidence. The model's position policy, attention-head layout and numerical precision must be held fixed unless the exercise explicitly changes them.

## Exercise

**Question:** Four layers, ten positions, sixteen channels, FP32 K and V: how many payload bytes?

<details><summary>Reveal the complete answer</summary>

2 × 4 × 10 × 16 × 4 = 5,120 bytes.

</details>

## Further exploration

Try a second workload with different context length or concurrency. Identify every assumption that changes. Explain whether the result is a memory-capacity estimate, a timing observation or a mathematical identity.

## Continue learning

[Mathematics study route](../../courses/maths-for-ai/inference-benchmark-mathematics.html) · [LLM learning path](../../courses/llm-from-scratch/inference-benchmark-learning-path.html)

*Service to Many Leads to Greatness.*
