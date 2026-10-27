# Lesson 255 — Measure key/value bandwidth per decode step

**Bits to Banking · Umicom Foundation**  
**Author:** Sammy Hegab  
**Course:** Building an LLM from Scratch · **Implementation language:** C23

**Learning objective:** Estimate memory traffic before choosing an optimisation.

## 1. Understand the concept

A one-query attention operation has relatively little arithmetic for each value fetched from memory, particularly at long contexts. At each decode step it typically reads all relevant keys and values for every participating head, together with the new query. The resulting memory traffic may dominate the cost of a small dot product.

Separate **capacity** (bytes that remain resident in a cache) from **traffic** (bytes read or written during a measured step). A cache can be small but repeatedly accessed. Conversely a large cache may be held in faster memory. The effective bottleneck depends on whether data fits in L1/L2/L3 cache, CPU memory, GPU high-bandwidth memory or another device.

## 2. Work through the numbers

Suppose one layer has eight KV heads, width 64, context 2,048 and FP32 storage. Reading every K and V value once costs `2×8×64×2048×4 = 8,388,608` bytes, or 8 MiB. Across 24 layers it is about 192 MiB per single generated token. This excludes parameter reads, activation writes, allocator overhead and any repeated access caused by implementation details.

An illustrative sustainable bandwidth of 40 GiB/s would imply a lower bound of about `192 MiB / 40 GiB/s ≈ 4.69 ms` solely for those reads if all of them reach that bandwidth tier. Actual decoding can be slower; cache hits may make this naive bound inapplicable.

## 3. Apply the concept to native model engineering

Record achieved bytes per token, first-token prefill separately, token latency and hardware counters when accessible. A useful optimisation might reduce reads, improve locality, batch several requests or change a trained model's KV head count.

Do not claim a speedup from this arithmetic estimate. The next experiments compare the native kernel with the canonical implementation under the same model weights and actual context sizes.

## 4. Check the mathematical foundation

The related exercise is [Mathematics for AI — Unit 146](../11-maths-for-ai/146-compare-arithmetic-intensity-with-bandwidth.md). Work out the arithmetic independently before inspecting an implementation.

## 5. Test your understanding

**Question:** How many bytes do 4,096 rows of 16 KV channels need for K and V together at FP32?

<details>
<summary>Reveal the worked answer</summary>
<p><code>2 × 4096 × 16 × 4 = 524,288</code> bytes = <code>512 KiB</code>, excluding metadata.</p>
</details>

## 6. Key distinctions

The mathematical examples are deliberately small and inspectable. Changes to attention topology, positional schemes, quantisation and decoding policy require explicit model or algorithm contracts. A standalone operator test does not establish complete Transformer equivalence or measured inference acceleration.

## Continue learning

[254 — Map grouped-query attention heads](254-map-grouped-query-attention-heads.md) · [256 — Quantise KV caches with an error budget](256-quantise-kv-caches-with-an-error-budget.md) · [HTML learning path](../../courses/llm-from-scratch/efficient-decoding-learning-path.html)

*Service to Many Leads to Greatness.*
