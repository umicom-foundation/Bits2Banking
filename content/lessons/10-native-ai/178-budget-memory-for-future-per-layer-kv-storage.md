# Lesson 178 — Budget Memory For Future Per Layer KV Storage

**Bits to Banking · Umicom Foundation**  
**Author:** Sammy Hegab  
**Native platform:** Umicom Framework, C23

> **Learning objective:** Estimate only what a KV tensor allocation actually represents.

## 1. The engineering question

A future FP32 cache retains K and V rows for every Transformer layer. With 3 layers, context 8 and 16 channels, its raw tensor storage is `2 × 3 × 8 × 16 × 4 = 3,072 bytes` per sequence. That excludes the decoder weights, logits, activations, allocator metadata and operating-system overhead.

The important distinction is between the behaviour of the existing, real multi-layer decoder and a proposal for a future more efficient runtime. We must describe what the software actually calculates before counting possible savings. A coherent set of model, data, position-policy and sampling assumptions is part of the experiment, not an optional implementation detail.

## 2. Reason through a worked example

A cache can lower redundant projection work but increases persistent memory. Multi-sequence concurrency multiplies retained storage. A complete capacity review must consider peak graph memory, temporary attention matrices, checkpoint copies, and CPU/GPU transfer buffers.

When a calculation uses a fixed number of positions, label those positions from zero. When it uses a model score, distinguish a score (logit) from a probability after softmax. In particular, an identical selected token does not establish that two output distributions agree. Keep the exact input tensor shape, the measured workload and the declared comparison tolerance alongside each claim.

## 3. Use the existing Framework service

The existing `UmiAiTrainingModelScalingEstimateBuild` and `UmiAiTrainingStackedPrefixCachePlanBuild` already own numeric planning. No application should hard-code a conflicting capacity formula.

The implementation belongs in `Umicom-Applications/framework/include/umicom/ai/training/` and `src/ai/training/`; the educational manuscript under Bits2Banking contains no separate model runtime. Read the public header before changing a call signature. Preserve the model and all caller-owned output buffers on rejected operations.

## 4. What evidence would establish correctness?

An appropriate acceptance test must execute the actual C23 library, reject malformed inputs, check unchanged outputs on rejection and verify that model parameters have not been silently updated by inference. Where the test compares predicted logits, inspect the entire relevant vocabulary row. Where it compares a model checkpoint, remember that SHA-256 identifies bytes but does not authenticate the person who supplied them.

For a future cache optimisation, a meaningful result also needs correctly separated reports of token-layer work, retained memory, CPU time and elapsed time. Do not treat a synthetic fixture or an estimate as a measured speedup.

## 5. Practice and worked answer

**Question:** What is the raw cache size for two concurrent sequences in this example?

<details><summary>Reveal the worked answer</summary>

Twice the per-sequence raw K/V storage: `2 × 3,072 = 6,144 bytes`, excluding all other allocations.

</details>

## 6. Continue learning

Study [the mathematical companion](../11-maths-for-ai/86-budget-key-value-memory.md) and the [complete native LLM HTML catalogue](../../courses/llm-from-scratch/advanced-lessons.html). The [HTML form of this lesson](../../courses/llm-from-scratch/lessons/178-budget-memory-for-future-per-layer-kv-storage.html) is an additional reading format, not a second implementation.

*Service to Many Leads to Greatness.*
