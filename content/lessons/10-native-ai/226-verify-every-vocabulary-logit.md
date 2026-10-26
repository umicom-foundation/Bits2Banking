# Lesson 226 — Verify every vocabulary logit against the canonical decoder

**Bits to Banking · Umicom Foundation**  
**Author:** Sammy Hegab  
**Language:** Native C23 · **Level:** Building beyond the introductory Transformer.

**Learning objective:** Compare numerical outputs rather than merely checking the most likely token.

## 1. The engineering question

Two logits vectors can select the same top-one token while differing substantially in other scores. Parity therefore compares every vocabulary component, requiring finite values and a declared floating-point tolerance. K/V rows are also compared against separately traced canonical projections.

## 2. Work through a concrete example

With vocabulary 260, each proposed prefix step must pass 260 logit comparisons. If one reference logit is -1.25000 and the proposal is -1.24997, absolute error is 0.00003. With an absolute bound of 0.00010, that component passes.

## 3. How Umicom Framework implements the idea

The native `test_stacked_incremental_step_parity` regression checks each eligible prefix length for models with one, two and three Transformer layers. It also checks each candidate K/V element independently before allowing the next step.

The relevant public contract is `umicom/ai/training/stacked_projection_trace.h`. The native implementation and numerical tests belong to Umicom Framework; this manuscript does not introduce an alternative application-local training or inference service. The training tape owns mathematical operators and tensor lifetimes, while consumers use explicit C23 handles and status results.

## 4. Check the mathematical foundation

For a step-by-step explanation of the arithmetic, read [Mathematics Unit 119](../11-maths-for-ai/119-measure-logit-parity-with-an-absolute-tolerance.md). Keep tensor **shape**, **absolute position**, **model checkpoint identity** and **actual executed work** distinct when describing a cache.

## 5. Practice and verify

**Question:** Why is a top-one token match insufficient to prove probability equivalence?

<details>
<summary>Reveal the worked explanation</summary>

Many different score vectors share the same maximum. Temperature scaling, top-p membership and next-token probabilities depend on the full distribution, not only its winning index.

</details>

## 6. Limits and responsible interpretation

Passing one small model is evidence for that tested configuration. Repeat with trained checkpoints, different seeds and sanitiser-enabled builds before deployment.

A passing test in an isolated demonstration is not a production integration result. Evaluate against the actual Framework checkout and document any numerical or timing limitations before making deployment claims.

## Continue learning

[Previous lesson](225-separate-proposal-from-cache-publication.md) · [Next lesson](227-reuse-projections-across-several-transformer-layers.md) · [Browser learning path](../../courses/llm-from-scratch/incremental-attention-learning-path.html)

*Service to Many Leads to Greatness.*
