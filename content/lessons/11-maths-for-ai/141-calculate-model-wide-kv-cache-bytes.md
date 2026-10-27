# Mathematics for AI — Unit 141: Calculate model-wide KV-cache bytes

**Bits to Banking · Umicom Foundation**  
**Author:** Sammy Hegab · **Prerequisites:** Arithmetic, vectors and previous attention units

**Learning objective:** Account for K, V, layers, context and precision.

## 1. Symbols and definitions

`T` denotes admitted causal tokens; `L` denotes Transformer layers; `Hq` is the query-head count; `Hkv` is the K/V head count; `d` is a head's channel width; `B` denotes bytes. The symbols are defined here to keep the exercise independent of a particular neural model size.

## 2. Step-by-step worked calculation

Without metadata, a grouped attention model stores `B=2 × L × T × Hkv × d × bytesPerElement` bytes of K/V cache. For `L=16`, `T=2048`, `Hkv=4`, `d=64` and two bytes per scalar: `B=2×16×2048×4×64×2=33,554,432 bytes =32 MiB`.

Doubling context length doubles this capacity. Halving the number of KV heads halves it as long as the head width and numerical representation stay fixed. Actual allocations add pages, block-table entries, alignment and fragmentation.

## 3. Practice problem

**Question:** How many MiB does the same model need if context doubles to 4096?

<details>
<summary>Show the worked answer</summary>
<p><code>64 MiB</code> of raw K/V values, before metadata.</p>
</details>

## 4. Connect the arithmetic to the native course

Read [LLM Lesson 255 — Measure key/value bandwidth per decode step](../10-native-ai/255-measure-key-value-bandwidth-per-decode-step.md) to see how these values become tensor shapes, buffer capacities or experimental measurements. Keep exact formulas separate from floating-point tolerances and measured execution times.

## Continue learning

[Previous unit](140-map-grouped-query-head-indices.md) · [Next unit](142-quantise-a-float-with-a-symmetric-scale.md) · [HTML mathematics route](../../courses/maths-for-ai/efficient-decoding-mathematics.html)

*Service to Many Leads to Greatness.*
