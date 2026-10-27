# Mathematics for AI — Unit 172: Compare MHA and GQA cache capacity

**Bits to Banking · Umicom Foundation**  
**Author:** Sammy Hegab · **Prerequisite:** Basic arithmetic and preceding course units.

## Learning outcome

Grouped-query attention changes K/V head count rather than merely query count.

## Step-by-step worked calculation

For 12 layers, 2,048 tokens, head width 64, two bytes per scalar, and K/V projections, four KV heads need 2 × 12 × 2048 × 4 × 64 × 2 = **25,165,824 bytes (24 MiB)**. Sixteen KV heads need four times as much: **96 MiB**. Model weights, positional metadata and dequantisation buffers are excluded.

**Unit conventions.** Nanoseconds (ns), milliseconds (ms), bytes, MiB and token positions are not interchangeable. Unless otherwise stated, the displayed figures are illustrative computations rather than measured Umicom performance.

## Application to a native AI system

The calculation supports [LLM Lesson 292](../10-native-ai/292-budget-multihead-versus-grouped-query-kv-memory.md). Native C23 services can capture counters and elapsed values, but an estimated ratio cannot replace independent runtime evidence. The model's position policy, attention-head layout and numerical precision must be held fixed unless the exercise explicitly changes them.

## Exercise

**Question:** With fixed dimensions and precision, how does doubling KV-head count change KV payload?

<details><summary>Reveal the complete answer</summary>

It doubles the payload.

</details>

## Further exploration

Try a second workload with different context length or concurrency. Identify every assumption that changes. Explain whether the result is a memory-capacity estimate, a timing observation or a mathematical identity.

## Continue learning

[Mathematics study route](../../courses/maths-for-ai/inference-benchmark-mathematics.html) · [LLM learning path](../../courses/llm-from-scratch/inference-benchmark-learning-path.html)

*Service to Many Leads to Greatness.*
