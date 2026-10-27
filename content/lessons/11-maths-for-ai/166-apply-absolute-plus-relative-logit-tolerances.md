# Mathematics for AI — Unit 166: Apply absolute plus relative logit tolerances

**Bits to Banking · Umicom Foundation**  
**Author:** Sammy Hegab · **Prerequisite:** Basic arithmetic and preceding course units.

## Learning outcome

Floating-point parity needs a transparent, predeclared inequality.

## Step-by-step worked calculation

Use |a−b| ≤ atol + rtol × max(|a|,|b|). For a=−3.0, b=−3.0002, atol=0.0001 and rtol=0.0001, bound = 0.0001 + 0.0001 × 3.0002 = **0.00040002**. Error 0.0002 passes. NaN does not pass, even if a naïve comparison expression would return false in a misleading way.

**Unit conventions.** Nanoseconds (ns), milliseconds (ms), bytes, MiB and token positions are not interchangeable. Unless otherwise stated, the displayed figures are illustrative computations rather than measured Umicom performance.

## Application to a native AI system

The calculation supports [LLM Lesson 286](../10-native-ai/286-qualify-full-logit-and-generated-token-parity.md). Native C23 services can capture counters and elapsed values, but an estimated ratio cannot replace independent runtime evidence. The model's position policy, attention-head layout and numerical precision must be held fixed unless the exercise explicitly changes them.

## Exercise

**Question:** For atol=0.0001, rtol=0 and an error of 0.00015, does it pass?

<details><summary>Reveal the complete answer</summary>

No. The allowed error is 0.0001.

</details>

## Further exploration

Try a second workload with different context length or concurrency. Identify every assumption that changes. Explain whether the result is a memory-capacity estimate, a timing observation or a mathematical identity.

## Continue learning

[Mathematics study route](../../courses/maths-for-ai/inference-benchmark-mathematics.html) · [LLM learning path](../../courses/llm-from-scratch/inference-benchmark-learning-path.html)

*Service to Many Leads to Greatness.*
