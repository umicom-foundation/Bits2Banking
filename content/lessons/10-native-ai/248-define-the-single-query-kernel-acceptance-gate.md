# Lesson 248 — Define the single-query kernel acceptance gate

**Bits to Banking · Umicom Foundation**  
**Course lead:** Sammy Hegab  
**Language:** Native C23 and Assembly where justified · **Level:** Advanced native Transformer engineering.

**Learning objective:** Turn lessons 233–247 into a concrete, reviewable plan for the next Framework engineering batch.

## 1. Understand the problem

The course has now narrowed the next change to a **dedicated last-query attention operation**, not an alternative model or second inference runtime. All reusable implementation remains in Umicom Framework. Bits2Banking owns examples, explanation and acceptance requirements, while the existing native stacked decoder remains the independent numerical reference.

A future Framework change should first expose the established cache view and correct single-row computation, then qualify per-head outputs, full logits, session rollback, position rollover and portable CPU behaviour. Acceptance means **the actual integrated tests have run successfully**; a compiled stub, isolated fixture or number of fewer theoretical operations cannot substitute.

## 2. Fully worked example

Define one acceptance record with model `(3 layers, 4 heads, width 32, context capacity 8)`, prompt lengths `1, 7, 8`, seeds `11, 29`, both greedy and sampled generation, and at least 10 output steps. The test must record all per-step vocabulary logits, first and repeated evictions, cache versions, maximum numerical errors, allocation failures and actual elapsed Release samples. It must also include a malformed-view negative test and checkpoint replacement.

## 3. Engineering verification and connection to Umicom Framework

Before merging a Framework kernel: (1) preserve existing C API and source comments; (2) build on Windows UCRT64 and a second compiler; (3) run unit, end-to-end and sanitiser tests; (4) prove unchanged behaviour under all acceptance axes; (5) measure realistic timings; (6) retain fallback until the project owner approves changes. The source may then be integrated into the existing session path, not a duplicated Bits2Banking implementation.

The existing Umicom Framework decoder, training tape and K/V ownership services remain the authority for implementation. This educational lesson specifies behaviour; it does **not** introduce a competing application-local inference engine or claim that the proposed single-query kernel is already merged or performance-qualified.

## 4. Mathematics connection

Review [Mathematics for AI — Unit 136](../11-maths-for-ai/136-read-paired-latency-measurements.md). The mathematics companion includes a calculation that can be verified independently of a compiled model.

## 5. Exercise

**Question:** What single statement is justified if a kernel passes head-output parity but full decoder logit parity has not been run?

<details>
<summary>Reveal the worked answer</summary>

Only that the tested head-output cases agree within the declared numerical limits. It is premature to claim an integrated accelerated LLM or production performance gain.

</details>

## 6. Acceptance note

Educational calculations and design specifications are not substitutes for running the complete numerical and memory-safety qualification suite against the actual Windows and other supported Framework builds. Do not claim an inference speedup from hypothetical arithmetic counts.

## Continue learning

[Previous lesson](247-plan-portable-cpu-kernel-optimisation.md) · [Browser learning path](../../courses/llm-from-scratch/single-query-attention-learning-path.html)

*Service to Many Leads to Greatness.*
