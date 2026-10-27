# Mathematics for AI — Unit 145: Rotate a two-dimensional positional pair

**Bits to Banking · Umicom Foundation**  
**Author:** Sammy Hegab · **Prerequisites:** Arithmetic, vectors and previous attention units

**Learning objective:** Compute the basic rotation used to explain rotary embeddings.

## 1. Symbols and definitions

`T` denotes admitted causal tokens; `L` denotes Transformer layers; `Hq` is the query-head count; `Hkv` is the K/V head count; `d` is a head's channel width; `B` denotes bytes. The symbols are defined here to keep the exercise independent of a particular neural model size.

## 2. Step-by-step worked calculation

For vector `(x,y)`, rotation by θ gives `(x cosθ−y sinθ, x sinθ+y cosθ)`. For `(1,0)` and 90 degrees, cosθ=0 and sinθ=1, producing `(0,1)`. Rotating `(0,1)` by the same amount gives `(−1,0)`.

RoPE applies position-dependent rotations to pairs of query/key dimensions. The angle schedule and pairing convention belong to a model architecture. Rotating an existing learned-absolute-position checkpoint is not a semantics-preserving decoder optimisation.

## 3. Practice problem

**Question:** What is the rotation of `(2,0)` by 180 degrees?

<details>
<summary>Show the worked answer</summary>
<p><code>(−2,0)</code>.</p>
</details>

## 4. Connect the arithmetic to the native course

Read [LLM Lesson 258 — Distinguish absolute positions from rotary positions](../10-native-ai/258-distinguish-absolute-positions-from-rotary-positions.md) to see how these values become tensor shapes, buffer capacities or experimental measurements. Keep exact formulas separate from floating-point tolerances and measured execution times.

## Continue learning

[Previous unit](144-calculate-paged-kv-internal-fragmentation.md) · [Next unit](146-compare-arithmetic-intensity-with-bandwidth.md) · [HTML mathematics route](../../courses/maths-for-ai/efficient-decoding-mathematics.html)

*Service to Many Leads to Greatness.*
