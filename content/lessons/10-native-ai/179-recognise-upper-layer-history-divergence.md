# Lesson 179 — Recognise Upper Layer History Divergence

**Bits to Banking · Umicom Foundation**  
**Author:** Sammy Hegab  
**Native platform:** Umicom Framework, C23

> **Learning objective:** Explain why a rotary position scheme alone cannot certify a multi-layer cache.

## 1. The engineering question

Imagine two attention layers. Layer one produces a representation for token B that attended to earlier A. Layer two builds B’s key and value from that representation. Later, the visible rolling window contains only `[B,C,D]` and A is gone.

The important distinction is between the behaviour of the existing, real multi-layer decoder and a proposal for a future more efficient runtime. We must describe what the software actually calculates before counting possible savings. A coherent set of model, data, position-policy and sampling assumptions is part of the experiment, not an optional implementation detail.

## 2. Reason through a worked example

The old layer-two key for B may retain information about A, whereas a fresh recomputation using only `[B,C,D]` would not. Both are possible deliberate semantics, but they are different. A cache design must declare whether it preserves full historical state or matches a truncated-window reference.

When a calculation uses a fixed number of positions, label those positions from zero. When it uses a model score, distinguish a score (logit) from a probability after softmax. In particular, an identical selected token does not establish that two output distributions agree. Keep the exact input tensor shape, the measured workload and the declared comparison tolerance alongside each claim.

## 3. Use the existing Framework service

Keep model identity, context policy, eviction policy and layer-history semantics separately identifiable. Qualify each with independent full-precision logit tests before reusing buffers across the eviction boundary.

The implementation belongs in `Umicom-Applications/framework/include/umicom/ai/training/` and `src/ai/training/`; the educational manuscript under Bits2Banking contains no separate model runtime. Read the public header before changing a call signature. Preserve the model and all caller-owned output buffers on rejected operations.

## 4. What evidence would establish correctness?

An appropriate acceptance test must execute the actual C23 library, reject malformed inputs, check unchanged outputs on rejection and verify that model parameters have not been silently updated by inference. Where the test compares predicted logits, inspect the entire relevant vocabulary row. Where it compares a model checkpoint, remember that SHA-256 identifies bytes but does not authenticate the person who supplied them.

For a future cache optimisation, a meaningful result also needs correctly separated reports of token-layer work, retained memory, CPU time and elapsed time. Do not treat a synthetic fixture or an estimate as a measured speedup.

## 5. Practice and worked answer

**Question:** Does replacing learned absolute positions with RoPE automatically make every upper-layer historical key identical to a fresh truncated-window key?

<details><summary>Reveal the worked answer</summary>

No. RoPE describes the positional transform; upper-layer inputs can still depend on earlier attention history. The two computations need not agree.

</details>

## 6. Continue learning

Study [the mathematical companion](../11-maths-for-ai/80-causal-suffix-invariance.md) and the [complete native LLM HTML catalogue](../../courses/llm-from-scratch/advanced-lessons.html). The [HTML form of this lesson](../../courses/llm-from-scratch/lessons/179-recognise-upper-layer-history-divergence.html) is an additional reading format, not a second implementation.

*Service to Many Leads to Greatness.*
