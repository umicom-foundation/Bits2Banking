# Lesson 238 — Compare the last canonical attention row

**Bits to Banking · Umicom Foundation**  
**Course lead:** Sammy Hegab  
**Language:** Native C23 and Assembly where justified · **Level:** Advanced native Transformer engineering.

**Learning objective:** Choose a non-circular numerical oracle for the new operator.

## 1. Understand the problem

The existing stacked decoder and projection-capture path remain the authoritative reference. The candidate single-query output should be compared with the **last valid attention row** from that path, using the same frozen model, prompt, position policy, K/V values, masks and floating-point datatype. Do not replace the reference with a copy of the candidate algorithm, or both may share a defect.

Parities form a hierarchy: projection-row parity, head-output parity, post-output-projection parity, per-layer hidden-state parity, and finally every vocabulary-logit parity. Failure at an earlier stage narrows the diagnosis; success at an earlier stage does not prove the end-to-end result.

## 2. Fully worked example

For a two-head model, suppose the reference head outputs are `(0.30, -0.10)` and `(0.20, 0.40)` and the candidate produces `(0.30, -0.10)` and `(0.20, 0.39)`. The second head differs by `0.01`, which might still preserve the selected token. If the documented attention-output threshold is `1e-5`, this candidate fails even though generation looks plausible.

## 3. Engineering verification and connection to Umicom Framework

Compare a numerical vector with absolute and relative errors, report maximum location and value, and reject any unexpected nonfinite results before applying tolerances. The threshold is a **documented test choice** based on datatype and reference operation ordering, not an excuse to widen limits until tests pass.

The existing Umicom Framework decoder, training tape and K/V ownership services remain the authority for implementation. This educational lesson specifies behaviour; it does **not** introduce a competing application-local inference engine or claim that the proposed single-query kernel is already merged or performance-qualified.

## 4. Mathematics connection

Review [Mathematics for AI — Unit 131](../11-maths-for-ai/131-calculate-absolute-and-relative-parity-errors.md). The mathematics companion includes a calculation that can be verified independently of a compiled model.

## 5. Exercise

**Question:** If the candidate picks exactly the same next token as the reference, has attention parity been established?

<details>
<summary>Reveal the worked answer</summary>

No. Different probability distributions can produce the same selected token; per-head outputs and full vocabulary logits must be qualified independently.

</details>

## 6. Acceptance note

Educational calculations and design specifications are not substitutes for running the complete numerical and memory-safety qualification suite against the actual Windows and other supported Framework builds. Do not claim an inference speedup from hypothetical arithmetic counts.

## Continue learning

[Previous lesson](237-budget-single-query-scratch-memory.md) · [Browser learning path](../../courses/llm-from-scratch/single-query-attention-learning-path.html) · [Next lesson](239-keep-learned-position-embeddings-consistent.md)

*Service to Many Leads to Greatness.*
