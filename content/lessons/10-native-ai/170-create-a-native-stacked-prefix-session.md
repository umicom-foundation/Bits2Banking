# Lesson 170 — Create A Native Stacked Prefix Session

**Bits to Banking · Umicom Foundation**  
**Author:** Sammy Hegab  
**Native platform:** Umicom Framework, C23

> **Learning objective:** Create one Framework-owned generation session with explicit memory and identity ownership.

## 1. The engineering question

A model has context length 8, and the input prompt contains three reviewed token IDs. The new session copies the three IDs, the nucleus policy and seeded random state. It borrows the decoder but owns its retained-context array. The first prediction reads the logit row of the third prompt token, not the last future-padding row.

The important distinction is between the behaviour of the existing, real multi-layer decoder and a proposal for a future more efficient runtime. We must describe what the software actually calculates before counting possible savings. A coherent set of model, data, position-policy and sampling assumptions is part of the experiment, not an optional implementation detail.

## 2. Reason through a worked example

Create must reject an empty prefix, a prefix longer than the decoder context, invalid IDs and an invalid sampling policy. It must never silently truncate the initial prompt or overwrite a live session output pointer. Decoder training while the session remains alive is prohibited.

When a calculation uses a fixed number of positions, label those positions from zero. When it uses a model score, distinguish a score (logit) from a probability after softmax. In particular, an identical selected token does not establish that two output distributions agree. Keep the exact input tensor shape, the measured workload and the declared comparison tolerance alongside each claim.

## 3. Use the existing Framework service

Use `UmiAiTrainingStackedPrefixSessionCreate`, then call `Next`, optionally `Inspect`, and finally `Destroy`. No application implements another sampler or attention engine.

The implementation belongs in `Umicom-Applications/framework/include/umicom/ai/training/` and `src/ai/training/`; the educational manuscript under Bits2Banking contains no separate model runtime. Read the public header before changing a call signature. Preserve the model and all caller-owned output buffers on rejected operations.

## 4. What evidence would establish correctness?

An appropriate acceptance test must execute the actual C23 library, reject malformed inputs, check unchanged outputs on rejection and verify that model parameters have not been silently updated by inference. Where the test compares predicted logits, inspect the entire relevant vocabulary row. Where it compares a model checkpoint, remember that SHA-256 identifies bytes but does not authenticate the person who supplied them.

For a future cache optimisation, a meaningful result also needs correctly separated reports of token-layer work, retained memory, CPU time and elapsed time. Do not treat a synthetic fixture or an estimate as a measured speedup.

## 5. Practice and worked answer

**Question:** Why must a session be destroyed before its borrowed decoder?

<details><summary>Reveal the worked answer</summary>

The session borrows the decoder and verifies its live checkpoint. Destroying the decoder first would leave a dangling pointer, which a hash comparison cannot make safe.

</details>

## 6. Continue learning

Study [the mathematical companion](../11-maths-for-ai/81-pending-samples-and-append-counts.md) and the [complete native LLM HTML catalogue](../../courses/llm-from-scratch/advanced-lessons.html). The [HTML form of this lesson](../../courses/llm-from-scratch/lessons/170-create-a-native-stacked-prefix-session.html) is an additional reading format, not a second implementation.

*Service to Many Leads to Greatness.*
