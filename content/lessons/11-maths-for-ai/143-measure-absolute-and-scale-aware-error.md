# Mathematics for AI — Unit 143: Measure absolute and scale-aware error

**Bits to Banking · Umicom Foundation**  
**Author:** Sammy Hegab · **Prerequisites:** Arithmetic, vectors and previous attention units

**Learning objective:** Avoid invalid relative-error conclusions near zero.

## 1. Symbols and definitions

`T` denotes admitted causal tokens; `L` denotes Transformer layers; `Hq` is the query-head count; `Hkv` is the K/V head count; `d` is a head's channel width; `B` denotes bytes. The symbols are defined here to keep the exercise independent of a particular neural model size.

## 2. Step-by-step worked calculation

For reference `r` and candidate `c`, absolute error is `|c−r|`. A guarded relative error can be written `|c−r|/max(|r|,ε)` for a documented positive floor `ε`. If `r=0.001` and `c=0.0015`, absolute error is `0.0005`, but relative error without a floor is `50%`. Near zero, ordinary relative error may exaggerate or become undefined.

For vectors, report a maximum absolute error plus a carefully specified scale-aware metric, compare non-finite handling separately and never silently change thresholds after seeing a failure.

## 3. Practice problem

**Question:** If `r=2` and `c=2.02`, what are absolute and relative errors?

<details>
<summary>Show the worked answer</summary>
<p>Absolute error is <code>0.02</code>; relative error is <code>0.02/2=0.01</code>, or <code>1%</code>.</p>
</details>

## 4. Connect the arithmetic to the native course

Read [LLM Lesson 250 — Compare a kernel against the canonical last row](../10-native-ai/250-compare-a-kernel-against-the-canonical-last-row.md) to see how these values become tensor shapes, buffer capacities or experimental measurements. Keep exact formulas separate from floating-point tolerances and measured execution times.

## Continue learning

[Previous unit](142-quantise-a-float-with-a-symmetric-scale.md) · [Next unit](144-calculate-paged-kv-internal-fragmentation.md) · [HTML mathematics route](../../courses/maths-for-ai/efficient-decoding-mathematics.html)

*Service to Many Leads to Greatness.*
