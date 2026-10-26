# Mathematics for AI — Unit 108: Measure numerical error without claiming speed

**Bits to Banking · Umicom Foundation**  
**Author:** Sammy Hegab

## Start with the idea

No specialist mathematics qualification is required. Each numerical symbol is tied to a concrete tensor, amount or test.

Performance and correctness are different dimensions. A cache could return quickly but compute wrong logits. A full-context implementation could compute accurate logits slowly. Mathematical acceptance starts by comparing corresponding values, before any timing comparison.

Use a combined threshold if justified: `|actual − reference| ≤ absoluteTolerance + relativeTolerance × |reference|`. Relative tolerance accommodates differences in scale, while absolute tolerance handles values near zero. Values must be finite.

For reference 0.010000, actual 0.010002, absolute tolerance 0.000001 and relative tolerance 0.001, the allowed error is `0.000001+0.001×0.010000=0.000011`. The observed difference 0.000002 passes.

## Your turn

**Exercise:** Reference 2.0, actual 2.0005, absTol 0.0001, relTol 0.0001. Pass or fail?

## Why this matters for a real native model

The Umicom Framework owns the actual model mathematics, K/V storage and numeric validation. The lesson calculates a small independent reference so a learner can recognise incorrect dimensions, wrong interpretation of results or numerical errors in a C23 regression. Nothing in this worked exercise claims that a production LLM has been trained or accelerated.

<details><summary>Reveal the calculation</summary>

The allowed difference is `0.0001+0.0001×2=0.0003`. The actual error is 0.0005, so the test fails.

</details>

[Previous unit](107-interpret-frozen-checkpoint-identities.md) · [Next unit](109-separate-stored-from-executed-token-rows.md) · [Browser version](../../courses/maths-for-ai/lessons/108-measure-error-without-claiming-speed.html) · [K/V mathematics reading path](projection-trace-mathematics.md).
