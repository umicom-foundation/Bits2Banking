# Lesson 268 — Derive last-row attention parity with the reference

**Bits to Banking · Umicom Foundation**  
**Author:** Sammy Hegab  
**Course:** Building an LLM from Scratch · Native C23

**Learning objective:** Compare the stable-softmax computation of a single query with the canonical final row.

## 1. Concept and motivation

For a head of width `d`, each visible key receives score `s_i = (q·k_i)/sqrt(d)`. Stable softmax computes `exp(s_i-m)/Σ_j exp(s_j-m)` where `m` is the largest score. In the canonical tape, those probabilities are stored as FP32 before they weight FP32 value channels. Matching this rounding and the order of accumulation avoids introducing an unnecessary source of drift.

## 2. Worked example

Let `q=(1,0)`, `k0=(1,0)`, `k1=(0,1)` and `d=2`. Scores are `[1/sqrt(2),0]`. The first attention weight is approximately `0.66976`. For values `v0=(2,4)` and `v1=(6,8)`, the output is approximately `(3.321,5.321)`. Use the actual rounded probability for an exact FP32 comparison.

## 3. Native Framework implementation and evidence

An independent parity test should create Q/K/V tensors in the original tape, run full multi-head causal attention, extract the last row and compare every output channel with `UmiAiTrainingSingleQueryAttentionForward`. Use multiple head widths and nonzero, signed inputs.

## 4. Mathematical companion

Read [Mathematics Unit 150 — Calculate final-row attention weights](../11-maths-for-ai/150-calculate-final-row-attention-weights.md). Check each numerical assumption against the example above before running a program.

## 5. Exercise

**Question:** Why is comparing only the maximum attention weight insufficient?

<details>
<summary>Reveal the worked answer</summary>

Many different probability distributions share the same argmax. Every output channel must be compared because small probability differences may change the weighted sum.

</details>

## 6. Interpretation

Stable-softmax parity still permits architecture- and compiler-dependent floating-point differences.

## Continue learning

[267 — Replace placeholder query rows without changing the model](267-replace-placeholder-query-rows.md) · [269 — Record the actual attention-query work](269-record-real-attention-query-work.md) · [Browser learning path](../../courses/llm-from-scratch/integrated-attention-learning-path.html)
