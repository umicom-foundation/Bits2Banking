# Lesson 253 — Understand multi-query attention without rewriting a checkpoint

**Bits to Banking · Umicom Foundation**  
**Author:** Sammy Hegab  
**Course:** Building an LLM from Scratch · **Implementation language:** C23

**Learning objective:** Distinguish multi-head attention from key/value sharing.

## 1. Understand the concept

Ordinary multi-head attention (MHA) has a distinct K/V head for each query head. **Multi-query attention (MQA)** retains several query heads but shares one K head and one V head across all of them. This can reduce cache capacity and K/V memory traffic during decoding. The query heads still produce separate attention outputs; they are not merged into one query.

MQA changes the learned projection shapes and therefore the model architecture. A trained MHA checkpoint cannot simply be re-labelled MQA while preserving its original predictions. Research on converting checkpoints uses additional training or carefully specified conversion procedures.

## 2. Work through the numbers

Assume eight query heads, each of width 64, and context length 1,000. With FP16 K and V, MHA holds `2 × 1,000 × 8 × 64 × 2 = 2,048,000` bytes per layer. MQA with one KV head holds `2 × 1,000 × 1 × 64 × 2 = 256,000` bytes per layer. That is one eighth as many cached KV bytes, excluding metadata and allocator overhead. The query projection has not disappeared.

## 3. Apply the concept to native model engineering

In a C ABI, encode the number of query heads and the number of KV heads as distinct fields rather than assuming they are equal. The current Umicom stacked educational decoder uses equal-width Q/K/V matrices and one K/V head per query head; MQA is presented here as a different model architecture, not an implemented switch in the existing decoder.

The original idea is explained in Noam Shazeer's work on multi-query attention and developed further in research on grouped-query attention. Keep checkpoint compatibility distinct from cache memory estimates.

## 4. Check the mathematical foundation

The related exercise is [Mathematics for AI — Unit 141](../11-maths-for-ai/141-calculate-model-wide-kv-cache-bytes.md). Work out the arithmetic independently before inspecting an implementation.

## 5. Test your understanding

**Question:** If eight query heads share one KV head, has the number of distinct query attention distributions fallen to one?

<details>
<summary>Reveal the worked answer</summary>
<p>No. Each of the eight queries computes its own dot products and attention weights against the same shared K/V projections.</p>
</details>

## 6. Key distinctions

The mathematical examples are deliberately small and inspectable. Changes to attention topology, positional schemes, quantisation and decoding policy require explicit model or algorithm contracts. A standalone operator test does not establish complete Transformer equivalence or measured inference acceleration.

## Continue learning

[252 — Separate prefill from incremental decode](252-separate-prefill-from-incremental-decode.md) · [254 — Map grouped-query attention heads](254-map-grouped-query-attention-heads.md) · [HTML learning path](../../courses/llm-from-scratch/efficient-decoding-learning-path.html)

*Service to Many Leads to Greatness.*
