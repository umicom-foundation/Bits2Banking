# Lesson 176 — Rebuild After Learned Position Rollover

**Bits to Banking · Umicom Foundation**  
**Author:** Sammy Hegab  
**Native platform:** Umicom Framework, C23

> **Learning objective:** Identify the exact boundary where old key/value information becomes stale.

## 1. The engineering question

A learned-absolute decoder with context `[A,B,C,D]` receives a new token E. Its new full context is `[B,C,D,E]`. B moves from learned position 1 to position 0, and every surviving token uses a different position embedding.

The important distinction is between the behaviour of the existing, real multi-layer decoder and a proposal for a future more efficient runtime. We must describe what the software actually calculates before counting possible savings. A coherent set of model, data, position-policy and sampling assumptions is part of the experiment, not an optional implementation detail.

## 2. Reason through a worked example

A key/value tensor computed for B at position 1 cannot generally be reused as B at position 0. In a multi-layer model, later-layer hidden states may also depend on the evicted A. Merely rotating keys or changing array indices does not solve this history dependence.

When a calculation uses a fixed number of positions, label those positions from zero. When it uses a model score, distinguish a score (logit) from a probability after softmax. In particular, an identical selected token does not establish that two output distributions agree. Keep the exact input tensor shape, the measured workload and the declared comparison tolerance alongside each claim.

## 3. Use the existing Framework service

The new reference prefix session runs the full canonical stacked decoder at every step. The earlier `StackedPrefixCachePlanBuild` treats post-eviction full rebuilds as a required condition, not an implemented optimisation.

The implementation belongs in `Umicom-Applications/framework/include/umicom/ai/training/` and `src/ai/training/`; the educational manuscript under Bits2Banking contains no separate model runtime. Read the public header before changing a call signature. Preserve the model and all caller-owned output buffers on rejected operations.

## 4. What evidence would establish correctness?

An appropriate acceptance test must execute the actual C23 library, reject malformed inputs, check unchanged outputs on rejection and verify that model parameters have not been silently updated by inference. Where the test compares predicted logits, inspect the entire relevant vocabulary row. Where it compares a model checkpoint, remember that SHA-256 identifies bytes but does not authenticate the person who supplied them.

For a future cache optimisation, a meaningful result also needs correctly separated reports of token-layer work, retained memory, CPU time and elapsed time. Do not treat a synthetic fixture or an estimate as a measured speedup.

## 5. Practice and worked answer

**Question:** After a four-token context becomes full, how many rows must an unchanged learned-absolute reference recompute for a new token?

<details><summary>Reveal the worked answer</summary>

Four token rows per Transformer layer are recalculated for the new full context. No pre-eviction key/value equivalence is assumed.

</details>

## 6. Continue learning

Study [the mathematical companion](../11-maths-for-ai/84-count-evictions-after-context-fills.md) and the [complete native LLM HTML catalogue](../../courses/llm-from-scratch/advanced-lessons.html). The [HTML form of this lesson](../../courses/llm-from-scratch/lessons/176-rebuild-after-learned-position-rollover.html) is an additional reading format, not a second implementation.

*Service to Many Leads to Greatness.*
