# Mathematics for AI — Unit 138: Calculate a probability-weighted value vector

**Bits to Banking · Umicom Foundation**  
**Author:** Sammy Hegab · **Prerequisites:** Arithmetic, vectors and previous attention units

**Learning objective:** Turn attention probabilities into a vector.

## 1. Symbols and definitions

`T` denotes admitted causal tokens; `L` denotes Transformer layers; `Hq` is the query-head count; `Hkv` is the K/V head count; `d` is a head's channel width; `B` denotes bytes. The symbols are defined here to keep the exercise independent of a particular neural model size.

## 2. Step-by-step worked calculation

If attention probabilities are `p=[0.25,0.75]` and value rows are `V₀=[2,6]` and `V₁=[10,−2]`, the output is `0.25×V₀ + 0.75×V₁`. The first component is `0.5+7.5=8`. The second is `1.5−1.5=0`. Thus the attended vector is `[8,0]`.

For multiple heads, calculate this operation separately within the channels belonging to each head and concatenate the outputs in the configured head order. This is not a simple average across heads.

## 3. Practice problem

**Question:** If probabilities are `[0.2,0.8]` and scalar values are `[5,15]`, what is the output?

<details>
<summary>Show the worked answer</summary>
<p><code>0.2×5+0.8×15=13</code>.</p>
</details>

## 4. Connect the arithmetic to the native course

Read [LLM Lesson 250 — Compare a kernel against the canonical last row](../10-native-ai/250-compare-a-kernel-against-the-canonical-last-row.md) to see how these values become tensor shapes, buffer capacities or experimental measurements. Keep exact formulas separate from floating-point tolerances and measured execution times.

## Continue learning

[Previous unit](137-derive-a-stable-softmax-normaliser.md) · [Next unit](139-count-prefill-and-decode-score-pairs.md) · [HTML mathematics route](../../courses/maths-for-ai/efficient-decoding-mathematics.html)

*Service to Many Leads to Greatness.*
