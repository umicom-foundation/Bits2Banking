# Mathematics for AI — Unit 164: Compare alternating A/B run orders

**Bits to Banking · Umicom Foundation**  
**Author:** Sammy Hegab · **Prerequisite:** Basic arithmetic and preceding course units.

## Learning outcome

Counterbalancing makes order effects observable.

## Step-by-step worked calculation

Pairs A→B and B→A yield A times [12, 9] ms and B times [10, 11] ms. The medians for two observations are A = (12+9)/2 = **10.5 ms**, B = (10+11)/2 = **10.5 ms**. The results are tied even though B wins the first pair and A wins the second. Run order affects the appearance of individual results.

**Unit conventions.** Nanoseconds (ns), milliseconds (ms), bytes, MiB and token positions are not interchangeable. Unless otherwise stated, the displayed figures are illustrative computations rather than measured Umicom performance.

## Application to a native AI system

The calculation supports [LLM Lesson 284](../10-native-ai/284-counterbalance-order-and-run-warmups.md). Native C23 services can capture counters and elapsed values, but an estimated ratio cannot replace independent runtime evidence. The model's position policy, attention-head layout and numerical precision must be held fixed unless the exercise explicitly changes them.

## Exercise

**Question:** Why should a benchmark record which implementation ran first?

<details><summary>Reveal the complete answer</summary>

Caches, frequency scaling and thermal state may favour or penalise the first implementation.

</details>

## Further exploration

Try a second workload with different context length or concurrency. Identify every assumption that changes. Explain whether the result is a memory-capacity estimate, a timing observation or a mathematical identity.

## Continue learning

[Mathematics study route](../../courses/maths-for-ai/inference-benchmark-mathematics.html) · [LLM learning path](../../courses/llm-from-scratch/inference-benchmark-learning-path.html)

*Service to Many Leads to Greatness.*
