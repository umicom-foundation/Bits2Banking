# Lesson 254 — Map grouped-query attention heads

**Bits to Banking · Umicom Foundation**  
**Author:** Sammy Hegab  
**Course:** Building an LLM from Scratch · **Implementation language:** C23

**Learning objective:** Calculate the group ownership of each query head.

## 1. Understand the concept

**Grouped-query attention (GQA)** lies between full multi-head attention and MQA. It retains `Hq` query heads and a smaller number `Hkv` of K/V heads. When the groups are uniform, `Hq` must be divisible by `Hkv`; each K/V head serves `groupSize = Hq/Hkv` consecutive query heads.

A common mapping is `kvHead = floor(queryHead/groupSize)`. Implementations may physically interleave or arrange projection weights differently, so the mapping must be part of the model's contract, not inferred from the cache file's byte order. GQA's memory benefits arise only if the model actually has shared K/V projections.

## 2. Work through the numbers

Take `Hq=12` and `Hkv=3`. Then `groupSize=4`. Query heads 0–3 read KV head 0, heads 4–7 read KV head 1, and heads 8–11 read KV head 2. A query from head 9 therefore selects KV head `floor(9/4)=2`. A query from head 4 selects KV head 1; this boundary is a useful unit test.

For a 40-layer model, a 4,096-token cache, head width 128 and 2 bytes/element, storing four rather than 32 KV heads reduces model-wide KV data from `2×40×4096×32×128×2 ≈ 2.68 GB` to `≈0.336 GB`, before page tables and fragmentation.

## 3. Apply the concept to native model engineering

GQA must be supported by projection weights, checkpoint metadata, shape validators, causal attention code and KV storage format. An output-only reinterpretation of the existing stacked decoder would not preserve mathematical meaning.

Ainslie et al. (2023) describe uptraining multi-head checkpoints into MQA/GQA forms. Study the evidence and distinguish the authors' reported results from an independently measured Umicom implementation.

## 4. Check the mathematical foundation

The related exercise is [Mathematics for AI — Unit 140](../11-maths-for-ai/140-map-grouped-query-head-indices.md). Work out the arithmetic independently before inspecting an implementation.

## 5. Test your understanding

**Question:** With `Hq=16` and `Hkv=4`, which KV head is used by query head 11?

<details>
<summary>Reveal the worked answer</summary>
<p><code>groupSize=4</code>; <code>floor(11/4)=2</code>, so query head 11 reads KV head 2.</p>
</details>

## 6. Key distinctions

The mathematical examples are deliberately small and inspectable. Changes to attention topology, positional schemes, quantisation and decoding policy require explicit model or algorithm contracts. A standalone operator test does not establish complete Transformer equivalence or measured inference acceleration.

## Continue learning

[253 — Understand multi-query attention without rewriting a checkpoint](253-understand-multi-query-attention.md) · [255 — Measure key/value bandwidth per decode step](255-measure-key-value-bandwidth-per-decode-step.md) · [HTML learning path](../../courses/llm-from-scratch/efficient-decoding-learning-path.html)

*Service to Many Leads to Greatness.*
