# Lesson 181 — Cancel Streaming Safely And Preserve Results

**Bits to Banking · Umicom Foundation**  
**Author:** Sammy Hegab  
**Native platform:** Umicom Framework, C23

> **Learning objective:** Make output publication and cancellation precise.

## 1. The engineering question

A streaming interface produces one token per successful `Next` call. The caller may display that token as a provisional answer. Destroying the session cancels future work; it does not roll back tokens already shown by the application.

The important distinction is between the behaviour of the existing, real multi-layer decoder and a proposal for a future more efficient runtime. We must describe what the software actually calculates before counting possible savings. A coherent set of model, data, position-policy and sampling assumptions is part of the experiment, not an optional implementation detail.

## 2. Reason through a worked example

For an atomic whole-answer request, call `StackedPrefixGenerateNucleus`, which stages all requested tokens privately and writes the caller’s output only after the complete run succeeds. A rejected call must leave both the provided token array and count untouched.

When a calculation uses a fixed number of positions, label those positions from zero. When it uses a model score, distinguish a score (logit) from a probability after softmax. In particular, an identical selected token does not establish that two output distributions agree. Keep the exact input tensor shape, the measured workload and the declared comparison tolerance alongside each claim.

## 3. Use the existing Framework service

No newly introduced script is needed. Framework owns generation state; the Umicom Studio user interface only renders received bytes and performs cancellation. A partial UTF-8 code point must remain buffered until completion.

The implementation belongs in `Umicom-Applications/framework/include/umicom/ai/training/` and `src/ai/training/`; the educational manuscript under Bits2Banking contains no separate model runtime. Read the public header before changing a call signature. Preserve the model and all caller-owned output buffers on rejected operations.

## 4. What evidence would establish correctness?

An appropriate acceptance test must execute the actual C23 library, reject malformed inputs, check unchanged outputs on rejection and verify that model parameters have not been silently updated by inference. Where the test compares predicted logits, inspect the entire relevant vocabulary row. Where it compares a model checkpoint, remember that SHA-256 identifies bytes but does not authenticate the person who supplied them.

For a future cache optimisation, a meaningful result also needs correctly separated reports of token-layer work, retained memory, CPU time and elapsed time. Do not treat a synthetic fixture or an estimate as a measured speedup.

## 5. Practice and worked answer

**Question:** If one-shot generation fails on the fifth of six requested tokens, may it return the first four as a successful full result?

<details><summary>Reveal the worked answer</summary>

No. That API is failure-atomic: a failed six-token operation publishes no partial token array or successful count.

</details>

## 6. Continue learning

Study [the mathematical companion](../11-maths-for-ai/81-pending-samples-and-append-counts.md) and the [complete native LLM HTML catalogue](../../courses/llm-from-scratch/advanced-lessons.html). The [HTML form of this lesson](../../courses/llm-from-scratch/lessons/181-cancel-streaming-safely-and-preserve-results.html) is an additional reading format, not a second implementation.

*Service to Many Leads to Greatness.*
