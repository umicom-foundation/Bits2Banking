# Lesson 269 — Record the actual attention-query work

**Bits to Banking · Umicom Foundation**  
**Author:** Sammy Hegab  
**Course:** Building an LLM from Scratch · Native C23

**Learning objective:** Interpret counters after the one-query path replaces historical multi-row work.

## 1. Concept and motivation

The query-row counter answers how many query vectors were processed by attention. It is not the number of keys scored, scalar dot-product operations, FP32 allocations or nanoseconds. For a prefix append, this count becomes the number of Transformer layers. Full-context prefill and context-rollover forwards still process the complete configured context because the canonical decoder remains authoritative at those boundaries.

## 2. Worked example

Take a context of six tokens, two layers, a prompt of length two and seven emitted tokens. The session performs one initial full forward (`12` token-layer rows), four prefix appends (`8` one-query rows), and two canonical rollovers (`24` rows). Total observed attention-query token-layer rows are `44`; the full-context reference strategy would process `7 × 6 × 2 = 84` rows.

## 3. Native Framework implementation and evidence

Use `UmiAiTrainingStackedKvStepReport.attentionQueryLayerRowsExecuted` for the incremental step and `UmiAiTrainingStackedKvIncrementalStats` for the session. Record full-context, incremental projection and attention-query counters independently.

## 4. Mathematical companion

Read [Mathematics Unit 152 — Compare full-query rows with one row](../11-maths-for-ai/152-compare-full-query-rows-with-one-row.md). Check each numerical assumption against the example above before running a program.

## 5. Exercise

**Question:** Does `44 / 84` imply the optimised model is 1.91 times faster?

<details>
<summary>Reveal the worked answer</summary>

No. The two counts describe only attention query rows. Execution also pays for K/V memory reads, embeddings, other layers, sampling, allocations and full-context rollover.

</details>

## 6. Interpretation

An operation count cannot substitute for measured wall-clock time.

## Continue learning

[268 — Derive last-row attention parity with the reference](268-show-last-row-attention-parity.md) · [270 — Compare multi-layer projections and every vocabulary logit](270-compare-multilayer-projections-and-all-logits.md) · [Browser learning path](../../courses/llm-from-scratch/integrated-attention-learning-path.html)
