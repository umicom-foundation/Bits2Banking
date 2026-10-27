# Lesson 266 — Distinguish forward inference from automatic differentiation

**Bits to Banking · Umicom Foundation**  
**Author:** Sammy Hegab  
**Course:** Building an LLM from Scratch · Native C23

**Learning objective:** Explain why a forward-only attention row can be used for sampling but not substituted into training.

## 1. Concept and motivation

The original training tape records an operation graph and the data needed to differentiate attention. Incremental sampling fixes the model parameters; it only needs the value of the latest attended row. A forward-only numerical operator can therefore reduce calculation and temporary storage in inference. However, treating its result as a leaf tensor disconnects the gradient path from Q/K/V, so it cannot replace the differentiable operator in training.

## 2. Worked example

Suppose the last attention output has four channels. A forward-only operator returns `[0.2, 0.7, -0.1, 0.4]`. Creating a nontrainable tape leaf with shape `[1,4]` allows the existing output projection and residual operators to proceed, but reverse-mode differentiation cannot infer how the original query or keys affected those four values.

## 3. Native Framework implementation and evidence

Use `UmiAiTrainingSingleQueryAttentionForward` only inside the incremental inference step. Leave `UmiAiTrainingMultiHeadCausalAttention` as the canonical training-time operator. In the tape, explicitly rewind the forward-only temporary nodes after the proposed logits and K/V rows have been copied out.

## 4. Mathematical companion

Read [Mathematics Unit 150 — Calculate final-row attention weights](../11-maths-for-ai/150-calculate-final-row-attention-weights.md). Check each numerical assumption against the example above before running a program.

## 5. Exercise

**Question:** Can a numerically matching forward-only attention result be silently substituted into a training graph?

<details>
<summary>Reveal the worked answer</summary>

No. Numeric forward parity does not provide the backward derivatives or attention probability lifetimes required by the training tape.

</details>

## 6. Interpretation

Forward equivalence and gradient equivalence are different acceptance properties.

## Continue learning

[265 — Trace one query through the stacked decoder](265-trace-a-single-query-through-the-decoder.md) · [267 — Replace placeholder query rows without changing the model](267-replace-placeholder-query-rows.md) · [Browser learning path](../../courses/llm-from-scratch/integrated-attention-learning-path.html)
