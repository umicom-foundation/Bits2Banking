# Lesson 259 — Compare IO-aware tiling with single-query streaming

**Bits to Banking · Umicom Foundation**  
**Author:** Sammy Hegab  
**Course:** Building an LLM from Scratch · **Implementation language:** C23

**Learning objective:** Distinguish arithmetic work from memory transfers at different context lengths.

## 1. Understand the concept

A conventional attention implementation may materialise an `T×T` score matrix. During prefill, this can cause substantial memory traffic and scratch allocation. **FlashAttention** studies IO-aware attention: process tiles that fit fast memory and use numerically stable accumulation to avoid storing the full attention matrix in high-bandwidth memory. It is often discussed alongside one-query decoding, but the workloads differ.

At decode time with a single newest query, the score vector has only `T` elements per head, not `T²`. A straightforward one-query CPU implementation can use a temporary vector of scores and probabilities. For longer contexts, an online normaliser can sometimes trade a different calculation order for lower scratch requirements. This is not the same as adopting an entire tiled GPU kernel.

## 2. Work through the numbers

For `T=4096`, one head and FP32 scores, a full `T×T` score matrix would hold `4096²×4 = 67,108,864` bytes, or 64 MiB, before probabilities. A one-query score vector needs `4096×4 = 16,384` bytes, or 16 KiB. The last-query calculation still reads K and V data for the admitted positions. Eliminating score storage does not eliminate these reads.

Tiling matters when the working set exceeds fast memory; small bounded educational tensors may not benefit from complex tiling.

## 3. Apply the concept to native model engineering

Compare three questions separately: How much temporary scratch is allocated? How many bytes move between memory tiers? How long does a complete inference step take? Keep model arithmetic and token-generation policy fixed. A different accumulation order can produce small numerical differences, so compare against the canonical tape within declared tolerances.

FlashAttention's published GPU results are specific to its system and evaluation. They are valuable as design evidence, not a prediction about the new native CPU kernel.

## 4. Check the mathematical foundation

The related exercise is [Mathematics for AI — Unit 146](../11-maths-for-ai/146-compare-arithmetic-intensity-with-bandwidth.md). Work out the arithmetic independently before inspecting an implementation.

## 5. Test your understanding

**Question:** For `T=1024`, how much FP32 scratch does one scalar score per token require?

<details>
<summary>Reveal the worked answer</summary>
<p><code>1024×4=4096</code> bytes = <code>4 KiB</code>. A dense 1024×1024 FP32 score matrix would need <code>4 MiB</code>.</p>
</details>

## 6. Key distinctions

The mathematical examples are deliberately small and inspectable. Changes to attention topology, positional schemes, quantisation and decoding policy require explicit model or algorithm contracts. A standalone operator test does not establish complete Transformer equivalence or measured inference acceleration.

## Continue learning

[258 — Distinguish absolute positions from rotary positions](258-distinguish-absolute-positions-from-rotary-positions.md) · [260 — Explain speculative decoding and verification](260-explain-speculative-decoding-and-verification.md) · [HTML learning path](../../courses/llm-from-scratch/efficient-decoding-learning-path.html)

*Service to Many Leads to Greatness.*
