# Lesson 276 — Build a multi-axis integration-test matrix

**Bits to Banking · Umicom Foundation**  
**Author:** Sammy Hegab  
**Course:** Building an LLM from Scratch · Native C23

**Learning objective:** Organise tests that exercise both single-query arithmetic and the entire decoder.

## 1. Concept and motivation

One clean arithmetic fixture is insufficient for a stateful Transformer. A useful qualification matrix crosses head counts, layer counts, prompt lengths, cache boundaries, sampler policies and model update states. Each test has its own oracle: canonical attention for one-row arithmetic, canonical projection traces for K/V and logits, and canonical generation for sampled sequences.

## 2. Worked example

For layer counts `[1,2,3]`, prompts `[1,3,6]` in a six-token context and policies `[greedy, top-p]`, there are `3 × 3 × 2 = 18` base combinations before varying seeds or error conditions. At least one generation sequence should cross the first and repeated rollover in each model family.

## 3. Native Framework implementation and evidence

Maintain strict C23 compiler diagnostics and sanitizers. Test rejection with short buffers, non-finite inputs and stale identities. Keep a separate Release timing experiment so correctness decisions cannot depend on whichever implementation is faster.

## 4. Mathematical companion

Read [Mathematics Unit 160 — Construct an integrated evidence matrix](../11-maths-for-ai/160-construct-the-integrated-evidence-matrix.md). Check each numerical assumption against the example above before running a program.

## 5. Exercise

**Question:** Which regression is most likely to miss the rollover defect?

<details>
<summary>Reveal the worked answer</summary>

A short prompt test that stops generation before the first context eviction; all surviving positions were unchanged in that region.

</details>

## 6. Interpretation

A registration count alone does not mean tests executed or passed.

## Continue learning

[275 — Set finite-precision acceptance thresholds](275-set-finite-precision-acceptance-thresholds.md) · [277 — Measure CPU time and memory costs of a single query](277-measure-cpu-and-memory-costs-of-single-query.md) · [Browser learning path](../../courses/llm-from-scratch/integrated-attention-learning-path.html)
