# Mathematics for AI — Unit 109: Separate stored K/V rows from executed token-layer work

**Bits to Banking · Umicom Foundation**  
**Author:** Sammy Hegab

## Start with the idea

No specialist mathematics qualification is required. Each numerical symbol is tied to a concrete tensor, amount or test.

A cache owner can accept one row while its producer recomputes a whole model. If a decoder has **L** layers and context **C**, one complete forward evaluates `L×C` token-layer rows. A diagnostic may keep only `L` rows from that evaluation when a new token is appended. These two counts have different meanings.

For `L=2`, `C=4`, `P=2`, prefill plus two appends means three complete forwards: `3×2×4=24` actually executed token-layer rows. Storage acceptance is `2×2 + 2 + 2 = 8` rows. The difference is **not** 16 avoided computations: all 24 were executed.

After a full-window replacement in this example, another `L×C=8` stored rows are admitted. The total becomes 16 stored rows versus 32 actually computed rows.

## Your turn

**Exercise:** What is actual computation after five full passes of a three-layer, eight-token model?

## Why this matters for a real native model

The Umicom Framework owns the actual model mathematics, K/V storage and numeric validation. The lesson calculates a small independent reference so a learner can recognise incorrect dimensions, wrong interpretation of results or numerical errors in a C23 regression. Nothing in this worked exercise claims that a production LLM has been trained or accelerated.

<details><summary>Reveal the calculation</summary>

`5×3×8=120` token-layer rows. Count actual passes, not only the rows retained in storage.

</details>

[Previous unit](108-measure-error-without-claiming-speed.md) · [Next unit](110-check-layer-major-address-arithmetic.md) · [Browser version](../../courses/maths-for-ai/lessons/109-separate-stored-from-executed-token-rows.html) · [K/V mathematics reading path](projection-trace-mathematics.md).
