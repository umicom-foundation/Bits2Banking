# Mathematics for AI — Unit 113: Count multi-layer Q/K/V tensor shapes

**Bits to Banking · Umicom Foundation**  
**Author:** Sammy Hegab · **Prerequisite:** Familiarity with simple arithmetic is enough.

## What will you learn?

A sequence is represented by a table with one row per token and one column per feature. Each Transformer layer stores independent key and value tables. Denote layers by L, retained tokens by T and channels by C.

## A fully worked example

Set L=3, T=4, C=8. One K tensor uses L×T×C = 3×4×8 = 96 float values. V uses another 96, so K+V contains 192 values. At four bytes per FP32 value the raw total is 768 bytes. This excludes model weights and allocator overhead.

**Helpful symbols:** `×` means multiplication, `÷` means division, `[rows, columns]` states a tensor shape, and a token row is one position in a text sequence. Each byte count and score is specific to the example, not a measured production model.

## Practise the calculation

**Question:** Calculate raw K+V bytes for L=2, T=6 and C=8.

<details>
<summary>Show the worked answer</summary>

2 × 2 × 6 × 8 × 4 = 768 bytes.

</details>

## Connect the idea to native C23

Use `UmiAiTrainingStackedKvStoreInspect` to compare the calculated raw tensor budget with Framework-reported reserved K/V bytes; not total process RAM.

The actual mathematical implementation remains in Umicom Framework. The connected [native Transformer learning path](../../courses/llm-from-scratch/incremental-attention-learning-path.html) applies this principle to a bounded real-model experiment.

## Continue learning

[Previous unit](112-design-controlled-inference-benchmarks.md) · [Next unit](114-calculate-one-query-attention-by-hand.md) · [Complete mathematics route](../../courses/maths-for-ai/incremental-attention-mathematics.html)

*Service to Many Leads to Greatness.*
