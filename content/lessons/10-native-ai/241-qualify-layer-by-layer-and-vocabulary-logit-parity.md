# Lesson 241 — Qualify layer-by-layer and vocabulary-logit parity

**Bits to Banking · Umicom Foundation**  
**Course lead:** Sammy Hegab  
**Language:** Native C23 and Assembly where justified · **Level:** Advanced native Transformer engineering.

**Learning objective:** Escalate from a correct attention row to a correct multi-layer prediction.

## 1. Understand the problem

Later Transformer layers consume the output of earlier layers. A small error after layer one can propagate through layer normalisation, attention, residual paths and MLPs. Therefore the replacement kernel must be exercised in the actual stacked execution path, not certified solely with a toy vector test.

For each candidate step, retain a test-only trace of pre-attention input, Q/K/V, final-row head outputs, attention projection, post-residual state and final logits. This **trace is test evidence**, not an alternative production inference engine. When the Framework cannot expose such intermediate values publicly, prefer existing observer/test facilities rather than modifying application-local logic.

## 2. Fully worked example

In a three-layer example, layers 1 and 2 each pass a `1e-5` head-output tolerance but layer 3 differs by `0.002`, and the final vocabulary vector differs by `0.003`. End-to-end parity fails despite two passing intermediate results. Record the **first divergent layer**, maximum absolute error and prompt position to make the regression actionable.

## 3. Engineering verification and connection to Umicom Framework

Use one-, two- and three-layer checkpoints, short and full prompts, at least two independent seeds, greedy and sampled generation, plus repeatable negatives. A sampled token sequence may be compared **after** per-step logits; never use it as the only acceptance criterion.

The existing Umicom Framework decoder, training tape and K/V ownership services remain the authority for implementation. This educational lesson specifies behaviour; it does **not** introduce a competing application-local inference engine or claim that the proposed single-query kernel is already merged or performance-qualified.

## 4. Mathematics connection

Review [Mathematics for AI — Unit 131](../11-maths-for-ai/131-calculate-absolute-and-relative-parity-errors.md). The mathematics companion includes a calculation that can be verified independently of a compiled model.

## 5. Exercise

**Question:** What should a regression report when only the third layer diverges?

<details>
<summary>Reveal the worked answer</summary>

Report layer 3 as the first failing boundary, include its tensor shape and maximum error, and retain the failing prompt, checkpoint hash and numerical tolerance.

</details>

## 6. Acceptance note

Educational calculations and design specifications are not substitutes for running the complete numerical and memory-safety qualification suite against the actual Windows and other supported Framework builds. Do not claim an inference speedup from hypothetical arithmetic counts.

## Continue learning

[Previous lesson](240-preserve-head-concatenation-and-output-projection.md) · [Browser learning path](../../courses/llm-from-scratch/single-query-attention-learning-path.html) · [Next lesson](242-validate-cache-identity-shape-and-lifetime.md)

*Service to Many Leads to Greatness.*
