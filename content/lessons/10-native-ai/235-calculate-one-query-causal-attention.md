# Lesson 235 — Calculate one-query causal attention

**Bits to Banking · Umicom Foundation**  
**Course lead:** Sammy Hegab  
**Language:** Native C23 and Assembly where justified · **Level:** Advanced native Transformer engineering.

**Learning objective:** Compute scaled dot products, softmax probabilities and the weighted value vector by hand.

## 1. Understand the problem

For one head, take a query vector `q` of width `d`, keys `k_0 … k_t`, and value vectors `v_0 … v_t`. Score key `i` with `s_i = dot(q, k_i) / sqrt(d)`. Apply softmax across **only the valid, unmasked keys** and return `sum_i probability_i × v_i`.

A causal decoder’s newest query normally sees every retained key and itself; there are no future keys in the accepted prefix. If the physical K/V allocation includes right padding, those rows are not part of the calculation. Use the learned projections and model-specific attention scaling defined by the existing decoder.

## 2. Fully worked example

Let `d=2`, `q=(2,0)`, `k_0=(1,0)`, `k_1=(0,1)` and `v_0=(1,0)`, `v_1=(0,2)`. The scores are `2/sqrt(2) ≈ 1.414214` and `0`. After subtracting the maximum, exponentials are `1` and `exp(-1.414214) ≈ 0.243117`. Normalise: `p_0≈0.80443`, `p_1≈0.19557`. The attention output is `(0.80443, 0.39114)`.

Only **one** query row was evaluated. A full `2×2` attention matrix would compute an earlier query output that the newest-token step does not need.

## 3. Engineering verification and connection to Umicom Framework

The numerical test should compare the dedicated candidate output with the matching final row of the original Framework operator, first at FP64 reference precision for this tiny example, then at the production datatype. Log the per-head maximum error; do not accept agreement of the argmax token as a substitute.

The existing Umicom Framework decoder, training tape and K/V ownership services remain the authority for implementation. This educational lesson specifies behaviour; it does **not** introduce a competing application-local inference engine or claim that the proposed single-query kernel is already merged or performance-qualified.

## 4. Mathematics connection

Review [Mathematics for AI — Unit 126](../11-maths-for-ai/126-calculate-scaled-dot-products-and-temperature.md). The mathematics companion includes a calculation that can be verified independently of a compiled model.

## 5. Exercise

**Question:** If a third physical slot is allocated but not valid, should its all-zero key join the softmax?

<details>
<summary>Reveal the worked answer</summary>

No. Even an all-zero key receives positive probability if included, reducing the weights of valid tokens and changing the result.

</details>

## 6. Acceptance note

Educational calculations and design specifications are not substitutes for running the complete numerical and memory-safety qualification suite against the actual Windows and other supported Framework builds. Do not claim an inference speedup from hypothetical arithmetic counts.

## Continue learning

[Previous lesson](234-trace-head-local-key-value-layout.md) · [Browser learning path](../../courses/llm-from-scratch/single-query-attention-learning-path.html) · [Next lesson](236-preserve-causal-masks-and-padding-semantics.md)

*Service to Many Leads to Greatness.*
