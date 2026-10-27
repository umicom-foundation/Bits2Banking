# Mathematics for AI — Unit 170: Separate system throughput from user latency

**Bits to Banking · Umicom Foundation**  
**Author:** Sammy Hegab · **Prerequisite:** Basic arithmetic and preceding course units.

## Learning outcome

Aggregate output rate and individual wait time cannot be substituted.

## Step-by-step worked calculation

A system emits 500 tokens in 2 seconds across ten requests: throughput is **250 tokens/s**. One user may nevertheless have a TTFT of 600 ms because the request waited in a queue. Changing the scheduler can increase throughput while also raising the slowest-user latency. Report both per-user and aggregate measurements.

**Unit conventions.** Nanoseconds (ns), milliseconds (ms), bytes, MiB and token positions are not interchangeable. Unless otherwise stated, the displayed figures are illustrative computations rather than measured Umicom performance.

## Application to a native AI system

The calculation supports [LLM Lesson 294](../10-native-ai/294-measure-throughput-latency-and-resource-pressure.md). Native C23 services can capture counters and elapsed values, but an estimated ratio cannot replace independent runtime evidence. The model's position policy, attention-head layout and numerical precision must be held fixed unless the exercise explicitly changes them.

## Exercise

**Question:** A batch emits 720 tokens over 3 s. Calculate aggregate rate.

<details><summary>Reveal the complete answer</summary>

720/3 = 240 tokens/s.

</details>

## Further exploration

Try a second workload with different context length or concurrency. Identify every assumption that changes. Explain whether the result is a memory-capacity estimate, a timing observation or a mathematical identity.

## Continue learning

[Mathematics study route](../../courses/maths-for-ai/inference-benchmark-mathematics.html) · [LLM learning path](../../courses/llm-from-scratch/inference-benchmark-learning-path.html)

*Service to Many Leads to Greatness.*
