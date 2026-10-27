# Lesson 271 — Preserve failure-atomic cache proposals

**Bits to Banking · Umicom Foundation**  
**Author:** Sammy Hegab  
**Course:** Building an LLM from Scratch · Native C23

**Learning objective:** Explain how cached generation avoids partially updating live state.

## 1. Concept and motivation

An incremental proposal reads retained K/V and produces new K/V and logits into caller-owned temporary buffers. The proposal must not append rows, move the sampling cursor or alter the random-number generator. Sampling and cache publication belong to a separate session operation. This separation is crucial when an allocation fails or a model is modified between steps.

## 2. Worked example

Imagine a request with enough room for K but a short V output buffer. A partial append would leave key row 4 present without its matching value. The correct result rejects the request with both arrays and the store unchanged. Similarly, a rejection during a later layer must not publish K/V rows from earlier layers.

## 3. Native Framework implementation and evidence

Validate sizes, aliases, checkpoint SHA-256 identity and the tape’s current node count before calculating. Stage outputs, perform all operations, roll back temporary graph nodes, verify identity again and publish the candidate only after success. Do not replace the store’s append transaction.

## 4. Mathematical companion

Read [Mathematics Unit 153 — Calculate operator scratch bytes](../11-maths-for-ai/153-calculate-operator-scratch-bytes.md). Check each numerical assumption against the example above before running a program.

## 5. Exercise

**Question:** Should a failed step advance the sampler seed to make retrying easier?

<details>
<summary>Reveal the worked answer</summary>

No. Rejected calls preserve inference state. Advancing the random stream would make a retry semantically different and break deterministic replay.

</details>

## 6. Interpretation

Memory ownership and failure atomicity are as important as numerical accuracy.

## Continue learning

[270 — Compare multi-layer projections and every vocabulary logit](270-compare-multilayer-projections-and-all-logits.md) · [272 — Rebuild the cache at learned-absolute-position rollover](272-rebuild-cache-on-absolute-position-rollover.md) · [Browser learning path](../../courses/llm-from-scratch/integrated-attention-learning-path.html)
