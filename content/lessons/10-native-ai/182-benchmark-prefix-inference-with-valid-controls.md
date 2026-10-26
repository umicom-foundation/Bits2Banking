# Lesson 182 — Benchmark Prefix Inference With Valid Controls

**Bits to Banking · Umicom Foundation**  
**Author:** Sammy Hegab  
**Native platform:** Umicom Framework, C23

> **Learning objective:** Measure correctness, resource work and performance as three separate dimensions.

## 1. The engineering question

A valid benchmark uses the same frozen checkpoint, prompt policy, seed, sample count, compiler configuration and hardware for both compared strategies. The benchmark must first prove numerical parity and exact token outputs, then measure real workload and wall-clock time over repeated trials.

The important distinction is between the behaviour of the existing, real multi-layer decoder and a proposal for a future more efficient runtime. We must describe what the software actually calculates before counting possible savings. A coherent set of model, data, position-policy and sampling assumptions is part of the experiment, not an optional implementation detail.

## 2. Reason through a worked example

A count of 288 observed token-layer rows says which tensor rows were evaluated; it is not a CPU instruction count or milliseconds. The chosen sampler, memory layout, cache allocation and kernel dispatch may outweigh theoretical row savings. Record warm-up, repeated timings, median and variability.

When a calculation uses a fixed number of positions, label those positions from zero. When it uses a model score, distinguish a score (logit) from a probability after softmax. In particular, an identical selected token does not establish that two output distributions agree. Keep the exact input tensor shape, the measured workload and the declared comparison tolerance alongside each claim.

## 3. Use the existing Framework service

The current full-context session can provide a reproducible reference. A future KV cache should be benchmarked only after passing the same per-layer and post-eviction correctness gates.

The implementation belongs in `Umicom-Applications/framework/include/umicom/ai/training/` and `src/ai/training/`; the educational manuscript under Bits2Banking contains no separate model runtime. Read the public header before changing a call signature. Preserve the model and all caller-owned output buffers on rejected operations.

## 4. What evidence would establish correctness?

An appropriate acceptance test must execute the actual C23 library, reject malformed inputs, check unchanged outputs on rejection and verify that model parameters have not been silently updated by inference. Where the test compares predicted logits, inspect the entire relevant vocabulary row. Where it compares a model checkpoint, remember that SHA-256 identifies bytes but does not authenticate the person who supplied them.

For a future cache optimisation, a meaningful result also needs correctly separated reports of token-layer work, retained memory, CPU time and elapsed time. Do not treat a synthetic fixture or an estimate as a measured speedup.

## 5. Practice and worked answer

**Question:** If the reference takes 4.1 ms and an actual cache takes 4.6 ms on one run, is the cache proven faster?

<details><summary>Reveal the worked answer</summary>

No. That isolated observation shows a slower measured duration. Repeat controlled tests and inspect variance before drawing a performance conclusion.

</details>

## 6. Continue learning

Study [the mathematical companion](../11-maths-for-ai/83-compare-actual-and-planned-cache-work.md) and the [complete native LLM HTML catalogue](../../courses/llm-from-scratch/advanced-lessons.html). The [HTML form of this lesson](../../courses/llm-from-scratch/lessons/182-benchmark-prefix-inference-with-valid-controls.html) is an additional reading format, not a second implementation.

*Service to Many Leads to Greatness.*
