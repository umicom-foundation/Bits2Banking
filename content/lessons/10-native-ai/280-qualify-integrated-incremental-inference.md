# Lesson 280 — Qualify the integrated incremental decoder

**Bits to Banking · Umicom Foundation**  
**Author:** Sammy Hegab  
**Course:** Building an LLM from Scratch · Native C23

**Learning objective:** Combine arithmetic, model, state, and performance evidence into one reproducible qualification.

## 1. Concept and motivation

A credible integration result has several independent layers of evidence. The standalone operator must match the canonical last attention row; the stacked proposal must reproduce every K/V projection and vocabulary logit; the stateful session must match greedy and sampled reference generations across context rollover; failures and checkpoint updates must preserve state. Only after these checks should real Release timing be interpreted.

## 2. Worked example

For a three-layer, six-token model generating eight tokens from a one-token prompt, there are five prefix append steps and two canonical rollovers among seven state transitions. The query-row count is `3*(6+2*6+5)=69` versus `3*6*8=144` full-context reference token-layer rows. These are analytically verifiable counters, not benchmarked speedup factors.

## 3. Native Framework implementation and evidence

The canonical implementation remains authoritative at learned-position rollover; one-query forward attention is used only for unchanged positions. All calculations stay in Framework C23, and applications consume the established opaque sessions and status results.

## 4. Mathematical companion

Read [Mathematics Unit 160 — Construct an integrated evidence matrix](../11-maths-for-ai/160-construct-the-integrated-evidence-matrix.md). Check each numerical assumption against the example above before running a program.

## 5. Exercise

**Question:** Which statements follow from passing the integrated numerical tests but collecting no Release timings?

<details>
<summary>Reveal the worked answer</summary>

The tested model configurations and inputs met their numerical and state invariants. No claim about whole-model latency, throughput or hardware scalability follows without actual measurements.

</details>

## 6. Interpretation

Classify results separately as static compilation, isolated arithmetic, integrated decoder parity, sanitizer outcome and measured performance.

## Continue learning

[279 — Separate inference caching from RAG and fine-tuning](279-separate-kv-inference-from-rag-and-fine-tuning.md) · [Browser learning path](../../courses/llm-from-scratch/integrated-attention-learning-path.html)
