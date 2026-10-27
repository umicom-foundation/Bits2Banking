# Mathematics for AI — Unit 163: Calculate paired runtime ratios

**Bits to Banking · Umicom Foundation**  
**Author:** Sammy Hegab · **Prerequisite:** Basic arithmetic and preceding course units.

## Learning outcome

A speed ratio has an explicit baseline and must not mix output lengths.

## Step-by-step worked calculation

Reference 18 ms, candidate 15 ms on identical outputs: speed ratio = 18/15 = **1.2×**. Percentage reduction in elapsed runtime = (18−15)/18 × 100 = **16.67%**. These are two distinct descriptions of the same measured pair; they are not a guarantee for any other prompt or environment.

**Unit conventions.** Nanoseconds (ns), milliseconds (ms), bytes, MiB and token positions are not interchangeable. Unless otherwise stated, the displayed figures are illustrative computations rather than measured Umicom performance.

## Application to a native AI system

The calculation supports [LLM Lesson 283](../10-native-ai/283-design-paired-canonical-versus-cached-experiments.md). Native C23 services can capture counters and elapsed values, but an estimated ratio cannot replace independent runtime evidence. The model's position policy, attention-head layout and numerical precision must be held fixed unless the exercise explicitly changes them.

## Exercise

**Question:** Reference 20 ms, candidate 25 ms. What is the candidate speed ratio?

<details><summary>Reveal the complete answer</summary>

20/25 = 0.8× relative to reference: the candidate is slower for this pair.

</details>

## Further exploration

Try a second workload with different context length or concurrency. Identify every assumption that changes. Explain whether the result is a memory-capacity estimate, a timing observation or a mathematical identity.

## Continue learning

[Mathematics study route](../../courses/maths-for-ai/inference-benchmark-mathematics.html) · [LLM learning path](../../courses/llm-from-scratch/inference-benchmark-learning-path.html)

*Service to Many Leads to Greatness.*
