# Mathematics for AI — Unit 137: Derive a stable softmax normaliser

**Bits to Banking · Umicom Foundation**  
**Author:** Sammy Hegab · **Prerequisites:** Arithmetic, vectors and previous attention units

**Learning objective:** Normalise exponentially weighted scores without overflow.

## 1. Symbols and definitions

`T` denotes admitted causal tokens; `L` denotes Transformer layers; `Hq` is the query-head count; `Hkv` is the K/V head count; `d` is a head's channel width; `B` denotes bytes. The symbols are defined here to keep the exercise independent of a particular neural model size.

## 2. Step-by-step worked calculation

For scores `sᵢ`, softmax is `pᵢ = exp(sᵢ-m)/Σⱼ exp(sⱼ-m)` with `m=max(s)`. Subtracting the same maximum from every score leaves the probabilities unchanged mathematically, because numerator and denominator are scaled by the same factor. It prevents overflow for large positive inputs.

For `[2,1,0]`, subtract 2 to obtain `[0,−1,−2]`. Exponentials are approximately `[1,0.367879,0.135335]`; denominator `1.503214`; probabilities `[0.665241,0.244728,0.090031]` (rounded). Their sum is one to rounding tolerance.

## 3. Practice problem

**Question:** Why is calculating `exp(1000)` directly in floating point a poor idea?

<details>
<summary>Show the worked answer</summary>
<p>It overflows ordinary floating-point formats, whereas subtracting the maximum turns the largest exponent into <code>exp(0)=1</code>.</p>
</details>

## 4. Connect the arithmetic to the native course

Read [LLM Lesson 249 — Implement a forward-only single-query kernel](../10-native-ai/249-implement-a-forward-only-single-query-kernel.md) to see how these values become tensor shapes, buffer capacities or experimental measurements. Keep exact formulas separate from floating-point tolerances and measured execution times.

## Continue learning

[Previous unit](136-read-paired-latency-measurements.md) · [Next unit](138-calculate-a-weighted-value-vector.md) · [HTML mathematics route](../../courses/maths-for-ai/efficient-decoding-mathematics.html)

*Service to Many Leads to Greatness.*
