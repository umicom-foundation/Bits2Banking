# Mathematics for AI — Unit 171: Model shared-prefix reference counts

**Bits to Banking · Umicom Foundation**  
**Author:** Sammy Hegab · **Prerequisite:** Basic arithmetic and preceding course units.

## Learning outcome

Sharing immutable prefix pages requires explicit reference ownership.

## Step-by-step worked calculation

Two requests point to the same immutable cache page. Its reference count starts at 2. Cancelling request A decrements the count to **1**, so request B may still read it. Cancelling B decrements to **0**, at which point the owner can reclaim memory. A model update may invalidate the page semantically even when a reference still exists; reclamation and validity are separate states.

**Unit conventions.** Nanoseconds (ns), milliseconds (ms), bytes, MiB and token positions are not interchangeable. Unless otherwise stated, the displayed figures are illustrative computations rather than measured Umicom performance.

## Application to a native AI system

The calculation supports [LLM Lesson 291](../10-native-ai/291-reason-about-prefix-sharing-and-cache-ownership.md). Native C23 services can capture counters and elapsed values, but an estimated ratio cannot replace independent runtime evidence. The model's position policy, attention-head layout and numerical precision must be held fixed unless the exercise explicitly changes them.

## Exercise

**Question:** A cache block has three borrowers. One finishes. What is its new reference count?

<details><summary>Reveal the complete answer</summary>

2, assuming each borrower owns exactly one reference.

</details>

## Further exploration

Try a second workload with different context length or concurrency. Identify every assumption that changes. Explain whether the result is a memory-capacity estimate, a timing observation or a mathematical identity.

## Continue learning

[Mathematics study route](../../courses/maths-for-ai/inference-benchmark-mathematics.html) · [LLM learning path](../../courses/llm-from-scratch/inference-benchmark-learning-path.html)

*Service to Many Leads to Greatness.*
