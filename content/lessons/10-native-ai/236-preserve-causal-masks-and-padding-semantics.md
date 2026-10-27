# Lesson 236 — Preserve causal masks and padding semantics

**Bits to Banking · Umicom Foundation**  
**Course lead:** Sammy Hegab  
**Language:** Native C23 and Assembly where justified · **Level:** Advanced native Transformer engineering.

**Learning objective:** Ensure the single-row optimisation gives attention only to valid past and current tokens.

## 1. Understand the problem

The newest-token attention operator usually needs no triangular future mask because the K/V view contains no future positions. That simplification is correct only when the view is restricted to **exactly** the admitted causal prefix. A larger allocation can contain stale rows, unused right padding or rows from an earlier checkpoint.

Masking and admission are related but different: validity checks decide which rows may be read; an attention mask decides which admitted rows receive probability mass. Do not treat masked `-∞` scores as ordinary nonfinite corruption. Conversely, reject NaN and unexpected infinity in unmasked projections or intermediate arithmetic. An all-masked row has no valid probability distribution and must fail explicitly rather than divide zero by zero.

## 2. Fully worked example

Suppose three physical slots hold attention scores `[2, unused, 1]`, with the middle slot masked out. The valid exponentials after subtracting 2 are `[1, 0, exp(-1)] = [1,0,0.367879]`; probabilities are approximately `[0.731059,0,0.268941]`. Accidentally treating the unused score as zero would produce a third positive term and change both valid weights.

## 3. Engineering verification and connection to Umicom Framework

Test an unpadded one-token prompt, a partly filled cache, a full valid cache, explicit masked rows, an all-masked rejection and a NaN in an unmasked key. Verify the result stays unchanged when garbage is written to **invalid** physical rows; a correct operator must not read them.

The existing Umicom Framework decoder, training tape and K/V ownership services remain the authority for implementation. This educational lesson specifies behaviour; it does **not** introduce a competing application-local inference engine or claim that the proposed single-query kernel is already merged or performance-qualified.

## 4. Mathematics connection

Review [Mathematics for AI — Unit 129](../11-maths-for-ai/129-reason-about-masked-softmax.md). The mathematics companion includes a calculation that can be verified independently of a compiled model.

## 5. Exercise

**Question:** Can an optimised operator omit mask application just because it processes the newest query?

<details>
<summary>Reveal the worked answer</summary>

Only if its contract proves the supplied view contains exactly the permitted keys. A newest-query shape alone does not prove that every allocated row is causally valid.

</details>

## 6. Acceptance note

Educational calculations and design specifications are not substitutes for running the complete numerical and memory-safety qualification suite against the actual Windows and other supported Framework builds. Do not claim an inference speedup from hypothetical arithmetic counts.

## Continue learning

[Previous lesson](235-calculate-one-query-causal-attention.md) · [Browser learning path](../../courses/llm-from-scratch/single-query-attention-learning-path.html) · [Next lesson](237-budget-single-query-scratch-memory.md)

*Service to Many Leads to Greatness.*
