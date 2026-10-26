# Lesson 177 — Separate Measured Work From Theoretical Cache Work

**Bits to Banking · Umicom Foundation**  
**Author:** Sammy Hegab  
**Native platform:** Umicom Framework, C23

> **Learning objective:** Read observed inference counters alongside hypothetical cache planning.

## 1. The engineering question

For 3 layers, context 8, prompt length 3 and 12 samples, a full-context reference computes `3 × 8 × 12 = 288` token-layer rows. A conditional incremental plan assumes a 3-row prefill, five one-row appends and six full 8-row rebuilds: `(3 + 5 + 6 × 8) × 3 = 168`.

The important distinction is between the behaviour of the existing, real multi-layer decoder and a proposal for a future more efficient runtime. We must describe what the software actually calculates before counting possible savings. A coherent set of model, data, position-policy and sampling assumptions is part of the experiment, not an optional implementation detail.

## 2. Reason through a worked example

The difference of 120 rows is theoretical, contingent on implementing mathematically equivalent retained key/value semantics. The new prefix generator does not possess a KV cache. Its actual full-context counter remains 288, and its clock time is not inferred from the planner.

When a calculation uses a fixed number of positions, label those positions from zero. When it uses a model score, distinguish a score (logit) from a probability after softmax. In particular, an identical selected token does not establish that two output distributions agree. Keep the exact input tensor shape, the measured workload and the declared comparison tolerance alongside each claim.

## 3. Use the existing Framework service

Display `StackedPrefixSessionInspect` separately from `StackedPrefixCachePlanBuild`, with clear labels for **observed reference work** and **conditional candidate work**. Never put the latter into measured runtime counters.

The implementation belongs in `Umicom-Applications/framework/include/umicom/ai/training/` and `src/ai/training/`; the educational manuscript under Bits2Banking contains no separate model runtime. Read the public header before changing a call signature. Preserve the model and all caller-owned output buffers on rejected operations.

## 4. What evidence would establish correctness?

An appropriate acceptance test must execute the actual C23 library, reject malformed inputs, check unchanged outputs on rejection and verify that model parameters have not been silently updated by inference. Where the test compares predicted logits, inspect the entire relevant vocabulary row. Where it compares a model checkpoint, remember that SHA-256 identifies bytes but does not authenticate the person who supplied them.

For a future cache optimisation, a meaningful result also needs correctly separated reports of token-layer work, retained memory, CPU time and elapsed time. Do not treat a synthetic fixture or an estimate as a measured speedup.

## 5. Practice and worked answer

**Question:** Why is it incorrect to call 120 fewer planned rows a measured 41.7% faster generator?

<details><summary>Reveal the worked answer</summary>

The planned reduction is in one counted operation type. The implementation has not saved those rows, and row count is not elapsed time. Measure a real cache after numerical qualification.

</details>

## 6. Continue learning

Study [the mathematical companion](../11-maths-for-ai/83-compare-actual-and-planned-cache-work.md) and the [complete native LLM HTML catalogue](../../courses/llm-from-scratch/advanced-lessons.html). The [HTML form of this lesson](../../courses/llm-from-scratch/lessons/177-separate-measured-work-from-theoretical-cache-work.html) is an additional reading format, not a second implementation.

*Service to Many Leads to Greatness.*
