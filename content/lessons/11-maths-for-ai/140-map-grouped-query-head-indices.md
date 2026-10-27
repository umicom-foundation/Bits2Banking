# Mathematics for AI — Unit 140: Map grouped-query head indices

**Bits to Banking · Umicom Foundation**  
**Author:** Sammy Hegab · **Prerequisites:** Arithmetic, vectors and previous attention units

**Learning objective:** Calculate the shared KV head used by each query head.

## 1. Symbols and definitions

`T` denotes admitted causal tokens; `L` denotes Transformer layers; `Hq` is the query-head count; `Hkv` is the K/V head count; `d` is a head's channel width; `B` denotes bytes. The symbols are defined here to keep the exercise independent of a particular neural model size.

## 2. Step-by-step worked calculation

For uniformly grouped attention, let `Hq=12` query heads and `Hkv=3` key/value heads. Then each KV group serves `g=Hq/Hkv=4` queries. The assignment is `kvHead=floor(queryHead/g)`. Query heads 0–3 map to 0, heads 4–7 map to 1 and heads 8–11 map to 2.

If `Hq` is not divisible by `Hkv`, this uniform grouping scheme is not defined. An implementation needs an explicitly specified alternative rather than truncating indices.

## 3. Practice problem

**Question:** With sixteen query heads and four KV heads, which KV head serves query 14?

<details>
<summary>Show the worked answer</summary>
<p><code>g=4</code>, and <code>floor(14/4)=3</code>.</p>
</details>

## 4. Connect the arithmetic to the native course

Read [LLM Lesson 254 — Map grouped-query attention heads](../10-native-ai/254-map-grouped-query-attention-heads.md) to see how these values become tensor shapes, buffer capacities or experimental measurements. Keep exact formulas separate from floating-point tolerances and measured execution times.

## Continue learning

[Previous unit](139-count-prefill-and-decode-score-pairs.md) · [Next unit](141-calculate-model-wide-kv-cache-bytes.md) · [HTML mathematics route](../../courses/maths-for-ai/efficient-decoding-mathematics.html)

*Service to Many Leads to Greatness.*
