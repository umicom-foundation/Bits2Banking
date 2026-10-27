# Lesson 245 — Design adversarial single-query fixtures

**Bits to Banking · Umicom Foundation**  
**Course lead:** Sammy Hegab  
**Language:** Native C23 and Assembly where justified · **Level:** Advanced native Transformer engineering.

**Learning objective:** Create small, diagnostic cases that expose masking, layout, arithmetic and lifetime faults.

## 1. Understand the problem

Random prompts are useful but poorly targeted. A good qualification set contains **constructed counterexamples**: distinct head values to catch axis swaps, uniform scores to catch bad normalisation, very large logits to catch overflow, masked garbage to catch over-read, and a frozen reference to catch position changes.

Every fixture needs a named property, expected behaviour, independent oracle and failure report. Negative tests should assert not only that an operation rejects bad input but also that the session and K/V store are unchanged. Avoid copying test code into this education repository: fixture specifications belong here, execution and reusable numerical services remain in Framework.

## 2. Fully worked example

A minimal table: (1) `scores=[0,0]`, values `[(2,0),(0,2)]`, output `(1,1)`; (2) `scores=[1000,999]`, output must be finite with probabilities approximately `(0.7311,0.2689)`; (3) physical capacity four but valid length two, changing rows 2–3 must not change output; (4) two heads with distinct labels must preserve their ordering; (5) all rows masked must produce a defined rejection.

## 3. Engineering verification and connection to Umicom Framework

Name each fixture with `checkpoint`, `layer`, `position policy`, `head count`, `valid length`, `mask shape`, `precision` and expected result. Pair every positive fixture with one malformed or boundary variant. Add address/UB sanitiser runs for lifetime and checked-integer failures.

The existing Umicom Framework decoder, training tape and K/V ownership services remain the authority for implementation. This educational lesson specifies behaviour; it does **not** introduce a competing application-local inference engine or claim that the proposed single-query kernel is already merged or performance-qualified.

## 4. Mathematics connection

Review [Mathematics for AI — Unit 129](../11-maths-for-ai/129-reason-about-masked-softmax.md). The mathematics companion includes a calculation that can be verified independently of a compiled model.

## 5. Exercise

**Question:** What does changing bytes in an invalid padded row test?

<details>
<summary>Reveal the worked answer</summary>

Whether the operator incorrectly reads non-causal storage. If the answer changes, the valid-length or mask contract is broken.

</details>

## 6. Acceptance note

Educational calculations and design specifications are not substitutes for running the complete numerical and memory-safety qualification suite against the actual Windows and other supported Framework builds. Do not claim an inference speedup from hypothetical arithmetic counts.

## Continue learning

[Previous lesson](244-treat-context-rollover-as-a-slow-path-gate.md) · [Browser learning path](../../courses/llm-from-scratch/single-query-attention-learning-path.html) · [Next lesson](246-benchmark-one-query-attention-with-fair-controls.md)

*Service to Many Leads to Greatness.*
