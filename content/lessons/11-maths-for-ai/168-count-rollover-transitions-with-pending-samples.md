# Mathematics for AI — Unit 168: Count rollover transitions with pending samples

**Bits to Banking · Umicom Foundation**  
**Author:** Sammy Hegab · **Prerequisite:** Basic arithmetic and preceding course units.

## Learning outcome

Generating a token and appending it to the context are separate steps.

## Step-by-step worked calculation

Context length 5, initial prompt length 3, generated outputs 7. First output uses existing prompt logits and causes no append. There are 6 later transitions. Two grow the prefix 3→4→5; four require full-window rollovers. With three layers, each rebuild performs 5×3 = 15 token-layer rows, for **60 rebuild rows** across those four transitions.

**Unit conventions.** Nanoseconds (ns), milliseconds (ms), bytes, MiB and token positions are not interchangeable. Unless otherwise stated, the displayed figures are illustrative computations rather than measured Umicom performance.

## Application to a native AI system

The calculation supports [LLM Lesson 288](../10-native-ai/288-benchmark-growing-prefix-and-window-rollover-separately.md). Native C23 services can capture counters and elapsed values, but an estimated ratio cannot replace independent runtime evidence. The model's position policy, attention-head layout and numerical precision must be held fixed unless the exercise explicitly changes them.

## Exercise

**Question:** Context=4, prompt=4, generated outputs=5: count rollovers.

<details><summary>Reveal the complete answer</summary>

Four rollovers: every post-first-token transition occurs with a full window.

</details>

## Further exploration

Try a second workload with different context length or concurrency. Identify every assumption that changes. Explain whether the result is a memory-capacity estimate, a timing observation or a mathematical identity.

## Continue learning

[Mathematics study route](../../courses/maths-for-ai/inference-benchmark-mathematics.html) · [LLM learning path](../../courses/llm-from-scratch/inference-benchmark-learning-path.html)

*Service to Many Leads to Greatness.*
