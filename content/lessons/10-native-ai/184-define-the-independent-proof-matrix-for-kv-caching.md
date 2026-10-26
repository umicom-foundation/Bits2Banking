# Lesson 184 — Define The Independent Proof Matrix For KV Caching

**Bits to Banking · Umicom Foundation**  
**Author:** Sammy Hegab  
**Native platform:** Umicom Framework, C23

> **Learning objective:** Specify the evidence required before releasing an optimised multi-layer cache.

## 1. The engineering question

A proposed cache must first satisfy a non-evicting growing-prefix oracle, compare complete vocabulary-logit vectors, match streamed and one-shot output IDs, preserve the model checkpoint and explicitly handle the first and repeated evictions. It must report memory allocated and actual computation separately from elapsed time.

The important distinction is between the behaviour of the existing, real multi-layer decoder and a proposal for a future more efficient runtime. We must describe what the software actually calculates before counting possible savings. A coherent set of model, data, position-policy and sampling assumptions is part of the experiment, not an optional implementation detail.

## 2. Reason through a worked example

The current prefix implementation establishes a deterministic reference context policy and a real model causality check. It intentionally performs full Transformer forwards. The work planner describes conditional savings only; neither component proves that an upper-layer historical cache is numerically equivalent.

When a calculation uses a fixed number of positions, label those positions from zero. When it uses a model score, distinguish a score (logit) from a probability after softmax. In particular, an identical selected token does not establish that two output distributions agree. Keep the exact input tensor shape, the measured workload and the declared comparison tolerance alongside each claim.

## 3. Use the existing Framework service

Run the independent real-model CTests `framework.ai.stacked_prefix.streaming`, `.causality`, and `.boundaries`. Keep the established stacked decoder and its checkpoint reader as the original mathematical authorities.

The implementation belongs in `Umicom-Applications/framework/include/umicom/ai/training/` and `src/ai/training/`; the educational manuscript under Bits2Banking contains no separate model runtime. Read the public header before changing a call signature. Preserve the model and all caller-owned output buffers on rejected operations.

## 4. What evidence would establish correctness?

An appropriate acceptance test must execute the actual C23 library, reject malformed inputs, check unchanged outputs on rejection and verify that model parameters have not been silently updated by inference. Where the test compares predicted logits, inspect the entire relevant vocabulary row. Where it compares a model checkpoint, remember that SHA-256 identifies bytes but does not authenticate the person who supplied them.

For a future cache optimisation, a meaningful result also needs correctly separated reports of token-layer work, retained memory, CPU time and elapsed time. Do not treat a synthetic fixture or an estimate as a measured speedup.

## 5. Practice and worked answer

**Question:** What should happen if an optimised cache matches every sampled token but differs from canonical logits by more than its declared tolerance?

<details><summary>Reveal the worked answer</summary>

Reject numerical qualification. The matching sampled token can conceal a changed probability distribution, so parity at the full-logit level is still required.

</details>

## 6. Continue learning

Study [the mathematical companion](../11-maths-for-ai/87-choose-a-numerical-parity-tolerance.md) and the [complete native LLM HTML catalogue](../../courses/llm-from-scratch/advanced-lessons.html). The [HTML form of this lesson](../../courses/llm-from-scratch/lessons/184-define-the-independent-proof-matrix-for-kv-caching.html) is an additional reading format, not a second implementation.

*Service to Many Leads to Greatness.*
