# Mathematics for AI — Unit 142: Quantise a float with a symmetric scale

**Bits to Banking · Umicom Foundation**  
**Author:** Sammy Hegab · **Prerequisites:** Arithmetic, vectors and previous attention units

**Learning objective:** Work through one element and state the approximation error.

## 1. Symbols and definitions

`T` denotes admitted causal tokens; `L` denotes Transformer layers; `Hq` is the query-head count; `Hkv` is the K/V head count; `d` is a head's channel width; `B` denotes bytes. The symbols are defined here to keep the exercise independent of a particular neural model size.

## 2. Step-by-step worked calculation

A simple symmetric int8 scheme uses a positive scale `s`, a signed integer `q=clip(round(x/s),−127,127)`, and reconstructed value `x̂=sq`. Let `x=0.37` and `s=0.02`; `x/s=18.5`. The answer depends on the documented tie-rounding rule. With round-half-away-from-zero, `q=19` and `x̂=0.38`, giving error `0.01`.

If the input exceeds the representable range, clipping creates additional error. Real quantisers may choose per-channel or per-block scales and special zero-point handling.

## 3. Practice problem

**Question:** With `x=0.42`, `s=0.1`, and nearest-integer rounding, what is reconstructed?

<details>
<summary>Show the worked answer</summary>
<p><code>q=round(4.2)=4</code>, so <code>x̂=0.4</code>; absolute error is <code>0.02</code>.</p>
</details>

## 4. Connect the arithmetic to the native course

Read [LLM Lesson 256 — Quantise KV caches with an error budget](../10-native-ai/256-quantise-kv-caches-with-an-error-budget.md) to see how these values become tensor shapes, buffer capacities or experimental measurements. Keep exact formulas separate from floating-point tolerances and measured execution times.

## Continue learning

[Previous unit](141-calculate-model-wide-kv-cache-bytes.md) · [Next unit](143-measure-absolute-and-scale-aware-error.md) · [HTML mathematics route](../../courses/maths-for-ai/efficient-decoding-mathematics.html)

*Service to Many Leads to Greatness.*
