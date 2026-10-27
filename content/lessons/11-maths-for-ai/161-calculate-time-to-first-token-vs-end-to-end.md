# Mathematics for AI — Unit 161: Calculate TTFT and end-to-end latency

**Bits to Banking · Umicom Foundation**  
**Author:** Sammy Hegab · **Prerequisite:** Basic arithmetic and preceding course units.

## Learning outcome

TTFT identifies first output availability, while full generation covers every token.

## Step-by-step worked calculation

If queue = 3 ms, prefill = 9 ms and initial sampling = 2 ms, then TTFT = 3 + 9 + 2 = **14 ms**. With four later tokens at 5 ms each, total latency = 14 + 4 × 5 = **34 ms**. Average full-response time per emitted token for five emitted tokens is 34/5 = **6.8 ms/token**, which does not equal the post-first-token TPOT of 5 ms/token.

**Unit conventions.** Nanoseconds (ns), milliseconds (ms), bytes, MiB and token positions are not interchangeable. Unless otherwise stated, the displayed figures are illustrative computations rather than measured Umicom performance.

## Application to a native AI system

The calculation supports [LLM Lesson 281](../10-native-ai/281-separate-prompt-prefill-from-token-decoding.md). Native C23 services can capture counters and elapsed values, but an estimated ratio cannot replace independent runtime evidence. The model's position policy, attention-head layout and numerical precision must be held fixed unless the exercise explicitly changes them.

## Exercise

**Question:** A 2-token answer has TTFT 30 ms and second-token delay 12 ms. Find end-to-end time.

<details><summary>Reveal the complete answer</summary>

30 + 12 = 42 ms.

</details>

## Further exploration

Try a second workload with different context length or concurrency. Identify every assumption that changes. Explain whether the result is a memory-capacity estimate, a timing observation or a mathematical identity.

## Continue learning

[Mathematics study route](../../courses/maths-for-ai/inference-benchmark-mathematics.html) · [LLM learning path](../../courses/llm-from-scratch/inference-benchmark-learning-path.html)

*Service to Many Leads to Greatness.*
