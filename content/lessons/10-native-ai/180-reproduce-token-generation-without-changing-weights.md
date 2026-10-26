# Lesson 180 — Reproduce Token Generation Without Changing Weights

**Bits to Banking · Umicom Foundation**  
**Author:** Sammy Hegab  
**Native platform:** Umicom Framework, C23

> **Learning objective:** Design a deterministic experiment that can be repeated safely.

## 1. The engineering question

A reproducible run pins checkpoint bytes, a complete prompt, temperature, top-K, top-p, seed, generated count and inference context policy. Changing any of those inputs can change the generated sequence without indicating a software defect.

The important distinction is between the behaviour of the existing, real multi-layer decoder and a proposal for a future more efficient runtime. We must describe what the software actually calculates before counting possible savings. A coherent set of model, data, position-policy and sampling assumptions is part of the experiment, not an optional implementation detail.

## 2. Reason through a worked example

A session uses its own random state and copies each nucleus policy. The original decoder is borrowed read-only. Run generation twice after resetting to the same pinned state; compare all token IDs in order. Run inference only while no other thread is training or destroying the decoder.

When a calculation uses a fixed number of positions, label those positions from zero. When it uses a model score, distinguish a score (logit) from a probability after softmax. In particular, an identical selected token does not establish that two output distributions agree. Keep the exact input tensor shape, the measured workload and the declared comparison tolerance alongside each claim.

## 3. Use the existing Framework service

The one-shot prefix generator and pull-based session are two views of the same Framework implementation. Their identity and sample parity should be accepted together with checkpoint immutability.

The implementation belongs in `Umicom-Applications/framework/include/umicom/ai/training/` and `src/ai/training/`; the educational manuscript under Bits2Banking contains no separate model runtime. Read the public header before changing a call signature. Preserve the model and all caller-owned output buffers on rejected operations.

## 4. What evidence would establish correctness?

An appropriate acceptance test must execute the actual C23 library, reject malformed inputs, check unchanged outputs on rejection and verify that model parameters have not been silently updated by inference. Where the test compares predicted logits, inspect the entire relevant vocabulary row. Where it compares a model checkpoint, remember that SHA-256 identifies bytes but does not authenticate the person who supplied them.

For a future cache optimisation, a meaningful result also needs correctly separated reports of token-layer work, retained memory, CPU time and elapsed time. Do not treat a synthetic fixture or an estimate as a measured speedup.

## 5. Practice and worked answer

**Question:** Two runs use the same seed but one uses BOS-left padding. Must the generated sequences match the unpadded prefix run?

<details><summary>Reveal the worked answer</summary>

No. The first prompt token occupies a different learned position, so the model logits need not match even before sampling.

</details>

## 6. Continue learning

Study [the mathematical companion](../11-maths-for-ai/85-read-content-hash-identities.md) and the [complete native LLM HTML catalogue](../../courses/llm-from-scratch/advanced-lessons.html). The [HTML form of this lesson](../../courses/llm-from-scratch/lessons/180-reproduce-token-generation-without-changing-weights.html) is an additional reading format, not a second implementation.

*Service to Many Leads to Greatness.*
