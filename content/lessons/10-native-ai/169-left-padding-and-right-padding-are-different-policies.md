# Lesson 169 — Left Padding And Right Padding Are Different Policies

**Bits to Banking · Umicom Foundation**  
**Author:** Sammy Hegab  
**Native platform:** Umicom Framework, C23

> **Learning objective:** Distinguish two valid prompt conventions without treating them as interchangeable.

## 1. The engineering question

A four-token decoder receives the byte tokens A and B. The historical policy evaluates `[BOS, BOS, A, B]` and samples logits at row 3. An unpadded-prefix policy evaluates `[A, B, BOS, BOS]` and samples logits at row 1. Both use four token rows, but A and B occupy different learned absolute positions.

The important distinction is between the behaviour of the existing, real multi-layer decoder and a proposal for a future more efficient runtime. We must describe what the software actually calculates before counting possible savings. A coherent set of model, data, position-policy and sampling assumptions is part of the experiment, not an optional implementation detail.

## 2. Reason through a worked example

Changing token positions changes their learned position embeddings. As a result, the two calls need not produce equal logits or the same generated token, despite using the same checkpoint and seed. The future BOS values in the right-padded context cannot affect the earlier prefix rows if causal masking works correctly.

When a calculation uses a fixed number of positions, label those positions from zero. When it uses a model score, distinguish a score (logit) from a probability after softmax. In particular, an identical selected token does not establish that two output distributions agree. Keep the exact input tensor shape, the measured workload and the declared comparison tolerance alongside each claim.

## 3. Use the existing Framework service

`UmiAiTrainingStackedPrefixSessionCreate` explicitly selects the unpadded convention. `UmiAiTrainingStackedGenerationSessionCreate` retains the historical left-padded convention. Neither replaces the other.

The implementation belongs in `Umicom-Applications/framework/include/umicom/ai/training/` and `src/ai/training/`; the educational manuscript under Bits2Banking contains no separate model runtime. Read the public header before changing a call signature. Preserve the model and all caller-owned output buffers on rejected operations.

## 4. What evidence would establish correctness?

An appropriate acceptance test must execute the actual C23 library, reject malformed inputs, check unchanged outputs on rejection and verify that model parameters have not been silently updated by inference. Where the test compares predicted logits, inspect the entire relevant vocabulary row. Where it compares a model checkpoint, remember that SHA-256 identifies bytes but does not authenticate the person who supplied them.

For a future cache optimisation, a meaningful result also needs correctly separated reports of token-layer work, retained memory, CPU time and elapsed time. Do not treat a synthetic fixture or an estimate as a measured speedup.

## 5. Practice and worked answer

**Question:** Which logit row should an unpadded three-token prefix use inside an eight-position decoder?

<details><summary>Reveal the worked answer</summary>

Row 2, because the real tokens occupy zero-based positions 0, 1 and 2. The five later positions must not be read as the current prediction.

</details>

## 6. Continue learning

Study [the mathematical companion](../11-maths-for-ai/79-read-the-right-logit-row.md) and the [complete native LLM HTML catalogue](../../courses/llm-from-scratch/advanced-lessons.html). The [HTML form of this lesson](../../courses/llm-from-scratch/lessons/169-left-padding-and-right-padding-are-different-policies.html) is an additional reading format, not a second implementation.

*Service to Many Leads to Greatness.*
