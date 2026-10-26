# Lesson 173 — Verify Model Identity Before And After Pulls

**Bits to Banking · Umicom Foundation**  
**Author:** Sammy Hegab  
**Native platform:** Umicom Framework, C23

> **Learning objective:** Explain why checkpoint integrity is an execution precondition.

## 1. The engineering question

The session captures a SHA-256 digest of the canonical stacked decoder checkpoint during creation. Before generating each token it verifies that digest against the borrowed decoder. It verifies again after the canonical decoder and sampler return, before updating the caller’s token.

The important distinction is between the behaviour of the existing, real multi-layer decoder and a proposal for a future more efficient runtime. We must describe what the software actually calculates before counting possible savings. A coherent set of model, data, position-policy and sampling assumptions is part of the experiment, not an optional implementation detail.

## 2. Reason through a worked example

A matching digest detects changed checkpoint bytes, not the authenticity of a publisher. If model training changes any weight while a session is active, continuing with the old context and RNG would mix model states. Applications must serialise model access and refuse stale sessions.

When a calculation uses a fixed number of positions, label those positions from zero. When it uses a model score, distinguish a score (logit) from a probability after softmax. In particular, an identical selected token does not establish that two output distributions agree. Keep the exact input tensor shape, the measured workload and the declared comparison tolerance alongside each claim.

## 3. Use the existing Framework service

`UmiAiTrainingStackedModelIdentityCapture` and `Verify` remain the identity authorities. The prefix session does not invent another hash function or alter existing checkpoint formats.

The implementation belongs in `Umicom-Applications/framework/include/umicom/ai/training/` and `src/ai/training/`; the educational manuscript under Bits2Banking contains no separate model runtime. Read the public header before changing a call signature. Preserve the model and all caller-owned output buffers on rejected operations.

## 4. What evidence would establish correctness?

An appropriate acceptance test must execute the actual C23 library, reject malformed inputs, check unchanged outputs on rejection and verify that model parameters have not been silently updated by inference. Where the test compares predicted logits, inspect the entire relevant vocabulary row. Where it compares a model checkpoint, remember that SHA-256 identifies bytes but does not authenticate the person who supplied them.

For a future cache optimisation, a meaningful result also needs correctly separated reports of token-layer work, retained memory, CPU time and elapsed time. Do not treat a synthetic fixture or an estimate as a measured speedup.

## 5. Practice and worked answer

**Question:** Why is a checkpoint SHA-256 not enough to accept a model downloaded from an unknown source?

<details><summary>Reveal the worked answer</summary>

An untrusted source can distribute a malicious model together with a matching unkeyed SHA-256. Publisher authentication and training-data approval require separate controls.

</details>

## 6. Continue learning

Study [the mathematical companion](../11-maths-for-ai/85-read-content-hash-identities.md) and the [complete native LLM HTML catalogue](../../courses/llm-from-scratch/advanced-lessons.html). The [HTML form of this lesson](../../courses/llm-from-scratch/lessons/173-verify-model-identity-before-and-after-pulls.html) is an additional reading format, not a second implementation.

*Service to Many Leads to Greatness.*
