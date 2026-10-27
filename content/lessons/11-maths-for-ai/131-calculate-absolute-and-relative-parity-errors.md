# Mathematics for AI — Unit 131: Calculate absolute and relative parity errors

**Bits to Banking · Umicom Foundation**  
**Course lead:** Sammy Hegab · **Prerequisite:** Basic arithmetic and an interest in neural networks.

## What will you learn?

Make numerical comparison rules explicit and handle near-zero reference values.

## Step-by-step calculation

For reference `r` and candidate `c`, absolute error is `abs(c-r)`. A common mixed rule accepts `abs(c-r) <= atol + rtol×abs(r)`. This avoids treating tiny reference values as relative-error catastrophes.

Example: `r=2.000`, `c=2.001`, `atol=0.0001`, `rtol=0.001`. Absolute error is `0.001`; allowed error is `0.0001+0.001×2=0.0021`, so it passes. If `r=0`, `c=0.001`, the allowed error is only `0.0001`, so it fails. Nonfinite unexpected values fail **before** tolerance comparisons. These tolerances are instructional examples, not a proposed project-wide constant.

**Notation guide:** `H` = number of attention heads; `T` = valid causal token count; `D` = channels per head; `L` = Transformer layers. The symbols describe *example data*, not the size or performance of an actual deployed model.

## Work it out yourself

**Question:** With `r=10`, `c=10.05`, `atol=0.01`, `rtol=0.001`, is the value within tolerance?

<details>
<summary>Show the worked answer</summary>

Limit `0.01+0.001×10=0.02`; actual error `0.05`; the candidate fails.

</details>

## Connect the numbers with native C23

[LLM Lesson 238](../10-native-ai/238-compare-the-last-canonical-attention-row.md) explains where this calculation belongs in the planned single-query kernel. The numerical implementation remains Framework-owned; these educational numbers are for checking reasoning, not a substitute for integrated decoder tests.

## Continue learning

[Previous unit](130-reconstruct-multihead-output-shapes.md) · [Browser mathematics path](../../courses/maths-for-ai/single-query-attention-mathematics.html) · [Next unit](132-calculate-cache-and-scratch-memory.md)

*Service to Many Leads to Greatness.*
