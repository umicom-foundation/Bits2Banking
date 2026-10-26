# Lesson 175 — Compare Every Logit Not Just The Winner

**Bits to Banking · Umicom Foundation**  
**Author:** Sammy Hegab  
**Native platform:** Umicom Framework, C23

> **Learning objective:** Understand how agreeing token IDs can conceal different model distributions.

## 1. The engineering question

Two models output score lists `[5,1,0]` and `[5,4,0]` for the same three candidates. Both choose the first candidate under greedy sampling. But the second candidate’s score differs by 3, so temperature sampling would assign substantially different probabilities.

The important distinction is between the behaviour of the existing, real multi-layer decoder and a proposal for a future more efficient runtime. We must describe what the software actually calculates before counting possible savings. A coherent set of model, data, position-policy and sampling assumptions is part of the experiment, not an optional implementation detail.

## 2. Reason through a worked example

An acceptance check that compares only the highest-scoring token misses this discrepancy. Independent comparison should inspect every finite score with a tolerance fixed before testing. The score ordering and the selected token are useful extra evidence, not replacements for all-logit parity.

When a calculation uses a fixed number of positions, label those positions from zero. When it uses a model score, distinguish a score (logit) from a probability after softmax. In particular, an identical selected token does not establish that two output distributions agree. Keep the exact input tensor shape, the measured workload and the declared comparison tolerance alongside each claim.

## 3. Use the existing Framework service

The prefix-causality qualification compares full prefix logit rows. A later optimised KV-cache implementation must compare its own logits against the established decoder independently, not merely against another cache schedule.

The implementation belongs in `Umicom-Applications/framework/include/umicom/ai/training/` and `src/ai/training/`; the educational manuscript under Bits2Banking contains no separate model runtime. Read the public header before changing a call signature. Preserve the model and all caller-owned output buffers on rejected operations.

## 4. What evidence would establish correctness?

An appropriate acceptance test must execute the actual C23 library, reject malformed inputs, check unchanged outputs on rejection and verify that model parameters have not been silently updated by inference. Where the test compares predicted logits, inspect the entire relevant vocabulary row. Where it compares a model checkpoint, remember that SHA-256 identifies bytes but does not authenticate the person who supplied them.

For a future cache optimisation, a meaningful result also needs correctly separated reports of token-layer work, retained memory, CPU time and elapsed time. Do not treat a synthetic fixture or an estimate as a measured speedup.

## 5. Practice and worked answer

**Question:** The reference second logit is 1.00000 and the candidate is 1.00009. Does a tolerance of 0.00004 accept this position?

<details><summary>Reveal the worked answer</summary>

No. The absolute difference is 0.00009, which exceeds 0.00004, even if the top-choice token remains unchanged.

</details>

## 6. Continue learning

Study [the mathematical companion](../11-maths-for-ai/87-choose-a-numerical-parity-tolerance.md) and the [complete native LLM HTML catalogue](../../courses/llm-from-scratch/advanced-lessons.html). The [HTML form of this lesson](../../courses/llm-from-scratch/lessons/175-compare-every-logit-not-just-the-winner.html) is an additional reading format, not a second implementation.

*Service to Many Leads to Greatness.*
