# Lesson 270 — Compare multi-layer projections and every vocabulary logit

**Bits to Banking · Umicom Foundation**  
**Author:** Sammy Hegab  
**Course:** Building an LLM from Scratch · Native C23

**Learning objective:** Create an independent acceptance criterion stronger than matching sampled tokens.

## 1. Concept and motivation

A cached decoder can return the same greedy token while its logits are already drifting. A strong test observes real Q/K/V at each layer, compares each newest cached K/V row with the authoritative decoder trace, and compares the full vocabulary-logit vector. This avoids false confidence from accidental equality of the top-ranked token.

## 2. Worked example

In a vocabulary of 260 entries, two vectors can both select token 65 while differ at 259 other positions. Across three layers and four prefix appends, compare all `4 × 260 = 1,040` candidate logit values and each layer’s new K/V vectors, not four token IDs.

## 3. Native Framework implementation and evidence

Run `UmiAiTrainingStackedDecoderTraceProjections` on a future-padded canonical context. Pull the newest logit row and newest per-layer K/V rows from the trace. Check element-wise absolute error at a stated threshold. Only after all checks pass should a regression exercise `StackedKvStoreAppend`.

## 4. Mathematical companion

Read [Mathematics Unit 154 — Compute absolute-plus-relative error](../11-maths-for-ai/154-compute-absolute-plus-relative-error.md). Check each numerical assumption against the example above before running a program.

## 5. Exercise

**Question:** Why is comparing logits at the correct prefix position essential?

<details>
<summary>Reveal the worked answer</summary>

The canonical decoder produces one vocabulary row per context position. Comparing against a padded future position tests different input and positional embeddings.

</details>

## 6. Interpretation

K/V parity, logits parity, sampler parity and checkpoint identity are separate requirements.

## Continue learning

[269 — Record the actual attention-query work](269-record-real-attention-query-work.md) · [271 — Preserve failure-atomic cache proposals](271-preserve-atomic-cache-proposals.md) · [Browser learning path](../../courses/llm-from-scratch/integrated-attention-learning-path.html)
