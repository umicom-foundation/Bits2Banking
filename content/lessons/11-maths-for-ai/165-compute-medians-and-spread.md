# Mathematics for AI — Unit 165: Compute medians and simple spread

**Bits to Banking · Umicom Foundation**  
**Author:** Sammy Hegab · **Prerequisite:** Basic arithmetic and preceding course units.

## Learning outcome

A summary must preserve variability rather than selecting the single best time.

## Step-by-step worked calculation

Observed milliseconds [7, 8, 8, 10, 18] are already sorted. The median is **8 ms** and the range is 18−7 = **11 ms**. The mean is 51/5 = 10.2 ms. The high outlier changes the mean but not the median; neither measure alone proves a speedup. Show the raw data.

**Unit conventions.** Nanoseconds (ns), milliseconds (ms), bytes, MiB and token positions are not interchangeable. Unless otherwise stated, the displayed figures are illustrative computations rather than measured Umicom performance.

## Application to a native AI system

The calculation supports [LLM Lesson 285](../10-native-ai/285-report-medians-spread-and-performance-uncertainty.md). Native C23 services can capture counters and elapsed values, but an estimated ratio cannot replace independent runtime evidence. The model's position policy, attention-head layout and numerical precision must be held fixed unless the exercise explicitly changes them.

## Exercise

**Question:** Find the median of [2, 3, 4, 9] ms.

<details><summary>Reveal the complete answer</summary>

(3+4)/2 = 3.5 ms.

</details>

## Further exploration

Try a second workload with different context length or concurrency. Identify every assumption that changes. Explain whether the result is a memory-capacity estimate, a timing observation or a mathematical identity.

## Continue learning

[Mathematics study route](../../courses/maths-for-ai/inference-benchmark-mathematics.html) · [LLM learning path](../../courses/llm-from-scratch/inference-benchmark-learning-path.html)

*Service to Many Leads to Greatness.*
