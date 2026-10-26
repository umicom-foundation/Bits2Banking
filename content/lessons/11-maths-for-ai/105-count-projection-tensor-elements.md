# Mathematics for AI — Unit 105: Count every K/V projection element

**Bits to Banking · Umicom Foundation**  
**Author:** Sammy Hegab

## Start with the idea

No specialist mathematics qualification is required. Each numerical symbol is tied to a concrete tensor, amount or test.

A Transformer stores a sequence of numerical vectors. There are three independent counts: **L** layers, **T** token positions, and **D** channels in each projected vector. The total number of key floats is `L × T × D`. The same number is needed for values, so both require `2 × L × T × D` floats. Ordinary FP32 occupies four bytes per float.

For `L=3`, `T=5`, `D=8`: each of K and V contains 120 floats, together 240 floats and `240×4=960` raw bytes. A model parameter table, logits, tensor gradients and allocations are not included.

**Indexing:** In layer-major layout, index `(layer × T + token) × D + channel`. Each index is zero-based. At layer 2, token 3, channel 7 with T=5 and D=8, the index is `(2×5+3)×8+7=111`. This is the 112th value.

## Your turn

**Exercise:** How many raw K/V bytes are needed for L=4,T=6,D=16?

## Why this matters for a real native model

The Umicom Framework owns the actual model mathematics, K/V storage and numeric validation. The lesson calculates a small independent reference so a learner can recognise incorrect dimensions, wrong interpretation of results or numerical errors in a C23 regression. Nothing in this worked exercise claims that a production LLM has been trained or accelerated.

<details><summary>Reveal the calculation</summary>

`2×4×6×16×4=3072` bytes. This is the mathematical tensor storage, not the total process memory.

</details>

[Previous unit](104-distinguish-latency-from-workload.md) · [Next unit](106-compare-multilayer-prefix-rows.md) · [Browser version](../../courses/maths-for-ai/lessons/105-count-projection-tensor-elements.html) · [K/V mathematics reading path](projection-trace-mathematics.md).
