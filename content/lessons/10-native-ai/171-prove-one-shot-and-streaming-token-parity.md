# Lesson 171 — Prove One Shot And Streaming Token Parity

**Bits to Banking · Umicom Foundation**  
**Author:** Sammy Hegab  
**Native platform:** Umicom Framework, C23

> **Learning objective:** Verify the two convenience interfaces implement one identical sampling sequence.

## 1. The engineering question

Choose prompt length 2, context length 4 and six samples. With a fixed seed and the same model, calling `Next` six times must produce exactly the same six IDs as one call to the one-shot generator. The final emitted token is still pending and is not appended to the retained context.

The important distinction is between the behaviour of the existing, real multi-layer decoder and a proposal for a future more efficient runtime. We must describe what the software actually calculates before counting possible savings. A coherent set of model, data, position-policy and sampling assumptions is part of the experiment, not an optional implementation detail.

## 2. Reason through a worked example

There are five append operations. Two fill positions 2 and 3, and the remaining three cause a full-window shift, giving exactly three evictions. Counts must be derived from actual session transitions rather than a guessed cache performance improvement.

When a calculation uses a fixed number of positions, label those positions from zero. When it uses a model score, distinguish a score (logit) from a probability after softmax. In particular, an identical selected token does not establish that two output distributions agree. Keep the exact input tensor shape, the measured workload and the declared comparison tolerance alongside each claim.

## 3. Use the existing Framework service

`UmiAiTrainingStackedPrefixGenerateNucleus` stages up to 64 outputs and publishes them only when all steps and the final inspection succeed. The regression compares all IDs and the full-context work counters.

The implementation belongs in `Umicom-Applications/framework/include/umicom/ai/training/` and `src/ai/training/`; the educational manuscript under Bits2Banking contains no separate model runtime. Read the public header before changing a call signature. Preserve the model and all caller-owned output buffers on rejected operations.

## 4. What evidence would establish correctness?

An appropriate acceptance test must execute the actual C23 library, reject malformed inputs, check unchanged outputs on rejection and verify that model parameters have not been silently updated by inference. Where the test compares predicted logits, inspect the entire relevant vocabulary row. Where it compares a model checkpoint, remember that SHA-256 identifies bytes but does not authenticate the person who supplied them.

For a future cache optimisation, a meaningful result also needs correctly separated reports of token-layer work, retained memory, CPU time and elapsed time. Do not treat a synthetic fixture or an estimate as a measured speedup.

## 5. Practice and worked answer

**Question:** With context 4, prompt 2 and generated 6, how many full-window shifts occur?

<details><summary>Reveal the worked answer</summary>

There are five pending-token appends. Two fit without eviction, and three shift the full window: three shifts.

</details>

## 6. Continue learning

Study [the mathematical companion](../11-maths-for-ai/81-pending-samples-and-append-counts.md) and the [complete native LLM HTML catalogue](../../courses/llm-from-scratch/advanced-lessons.html). The [HTML form of this lesson](../../courses/llm-from-scratch/lessons/171-prove-one-shot-and-streaming-token-parity.html) is an additional reading format, not a second implementation.

*Service to Many Leads to Greatness.*
