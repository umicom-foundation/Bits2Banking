# Mathematics for AI — Unit 139: Count prefill and decode score pairs

**Bits to Banking · Umicom Foundation**  
**Author:** Sammy Hegab · **Prerequisites:** Arithmetic, vectors and previous attention units

**Learning objective:** Compare triangular causal work with a last-query-only calculation.

## 1. Symbols and definitions

`T` denotes admitted causal tokens; `L` denotes Transformer layers; `Hq` is the query-head count; `Hkv` is the K/V head count; `d` is a head's channel width; `B` denotes bytes. The symbols are defined here to keep the exercise independent of a particular neural model size.

## 2. Step-by-step worked calculation

A full causal attention matrix over `T` tokens contains `1+2+...+T=T(T+1)/2` permitted query–key score pairs per head. The newest query alone uses `T` score pairs. With `T=8`, full prefill has `8×9/2=36` permitted pairs per head, while the last-query calculation has eight. For four heads the respective counts become 144 and 32.

These are arithmetic counts, not the number of bytes read or elapsed milliseconds. Projection and MLP work are additional terms in the complete Transformer.

## 3. Practice problem

**Question:** How many permitted causal score pairs exist at `T=10` for two heads?

<details>
<summary>Show the worked answer</summary>
<p><code>2×(10×11/2)=110</code> score pairs.</p>
</details>

## 4. Connect the arithmetic to the native course

Read [LLM Lesson 252 — Separate prefill from incremental decode](../10-native-ai/252-separate-prefill-from-incremental-decode.md) to see how these values become tensor shapes, buffer capacities or experimental measurements. Keep exact formulas separate from floating-point tolerances and measured execution times.

## Continue learning

[Previous unit](138-calculate-a-weighted-value-vector.md) · [Next unit](140-map-grouped-query-head-indices.md) · [HTML mathematics route](../../courses/maths-for-ai/efficient-decoding-mathematics.html)

*Service to Many Leads to Greatness.*
